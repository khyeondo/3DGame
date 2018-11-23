#include "Shader.h"
#include"Renderer3D.h"
#include "Camera.h"
#include "Light.h"

void FlatShader::Shading(Vec3& brightness,SDL_Surface * pSurface,
	Vec3 & normalVec, Matrix4X4* plookAtMat, 
	int i, int j, int sx, int sy,Vec3 center, Light* light)
{
	Vec3 lightDir = center - light->pos;
	float dist = lightDir.Length();

	if (dist > light->brightness*500.f)
	{
		return;
	}

	lightDir.Normalize();
	float intensity = Vec3::DotProduct(lightDir, normalVec);
	intensity *= -1;
	intensity = (((intensity) > (0)) ? (intensity) : (0));
	intensity /= (dist/(30.f*light->brightness));
	intensity = (((intensity) < (1)) ? (intensity) : (1));

	brightness.x += light->color.r/255.f * intensity;
	brightness.y += light->color.g/255.f * intensity;
	brightness.z += light->color.b/255.f * intensity;
}

void PixelShader::Shading(Vec3& brightness,SDL_Surface * pSurface,
	Vec3 & normalVec, Matrix4X4* plookAtMat, 
	int i, int j, int sx, int sy, Vec3 center, Light* light)
{
	//Uint32 normalMapColor = Renderer3D::Instance()->GetPixel(pSurface, sx, sy);
	//Vec3 normalMapVec = { (float)((normalMapColor & 0x000000FF)),
	//	(float)((normalMapColor & 0x0000FF00) >> 8),
	//	(float)((normalMapColor & 0x00FF0000) >> 16) };
	//normalMapVec *= (2.f / 255.f); 
	//normalMapVec -= 1;
	//normalMapVec.Normalize();
	//normalMapVec *= *plookAtMat;
	//Vec3 light = center - Renderer3D::Instance()->GetCamera()->pos;
	//float dist = light.Length();
	//light = light.Normalize() * (*plookAtMat);
	//float brightness = Vec3::DotProduct(light, normalMapVec);
	//brightness /= (dist / 50.f);
	////brightness *= -1;
	//brightness = (((brightness) > (minBrightness)) ? (brightness) : (minBrightness));
	//brightness = (((brightness) < (1)) ? (brightness) : (1));
	//return brightness;
}