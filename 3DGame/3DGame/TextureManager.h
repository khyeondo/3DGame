#pragma once

#include <map>
#include <SDL_image.h>

using namespace std;

class TextureManager
{
private:
	static TextureManager* s_pInstance;

	map<string, SDL_Texture*> m_textureMap;

	TextureManager() {}
public:
	~TextureManager() {}

	static TextureManager* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new TextureManager();
			return s_pInstance;
		}
		return s_pInstance;
	}

	bool load(string fileName, string id,
		SDL_Renderer* pRenderer);

	void draw(string id, int x, int y, int width, int height,
		SDL_Renderer* pRenderer,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	void drawFrame(string id, int x, int y, int width, int height,
		int currentRow, int currentFrame,
		SDL_Renderer* pRenderer,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

};
typedef class TextureManager TheTextureManager;