#include "Painter.h"
#include "Renderer3D.h"

void ColorPainter::DrawPolygon(Renderer3D * pRenderer, SDL_Surface * pSurface, Color * color, float tex_w, int i, int j, int sx, int sy, float brightness)
{
	pRenderer->m_pScreenPixels[4 * (i * pRenderer->m_pScreenBuffer->w + j) + 0] = color->b;
	pRenderer->m_pScreenPixels[4 * (i * pRenderer->m_pScreenBuffer->w + j) + 1] = color->g;
	pRenderer->m_pScreenPixels[4 * (i * pRenderer->m_pScreenBuffer->w + j) + 2] = color->r;
	pRenderer->m_pScreenPixels[4 * (i * pRenderer->m_pScreenBuffer->w + j) + 3] = 255;
	pRenderer->m_pDepthBuffer[i*pRenderer->m_screenW + j] = tex_w;
}


void TexturePainter::DrawPolygon(Renderer3D* pRenderer, SDL_Surface * pSurface, Color * color,
	float tex_w,int i, int j, int sx, int sy, float brightness)
{
	Uint32 tcolor = pRenderer->GetPixel(pSurface, sx, sy);
	Uint8 a;
	if (a = (Uint8)((tcolor & 0xFF000000) >> 24) != 0)
	{
		Uint8 r = (Uint8)((tcolor & 0x000000FF));
		Uint8 b = (Uint8)((tcolor & 0x00FF0000) >> 16);
		Uint8 g = (Uint8)((tcolor & 0x0000FF00) >> 8);

		pRenderer->m_pScreenPixels[4 * (i * pRenderer->m_pScreenBuffer->w + j) + 0] = b * brightness;
		pRenderer->m_pScreenPixels[4 * (i * pRenderer->m_pScreenBuffer->w + j) + 1] = g * brightness;
		pRenderer->m_pScreenPixels[4 * (i * pRenderer->m_pScreenBuffer->w + j) + 2] = r * brightness;
		pRenderer->m_pScreenPixels[4 * (i * pRenderer->m_pScreenBuffer->w + j) + 3] = a * brightness;
		pRenderer->m_pDepthBuffer[i*pRenderer->m_screenW + j] = tex_w;
	}
}

