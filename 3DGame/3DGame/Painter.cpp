#include "Painter.h"
#include "Renderer3D.h"
#include "GameObject3D.h"
#include <functional>
#include "LightManger.h"

void ColorPainter::DrawPolygon(GameObject3D * pGameObject,Polygon& poly)
{
	int screenW = Renderer3D::Instance()->m_screenW;
	int screenH = Renderer3D::Instance()->m_screenH;
	SDL_Surface* pScreenBuffer = Renderer3D::Instance()->m_pScreenBuffer;
	
	unsigned char* pScreenPixels = Renderer3D::Instance()->m_pScreenPixels;
	float* pDepthBuffer = Renderer3D::Instance()->m_pDepthBuffer;
	//
	Color color = pGameObject->RefColor();
	Vec3 brightness = { 0,0,0 };
	for(Light* light : LightManager::Instance()->m_lights)
		pGameObject->GetShader()->Shading(brightness,NULL, poly.normalVec, NULL, 0, 0, 0, 0,  poly.center, light);
	color *= brightness;

	if (poly.vertex[1].y < poly.vertex[0].y)
	{
		Swap(poly.vertex[0].y, poly.vertex[1].y);
		Swap(poly.vertex[0].x, poly.vertex[1].x);
		Swap(poly.vertex[0].w, poly.vertex[1].w);
	}
	
	if (poly.vertex[2].y < poly.vertex[0].y)
	{
		Swap(poly.vertex[0].y, poly.vertex[2].y);
		Swap(poly.vertex[0].x, poly.vertex[2].x);
		Swap(poly.vertex[0].w, poly.vertex[2].w);
	}
	
	if (poly.vertex[2].y < poly.vertex[1].y)
	{
		Swap(poly.vertex[1].y, poly.vertex[2].y);
		Swap(poly.vertex[1].x, poly.vertex[2].x);
		Swap(poly.vertex[1].w, poly.vertex[2].w);
	}
	
	int dy1 = poly.vertex[1].y - poly.vertex[0].y;
	int dx1 = poly.vertex[1].x - poly.vertex[0].x;
	float dw1 = poly.vertex[1].w - poly.vertex[0].w;
	
	int dy2 = poly.vertex[2].y - poly.vertex[0].y;
	int dx2 = poly.vertex[2].x - poly.vertex[0].x;
	float dw2 = poly.vertex[2].w - poly.vertex[0].w;
	
	float tex_w;
	
	float dax_step = 0, dbx_step = 0,
	dw1_step = 0, dw2_step = 0;
	
	if (dy1) {
		dax_step = dx1 / (float)abs(dy1);
		dw1_step = dw1 / (float)abs(dy1);
	}
	
	
	if (dy2) {
		dbx_step = dx2 / (float)abs(dy2);
		dw2_step = dw2 / (float)abs(dy2);
	}
	
	if (dy1)
	{
		for (int i = poly.vertex[0].y; i <= poly.vertex[1].y; i++)
		{
			int ax = poly.vertex[0].x + (float)(i - poly.vertex[0].y) * dax_step;
			int bx = poly.vertex[0].x + (float)(i - poly.vertex[0].y) * dbx_step;
	
			float tex_sw = poly.vertex[0].w + (float)(i - poly.vertex[0].y) * dw1_step;
	
			float tex_ew = poly.vertex[0].w + (float)(i - poly.vertex[0].y) * dw2_step;
	
			if (ax > bx)
			{
				Swap(ax, bx);
				Swap(tex_sw, tex_ew);
			}
			float smallest = (poly.vertex[0].x > poly.vertex[1].x ? poly.vertex[1].x : poly.vertex[0].x);
			smallest = (smallest > poly.vertex[2].x ? poly.vertex[2].x : smallest);
			if (ax < smallest)
				ax = smallest;
			float biggest = (poly.vertex[0].x < poly.vertex[1].x ? poly.vertex[1].x : poly.vertex[0].x);
			biggest = (biggest < poly.vertex[2].x ? poly.vertex[2].x : biggest);
			if (bx > biggest)
				bx = biggest;

			tex_w = tex_sw;
	
			float tstep = 1.0f / ((float)(bx - ax));
			float t = 0.0f;
	
			for (int j = ax; j < bx; j++)
			{
				if ((j < 0 || j >= screenW) || (i < 0 || i >= screenH))
				{
					t += tstep;
					continue;
				}
				tex_w = (1.0f - t) * tex_sw + t * tex_ew;
	
				if (tex_w > pDepthBuffer[i * screenW + j])
				{
					////
					//pGameObject->GetPainter()->DrawPolygon(this, pGameObject->GetSurface(), &pGameObject->RefColor(),
					//	tex_w, i, j, sx, sy, brightness);
	
					pScreenPixels[4 * (i * pScreenBuffer->w + j) + 0] = color.b;
					pScreenPixels[4 * (i * pScreenBuffer->w + j) + 1] = color.g;
					pScreenPixels[4 * (i * pScreenBuffer->w + j) + 2] = color.r;
					pScreenPixels[4 * (i * pScreenBuffer->w + j) + 3] = 255;
					pDepthBuffer[i* screenW + j] = tex_w;
					////
				}
				t += tstep;
			}
		}
	}
	
	dy1 = poly.vertex[2].y - poly.vertex[1].y;
	dx1 = poly.vertex[2].x - poly.vertex[1].x;
	dw1 = poly.vertex[2].w - poly.vertex[1].w;
	
	if (dy1) {
		dax_step = dx1 / (float)abs(dy1);
		dw1_step = dw1 / (float)abs(dy1);
	}
	
	if (dy2) dbx_step = dx2 / (float)abs(dy2);
	
	if (dy1)
	{
		for (int i = poly.vertex[1].y; i <= poly.vertex[2].y; i++)
		{
			int ax = poly.vertex[1].x + (float)(i - poly.vertex[1].y) * dax_step;
			int bx = poly.vertex[0].x + (float)(i - poly.vertex[0].y) * dbx_step;
	
			float tex_sw = poly.vertex[1].w + (float)(i - poly.vertex[1].y) * dw1_step;
	
			float tex_ew = poly.vertex[0].w + (float)(i - poly.vertex[0].y) * dw2_step;
	
			if (ax > bx)
			{
				Swap(ax, bx);
				Swap(tex_sw, tex_ew);
			}
	
			tex_w = tex_sw;
	
			float tstep = 1.0f / ((float)(bx - ax));
			float t = 0.0f;
			
			float smallest = (poly.vertex[0].x > poly.vertex[1].x ? poly.vertex[1].x : poly.vertex[0].x);
			smallest = (smallest > poly.vertex[2].x ? poly.vertex[2].x : smallest);
			if (ax < smallest)
				ax = smallest;
			float biggest = (poly.vertex[0].x < poly.vertex[1].x ? poly.vertex[1].x : poly.vertex[0].x);
			biggest = (biggest < poly.vertex[2].x ? poly.vertex[2].x : biggest);
			if (bx > biggest)
				bx = biggest;

			for (int j = ax; j < bx; j++)
			{
				if ((j < 0 || j >= screenW) || (i < 0 || i >= screenH)) {
					t += tstep;
					continue;
				}
				tex_w = (1.0f - t) * tex_sw + t * tex_ew;
	
				if (tex_w > pDepthBuffer[i * screenW + j])
				{
					pScreenPixels[4 * (i * pScreenBuffer->w + j) + 0] = color.b;
					pScreenPixels[4 * (i * pScreenBuffer->w + j) + 1] = color.g;
					pScreenPixels[4 * (i * pScreenBuffer->w + j) + 2] = color.r;
					pScreenPixels[4 * (i * pScreenBuffer->w + j) + 3] = 255;
					pDepthBuffer[i* screenW + j] = tex_w;
				}
				t += tstep;
			}
		}
	}
}

