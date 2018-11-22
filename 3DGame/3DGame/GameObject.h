#pragma once

#include "DeltaTime.h"
#include <string>

using namespace std;

class GameState;

class GameObject
{
public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	string GetTag() {
		return m_tag;
	}
protected:
	GameObject() {}
	virtual ~GameObject() {}

	string m_tag;
	GameState* m_pGameState;
};