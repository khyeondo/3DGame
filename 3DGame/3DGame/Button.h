#pragma once

#include "GameObject2D.h"

class LoaderParams;

enum button_state
{
	MOUSE_OUT = 0,
	MOUSE_OVER = 1,
	CLICKED = 2
};

class Button : public GameObject2D
{
public:
	Button(Vec2 pos, Vec2 size, std::string textureID, void(*callback)()) :
		GameObject2D(pos, size, textureID), m_callback(callback) {}
	~Button() {
		GameObject2D::~GameObject2D();
	}
	virtual void Render();
	virtual void Update();
	virtual void Clean();

private:
	void(*m_callback)();

	bool m_bReleased;
};
