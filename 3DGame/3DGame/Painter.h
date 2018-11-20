#pragma once

#include <vector>
#include "Polygon.h"

using namespace std;

class Renderer3D;
class SDL_Surface;
class Color;
class GameObject3D;

class Painter
{
public:
	virtual ~Painter() {}
	virtual void DrawPolygon(GameObject3D * pGameObject, Polygon& poly) = 0;

protected:
	void Swap(int& a, int& b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	void Swap(float& a, float& b)
	{
		float temp = a;
		a = b;
		b = temp;
	}
};

class ColorPainter : public Painter
{
public:
	friend class Renderer3D;
	virtual void DrawPolygon(GameObject3D * pGameObject, Polygon& poly);
};

class TexturePainter : public Painter
{
public:
	friend class Renderer3D;
	virtual void DrawPolygon(GameObject3D * pGameObject, Polygon& poly);
};
