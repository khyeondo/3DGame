#pragma once

struct Vec3;
class Camera;
class Renderer3D;
struct SDL_Surface;
class Matrix4X4;
class Light;

class Shader
{
protected:
	const float minBrightness = 0.3f;
public:
	virtual ~Shader() {}
	virtual void Shading(Vec3& brightness,SDL_Surface * pSurface,
		Vec3& normalVec,Matrix4X4* plookAtMat,
		int i, int j, int sx, int sy,
		Vec3 center,Light* light) = 0;
};
class FlatShader : public Shader
{
public:
	virtual void Shading(Vec3& brightness,SDL_Surface * pSurface,
		Vec3& normalVec, Matrix4X4* plookAtMat, 
		int i, int j, int sx, int sy, 
		Vec3 center, Light* light);
};
class PixelShader : public Shader
{
public:
	virtual void Shading(Vec3& brightness,SDL_Surface * pSurface,
		Vec3& normalVec, Matrix4X4* plookAtMat, 
		int i, int j, int sx, int sy, 
		Vec3 center, Light* light);
};