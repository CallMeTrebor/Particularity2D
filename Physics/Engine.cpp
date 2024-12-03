#include "Engine.hpp"
#include "PhysicsObject.hpp"
#include <thread>
#include "PhysicsRect.hpp"
#include "Collision.hpp"
#include <limits>
#include "Influence.hpp"

Engine::Engine(double spaceWidth, double spaceHeight, double bucketWidth, double bucketHeight) {
	this->spaceWidth = spaceWidth;
	this->spaceHeight = spaceHeight;
	this->bucketWidth = bucketWidth;
	this->bucketHeight = bucketHeight;

	createBuckets();
}

Engine::~Engine() {
	for (PhysicsObject* obj : objects) {
		delete obj;
	}

	for(Influence* inf : influences) {
		delete inf;
	}
}

void Engine::addObject(PhysicsObject* obj) {
	obj->setId(idCounter++);
	objects.push_back(obj);
}

void Engine::removeObject(PhysicsObject* obj) {
	(void)std::remove(objects.begin(), objects.end(), obj);
}

std::vector<PhysicsObject*> Engine::getObjects() const {
	return objects;
}

double Engine::getStepsPerSecond() const {
	return stepsPerSecond;
}

void Engine::setStepsPerSecond(double stepsPerSecond) {
	this->stepsPerSecond = stepsPerSecond;
}

void Engine::updateSim(double timePassed) {
	handleCollisions();
	/*for (int i = 0; i < objects.size(); ++i) {
		for (int j = i + 1 ; j < objects.size(); ++j) {
			Collision::handleCollision(objects[i], objects[j]);
		}
	}*/

	// move objects
	for (PhysicsObject* obj : objects) {
		obj->applyVelocity(timePassed, 0, 0, spaceWidth, spaceHeight);
	}

	for (PhysicsObject* obj : objects) {
		for(Influence* inf : influences) {
			inf->enactInfluence(*obj);
		}

		// rebucket objects
		assignObjectToBuckets(obj);
	}
}

EngineResponse* Engine::handleRequest(EngineQuery& request) {
	switch (request.type){
	case EngineQuery::ADD_OBJECT:
		addObject(request.obj);
		break;

	case EngineQuery::REMOVE_OBJECT:
		removeObject(request.obj);
		break;

	case EngineQuery::GET_STATE:
		return new EngineResponse{ getState() };
		break;
	case EngineQuery::SET_QUIT:
		setQuit(request.quit);
		break;
	default:
		break;
	}

	return nullptr;
}

void Engine::createBuckets() {
	this->bucketWidth = bucketWidth;
	this->bucketHeight = bucketHeight;
	numBucketsX = static_cast<int>(std::ceil(spaceWidth / bucketWidth));
	numBucketsY = static_cast<int>(std::ceil(spaceHeight / bucketHeight));

	buckets.resize(numBucketsX, std::vector<Bucket>(numBucketsY));

	for (int i = 0; i < numBucketsX; ++i) {
		for (int j = 0; j < numBucketsY; ++j) {
			PhysicalPosition leftTop = { i * bucketWidth, j * bucketHeight };
			PhysicalPosition rightBottom = { (i + 1) * bucketWidth, (j + 1) * bucketHeight };
			buckets[i][j] = Bucket(leftTop, { leftTop.getX(), rightBottom.getY()}, rightBottom, {rightBottom.getX(), leftTop.getY()});

			if (i > 0) buckets[i][j].setLeft(&buckets[i - 1][j]);
			if (j > 0) buckets[i][j].setTop(&buckets[i][j - 1]);
			if (i < numBucketsX - 1) buckets[i][j].setRight(&buckets[i + 1][j]);
			if (j < numBucketsY - 1) buckets[i][j].setBottom(&buckets[i][j + 1]);
		}
	}

	for (auto& obj : objects) {
		assignObjectToBuckets(obj);
	}
}

