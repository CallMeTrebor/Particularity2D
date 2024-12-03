

class MouseButtonRequest {
protected:
	UIPosition position;
public:
	MouseButtonRequest(int x, int y) : position(x, y) {}
	MouseButtonRequest(UIPosition position) : position(position) {}
	int getX() const { return position.getX(); }
	int getY() const { return position.getY(); }
};

class LeftMouseButtonDownRequest : public MouseButtonRequest, UIRequest {
public:
	LeftMouseButtonDownRequest(int x, int y) :
		UIRequest(LEFT_MOUSE_BUTTON_DOWN_REQUEST), MouseButtonRequest(x, y) {}
	LeftMouseButtonDownRequest(UIPosition position) :
		UIRequest(LEFT_MOUSE_BUTTON_DOWN_REQUEST), MouseButtonRequest(position) {}
};

class RightMouseButtonDownRequest : public MouseButtonRequest, UIRequest {
public:
	RightMouseButtonDownRequest(int x, int y) :
		UIRequest(RIGHT_MOUSE_BUTTON_DOWN_REQUEST), MouseButtonRequest(x, y) {}
	RightMouseButtonDownRequest(UIPosition position) :
		UIRequest(RIGHT_MOUSE_BUTTON_DOWN_REQUEST), MouseButtonRequest(position) {}
};