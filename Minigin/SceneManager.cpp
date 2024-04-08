#include "SceneManager.h"
#include "Scene.h"

void boop::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void boop::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void boop::SceneManager::Delete()
{
	/*for (const auto& scene : m_ScenesPtr)
	{
		scene->CleanUp();
	}*/
}

boop::SceneManager::SceneManager()
{
}

boop::SceneManager::~SceneManager()
{
}

boop::Scene& boop::SceneManager::CreateScene(const std::string& name)
{
	//const auto& scene = std::make_unique<Scene>(name);
	const auto& scene = m_scenes.emplace_back(std::make_unique<Scene>(name));
	return *scene;
}
