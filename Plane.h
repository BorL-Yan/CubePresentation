#pragma once
#include "Vector3.h"
#include "Matrix.h"

class Plane : Vector3, Matrix4x4
{
public:
	Vector3 vertecs[4];

	Plane();

	Plane(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4);

	void rotate(float angle, const Vector3& axis);

};