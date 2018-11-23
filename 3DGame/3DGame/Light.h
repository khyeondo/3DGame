#pragma once

#include "Vec3.h"
#include "Color.h"

class GameObject3D;

class Light
{
public:
	Light(GameObject3D* pGameObject);
	~Light();

private:
	int number;

public:
	const Vec3& pos;
	Color color;
	float brightness;

	void Delete();

};