void TexturePainter::DrawPolygon(GameObject3D * pGameObject, Polygon& poly)
{
	Matrix4X4 normalMat;
	Vec3 origin = { 0,0,0 };
	Vec3 lookAt = poly.vertex[1] - poly.vertex[0];

	Renderer3D* pRenderer3D = Renderer3D::Instance();

	int screenW = pRenderer3D->m_screenW;
	int screenH = pRenderer3D->m_screenH;
	SDL_Surface* pScreenBuffer = pRenderer3D->m_pScreenBuffer;

	SDL_Surface* pObjectSurface = pGameObject->GetSurface();
	SDL_Surface* pNormalMap = pGameObject->GetNormalMap();

	unsigned char* pScreenPixels = pRenderer3D->m_pScreenPixels;
	float* pDepthBuffer			 = pRenderer3D->m_pDepthBuffer;

	Vec3 brightness = { 0,0,0 };
	for (Light* light : LightManager::Instance()->m_lights)
		pGameObject->GetShader()->Shading(brightness, NULL, poly.normalVec, NULL, 0, 0, 0, 0, poly.center, light);
	

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

	if (dy1) {
		dax_step = dx1 / (float)abs(dy1);
		du1_step = du1 / (float)abs(dy1);
		dv1_step = dv1 / (float)abs(dy1);
		dw1_step = dw1 / (float)abs(dy1);
	}

	if (dy2) {
		dbx_step = dx2 / (float)abs(dy2);
		du2_step = du2 / (float)abs(dy2);
		dv2_step = dv2 / (float)abs(dy2);
		dw2_step = dw2 / (float)abs(dy2);
	}

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
				if ((j < 0 || j >= screenW) || (i < 0 || i >= screenH))
				{
					t += tstep;
					continue;
				}

				tex_u = (1.0f - t) * tex_su + t * tex_eu;
				tex_v = (1.0f - t) * tex_sv + t * tex_ev;
				tex_w = (1.0f - t) * tex_sw + t * tex_ew;

				if (tex_w > pDepthBuffer[i * screenW + j])
				{
					int sx = (int)((tex_u / tex_w)*pObjectSurface->w);
					int sy = (int)((tex_v / tex_w)*pObjectSurface->h);
					if (!(sx < 0 || sx >= pObjectSurface->clip_rect.w || sy < 0 || sy >= pObjectSurface->clip_rect.h))
					{
						if (pNormalMap != 0) {
							//brightness = pGameObject->GetShader()->Shading(pNormalMap,
							//	poly.normalVec, &normalMat, i, j, sx, sy, 0.3f, poly.center);
						}
						////
						//pGameObject->GetPainter()->DrawPolygon(this, pGameObject->GetSurface(), &pGameObject->RefColor(),
						//	tex_w, i, j, sx, sy, brightness);
						Uint32 tcolor = pRenderer3D->GetPixel(pObjectSurface, sx, sy);
						Uint8 a;
						if (a = (Uint8)((tcolor & 0xFF000000) >> 24) != 0)
						{
							Uint8 r = (Uint8)((tcolor & 0x000000FF));
							Uint8 b = (Uint8)((tcolor & 0x00FF0000) >> 16);
							Uint8 g = (Uint8)((tcolor & 0x0000FF00) >> 8);

							pScreenPixels[4 * (i * pScreenBuffer->w + j) + 0] = b * brightness.z;
							pScreenPixels[4 * (i * pScreenBuffer->w + j) + 1] = g * brightness.y;
							pScreenPixels[4 * (i * pScreenBuffer->w + j) + 2] = r * brightness.x;
							pScreenPixels[4 * (i * pScreenBuffer->w + j) + 3] = a;
							pDepthBuffer[i* screenW + j] = tex_w;
						}
						////
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
				if ((j < 0 || j >= screenW) || (i < 0 || i >= screenH)) {
					t += tstep;
					continue;
				}
				tex_u = (1.0f - t) * tex_su + t * tex_eu;
				tex_v = (1.0f - t) * tex_sv + t * tex_ev;
				tex_w = (1.0f - t) * tex_sw + t * tex_ew;

				if (tex_w > pDepthBuffer[i * screenW + j])
				{
					int sx = (int)((tex_u / tex_w)*pObjectSurface->w);
					int sy = (int)((tex_v / tex_w)*pObjectSurface->h);
					if (!(sx < 0 || sx >= pObjectSurface->clip_rect.w || sy < 0 || sy >= pObjectSurface->clip_rect.h))
					{
						if (pNormalMap != 0) {
							//brightness = pGameObject->GetShader()->Shading(pNormalMap,
							//	poly.normalVec, &normalMat, i, j, sx, sy, 0.3f, poly.center);
						}
						////
						//pGameObject->GetPainter()->DrawPolygon(this, pGameObject->GetSurface(), &pGameObject->RefColor(),
						//	tex_w, i, j, sx, sy, brightness);
						Uint32 tcolor = pRenderer3D->GetPixel(pObjectSurface, sx, sy);
						Uint8 a;
						if (a = (Uint8)((tcolor & 0xFF000000) >> 24) != 0)
						{
							Uint8 r = (Uint8)((tcolor & 0x000000FF));
							Uint8 b = (Uint8)((tcolor & 0x00FF0000) >> 16);
							Uint8 g = (Uint8)((tcolor & 0x0000FF00) >> 8);

							pScreenPixels[4 * (i * pScreenBuffer->w + j) + 0] = b * brightness.z;
							pScreenPixels[4 * (i * pScreenBuffer->w + j) + 1] = g * brightness.y;
							pScreenPixels[4 * (i * pScreenBuffer->w + j) + 2] = r * brightness.x;
							pScreenPixels[4 * (i * pScreenBuffer->w + j) + 3] = a;
							pDepthBuffer[i* screenW + j] = tex_w;
						}
						////
					}
				}
				t += tstep;
			}
		}
	}

}

