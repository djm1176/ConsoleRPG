#pragma once
#include "Renderer.h"

//A character, such as the Player, Enemies, and NPCs
class Actor : public Renderer {
private:
public:
	//Moves this Actor by offsetting their current position with given x and y
	bool Move(int x, int y) {
		//Offset the actor's position
		this->position.x += x;
		this->position.y += y;
		return true;
	}
	virtual std::string toString() const override {
		return "Actor";
	}

	virtual void update() override {
		
	}
};