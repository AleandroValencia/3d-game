#include "Game.h"

int main(int argc, char* args[])
{
	Game::Instance().Initialise();
	Game::Instance().MainLoop();
	Game::Instance().ShutDown();

	return 0;
}
