#include "SceneManager.h"
#include "Scene.h"

void boop::SceneManager::FixedUpdate(float deltaTime)
{
	for (auto& scene : m_scenes)
	{
		scene->FixedUpdate(deltaTime);
	}
}

void boop::SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_scenes)
	{
		scene->Update(deltaTime);
	}
}

void boop::SceneManager::LateUpdate(float deltaTime)
{
	for (auto& scene : m_scenes)
	{
		scene->LateUpdate(deltaTime);
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
