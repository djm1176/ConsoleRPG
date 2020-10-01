#include <iostream>
#include <string>
#include "olcConsoleGameEngine.h"
#include "Game.h"
#include "Debug.h"
#include "MapTools.h"

const int GAME_WIDTH = 80;
const int GAME_HEIGHT = 24;


// Inherited via olcConsoleGameEngine
bool Game::OnUserCreate() {

	//Initialize managers
	inputManager = new InputManager(this);
	screenManager = new ScreenManager(40, 20, this);

	//Test perlin map
	MapBuilder::generatePerlinTiles(0, 0, screenManager->getWidth(), screenManager->getHeight(), screenManager->tiles());

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
