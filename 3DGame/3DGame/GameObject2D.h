#pragma once
#include "GameObject.h"
#include "Vec2.h"

class GameObject2D : public GameObject
{
protected:
	Vec2 m_pos;
	Vec2 m_size;
	string m_textureID;

	int m_currentRow;
	int m_currentFrame;
public:
	GameObject2D(Vec2 pos, Vec2 size, std::string textureID) :
		m_pos(pos), m_size(size), m_textureID(textureID) {
		m_currentRow = 1;
		m_currentFrame = 1;
	}
	virtual ~GameObject2D();

	virtual void Init(GameState* pGameState);
	virtual void Update();
	virtual void Render();
	virtual void Clean();

	Vec2 GetPos() {
		return m_pos;
	}
	Vec2 GetSize(){
		return m_size;
	}
};