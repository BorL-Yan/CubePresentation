#include "pch.h"
#include "Cube.h"
//#include "Vector3.h"
#define Pi 3.14

Cube::Cube() {
	
}

void Cube::operator()(Vector3 center, Vector3 localRotation, int size) {
	Center = center;
	CubeSize = size;
	AxisX = Vector3(1, 0, 0);
	AxisY = Vector3(0, 1, 0);
	AxisZ = Vector3(0, 0, 1);
	for (int j = 0; j < 6; j++)
	{
		Vector3 Vertecs[4]{
			{-1,-1,1},
			{ 1,-1,1},
			{ 1, 1,1},
			{-1, 1,1}
		};
		for (int k = 0; k < 4; k++) {
			//index :: 0 - Up, 1 - Down, 2 - Left, 3 - Front, 4 - Right, 5 - Back
				switch (j)
				{
				case 0:
					Rotation(Vertecs[k], Vector3(90, 0, 0));
					break;

				case 1:
					Rotation(Vertecs[k], Vector3(-90, 0, 0));
					break;

				case 2:
					Rotation(Vertecs[k], Vector3(0, -90, 0));
					break;

				case 3:
					Rotation(Vertecs[k], Vector3(0, 0, 0));
					break;
				case 4:
					Rotation(Vertecs[k], Vector3(0, 90, 0));
					break;

				case 5:
					Rotation(Vertecs[k], Vector3(0, 180, 0));
					break;
				}
			this->faces[j].vertecs[k] = Vertecs[k];
		}
	}
}

void Cube::Sort() {
	for (int i = 0; i < 5; i++) {
		for (int j = i + 1; j < 6; j++)
		{
			if (zBufer[i] > zBufer[j]) {

				std::swap(zBufer[i], zBufer[j]);
				std::swap(faces[i], faces[j]);
			}
		}
	}
}

void Cube::GetFace(Vector2* point, int index)
{
	for (int i = 0; i < 4; i++)
	{
		int distance = 5;
		
		auto vertecs = faces[index].vertecs[i];
		
		float z = 1 / (distance - vertecs.z);
		
		Vector3(vertecs.x * z, vertecs.y * z, vertecs.z);
		
		point[i].x = static_cast<int>(vertecs.x * CubeSize) + Center.x;
		point[i].y = static_cast<int>(vertecs.y * CubeSize) + Center.y;
	}
}

void Cube::RotationX(Vector3& rotating, float angle) const {
	rotating = Vector3(rotating.x,
		rotating.y * (float)cos(angle * Pi / 180.0f) - rotating.z * (float)sin(angle * Pi / 180.0f),
		rotating.z * (float)cos(angle * Pi / 180.0f) + rotating.y * (float)sin(angle * Pi / 180.0f));

}

void Cube::RotationY(Vector3& rotating, float angle) const {
	rotating = Vector3(rotating.x * (float)cos(angle * Pi / 180.0f) + rotating.z * (float)sin(angle * Pi / 180.0f),
		rotating.y,
		rotating.z * (float)cos(angle * Pi / 180.0f) - rotating.x * (float)sin(angle * Pi / 180.0f));
}

void Cube::RotationZ(Vector3& rotating, float angle) const {
	rotating = Vector3(rotating.x * (float)cos(angle * Pi / 180.0f) - rotating.y * (float)sin(angle * Pi / 180.0f),
		rotating.y * (float)cos(angle * Pi / 180.0f) + rotating.x * (float)sin(angle * Pi / 180.0f),
		rotating.z);
}

void Cube:: Rotation(Vector3& rotation, Vector3 axis) const {
	RotationX(rotation, axis.x);
	RotationY(rotation, axis.y);
	RotationZ(rotation, axis.z);
}

