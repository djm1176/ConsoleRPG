#pragma once
#include "Vectors.h"
#include <vector>
#include <iostream>


class Object {
public:
	Object(Vector _position = Vector::zero);

	virtual void update() = 0;
	
	bool isActive() const;
	void destroy();


	Vector position;

private:
	bool m_active = true;
	bool m_alive = true;
	
};