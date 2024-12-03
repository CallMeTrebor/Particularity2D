#include <iostream>
#include <thread>
#include "UI.hpp"
#include "Engine.hpp"
#include "PhysicsPixel.hpp"
#include "UIRequest.hpp"
#include "Interface.hpp"
#include "Gravity.hpp"
#include "GravityWell.hpp"

using namespace std;

const string WINDOW_TITLE = "TEMP_NAME";
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;
const int FRAME_RATE = 144;

int main() {
    Engine engine(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH/20, WINDOW_HEIGHT/20);
    engine.setFixed(true);
    engine.setStepsPerSecond(FRAME_RATE);
    ThreadSafeQueue<UIRequest*> uiRequestQueue;
    ThreadSafeQueue<EngineResponse*> engineResponseQueue;
    UI ui(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT, FRAME_RATE, uiRequestQueue);

    const double GRAV_GUN_POWER = 10;
    GravityWell* mobileGrav = new GravityWell(PhysicalPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), 0);
    engine.addInfluence(mobileGrav);

    thread& uiThread = ui.startUiThread();
    thread& engineThread = engine.startEngineThread();

    bool leftMouseButtonDown = false;
    bool rightMouseButtonDown = false;
    int mouseX = -1, mouseY = -1;
    int holdStartX, holdStartY;
    double timePassed = 50.0 / FRAME_RATE;
    int deltaX, deltaY;
    PhysicsPixel* pixel = nullptr;
    PhysicsRect* rect = nullptr;
    vector<RenderableColor*> colorMap;

    for (int i = 0; i < 500; ++i) {
        //int length = 20;
        //int height = 20;
        int length = rand() % 30 + 1;
        int height = rand() % 30 + 1;
        rect = new PhysicsRect(PhysicalPosition(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT), length, height, (length + height) / 20);
		engine.makeQuery(EngineQuery{ nullptr, EngineQuery::RequestType::ADD_OBJECT, rect, false });
    }
        
    while (!ui.getQuit()) {
        // process UI requests
        while (!uiRequestQueue.empty()) {
			UIRequest* request = uiRequestQueue.pop();
            switch (request->type) {
            case RequestType::RENDERABLE_STATE_REQUEST:
				engine.makeQuery(EngineQuery{ &engineResponseQueue, EngineQuery::RequestType::GET_STATE, nullptr, false });
                break;
            case RequestType::LEFT_MOUSE_BUTTON_DOWN_REQUEST:
                holdStartX = ((MouseMoveRequest*)request)->getX();
                holdStartY = ((MouseMoveRequest*)request)->getY();
                leftMouseButtonDown = true;
				break;
            case RequestType::LEFT_MOUSE_BUTTON_UP_REQUEST:
                deltaX = ((MouseMoveRequest*)request)->getX() - holdStartX;
                deltaY = ((MouseMoveRequest*)request)->getY() - holdStartY;
                rect = new PhysicsRect(PhysicalPosition(holdStartX, holdStartY), 20, 20, 1);
                rect->setVelocity(PhysicsVector(-deltaX / timePassed, -deltaY / timePassed));
                engine.makeQuery(EngineQuery{ nullptr, EngineQuery::RequestType::ADD_OBJECT, rect, false });
				leftMouseButtonDown = false;
				break;
            case RequestType::RIGHT_MOUSE_BUTTON_DOWN_REQUEST:
                mobileGrav->setSourcePosition(PhysicalPosition(((MouseMoveRequest*)request)->getX(), ((MouseMoveRequest*)request)->getY()));
                mobileGrav->setMagnitude(GRAV_GUN_POWER);
                rightMouseButtonDown = true;
                break;
            case RequestType::RIGHT_MOUSE_BUTTON_UP_REQUEST:
                mobileGrav->setMagnitude(0);
                rightMouseButtonDown = false;
                break;
            case RequestType::MOUSE_MOVE_REQUEST:
                if (rightMouseButtonDown) {
                    mobileGrav->setSourcePosition(PhysicalPosition(((MouseMoveRequest*)request)->getX(), ((MouseMoveRequest*)request)->getY()));
                }
				break;
			}
            //std::cout << '\r' << string(30, ' ') << '\r' << leftMouseButtonDown << ' ' << rightMouseButtonDown << ' ' << mouseX << ' ' << mouseY;

            if (dynamic_cast<MouseRequest*>(request)) {
                mouseX = ((MouseMoveRequest*)request)->getX();
                mouseY = ((MouseMoveRequest*)request)->getY();
                delete (MouseRequest*)request;
            }
            else {
                delete request;
            }
		}

        // process engine responses
        while (!engineResponseQueue.empty()) {
			EngineResponse* responseQueue = engineResponseQueue.pop();
            RenderableStateResponse* uiResponse = new RenderableStateResponse(physicalStateToRenderableState(responseQueue->state));
            if(colorMap.size() <= uiResponse->getState()->objects.size()) colorMap.resize(uiResponse->getState()->objects.size(), nullptr);
            for (auto obj : uiResponse->getState()->objects) {
                if (colorMap[obj->getId()] == nullptr) {
                    colorMap[obj->getId()] = new RenderableColor{ (uint8_t)(rand() % 256), (uint8_t)(rand() % 256), (uint8_t)(rand() % 256), 255 };
                }
                obj->setColor(*colorMap[obj->getId()]);
			}
            ui.respond(uiResponse);
            delete responseQueue;
		}
    }

    // free memory
    for(auto color : colorMap) delete color;

    // shut down engine
    engine.makeQuery(EngineQuery{ nullptr, EngineQuery::RequestType::SET_QUIT, nullptr, true });

    // wait for threads to finish
    engineThread.join();
    uiThread.join();

    return 0;
}
