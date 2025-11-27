#include "core/Game.h"

int main() 
{
	Game game;

	game.run_game_loop();

	game.shut_down();

	return 0;
}