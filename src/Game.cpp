#include <iostream>
#include <string>
#include "olcConsoleGameEngine.h"
#include "Game.h"
#include "Debug.h"

const int GAME_WIDTH = 80;
const int GAME_HEIGHT = 24;


// Inherited via olcConsoleGameEngine
bool Game::OnUserCreate() {

	//Initialize managers
	inputManager = new InputManager(this);
	screenManager = new ScreenManager(40, 20, this);

	//Randomize the tiles
	for (int y = 0; y < screenManager->getHeight(); y++) {
		for (int x = 0; x < screenManager->getWidth(); x++) {
			if (rand() % 5 != 1) {
				screenManager->at(x, y).setchar(L' ');
			} else {
				screenManager->at(x, y).setchar(L'#');
				screenManager->at(x, y).setMoveableType(Tile::barrier);
			}

		}
	}

	//Debugging and testing


	return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {
	//Update the ScreenManager
	screenManager->update();
	inputManager->processInput();

	return true;
}

bool Game::OnUserDestroy() {
	delete inputManager;
	return true;
}


int main() {

	Game g;
	g.ConstructConsole(GAME_WIDTH, GAME_HEIGHT, 10, 20);
	g.Start();

	return 0;
}
