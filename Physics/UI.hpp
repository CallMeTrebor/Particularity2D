#ifndef UI_HPP
#define UI_HPP

#include <thread>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <vector>
#include "ThreadSafeQueue.hpp"
#include "RenderableObject.hpp"
#include "RenderableState.hpp"
#include "UIResponse.hpp"
#include "UIRequest.hpp"

class UI {
	const std::string WINDOW_TITLE;
	int centerX, centerY;
	int width;
	int height;
	int fps;
	bool quit = false;
	RenderableState dynamicState;
	ThreadSafeQueue<UIResponse*> responseQueue;
	ThreadSafeQueue<UIRequest*>& requestCenter;

public:
	void SDLInit(SDL_Window*& window, SDL_Renderer*& renderer);
	void renderLoop();
	void shutDownWindow(SDL_Window* window, SDL_Renderer* renderer);
	bool getQuit() const { return quit; }

public:
	UI(ThreadSafeQueue<UIRequest*>& requestQueue) :
		UI("Window Name", 980, 1720, 144, requestQueue) {};
	UI(const std::string WINDOW_TITLE, const int width, const int height, const int frameRate, ThreadSafeQueue<UIRequest*>& requestQueue):
		WINDOW_TITLE(WINDOW_TITLE), width(width), height(height),
		fps(frameRate), requestCenter(requestQueue), centerX(width/2), centerY(height/2) {}
	std::thread& startUiThread();
	void respond(UIResponse* response);
};

#endif // !UI_HPP