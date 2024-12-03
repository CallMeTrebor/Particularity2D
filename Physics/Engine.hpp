#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "PhysicsObject.hpp"
#include "ThreadSafeQueue.hpp"
#include "Influence.hpp"
#include <vector>
#include <thread>
#include "Bucket.hpp"
#include "PhysicsRect.hpp"

struct PhysicalState {
	std::vector<PhysicsObject*>& objects;
};

struct EngineResponse {
	PhysicalState state;
};

struct EngineQuery {
	enum RequestType {
		ADD_OBJECT,
		REMOVE_OBJECT,
		GET_STATE,
		SET_QUIT
	};
	
	ThreadSafeQueue<EngineResponse*>* sender;
	RequestType type;
	PhysicsObject* obj;
	bool quit;
};


class Engine {
private:
	uint64_t idCounter = 0;
	std::vector<PhysicsObject*> objects;
	double stepsPerSecond = 60;
	bool fixed = false;
	ThreadSafeQueue<EngineQuery> requests;
	bool quit = false;
	std::vector<std::vector<Bucket>> buckets;
	std::vector<Influence*> influences;
	double spaceWidth, spaceHeight;
	double bucketWidth, bucketHeight;
	double collisionRetainFactor = 0.5;
	int numBucketsX, numBucketsY;
	void updateSim(double timePassed);
	void startSimulation();
	void handleCollisions();
	EngineResponse* handleRequest(EngineQuery& request);
	void createBuckets();
	void assignObjectToBuckets(PhysicsObject* obj);
public:
	~Engine();
	Engine(double spaceWidth, double spaceHeight, double bucketWidth, double bucketHeight);
	void addObject(PhysicsObject* obj);
	void removeObject(PhysicsObject* obj);
	std::vector<PhysicsObject*> getObjects() const;

	double getStepsPerSecond() const;
	void setStepsPerSecond(double stepsPerSecond);
	bool getFixed() const { return fixed; }
	bool getQuit() const { return quit; }
	void setFixed(bool fixed) { this->fixed = fixed; }
	void setQuit(bool quit) { this->quit = quit; }
	void addInfluence(Influence* influence);

	std::thread& startEngineThread();

	void makeQuery(EngineQuery request);

	PhysicalState getState();
};

#endif // !ENGINE_HPP