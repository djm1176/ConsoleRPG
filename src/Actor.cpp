#include "Actor.h"
#include "Game.h"

Actor::Actor(Game* context) : m_context{ context } {}

//Moves this Actor by offsetting their current position with given x and y
bool Actor::Move(int x, int y) {
	//Ensure the player can move to this tile
	//TODO: This should be a generic collision detection
	int _x = this->position.x + x;
	int _y = this->position.y + y;

	if (_x < 0 || _y < 0 ||
		_x >= m_context->screenManager->getWidth() ||
		_y >= m_context->screenManager->getHeight()) return false;

	if (m_context->screenManager->at(_x, _y)
		.getMoveableType() == Tile::barrier) return false;

	//Offset the actor's position
	this->position.x = _x;
	this->position.y = _y;
	return true;
}

void Actor::update() {

}