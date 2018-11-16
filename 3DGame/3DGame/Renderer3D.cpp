
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
	vector<reference_wrapper<Polygon>> culledPolys;
	vector<reference_wrapper<Polygon>> clipedPolys;

	WorldSpace(pGameObject3D, polys);
	BackfaceCulling(polys, culledPolys);
	ViewSpace(culledPolys, clipedPolys);
	Projection(clipedPolys);
	Viewport(clipedPolys);
	Texturing(pGameObject3D, clipedPolys);

	polys.clear();
	culledPolys.clear();
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
	Matrix4X4::MakeRotationX(rotateX, pGameObject->RefAngle().x);
	Matrix4X4::MakeRotationY(rotateY, pGameObject->RefAngle().y);
	Matrix4X4::MakeRotationZ(rotateZ, pGameObject->RefAngle().z);

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
		}
		polys.push_back(poly);
	}
}

void Renderer3D::BackfaceCulling(vector<Polygon>& polys, vector<reference_wrapper<Polygon>>& culledPolys)
{
	//시계방향 후면 추리기
	for (Polygon& poly : polys)
	{
		Vec3 line1, line2;
		line1 = poly.vertex[1] - poly.vertex[0];
		line2 = poly.vertex[2] - poly.vertex[0];

		poly.normalVec = Vec3::CrossProduct(line1, line2).Normalize();
		Vec3 cameraRay = poly.vertex[0] - m_pCamera->pos;
		if (Vec3::DotProduct(poly.normalVec, cameraRay) < 0.0f)
		{
			culledPolys.push_back(poly);
		}
	}
}

void Renderer3D::ViewSpace(vector<reference_wrapper<Polygon>>& culledPolys, vector<reference_wrapper<Polygon>>& cilpedPolys)
{
	Matrix4X4::MakeLookAtMatrix(m_matLootAt, m_pCamera->pos, m_pCamera->lookAt, Vec3(0, 1, 0));
	for (Polygon& poly : culledPolys)
	{
		poly.vertex[0] *= m_matLootAt;
		poly.vertex[1] *= m_matLootAt;
		poly.vertex[2] *= m_matLootAt;

		if (poly.vertex[0].z >= m_pCamera->near ||
			poly.vertex[1].z >= m_pCamera->near ||
			poly.vertex[2].z >= m_pCamera->near)
		{
			cilpedPolys.push_back(poly);
		}
	}
}

void Renderer3D::Projection(vector<reference_wrapper<Polygon>>& culledPolys)
{
	for (Polygon& poly : culledPolys)
	{
		poly.vertex[0] *= m_matProj;
		poly.vertex[1] *= m_matProj;
		poly.vertex[2] *= m_matProj;

		poly.vertex[0] /= poly.vertex[0].w;
		poly.vertex[1] /= poly.vertex[1].w;
		poly.vertex[2] /= poly.vertex[2].w;
	}
}

void Renderer3D::Viewport(vector<reference_wrapper<Polygon>>& culledPolys)
{
	for (Polygon& poly : culledPolys)
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

		poly.vertex[0].y *= -m_screenH / 2.f;
		poly.vertex[1].y *= -m_screenH / 2.f;
		poly.vertex[2].y *= -m_screenH / 2.f;

		poly.vertex[0].w = 1.f / poly.vertex[0].w;
		poly.vertex[1].w = 1.f / poly.vertex[1].w;
		poly.vertex[2].w = 1.f / poly.vertex[2].w;
	}
}

