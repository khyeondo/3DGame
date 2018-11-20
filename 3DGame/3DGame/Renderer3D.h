#pragma once

#include "Matrix4X4.h"
#include "Vec3.h"
#include "Polygon.h"
#include "Color.h"
#include "Painter.h"
#include "Shader.h"
#include <SDL.h>
#include <vector>

using namespace std;

class SDL_Surface;
class SDL_Renderer;
class Camera;
class GameObject3D;
class GameObejct2D;

class Renderer3D
{
#pragma region Singleton
private:
	static Renderer3D* inst;
public:
	static Renderer3D* Instance() {
		if (inst == 0)
			inst = new Renderer3D;
		return inst;
	}
	static Renderer3D* DeleteInstance() {
		if (inst != 0) {
			delete inst;
			inst = 0;
		}
	}
#pragma endregion

private:
	SDL_Renderer * m_pRenderer;
	SDL_Surface * m_pScreenBuffer = 0;
	unsigned char* m_pScreenPixels = 0;
	float* m_pDepthBuffer = 0;
	Camera* m_pCamera = 0;

	int m_screenW;
	int m_screenH;

	//원근투영 행렬
	Matrix4X4 m_matProj;
	//카메라 좌표계 행렬
	Matrix4X4 m_matLootAt;
	//뷰포트 행렬
	Matrix4X4 m_matViewport;

	Vec3 m_light;
	Color m_background;

public:
	ColorPainter m_colorPainter;
	TexturePainter m_texturePainter;
	FlatShader m_flatShader;
	PixelShader m_plxelShader;

public:
	~Renderer3D();

	bool Init(SDL_Renderer* pRenderer, Camera* pCamera, Vec3 light,Color background, int screenW, int screenH);
	void Rendering(GameObject3D* pGameObject3D);
	
	void Present();

	Camera* GetCamera() {
		return m_pCamera;
	}
	Vec3& RefLight() {
		return m_light;
	}

private:
	void WorldSpace(GameObject3D* pGameObject,vector<Polygon>& polys);
	void BackfaceCulling(vector<Polygon>& polys, vector<reference_wrapper<Polygon>>& culledPolys);
	void ViewSpace(vector<reference_wrapper<Polygon>>& culledPolys, vector<reference_wrapper<Polygon>>& cilpedPolys);
	void Projection(vector<reference_wrapper<Polygon>>& polys);
	void Viewport(vector<reference_wrapper<Polygon>>& polys);
	void Texturing(GameObject3D* pGameObject, vector<reference_wrapper<Polygon>>& polys);

private:
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

	Uint32 GetPixel(SDL_Surface *surface, int x, int y);

public:
	friend class TexturePainter;
	friend class ColorPainter;
	friend class FlatShader;
	friend class PixelShader;
};