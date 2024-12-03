#ifndef UI_POSITION_HPP
#define UI_POSITION_HPP

class UIPosition {
protected:
	int x, y;

public:
	UIPosition(int x, int y) : x(x), y(y) {};
	UIPosition(const UIPosition& p) : UIPosition(p.x, p.y) {};

	int getX() const { return x; }
	int getY() const { return y; }
};

#endif // !UI_POSITION_HPP
