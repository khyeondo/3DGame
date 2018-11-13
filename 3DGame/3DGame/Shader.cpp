#include "Shader.h"
#include"Renderer3D.h"
#include "Camera.h"
float FlatShader::Shading(Renderer3D * pRenderer, SDL_Surface * pSurface, 
	Vec3 & normalVec, Matrix4X4* plookAtMat, int i, int j, int sx, int sy, float minBrightness)
{
	float brightness = Vec3::DotProduct(pRenderer->m_light, normalVec);
	brightness *= -1;
	brightness = (((brightness) > (minBrightness)) ? (brightness) : (minBrightness));
	return brightness;
}

float PixelShader::Shading(Renderer3D * pRenderer, SDL_Surface * pSurface, 
	Vec3 & normalVec, Matrix4X4* plookAtMat, int i, int j, int sx, int sy, float minBrightness)
{
	Uint32 normalMapColor = pRenderer->GetPixel(pSurface, sx, sy);
	Vec3 normalMapVec = { (float)((normalMapColor & 0x000000FF)),
		(float)((normalMapColor & 0x0000FF00) >> 8),
		(float)((normalMapColor & 0x00FF0000) >> 16) };
	normalMapVec *= (2.f / 255.f);
	normalMapVec -= 1;
	normalMapVec.Normalize();
	normalMapVec *= *plookAtMat;
	Vec3 light = pRenderer->m_light * (*plookAtMat);
	float brightness = Vec3::DotProduct(light, normalMapVec);
	//brightness *= -1;
	brightness = (((brightness) > (minBrightness)) ? (brightness) : (minBrightness));
	return brightness;
}