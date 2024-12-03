#define SDL_MAIN_HANDLED
#include "UI.hpp"
#include <thread>
#include <SDL2/SDL.h>
#include <vector>
#include "RenderableObject.hpp"

void UI::SDLInit(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDL_GetError();
    }

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Quit();
        throw SDL_GetError();
    }

    // Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw SDL_GetError();
    }
}

void UI::renderLoop() {
    // init window
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDLInit(window, renderer);

    double updateRate = 1000.0 / fps;
    SDL_Event e;
    bool isRightMouseButtonDown = false;
    bool isLeftMouseButtonDown = false;
    bool needState = false;
    int mouseX = 0, mouseY = 0;
    requestCenter.push(new RenderableStateRequest(&this->responseQueue));
    while (!quit) {
        int currentFrameTime = SDL_GetTicks();
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    isRightMouseButtonDown = true;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    requestCenter.push((UIRequest*) new RightMouseButtonDownRequest(mouseX, mouseY));
                }
                else if (e.button.button == SDL_BUTTON_LEFT) {
                    isLeftMouseButtonDown = true;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    requestCenter.push((UIRequest*) new LeftMouseButtonDownRequest(mouseX, mouseY));
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (e.button.button == SDL_BUTTON_RIGHT) {
                    isRightMouseButtonDown = false;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    requestCenter.push((UIRequest*) new RightMouseButtonUpRequest(mouseX, mouseY));
                }
                else if (e.button.button == SDL_BUTTON_LEFT) {
                    isLeftMouseButtonDown = false;
                    SDL_GetMouseState(&mouseX, &mouseY);
                    requestCenter.push((UIRequest*) new LeftMouseButtonUpRequest(mouseX, mouseY));
                }
                break;
            case SDL_MOUSEMOTION:
                mouseX = e.motion.x;
                mouseY = e.motion.y;
                requestCenter.push((UIRequest*) new MouseMoveRequest(mouseX, mouseY));
                break;
            }
        }

        // get dynamicState from parent
        if (!responseQueue.empty()) {
            UIResponse* response = responseQueue.pop();
            if (dynamic_cast<RenderableStateResponse*>(response)) {
                dynamicState = *((RenderableStateResponse*)response)->getState();
            }
            else if (dynamic_cast<DrawObjectResponse*>(response)) {
				dynamicState.objects.push_back(((DrawObjectResponse*) response)->getObject());
			}

            // clear the screen
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            for (RenderableObject* obj : dynamicState.objects) {
                obj->render(renderer);
            }
            dynamicState.clear();
            delete response;
            needState = true;
        }

        // Update the screen
        SDL_RenderPresent(renderer);

        // wait for the next frame
        int frameTime = SDL_GetTicks() - currentFrameTime;
        if (frameTime < updateRate) {
			SDL_Delay(updateRate - frameTime);
            if (needState) {
                requestCenter.push(new RenderableStateRequest(&responseQueue));
                needState = false;
            }
		}
    }

    shutDownWindow(window, renderer);
}

void UI::shutDownWindow(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

std::thread& UI::startUiThread() {
    thread_local std::thread uiThread(&UI::renderLoop, this);
    return uiThread;
}

void UI::respond(UIResponse* responseQueue) {
    this->responseQueue.push(responseQueue);
}