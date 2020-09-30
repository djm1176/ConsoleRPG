#pragma once
#include <memory>
#include "Renderer.h"

//Represents a single unit on screen, represented as a colored Unicode character
class Tile : public Renderer {
public:
	enum MoveableType { moveable, barrier, item };
private:
	MoveableType m_moveable = MoveableType::moveable;		//Default to a moveable tile

public:

	// Inherited via Object
	virtual void update() override {

	}

	std::string toString() const {
		return "Tile";
	}

	void setMoveableType(MoveableType type) {
		m_moveable = type;
	}

	MoveableType getMoveableType() const {
		return m_moveable;
	}
};
