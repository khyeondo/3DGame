
#include "Renderer3D.h"
#include "Camera.h"
#include "GameObject3D.h"
#include "Mesh.h"
#include "Painter.h"
#include "Shader.h"

Renderer3D* Renderer3D::inst = 0;

Renderer3D::~Renderer3D()
{
	SDL_FreeSurface(m_pScreenBuffer);
	delete[] m_pDepthBuffer;
}

bool Renderer3D::Init(SDL_Renderer * pRenderer, Camera * pCamera, Vec3 light, Color background, int screenW, int screenH)
{
	m_pRenderer = pRenderer;

	m_screenW = screenW;
	m_screenH = screenH;

	m_background = background;

	m_light = light;
	light.Normalize();

	m_pCamera = pCamera;

	Matrix4X4::MakeProjectionMatrix(m_matProj, m_pCamera->fov, m_pCamera->near, 
		m_pCamera->far, m_screenW, m_screenH);
	Matrix4X4::MakeViewPortMatrix(m_matViewport, m_screenW, m_screenH);

	if ((m_pScreenBuffer = SDL_CreateRGBSurface(0, screenW, screenH, 32, 0, 0, 0, 0)) == 0)
		return false;
	m_pScreenPixels = (unsigned char*)m_pScreenBuffer->pixels;

	m_pDepthBuffer = new float[screenW*screenH];
	for (int i = 0; i < m_screenW; i++)
		for (int j = 0; j < m_screenH; j++)
		{
			m_pScreenPixels[4 * (j * m_pScreenBuffer->w + i) + 0] = m_background.b;
			m_pScreenPixels[4 * (j * m_pScreenBuffer->w + i) + 1] = m_background.g;
			m_pScreenPixels[4 * (j * m_pScreenBuffer->w + i) + 2] = m_background.r;
			m_pScreenPixels[4 * (j * m_pScreenBuffer->w + i) + 3] = 255;
			m_pDepthBuffer[j*m_screenW + i] = 0.f;
		}

	for (int i = 0; i < screenH*screenW; i++)
		m_pDepthBuffer[i] = 0;

	light.Normalize();

	return true;
}

void Renderer3D::Rendering(GameObject3D * pGameObject3D)
{
		vector<Polygon> polys;
		//vector<reference_wrapper<Polygon>> culledPolys;
		//vector<reference_wrapper<Polygon>> clipedPolys;

	Matrix4X4::MakeLookAtMatrix(m_matLootAt, m_pCamera->pos, m_pCamera->lookAt, Vec3(0, 1, 0));

	//WorldSpace(pGameObject3D, polys);
	//BackfaceCulling(polys, culledPolys);
	//ViewSpace(culledPolys, clipedPolys);
	//Projection(clipedPolys);
	//Viewport(clipedPolys);
	//Texturing(pGameObject3D, clipedPolys);
	WorldSpace(pGameObject3D, polys);

	polys.clear();
	//culledPolys.clear();

}

void Renderer3D::Present()
{
	SDL_Texture* pTexture;
	pTexture = SDL_CreateTextureFromSurface(m_pRenderer, m_pScreenBuffer);

	SDL_Rect rect;
	rect.x = rect.y = 0;
	rect.w = m_screenW;
	rect.h = m_screenH;
	SDL_RenderCopy(m_pRenderer, pTexture, &rect, &rect);
	SDL_DestroyTexture(pTexture);

	for (int i = 0; i < m_screenW; i++)
		for (int j = 0; j < m_screenH; j++)
		{
			m_pScreenPixels[4 * (j * m_pScreenBuffer->w + i) + 0] = m_background.b;
			m_pScreenPixels[4 * (j * m_pScreenBuffer->w + i) + 1] = m_background.g;
			m_pScreenPixels[4 * (j * m_pScreenBuffer->w + i) + 2] = m_background.r;
			m_pScreenPixels[4 * (j * m_pScreenBuffer->w + i) + 3] = 255;
			m_pDepthBuffer[j*m_screenW + i] = 0.f;
		}
}

void Renderer3D::WorldSpace(GameObject3D * pGameObject, vector<Polygon>& polys)
{
	Matrix4X4 scaling;
	Matrix4X4 rotateX, rotateY, rotateZ;

	Matrix4X4::MakeScalingMatrix(scaling,
		pGameObject->GetScale().x, pGameObject->GetScale().y, pGameObject->GetScale().z);
	Matrix4X4::MakeRotationX(rotateX, pGameObject->RefAngle().x + pGameObject->RefLookAtAngle().x);
	Matrix4X4::MakeRotationY(rotateY, pGameObject->RefAngle().y + pGameObject->RefLookAtAngle().y);
	Matrix4X4::MakeRotationZ(rotateZ, pGameObject->RefAngle().z + pGameObject->RefLookAtAngle().z);

	//Matrix4X4 worldMat; 
	//Matrix4X4::MatrixMultiplyMatrix(rotateZ, scaling, worldMat);
	//Matrix4X4::MatrixMultiplyMatrix(rotateX, worldMat, worldMat);
	//Matrix4X4::MatrixMultiplyMatrix(rotateY, worldMat, worldMat);

	//크기 -> 회전(z->x->y) -> 이동
	for (Polygon poly : pGameObject->GetMesh()->polys)
	{
		for (int i = 0; i < 3; i++)
		{
			poly.vertex[i] *= scaling;
			poly.vertex[i] *= rotateZ;
			poly.vertex[i] *= rotateX;
			poly.vertex[i] *= rotateY;

			//poly.vertex[i] *= worldMat;
			poly.vertex[i] += pGameObject->RefPos();

			poly.center = (poly.vertex[0] + poly.vertex[1] + poly.vertex[2]) / 3.f;
		}
		BackfaceCulling(pGameObject, poly);
	}
}

