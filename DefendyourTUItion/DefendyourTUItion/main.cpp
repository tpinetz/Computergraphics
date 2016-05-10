#include "Game.h"

int main() {
	Game::Game* game = new Game::Game(1024, 768);
	
	
	if (!game->init()) {
		std::cerr << "Failed to init Game.";
		return -1;
	}
	
	game->run();

	delete game;
	return 0;
}