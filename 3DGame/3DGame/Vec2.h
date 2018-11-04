#pragma once

struct Vec2
{
public:
	float x, y;

public:
	Vec2() {}
	Vec2(float x, float y) {
		this->x = x; this->y = y;
	}

	void operator /= (float f)
	{
		x /= f;
		y /= f;
	}
};
