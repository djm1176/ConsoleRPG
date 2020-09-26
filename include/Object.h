#pragma once
#include "olcConsoleGameEngine.h"
#include "Vectors.h"
#include <vector>
#include <iostream>


class Object {
public:
	Object(Vector _position = Vector::zero) : position{_position} {}

	virtual void update() = 0;
	virtual std::string toString() const = 0; 
	
	bool isActive() const { return m_active; }
	void destroy() { m_alive = false; m_active = false; }


	Vector position;

private:
	bool m_active = true;
	bool m_alive = true;
	
};

void Object::update() {

}
