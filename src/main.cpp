#include <iostream>

#include "GameEngine.h"

int main() {

	GameEngine game;

	while (game.isOpen()) {

		game.Update();

		game.Render();

	}


	return 0;

}