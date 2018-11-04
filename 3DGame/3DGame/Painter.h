#pragma once
class Renderer3D;
class SDL_Surface;
class Color;


class Painter
{
public:
	virtual ~Painter() {}
	virtual void DrawPolygon(Renderer3D* pRenderer, SDL_Surface* pSurface, Color* color, float tex_w, int i, int j, int sx, int sy, float brightness) = 0;
};
class ColorPainter : public Painter
{
public:
	virtual void DrawPolygon(Renderer3D* pRenderer, SDL_Surface* pSurface, Color* color, float tex_w, int i, int j, int sx, int sy, float brightness);
};
class TexturePainter : public Painter
{
public:
	virtual void DrawPolygon(Renderer3D* pRenderer, SDL_Surface* pSurface, Color* color, float tex_w, int i, int j, int sx, int sy, float brightness);
};
