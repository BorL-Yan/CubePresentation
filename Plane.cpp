#include "pch.h"
#include "Plane.h"

Plane::Plane() {
	
}

Plane::Plane(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4) {
	vertecs[0] = v1;
	vertecs[1] = v2;
	vertecs[2] = v3;
	vertecs[3] = v4;
}

void Plane :: rotate(float angle, const Vector3& axis) {
	Matrix4x4 rotMatrix = rotMatrix.rotation(angle, axis);
	for (int i = 0; i < 4; ++i) {
		vertecs[i] = rotMatrix.multiply(vertecs[i]);
	}
}
