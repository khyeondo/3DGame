#pragma once

struct Vec3;
class Camera;
class Renderer3D;
struct SDL_Surface;
class Matrix4X4;

class Shader
{
public:
	virtual ~Shader() {}
	virtual float Shading(SDL_Surface * pSurface,
		Vec3& normalVec,Matrix4X4* plookAtMat,int i, int j, int sx, int sy, float minBrightness,Vec3 center) = 0;
};
class FlatShader : public Shader
{
public:
	virtual float Shading(SDL_Surface * pSurface,
		Vec3& normalVec, Matrix4X4* plookAtMat, int i, int j, int sx, int sy, float minBrightness, Vec3 center);
};
class PixelShader : public Shader
{
public:
	virtual float Shading(SDL_Surface * pSurface,
		Vec3& normalVec, Matrix4X4* plookAtMat, int i, int j, int sx, int sy, float minBrightness, Vec3 center);
};