#include "Object.h"


Object::Object(Vector _position) : position{ _position } {}

bool Object::isActive() const {
	return m_active;
}

void Object::destroy() {
	m_alive = false; m_active = false;
}

void Object::update() {

}
