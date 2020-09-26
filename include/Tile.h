#pragma once
#include <memory>
#include "olcConsoleGameEngine.h"
#include "Renderer.h"

//Represents a single unit on screen, represented as a colored Unicode character
class Tile : public Renderer {
	enum MoveableType {Moveable, Barrier, Item};
private:
	MoveableType m_moveable = MoveableType::Moveable;		//Default to a moveable tile

public:

	// Inherited via Object
	virtual void update() override {

	}

	std::string toString() const {
		return "Tile";
	}
};
