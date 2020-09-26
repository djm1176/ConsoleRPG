#pragma once
#include <ostream>
#include <string>

struct Vector {

	/// <summary>
	/// The x, y, and z components of this Vector.
	/// </summary>
	float x, y, z;

	/// <summary>
	/// Constructs a Vector with default values of 0.
	/// </summary>
	Vector() : x{ 0.0f }, y{ 0.0f }, z{ 0.0f } {}

	/// <summary>
	/// Constructs a Vector with the same x, y, z components.
	/// </summary>
	/// <param name="xyz">The value to set each component to.</param>
	Vector(float xyz) : x{ xyz }, y{ xyz }, z{ xyz } {}

	/// <summary>
	/// Constructs a Vector with specified component values.
	/// </summary>
	/// <param name="x">The x value.</param>
	/// <param name="y">The y value.</param>
	/// <param name="z">The z value.</param>
	Vector(float x, float y, float z) : x{ x }, y{ y }, z{ z } {}

	/// <summary>
	/// Copy a Vector to another Vector.
	/// </summary>
	/// <param name="vec">The Vector to copy from.</param>
	Vector(const Vector& vec) = default;

	/// <summary>
	/// Move a (temporary) Vector to another Vector.
	/// </summary>
	/// <param name="vec">The Vector to move from.</param>
	Vector(Vector&& vec) = default;
	
	operator std::string() const { return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")"; }

	/// <summary>
	/// A Vector with all components equal to 0.
	/// </summary>
	static const Vector zero;

	/// <summary>
	/// A Vector with all components equal to 1.
	/// </summary>
	static const Vector one;

	/// <summary>
	/// A Vector with the Y component equal to 1 (pointing up).
	/// </summary>
	static const Vector up;

	/// <summary>
	/// A Vector with the X component equal to 1 (pointing right).
	/// </summary>
	static const Vector right;

	/// <summary>
	/// A Vector with the z component equal to 1 (pointing forward).
	/// </summary>
	static const Vector forward;

private:
	static const float kEpsilon; //Used by some methods as a lower bound of floats; initialization is in source Vector.cpp file

public:

	//TODO: Consider caching magnitude, square magnitude, and normalized values; then return by reference

	/// <summary>
	/// Get the magnitude, or hypotenuse, of this Vector.
	/// </summary>
	/// <returns>The magnitude of this Vector.</returns>
	const float magnitude() const;

	/// <summary>
	/// Get the square magnitude of this Vector.
	/// </summary>
	/// <remarks>This operation is faster than magnitude, as a square root calculation is not required.</remarks>
	/// <returns>The square magnitude of this Vector.</returns>
	const float sqrMagnitude() const;

	/// <summary>
	/// Get a copy of this Vector where its magnitude, or hypotenuse, is 1.
	/// </summary>
	/// <returns>A normalized copy of this Vector.</returns>
	const Vector normalized() const;

	/// <summary>
	/// Get the cross product of this Vector.
	/// </summary>
	/// <param name="a">The first Vector to compare.</param>
	/// <param name="b">The second Vector to compare.</param>
	/// <returns>The cross product of this Vector.</returns>
	static const Vector cross(const Vector& a, const Vector& b);

	/// <summary>
	/// Get the distance between two Vectors.
	/// </summary>
	/// <param name="a">The first Vector.</param>
	/// <param name="b">The second Vector.</param>
	/// <returns>The distance between vectors a and b.</returns>
	static const float distance(const Vector& a, const Vector& b);

	/// <summary>
	/// Get the dot product of two Vectors.
	/// </summary>
	/// <param name="a">The first Vector.</param>
	/// <param name="b">The second Vector.</param>
	/// <returns>The dot product of two Vectors.</returns>
	static const float dot(const Vector& a, const Vector& b);

	/// <summary>
	/// Get a linearly interpolated position between two Vectors.
	/// </summary>
	/// <param name="a">The first Vector.</param>
	/// <param name="b">The second Vector.</param>
	/// <param name="t">The time between 0.0 and 1.0 to interpolate between the two Vectors.</param>
	/// <returns>A Vector that is at position t on a line between two Vectors.</returns>
	static const Vector lerp(const Vector& a, const Vector& b, float t);

	/// <summary>
	/// Copies the value from one Vector to another.
	/// </summary>
	/// <param name="vec">The pre-existing Vector to copy from.</param>
	/// <returns>This Vector with new values.</returns>
	Vector& operator=(const Vector& vec) = default;

	/// <summary>
	/// Moves the value from one (temporary) Vector to another.
	/// </summary>
	/// <param name="vec">The pre-existing (temporary) Vector to move from.</param>
	/// <returns>This Vector with new values.</returns>
	Vector& operator=(Vector&& vec) = default;

	/// <summary>
	/// Add to this Vector component-wise.
	/// </summary>
	/// <param name="vec">The Vector to add from.</param>
	/// <returns>This Vector with new values.</returns>
	Vector& operator+=(const Vector& vec);

	/// <summary>
	/// Subtract from this Vector component-wise.
	/// </summary>
	/// <param name="vec">The Vector to subtract from.</param>
	/// <returns>This Vector with new values.</returns>
	Vector& operator-=(const Vector& vec);

	/// <summary>
	/// Multiply this Vector by a Scalar.
	/// </summary>
	/// <param name="scalar">The value to scale this Vector by.</param>
	/// <returns>This Vector with new values.</returns>
	Vector& operator*=(float scalar);

	/// <summary>
	/// Divide this Vector by a Scalar.
	/// </summary>
	/// <param name="scalar">The value to scale this Vector by.</param>
	/// <returns>This Vector with new values.</returns>
	Vector& operator/=(float scalar);

	/// <summary>
	/// Add to this Vector component-wise.
	/// </summary>
	/// <param name="vec">The Vector in which each component is added to this Vector.</param>
	/// <returns>A copy of this Vector with new values.</returns>
	const Vector operator+(const Vector& vec) const;

	/// <summary>
	/// Subtract from this Vector component-wise.
	/// </summary>
	/// <param name="vec">The Vector in which each component is subtracted from this Vector.</param>
	/// <returns>This Vector with new values.</returns>
	const Vector operator-(const Vector& vec) const;

	/// <summary>
	/// Scale this Vector by a scalar.
	/// </summary>
	/// <param name="scalar">The value to scale this Vector by.</param>
	/// <returns>This newly scaled Vector.</returns>
	const Vector operator*(float scalar) const;

	/// <summary>
	/// Scale this Vector by a scalar.
	/// </summary>
	/// <param name="scalar">The value to scale this Vector by.</param>
	/// <returns>This newly scaled Vector.</returns>
	const Vector operator/(float scalar) const;

	/// <summary>
	/// Compares this Vector with another component-wise.
	/// </summary>
	/// <param name="other">A Vector to compare with.</param>
	/// <returns>True if the two Vectors have exactly matching components.</returns>
	bool operator==(const Vector& other) const;

	/// <summary>
	/// Compares this Vector with another component-wise.
	/// </summary>
	/// <param name="other">A Vector to compare with.</param>
	/// <returns>True if the two Vectors don't have exactly matching components.</returns>
	bool operator!=(const Vector& other) const;

	/// <summary>
	/// Return the x, y, or z component of this Vector.
	/// </summary>
	/// <param name="index">An integer where 0, 1, and 2 correspond to x, y, z components, Respectively.</param>
	/// <returns>The value of the component of this Vector.</returns>
	float& operator[](int index);

};

