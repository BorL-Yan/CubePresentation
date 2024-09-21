#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include "Plane.h"


class Cube : public Vector3, Plane, Vector2
{
public:
	Plane faces[4];

	Vector3 Center;
	Vector3 AxisX;
	Vector3 AxisY;
	Vector3 AxisZ;

	Cube();

	float zBufer[6];

	int CubeSize;

	void operator()(Vector3 center, Vector3 localRotation, int size);

	void Sort();

	void GetFace(Vector2* point, int index);

	void RotationX(Vector3& rotating, float angle) const;

	void RotationY(Vector3& rotating, float angle) const;

	void RotationZ(Vector3& rotating, float angle) const;

	void Rotation(Vector3& rotation, Vector3 axis) const;
	

};
