#pragma once

#include "GameObject.h"
#include "Vectors.h"
#include <iostream>

class Transform : public Component {
public:
	Transform() : m_Position{ Vector{} }, m_Scale{ Vector::one }, m_Rotation{ 0.0f } {}

	Vector position() { if (m_Parent == nullptr) return m_Position; else return m_Position + m_Parent->m_Position; }
	Vector& localPosition() { return m_Position; }
	Vector& scale() { return m_Scale; }
	float& rotation() { return m_Rotation; }

	const Transform* parent() { return m_Parent; }
	void setParent(Transform& newParent);
	
	/*
	Vector up();
	Vector forward();
	Vector right();
	*/

private:
	Vector m_Position;
	Vector m_Scale;
	float m_Rotation;
	
	Transform* m_Parent;
};
