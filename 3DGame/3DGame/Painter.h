#pragma once

#include <vector>
#include "Polygon.h"

using namespace std;

class Renderer3D;
struct SDL_Surface;
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
		a ^= b ^= a ^= b;
	}
	void Swap(float& a, float& b)
	{
		a = a + b;
		b = a - b;
		a = a - b;
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