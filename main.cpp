#include <iostream>
#include <vector>
#include <SDL.h>
#include "game.h"



int main(int argc, char** argv) {
	Game *game = new Game();
	game->init();
	game->initImages();
	game->initObjects();
	//Hero* player = new Swordsman(32,32,4,4,2,16);

	while (game->running()) {
		game->update();
	}

	delete game;

	system("pause");
	return 0;
}