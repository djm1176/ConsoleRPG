#include "Vectors.h"
#include "MathUtils.h"

const Vector Vector::zero{ 0.0f };
const Vector Vector::one{ 1.0f };

const Vector Vector::up{ 0.0f, 1.0f, 0.0f };
const Vector Vector::right{ 1.0f, 0.0f, 0.0f };
const Vector Vector::forward{ 0.0f, 0.0f, 1.0f };
const float Vector::kEpsilon{ 0.00001f };

const float Vector::magnitude() const {
	return sqrt(x * x + y * y + z * z);
}

const float Vector::sqrMagnitude() const {
	return x * x + y * y + z * z;
}

const Vector Vector::normalized() const {
	float mag = magnitude();
	if (mag > kEpsilon)
		return *this / mag;
	else
		return zero;
}

const Vector Vector::cross(const Vector& a, const Vector& b) {
	return Vector(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.z - a.z * b.x);
}

const float Vector::distance(const Vector& a, const Vector& b) {
	Vector delta = b - a;
	return sqrt(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
}

const float Vector::dot(const Vector& a, const Vector& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

const Vector Vector::lerp(const Vector& a, const Vector& b, float t) {
	t = Math::clamp(0.0f, 1.0f, t);
	return Vector(
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t);
}

Vector& Vector::operator+=(const Vector& vec) {
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	return *this;
}

Vector& Vector::operator-=(const Vector& vec) {
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	return *this;
}

Vector& Vector::operator*=(float scalar) {
	this->x *= scalar;
	this->y *= scalar;
	this->z *= scalar;
	return *this;
}

Vector& Vector::operator/=(float scalar) {
	this->x /= scalar;
	this->y /= scalar;
	this->z /= scalar;
	return *this;
}

const Vector Vector::operator+(const Vector& vec) const {
	return Vector(
		this->x + vec.x,
		this->y + vec.y,
		this->z + vec.z);
}

const Vector Vector::operator-(const Vector& vec) const {
	return Vector(
		this->x - vec.x,
		this->y - vec.y,
		this->z - vec.z);
}

const Vector Vector::operator*(float scalar) const {
	return Vector(
		this->x * scalar,
		this->y * scalar,
		this->z * scalar);
}

const Vector Vector::operator/(float scalar) const {
	return Vector(
		this->x / scalar,
		this->y / scalar,
		this->z / scalar);
}

bool Vector::operator==(const Vector& other) const {
	return	this->x == other.x &&
			this->y == other.y &&
			this->z == other.z;
}

bool Vector::operator!=(const Vector& other) const {
	return !(*this == other);
}

float& Vector::operator[](int index) {
	switch (index) {
	case 0:
		return this->x;
	case 1:
		return this->y;
	case 2:
		return this->z;
	}
}
