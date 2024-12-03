#ifndef UIRESPONSE_HPP
#define UIRESPONSE_HPP

#include "UI.hpp"
#include "RenderableObject.hpp"
class RenderableState;

class UIResponse { 
public:
	virtual ~UIResponse() {}
};

class RenderableStateResponse : public UIResponse {
	RenderableState* state;
public:
	~RenderableStateResponse() { delete state; }
	RenderableStateResponse(RenderableState* state): state(state){}
	RenderableState* getState() { return state; }
};

class DrawObjectResponse : public UIResponse {
	RenderableObject* object;

public:
	DrawObjectResponse(RenderableObject* object) : object(object) {}
	~DrawObjectResponse() { delete object; }
	RenderableObject* getObject() { return object; }
};

#endif // !UIRESPONSE_HPP