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
	sceneManager = new ScreenManager(40, 20, this);
	uiManager = new UIManager(this);

	//Randomize the tiles
	for (int y = 0; y < sceneManager->getHeight(); y++) {
		for (int x = 0; x < sceneManager->getWidth(); x++) {
			if (rand() % 2 == 1) {
				sceneManager->at(x, y).setchar(L' ');
			} else {
				sceneManager->at(x, y).setchar(L'#');
				sceneManager->at(x, y).setMoveableType(Tile::barrier);
			}

		}
	}

	//Demo UI Testing

	Panel _panel = Panel(Vector{ GAME_WIDTH - 36, GAME_HEIGHT - 4, 0 }, Vector{ 35, 3, 0 });
	_panel.setBorder(true);
	RadioButton btn = RadioButton("Option 1", Vector{GAME_WIDTH - 35, GAME_HEIGHT - 3, 0});
	RadioButton btn2 = RadioButton("Option 2", Vector{ GAME_WIDTH - 35, GAME_HEIGHT - 2, 0 });
	uiManager->insert(_panel);
	uiManager->insert(btn);
	uiManager->insert(btn2);

	return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {
	//Update the ScreenManager
	sceneManager->update();
	inputManager->processInput();
	uiManager->update();


	return true;
}

bool Game::OnUserDestroy() {
	delete sceneManager;
	delete inputManager;
	return true;
}


int main() {

	Game g;
	g.ConstructConsole(GAME_WIDTH, GAME_HEIGHT, 10, 20);
	g.Start();

	return 0;
}
