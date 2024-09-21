#pragma once
#include "Vector3.h"
//class struct Vector2 {
//	float x, y;
//	Vector2(int x = 0, int y = 0) :x(x), y(y) {};
//};


class Matrix4x4 : Vector3 {
public:
	float m[4][4];

	Matrix4x4();

	Vector3 multiply(const Vector3& v) const;

	static Matrix4x4 rotation(float angle, const Vector3& axis);
};

