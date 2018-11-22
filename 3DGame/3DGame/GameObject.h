#pragma once

#include "DeltaTime.h"
#include <string>

using namespace std;

class GameState;

class GameObject
{
public:
	virtual void Init(GameState* pGameState) = 0;
	virtual void Update(GameState* pGameState) = 0;
	virtual void Render() = 0;

	string GetTag() {
		return m_tag;
	}
protected:
	GameObject() {}
	virtual ~GameObject() {}

	string m_tag;
};