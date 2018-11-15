
#include "GameObject3D.h"

class Cube : public GameObject3D
{
public:
	Cube(SDL_Surface* surface, SDL_Surface* normalMap, Mesh* mesh);
	
	virtual void Init();
	virtual void Update();
	virtual void Render();
};