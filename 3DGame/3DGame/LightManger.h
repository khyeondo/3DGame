#pragma once

#include <vector>

class Light;

using namespace std;

class LightManager
{
private:
	LightManager() {}
	static LightManager * s_pinst;

public:
	static LightManager* Instance() {
		if (s_pinst == 0)
			s_pinst = new LightManager;
		return s_pinst;
	}

private:
	vector<Light*> m_lights;

public:
	void Destroy(Light* pLight);

public:
	friend class Light;
	friend class ColorPainter;
	friend class TexturePainter;
};