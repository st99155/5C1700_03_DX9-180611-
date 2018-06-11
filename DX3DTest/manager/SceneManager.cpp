#include "stdafx.h"
#include "SceneManager.h"
#include "./object/interface/IScene.h"
#include "./scene/SceneGrid.h"


SceneManager* SceneManager::instance = NULL;

SceneManager * SceneManager::Get()
{
	if (instance == NULL)
		instance = new SceneManager();

	return instance;
}

void SceneManager::Delete()
{
	SAFE_DELETE(instance);
}

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (auto p : m_vecScene)
	{
		SAFE_RELEASE(p);
	}
}

void SceneManager::Init()
{	
	m_vecScene.push_back(new SceneGrid);

	SetCurrentScene(SCENE_GRID);
}


void SceneManager::Update()
{
	SAFE_UPDATE(m_pCurrentScene);
}

void SceneManager::Render()
{
	SAFE_RENDER(m_pCurrentScene);
}


void SceneManager::SetCurrentScene(size_t index)
{
	if (index >= m_vecScene.size()) return;

	IScene* pScene = m_vecScene[index];
	if (pScene)
	{
		pScene->Init();
		m_pCurrentScene = pScene;
	}
}

