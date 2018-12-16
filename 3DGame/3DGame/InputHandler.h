#pragma once

#include <SDL.h>
#include <vector>

class Vec2;

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
	~InputHandler() {}
	static InputHandler* Instance()
	{
		if (s_pInstance == 0) {
			s_pInstance = new InputHandler();
		}
		return s_pInstance;
	}

	void update();
	void clean();  // 디바이스 관련 초기화된 부분을 clear 

				   //bool isKeyDown(SDL_Scancode key);

	bool isKeyUp(SDL_Scancode key);
	bool isKeyDown(SDL_Scancode key);
	bool isKeyHolding(SDL_Scancode key);

	bool getMouseButtonState(int buttonNumber);
	Vec2* getMousePosition();

private:
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);

	void onKeyUp(SDL_Event& event);
	void onKeyDown(SDL_Event& event);

private:
	InputHandler();

	static InputHandler* s_pInstance;

	const Uint8* m_keystates;

	bool m_isKeyUp[513] = { false };
	bool m_isKeyDown[513] = { false };
	bool m_isKeyHolding[513] = { false };

	int m_keyDownCheck;
	int m_keyUpCheck;

	// mouse buttion events								
	std::vector<bool> m_mouseButtonStates;

	// mouse motion event					
	Vec2* m_mousePosition;



};


typedef InputHandler TheInputHandler;