#ifndef UIREQUEST_HPP
#define UIREQUEST_HPP

#include "ThreadSafeQueue.hpp"
#include "UIResponse.hpp"
class UIResponse; // forward declaration

enum RequestType {
	RENDERABLE_STATE_REQUEST,
	LEFT_MOUSE_BUTTON_DOWN_REQUEST,
	LEFT_MOUSE_BUTTON_UP_REQUEST,
	RIGHT_MOUSE_BUTTON_DOWN_REQUEST,
	RIGHT_MOUSE_BUTTON_UP_REQUEST,
	MOUSE_MOVE_REQUEST,
};

class UIRequest {
public:
	RequestType type;
	ThreadSafeQueue<UIResponse*>* responseQueue;

	UIRequest(RequestType type): type(type), responseQueue(nullptr) {}
	UIRequest(RequestType type, ThreadSafeQueue<UIResponse*>* responseQueue):
		type(type), responseQueue(responseQueue) {}
	virtual ~UIRequest() = default;
};

class RenderableStateRequest : public UIRequest {
public:
	RenderableStateRequest(ThreadSafeQueue<UIResponse*>* responseQueue):
		UIRequest(RENDERABLE_STATE_REQUEST, responseQueue) {}
};

class MouseRequest : public UIRequest{
protected:
	UIPosition position;
public:
	MouseRequest(RequestType request, int x, int y) : UIRequest(request), position(x, y) {}
	MouseRequest(RequestType request, UIPosition position) : UIRequest(request), position(position) {}
	int getX() const { return position.getX(); }
	int getY() const { return position.getY(); }
	virtual ~MouseRequest() = default;
};

class LeftMouseButtonDownRequest : public MouseRequest {
public:
	LeftMouseButtonDownRequest(int x, int y):
		MouseRequest(LEFT_MOUSE_BUTTON_DOWN_REQUEST, x, y) {}
	LeftMouseButtonDownRequest(UIPosition position):
		MouseRequest(LEFT_MOUSE_BUTTON_DOWN_REQUEST, position) {}
};

class RightMouseButtonDownRequest : public MouseRequest {
public:
	RightMouseButtonDownRequest(int x, int y) :
		MouseRequest(RIGHT_MOUSE_BUTTON_DOWN_REQUEST, x, y) {}
	RightMouseButtonDownRequest(UIPosition position) :
		MouseRequest(RIGHT_MOUSE_BUTTON_DOWN_REQUEST, position) {}
};

class LeftMouseButtonUpRequest : public MouseRequest {
public:
	LeftMouseButtonUpRequest(int x, int y) :
		MouseRequest(LEFT_MOUSE_BUTTON_UP_REQUEST, x, y) {}
	LeftMouseButtonUpRequest(UIPosition position) :
		MouseRequest(LEFT_MOUSE_BUTTON_UP_REQUEST, position) {}
};

class RightMouseButtonUpRequest : public MouseRequest {
public:
	RightMouseButtonUpRequest(int x, int y) :
		MouseRequest(RIGHT_MOUSE_BUTTON_UP_REQUEST, x, y) {}
	RightMouseButtonUpRequest(UIPosition position) :
		MouseRequest(RIGHT_MOUSE_BUTTON_UP_REQUEST, position) {}
};

class MouseMoveRequest : public MouseRequest {
public:
	MouseMoveRequest(int x, int y) :
		MouseRequest(MOUSE_MOVE_REQUEST, x, y) {}
	MouseMoveRequest(UIPosition position) :
		MouseRequest(MOUSE_MOVE_REQUEST, position) {}
};

#endif // !UIREQUEST_HPP