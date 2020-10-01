#pragma once

#include "Object.h"
#include "Tile.h"
#include "Player.h"
#include "Input.h"

class Game;
class UIManager;

//Manages all Objects in the game
class ScreenManager {
	class InputToggleMenu : public InputActionBase {
	public:
		// Inherited via InputActionBase
		virtual int funct(std::string) override;
		//Reference to base class
		ScreenManager* m_Manager;
		InputToggleMenu(Game*, ScreenManager*);
	};

private:
	Game* const m_context;	//Reference to the Game context for accessing things
	UIManager* m_UIManager;

	int m_width, m_height;
	std::vector<Tile> m_Tiles;
	Player m_Player;

	InputToggleMenu* m_toggleUIInput;

public:

	//Initializes the ScreenManager so that objects can be created, etc.
	ScreenManager(int, int, Game*);

	Tile& operator[] (int);

	Tile& at(int index);

	Tile& at(int x, int y);

	std::vector<Tile> tiles();

	int getWidth() const;
	int getHeight() const;

	void update();

	Player* getPlayer();

	~ScreenManager();
};