#pragma once
class Vector3 {
public:
	float x, y, z;
	Vector3();

	Vector3(float X, float Y, float Z);

	Vector3 operator+(const Vector3& v) const;

	Vector3 operator-(const Vector3& v) const;

	Vector3 operator*(float scalar) const;

};

