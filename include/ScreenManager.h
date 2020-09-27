#pragma once

#include "Object.h"
#include "Tile.h"
#include "Player.h"

class Game;

//Manages all Objects in the game
class ScreenManager {
private:
	int m_width, m_height;
	Game* const m_context;	//Reference to the Game context for accessing things
	std::vector<Tile> m_Tiles;
	Player m_Player;

public:

	//Initializes the ObjectManager so that objects can be created, etc.
	ScreenManager(int, int, Game*);

	Tile& operator[] (int);

	Tile& at(int);

	void update();


};