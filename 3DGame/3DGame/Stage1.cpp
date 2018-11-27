#include "Stage1.h"
#include "GameObject.h"
#include "Player.h"
#include "MapManager.h"
#include "SurfaceManager.h"
#include "MeshManager.h"
#include "Renderer3D.h"
#include "Camera.h"
#include "CollideManger.h"
#include "TextureManager.h"
#include "PlayerUI.h"
#include "Pause.h"
#include <iostream>

Stage1* Stage1::s_pInstance = 0;
const std::string Stage1::s_Stage1ID = "STAGE1";

void Stage1::init()
{
	//for (GameObject* gameObject : m_gameObjects)
	//{
	//	gameObject->Init(this);
	//}
}

void Stage1::update()
{
	for (int i = 0; i < m_3DGameObjects.size(); i++)
	{
		m_3DGameObjects[i]->Update();
	}
	ColliderManager::Instance()->Update();

	for (int i = 0; i < m_2DGameObjects.size(); i++)
	{
		m_2DGameObjects[i]->Update();
	}
	for (int i = 0; i < m_UIGameObjects.size(); i++)
	{
		m_UIGameObjects[i]->Update();
	}
}

void Stage1::render()
{
	for (int i = 0; i != m_3DGameObjects.size(); i++)
	{
		m_3DGameObjects[i]->Render();
	}
	Renderer3D::Instance()->Present();

	for (int i = 0; i != m_2DGameObjects.size(); i++)
	{
		m_2DGameObjects[i]->Render();
	}
	for (int i = 0; i != m_UIGameObjects.size(); i++)
	{
		m_UIGameObjects[i]->Render();
	}
}

bool Stage1::onEnter()
{
	SurfaceManager::Instance()->load("Assets/box.png", "box");
	SurfaceManager::Instance()->load("Assets/bullet.png", "bullet");
	SurfaceManager::Instance()->load("Assets/NormalMap.png", "normalMap");

	SurfaceManager::Instance()->load("Assets/fire/fire(1).png", "fire");
	SurfaceManager::Instance()->load("Assets/fire/fire(2).png", "fire");
	SurfaceManager::Instance()->load("Assets/fire/fire(3).png", "fire");
	SurfaceManager::Instance()->load("Assets/fire/fire(4).png", "fire");
	SurfaceManager::Instance()->load("Assets/fire/fire(5).png", "fire");
	SurfaceManager::Instance()->load("Assets/fire/fire(6).png", "fire");
	SurfaceManager::Instance()->load("Assets/fire/fire(7).png", "fire");
	SurfaceManager::Instance()->load("Assets/fire/fire(8).png", "fire");
	SurfaceManager::Instance()->load("Assets/fire/fire(9).png", "fire");

	SurfaceManager::Instance()->load("Assets/monster/walk/walk (1).png", "monster_walk");
	SurfaceManager::Instance()->load("Assets/monster/walk/walk (2).png", "monster_walk");
	SurfaceManager::Instance()->load("Assets/monster/walk/walk (3).png", "monster_walk");
	SurfaceManager::Instance()->load("Assets/monster/walk/walk (4).png", "monster_walk");

	SurfaceManager::Instance()->load("Assets/monster/attack/attack (1).png", "monster_attack");
	SurfaceManager::Instance()->load("Assets/monster/attack/attack (2).png", "monster_attack");
	SurfaceManager::Instance()->load("Assets/monster/attack/attack (3).png", "monster_attack");

	SurfaceManager::Instance()->load("Assets/monster/attacked/attacked (1).png", "monster_attacked");

	SurfaceManager::Instance()->load("Assets/monster/die/die (1).png", "monster_die");
	SurfaceManager::Instance()->load("Assets/monster/die/die (2).png", "monster_die");
	SurfaceManager::Instance()->load("Assets/monster/die/die (3).png", "monster_die");
	SurfaceManager::Instance()->load("Assets/monster/die/die (4).png", "monster_die");
	SurfaceManager::Instance()->load("Assets/monster/die/die (5).png", "monster_die");

	TextureManager::Instance()->load("Assets/gun_shoot.png", "gun_shoot");
	TextureManager::Instance()->load("Assets/aim.png", "aim");
	TextureManager::Instance()->load("Assets/hp.png", "hp");
	TextureManager::Instance()->load("Assets/hp_bar.png", "hp_bar");
	TextureManager::Instance()->load("Assets/pause.png", "pause");

	Mesh* cube = new Mesh();
	Mesh* plane = new Mesh();
	plane->SetPlane(Vec3(1.f, 1.f, 1.f));
	cube->SetCube(Vec3(5.f, 5.f, 5.f), Vec3(10, 10, 10));

	MeshManager::Instance()->SetMesh(plane, "plane");

	GameObject3DInstantiate(new Player(Renderer3D::Instance()->GetCamera()),Vec3(100.f,30.f,100.f));
	GameObject3DInstantiate(new MapManager());

	GameObject2DInstantiate(new PlayerUI(Vec2(313.f, 400.f), Vec2(173.f, 200.f), "gun_shoot"));
	GameObjectUIInstantiate(new Pause(Vec2(0.f, 0.f), Vec2(800.f, 600.f), "pause"));

	//m_gameObjects.push_back(new Cube(SurfaceManager::Instance()->GetSurface("box")->at(0), 
	//	NULL, MeshManager::Instance()->GetMesh("cube")));

	std::cout << "entering stage1\n";
	return true;
}

bool Stage1::onExit()
{
	Clean();
	TextureManager::Instance()->Clear();
	SurfaceManager::Instance()->Clear();
	ColliderManager::Instance()->Clear();
	MeshManager::Instance()->Clear();
	std::cout << "exiting stage1\n";
	return true;
}
