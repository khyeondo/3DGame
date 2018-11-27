#include "Button.h"
#include "InputHandler.h"

void Button::Render()
{
	GameObject2D::Render();
}

void Button::Update()
{
	Vec2* pMousePos = TheInputHandler::Instance()->getMousePosition();
	if (pMousePos->x < (m_pos.x + m_size.x)
		&& pMousePos->x > m_pos.x
		&& pMousePos->y < (m_pos.y + m_size.y)
		&& pMousePos->y > m_pos.y)
	{
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased) {
			m_currentFrame = CLICKED;
			m_callback(); // call our callback function
			m_bReleased = false;
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT)) {
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else {
		m_currentFrame = MOUSE_OUT;
	}
}

void Button::Clean()
{
	GameObject2D::Clean();
}
