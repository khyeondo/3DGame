#include "Stage1.h"
#include "GameObject.h"
#include "Player.h"
#include "Cube.h"
#include "MapManager.h"
#include "SurfaceManager.h"
#include "MeshManager.h"
#include "Renderer3D.h"
#include "Camera.h"
#include "CollideManger.h"
#include <iostream>

Stage1* Stage1::s_pInstance = 0;
const std::string Stage1::s_Stage1ID = "STAGE1";

void Stage1::init()
{
	for (GameObject* gameObject : m_gameObjects)
	{
		gameObject->Init(this);
	}
}

void Stage1::update()
{
	for (std::vector<GameObject*>::size_type i = 0;
		i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Update(this);
	}
	ColliderManager::Instance()->Update();
}

void Stage1::render()
{
	for (std::vector<GameObject*>::size_type i = 0;
		i != m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->Render();
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

	Mesh* cube = new Mesh();
	Mesh* plane = new Mesh();
	plane->SetPlane(Vec3(1.f, 1.f, 1.f));
	cube->SetCube(Vec3(5.f, 5.f, 5.f), Vec3(10, 10, 10));

	MeshManager::Instance()->SetMesh(plane, "plane");
	MeshManager::Instance()->SetMesh(cube, "cube");

	GameObject3DInstantiate(new Player(Renderer3D::Instance()->GetCamera()));
	GameObject3DInstantiate(new Cube(SurfaceManager::Instance()->GetSurface("box")->at(0),
		NULL, MeshManager::Instance()->GetMesh("cube")));
	m_gameObjects.push_back(new MapManager());

	//m_gameObjects.push_back(new Cube(SurfaceManager::Instance()->GetSurface("box")->at(0), 
	//	NULL, MeshManager::Instance()->GetMesh("cube")));

	std::cout << "entering stage1\n";
	return true;
}

bool Stage1::onExit()
{
	SurfaceManager::Instance()->Clear();
	ColliderManager::Instance()->Clear();
	std::cout << "exiting stage1\n";
	return true;
}