void Renderer3D::Texturing(GameObject3D * pGameObject, vector<reference_wrapper<Polygon>>& culledPolys)
{
	int surfaceW, surfaceH;
	if (pGameObject->GetSurface() == 0)
	{
		surfaceW = surfaceH = 1;
	}
	else 
	{
		surfaceW = pGameObject->GetSurface()->clip_rect.w;
		surfaceH = pGameObject->GetSurface()->clip_rect.h;
	}

	for (Polygon& poly : culledPolys)
	{
		Matrix4X4 normalMat;
		Vec3 origin = { 0,0,0 };
		Vec3 lookAt = poly.vertex[1] - poly.vertex[0];

		Matrix4X4::MakeLookAtMatrix(normalMat, origin, lookAt, poly.normalVec);

		//폴리곤의 정점이 화면 밖에 있으면 출력하지 않는다.		
		if (poly.vertex[0].x < 0 || poly.vertex[1].x < 0 || poly.vertex[2].x < 0 ||
			poly.vertex[0].y < 0 || poly.vertex[1].y < 0 || poly.vertex[2].y < 0 ||
			poly.vertex[0].x > m_screenW || poly.vertex[1].x > m_screenW || poly.vertex[2].x > m_screenW ||
			poly.vertex[0].y > m_screenW || poly.vertex[1].y > m_screenW || poly.vertex[2].y > m_screenW)
			continue;

		if (poly.vertex[1].y < poly.vertex[0].y)
		{
			Swap(poly.vertex[0].y, poly.vertex[1].y);
			Swap(poly.vertex[0].x, poly.vertex[1].x);
			Swap(poly.uv[0].x, poly.uv[1].x);
			Swap(poly.uv[0].y, poly.uv[1].y);
			Swap(poly.vertex[0].w, poly.vertex[1].w);
		}

		if (poly.vertex[2].y < poly.vertex[0].y)
		{
			Swap(poly.vertex[0].y, poly.vertex[2].y);
			Swap(poly.vertex[0].x, poly.vertex[2].x);
			Swap(poly.uv[0].x, poly.uv[2].x);
			Swap(poly.uv[0].y, poly.uv[2].y);
			Swap(poly.vertex[0].w, poly.vertex[2].w);
		}

		if (poly.vertex[2].y < poly.vertex[1].y)
		{
			Swap(poly.vertex[1].y, poly.vertex[2].y);
			Swap(poly.vertex[1].x, poly.vertex[2].x);
			Swap(poly.uv[1].x, poly.uv[2].x);
			Swap(poly.uv[1].y, poly.uv[2].y);
			Swap(poly.vertex[1].w, poly.vertex[2].w);
		}

		int dy1 = poly.vertex[1].y - poly.vertex[0].y;
		int dx1 = poly.vertex[1].x - poly.vertex[0].x;
		float dv1 = poly.uv[1].y - poly.uv[0].y;
		float du1 = poly.uv[1].x - poly.uv[0].x;
		float dw1 = poly.vertex[1].w - poly.vertex[0].w;

		int dy2 = poly.vertex[2].y - poly.vertex[0].y;
		int dx2 = poly.vertex[2].x - poly.vertex[0].x;
		float dv2 = poly.uv[2].y - poly.uv[0].y;
		float du2 = poly.uv[2].x - poly.uv[0].x;
		float dw2 = poly.vertex[2].w - poly.vertex[0].w;

		float tex_u, tex_v, tex_w;

		float dax_step = 0, dbx_step = 0,
			du1_step = 0, dv1_step = 0,
			du2_step = 0, dv2_step = 0,
			dw1_step = 0, dw2_step = 0;

		if (dy1) dax_step = dx1 / (float)abs(dy1);
		if (dy2) dbx_step = dx2 / (float)abs(dy2);

		if (dy1) du1_step = du1 / (float)abs(dy1);
		if (dy1) dv1_step = dv1 / (float)abs(dy1);
		if (dy1) dw1_step = dw1 / (float)abs(dy1);

		if (dy2) du2_step = du2 / (float)abs(dy2);
		if (dy2) dv2_step = dv2 / (float)abs(dy2);
		if (dy2) dw2_step = dw2 / (float)abs(dy2);

		if (dy1)
		{
			for (int i = poly.vertex[0].y; i <= poly.vertex[1].y; i++)
			{
				int ax = poly.vertex[0].x + (float)(i - poly.vertex[0].y) * dax_step;
				int bx = poly.vertex[0].x + (float)(i - poly.vertex[0].y) * dbx_step;

				float tex_su = poly.uv[0].x + (float)(i - poly.vertex[0].y) * du1_step;
				float tex_sv = poly.uv[0].y + (float)(i - poly.vertex[0].y) * dv1_step;
				float tex_sw = poly.vertex[0].w + (float)(i - poly.vertex[0].y) * dw1_step;

				float tex_eu = poly.uv[0].x + (float)(i - poly.vertex[0].y) * du2_step;
				float tex_ev = poly.uv[0].y + (float)(i - poly.vertex[0].y) * dv2_step;
				float tex_ew = poly.vertex[0].w + (float)(i - poly.vertex[0].y) * dw2_step;

				if (ax > bx)
				{
					Swap(ax, bx);
					Swap(tex_su, tex_eu);
					Swap(tex_sv, tex_ev);
					Swap(tex_sw, tex_ew);
				}

				tex_u = tex_su;
				tex_v = tex_sv;
				tex_w = tex_sw;

				float tstep = 1.0f / ((float)(bx - ax));
				float t = 0.0f;

				for (int j = ax; j < bx; j++)
				{
					if ((j < 0 || j >= m_screenW) || (i < 0 || i >= m_screenH))
					{
						t += tstep;
						continue;
					}

					tex_u = (1.0f - t) * tex_su + t * tex_eu;
					tex_v = (1.0f - t) * tex_sv + t * tex_ev;
					tex_w = (1.0f - t) * tex_sw + t * tex_ew;

					if (tex_w > m_pDepthBuffer[i * m_screenW + j])
					{
						if (pGameObject->GetSurface() == 0)
						{
							m_pScreenPixels[4 * (i * m_pScreenBuffer->w + j) + 0] = pGameObject->RefColor().b*poly.brightness;
							m_pScreenPixels[4 * (i * m_pScreenBuffer->w + j) + 1] = pGameObject->RefColor().g*poly.brightness;
							m_pScreenPixels[4 * (i * m_pScreenBuffer->w + j) + 2] = pGameObject->RefColor().r*poly.brightness;
							m_pScreenPixels[4 * (i * m_pScreenBuffer->w + j) + 3] = 255;
							m_pDepthBuffer[i*m_screenW + j] = tex_w;
							t += tstep;
							continue;
						}
						int sx = (int)((tex_u / tex_w)*surfaceW);
						int sy = (int)((tex_v / tex_w)*surfaceH);
						if (!(sx < 0 || sx >= pGameObject->GetSurface()->clip_rect.w || sy < 0 || sy >= pGameObject->GetSurface()->clip_rect.h))
						{
							float brightness = pGameObject->GetShader()->Shading(this, pGameObject->GetNormalMap(),
								poly.normalVec,&normalMat, i, j, sx, sy, 0.3f);
							pGameObject->GetPainter()->DrawPolygon(this, pGameObject->GetSurface(), &pGameObject->RefColor(),
								tex_w, i, j, sx, sy, brightness);
						}
					}
					t += tstep;
				}
			}
		}

		dy1 = poly.vertex[2].y - poly.vertex[1].y;
		dx1 = poly.vertex[2].x - poly.vertex[1].x;
		dv1 = poly.uv[2].y - poly.uv[1].y;
		du1 = poly.uv[2].x - poly.uv[1].x;
		dw1 = poly.vertex[2].w - poly.vertex[1].w;

		if (dy1) dax_step = dx1 / (float)abs(dy1);
		if (dy2) dbx_step = dx2 / (float)abs(dy2);

		du1_step = 0, dv1_step = 0;
		if (dy1) du1_step = du1 / (float)abs(dy1);
		if (dy1) dv1_step = dv1 / (float)abs(dy1);
		if (dy1) dw1_step = dw1 / (float)abs(dy1);

		if (dy1)
		{
			for (int i = poly.vertex[1].y; i <= poly.vertex[2].y; i++)
			{
				int ax = poly.vertex[1].x + (float)(i - poly.vertex[1].y) * dax_step;
				int bx = poly.vertex[0].x + (float)(i - poly.vertex[0].y) * dbx_step;

				float tex_su = poly.uv[1].x + (float)(i - poly.vertex[1].y) * du1_step;
				float tex_sv = poly.uv[1].y + (float)(i - poly.vertex[1].y) * dv1_step;
				float tex_sw = poly.vertex[1].w + (float)(i - poly.vertex[1].y) * dw1_step;

				float tex_eu = poly.uv[0].x + (float)(i - poly.vertex[0].y) * du2_step;
				float tex_ev = poly.uv[0].y + (float)(i - poly.vertex[0].y) * dv2_step;
				float tex_ew = poly.vertex[0].w + (float)(i - poly.vertex[0].y) * dw2_step;

				if (ax > bx)
				{
					Swap(ax, bx);
					Swap(tex_su, tex_eu);
					Swap(tex_sv, tex_ev);
					Swap(tex_sw, tex_ew);
				}

				tex_u = tex_su;
				tex_v = tex_sv;
				tex_w = tex_sw;

				float tstep = 1.0f / ((float)(bx - ax));
				float t = 0.0f;

				for (int j = ax; j < bx; j++)
				{
					if ((j < 0 || j >= m_screenW) || (i < 0 || i >= m_screenH)) {
						t += tstep;
						continue;
					}
					tex_u = (1.0f - t) * tex_su + t * tex_eu;
					tex_v = (1.0f - t) * tex_sv + t * tex_ev;
					tex_w = (1.0f - t) * tex_sw + t * tex_ew;

					if (tex_w > m_pDepthBuffer[i * m_screenW + j])
					{
						if (pGameObject->GetSurface() == 0)
						{
							m_pScreenPixels[4 * (i * m_pScreenBuffer->w + j) + 0] = pGameObject->RefColor().b*poly.brightness;
							m_pScreenPixels[4 * (i * m_pScreenBuffer->w + j) + 1] = pGameObject->RefColor().g*poly.brightness;
							m_pScreenPixels[4 * (i * m_pScreenBuffer->w + j) + 2] = pGameObject->RefColor().r*poly.brightness;
							m_pScreenPixels[4 * (i * m_pScreenBuffer->w + j) + 3] = 255;
							m_pDepthBuffer[i*m_screenW + j] = tex_w;
							t += tstep;
							continue;
						}
						int sx = (int)((tex_u/tex_w)*surfaceW);
						int sy = (int)((tex_v/tex_w)*surfaceH);
						if (!(sx < 0 || sx >= pGameObject->GetSurface()->clip_rect.w || sy < 0 || sy >= pGameObject->GetSurface()->clip_rect.h))
						{
							float brightness = pGameObject->GetShader()->Shading(this, pGameObject->GetNormalMap(),
								poly.normalVec, &normalMat, i, j, sx, sy, 0.3f);
							pGameObject->GetPainter()->DrawPolygon(this, pGameObject->GetSurface(), &pGameObject->RefColor(),
								tex_w, i, j, sx, sy, brightness);
						}
					}
					t += tstep;
				}
			}
		}
	}
}

Uint32 Renderer3D::GetPixel(SDL_Surface * surface, int x, int y)
{
	if (surface == NULL)
		return NULL;
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32 *)p;
		break;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}