#pragma once

#include "DeltaTime.h"
#include <string>

using namespace std;

class GameState;

class GameObject
{
public:
	virtual void Init(GameState* pGameState) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Clean() = 0;

	string GetTag() {
		return m_tag;
	}
protected:
	GameObject() {}

	string m_tag;
public:
	virtual ~GameObject() {}
};