#pragma once
#include "Renderer.h"

class Game;

//A character, such as the Player, Enemies, and NPCs
class Actor : public Renderer {
protected:
	Game* m_context;

public:
	Actor(Game* context);

	//Moves this Actor by offsetting their current position with given x and y
	bool Move(int x, int y);

	virtual void update() override;
};