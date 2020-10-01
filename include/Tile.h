#pragma once
#include <memory>
#include "Renderer.h"

//Represents a single unit on screen, represented as a colored Unicode character
class Tile : public Renderer {
public:
	enum MoveableType { moveable, barrier, item };
private:
	std::string m_name;
	MoveableType m_moveable = MoveableType::moveable;		//Default to a moveable tile

public:
	Tile() = default;
	Tile(std::string name, MoveableType type, wchar_t _char, short color)
		: Renderer{ _char, color }, m_name{ name }, m_moveable{ type } {}

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
