#pragma once

#include <SDL.h>

struct Color
{
public:
	Color() {}
	Color(Uint8 r, Uint8 g, Uint8 b) {
		this->r = r; this->g = g; this->b = b;
	}
public:
	Uint8 r, g, b;

	void operator *= (Vec3 vec)
	{
		int r = this->r;
		int g = this->g;
		int b = this->b;
		r *= vec.x;
		g *= vec.y;
		b *= vec.z;
		if (r > 255) r = 255;
		if (g > 255) g = 255;
		if (b > 255) b = 255;
		this->r = (Uint8)r;
		this->g = (Uint8)g;
		this->b = (Uint8)b;
	}

	void operator * (float a)
	{
		r *= (Uint8)a;
		g *= (Uint8)a;
		b *= (Uint8)a;
	}
	void operator + (int i)
	{
		r += i;
		g += i;
		b += i;
	}
};
