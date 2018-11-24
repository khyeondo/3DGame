#include "Game.h"
#include "DeltaTime.h"

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//const int FPS = 10;
	//const int DELAY_TIME = 1000.0f / FPS;

	Game::Instance()->init("3DGame", 100, 100, 800, 600, true);
	Game::Instance()->start();

	Uint32 frameStart, frameTime;
	while (Game::Instance()->running())
	{
		frameStart = SDL_GetTicks();
		DeltaTime::Instance()->SetDeltaTime();
		Game::Instance()->handleEvents();
		Game::Instance()->update();
		Game::Instance()->render();

		//frameTime = SDL_GetTicks() - frameStart;
		//
		//if (frameTime < DELAY_TIME)
		//{
		//	SDL_Delay((int)(DELAY_TIME - frameTime));
		//}
	}
	
	Game::Instance()->clean();
	Game::Instance()->DeleteSingle();
	
	return 0;
}