void Engine::assignObjectToBuckets(PhysicsObject* obj) {
	for (auto& row : buckets) {
		for (auto& bucket : row) {
			bucket.removeObject(obj);
		}
	}

	PhysicalPosition objPos = obj->getPos();
	double objLeft, objRight, objTop, objBottom;

	if (auto* rect = dynamic_cast<PhysicsRect*>(obj)) {
		auto bbox = rect->getBoundingBox();
		objLeft = bbox.first.getX();
		objRight = bbox.second.getX();
		objTop = bbox.first.getY();
		objBottom = bbox.second.getY();
	}
	else if (auto* pixel = dynamic_cast<PhysicsPixel*>(obj)) {
		objLeft = objRight = objPos.getX();
		objTop = objBottom = objPos.getY();
	}
	else if (auto* point = dynamic_cast<Point*>(obj)) {
		objLeft = objRight = objPos.getX();
		objTop = objBottom = objPos.getY();
	}
	else {
		throw std::runtime_error("Trying to add unsupported obj type to buckets");
	}

	int startX = static_cast<int>(std::floor(objLeft / bucketWidth));
	int endX = static_cast<int>(std::floor(objRight / bucketWidth));
	int startY = static_cast<int>(std::floor(objTop / bucketHeight));
	int endY = static_cast<int>(std::floor(objBottom / bucketHeight));

	for (int i = startX; i <= endX; ++i) {
		for (int j = startY; j <= endY; ++j) {
			if (i >= 0 && i < numBucketsX && j >= 0 && j < numBucketsY) {
				buckets[i][j].addObject(obj);
			}
		}
	}
}

//#include <iostream>
void Engine::startSimulation() {
	auto lastTime = std::chrono::system_clock::now();
	double deltaTime = 0.0;
	const double fixedDeltaTime = 1.0 / stepsPerSecond;

	while (!quit) {
		auto currentTime = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsedTime = currentTime - lastTime;
		lastTime = currentTime;

		deltaTime += elapsedTime.count();
		//std::cout << 1.0 / elapsedTime.count() << std::endl;

		while (deltaTime >= fixedDeltaTime) {
			updateSim(fixedDeltaTime);
			while (!requests.empty()) {
				EngineQuery request = requests.pop();
				EngineResponse* responseQueue = handleRequest(request);
				if (responseQueue != nullptr && request.sender != nullptr) {
					request.sender->push(handleRequest(request));
				}
			}

			deltaTime -= fixedDeltaTime;
		}
	}
}

void Engine::handleCollisions(){
	for (int i = 0; i < numBucketsX; ++i) {
		for (int j = 0; j < numBucketsY; ++j) {
			auto& bucket = buckets[i][j];
			auto& objects = bucket.getObjects();

			// check in bucket
			for (size_t k = 0; k < objects.size(); ++k) {
				for (size_t l = k + 1; l < objects.size(); ++l) {
					Collision::handleCollision(objects[k], objects[l]);
				}
			}

			// check in neighbouring buckets
			if (bucket.getRight()) {
				auto& rightObjects = bucket.getRight()->getObjects();
				for (auto obj : objects) {
					for (auto rightObj : rightObjects) {
						Collision::handleCollision(obj, rightObj);
					}
				}
			}

			if (bucket.getBottom()) {
				auto& bottomObjects = bucket.getBottom()->getObjects();
				for (auto obj : objects) {
					for (auto bottomObj : bottomObjects) {
						Collision::handleCollision(obj, bottomObj);
					}
				}
			}

			if (bucket.getTop()) {
				auto& topObjects = bucket.getTop()->getObjects();
				for (auto obj : objects) {
					for (auto topObj : topObjects) {
						Collision::handleCollision(obj, topObj);
					}
				}
			}

			if (bucket.getLeft()) {
				auto& bottomObject = bucket.getLeft()->getObjects();
				for(auto obj : objects) {
					for (auto bottomObj : bottomObject) {
						Collision::handleCollision(obj, bottomObj);
					}
				}
			}
		}
	}
}

void Engine::makeQuery(EngineQuery request) {
	requests.push(request);
}

PhysicalState Engine::getState() {
	PhysicalState state{ objects };
	return state;
}

std::thread& Engine::startEngineThread() {
	thread_local std::thread engineThread(&Engine::startSimulation, this);
	return engineThread;
}

void Engine::addInfluence(Influence* inf) {
	influences.push_back(inf);
}