void Renderer3D::BackfaceCulling(GameObject3D* pGameObject, Polygon& poly)
{
	//시계방향 후면 추리기
	Vec3 line1, line2;
	line1 = poly.vertex[1] - poly.vertex[0];
	line2 = poly.vertex[2] - poly.vertex[0];

	poly.normalVec = Vec3::CrossProduct(line1, line2).Normalize();
	Vec3 cameraRay = poly.vertex[0] - m_pCamera->pos;
	if (Vec3::DotProduct(poly.normalVec, cameraRay) < 0.0f)
	{
		ViewSpace(pGameObject, poly);
	}

}

void Renderer3D::ViewSpace(GameObject3D * pGameObject, Polygon & poly)
{
	//Matrix4X4::MakeLookAtMatrix(m_matLootAt, m_pCamera->pos, m_pCamera->lookAt, Vec3(0, 1, 0));
	poly.vertex[0] *= m_matLootAt;
	poly.vertex[1] *= m_matLootAt;
	poly.vertex[2] *= m_matLootAt;

	if (poly.vertex[0].z >= m_pCamera->near &&
		poly.vertex[1].z >= m_pCamera->near &&
		poly.vertex[2].z >= m_pCamera->near &&
		poly.vertex[0].z <= m_pCamera->far &&
		poly.vertex[1].z <= m_pCamera->far &&
		poly.vertex[2].z <= m_pCamera->far)
	{
		Projection(pGameObject, poly);
	}
}

void Renderer3D::Projection(GameObject3D * pGameObject, Polygon & poly)
{

	poly.vertex[0] *= m_matProj;
	poly.vertex[1] *= m_matProj;
	poly.vertex[2] *= m_matProj;

	poly.vertex[0] /= poly.vertex[0].w;
	poly.vertex[1] /= poly.vertex[1].w;
	poly.vertex[2] /= poly.vertex[2].w;

	Viewport(pGameObject, poly);
}

void Renderer3D::Viewport(GameObject3D * pGameObject, Polygon & poly)
{
	Vec3 temp = { 2.f,-1.f,0.f };
	poly.vertex[0] += temp;
	poly.vertex[1] += temp;
	poly.vertex[2] += temp;

	poly.uv[0] /= poly.vertex[0].w;
	poly.uv[1] /= poly.vertex[1].w;
	poly.uv[2] /= poly.vertex[2].w;

	poly.vertex[0].x *= m_screenW / 4.f;
	poly.vertex[1].x *= m_screenW / 4.f;
	poly.vertex[2].x *= m_screenW / 4.f;

	poly.vertex[0].y *= -m_screenH / 2.3f;
	poly.vertex[1].y *= -m_screenH / 2.3f;
	poly.vertex[2].y *= -m_screenH / 2.3f;

	poly.vertex[0].w = 1.f / poly.vertex[0].w;
	poly.vertex[1].w = 1.f / poly.vertex[1].w;
	poly.vertex[2].w = 1.f / poly.vertex[2].w;

	Texturing(pGameObject, poly);
}

void Renderer3D::Texturing(GameObject3D * pGameObject, Polygon & poly)
{
	if (!(poly.vertex[0].x < -300 || poly.vertex[1].x <-300 || poly.vertex[2].x < -300 ||
		poly.vertex[0].y < -300 || poly.vertex[1].y <-300 || poly.vertex[2].y < -300 ||
		poly.vertex[0].x > m_screenW + 300 || poly.vertex[1].x > m_screenW + 300 || poly.vertex[2].x > m_screenW + 300 ||
		poly.vertex[0].y > m_screenW + 300 || poly.vertex[1].y > m_screenW + 300 || poly.vertex[2].y > m_screenW + 300))
		pGameObject->GetPainter()->DrawPolygon(pGameObject, poly);
}

Uint32 Renderer3D::GetPixel(SDL_Surface * surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;

	return *(Uint32 *)p;
	//switch (bpp) {
	//case 1:
	//	return *p;
	//	break;
	//
	//case 2:
	//	return *(Uint16 *)p;
	//	break;
	//
	//case 3:
	//	if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
	//		return p[0] << 16 | p[1] << 8 | p[2];
	//	else
	//		return p[0] | p[1] << 8 | p[2] << 16;
	//	break;
	//
	//case 4:
	//	return *(Uint32 *)p;
	//	break;
	//
	//default:
	//	return 0;       /* shouldn't happen, but avoids warnings */
	//}
}
