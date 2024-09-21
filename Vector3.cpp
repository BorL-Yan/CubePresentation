#include "pch.h"
#include "Vector3.h"


Vector3::Vector3() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(float X, float Y , float Z) :x(X), y(Y), z(Z) {};

Vector3 Vector3:: operator+(const Vector3& v) const {
	return { x + v.x, y + v.y, z + v.z };
}

Vector3 Vector3:: operator-(const Vector3& v) const {
	return { x - v.x, y - v.y, z - v.z };
}

Vector3 Vector3:: operator*(float scalar) const {
	return { x * scalar, y * scalar, z * scalar };
}