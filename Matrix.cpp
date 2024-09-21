#include "pch.h"
#include "Matrix.h"


Matrix4x4::Matrix4x4() {
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			m[i][j] = (i == j) ? 1.0f : 0.0f;
}

Vector3 Matrix4x4::multiply(const Vector3& v) const {
	return {
		m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
		m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
		m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
	};
}



Matrix4x4 Matrix4x4::rotation(float angle, const Vector3& axis) {
	Matrix4x4 rot;
	float cosTheta = cos(angle);
	float sinTheta = sin(angle);
	float oneMinusCos = 1.0f - cosTheta;

	rot.m[0][0] = cosTheta + axis.x * axis.x * oneMinusCos;
	rot.m[0][1] = axis.x * axis.y * oneMinusCos - axis.z * sinTheta;
	rot.m[0][2] = axis.x * axis.z * oneMinusCos + axis.y * sinTheta;

	rot.m[1][0] = axis.y * axis.x * oneMinusCos + axis.z * sinTheta;
	rot.m[1][1] = cosTheta + axis.y * axis.y * oneMinusCos;
	rot.m[1][2] = axis.y * axis.z * oneMinusCos - axis.x * sinTheta;

	rot.m[2][0] = axis.z * axis.x * oneMinusCos - axis.y * sinTheta;
	rot.m[2][1] = axis.z * axis.y * oneMinusCos + axis.x * sinTheta;
	rot.m[2][2] = cosTheta + axis.z * axis.z * oneMinusCos;

	return rot;
}