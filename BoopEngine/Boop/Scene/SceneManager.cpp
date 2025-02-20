#include "SceneManager.h"
#include "Scene.h"

void boop::SceneManager::FixedUpdate(float deltaTime)
{
	/*for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(deltaTime);
	}*/
	m_Scenes[m_ActiveSceneId]->FixedUpdate(deltaTime);
}

void boop::SceneManager::Update(float deltaTime)
{
	/*for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}*/
	m_Scenes[m_ActiveSceneId]->Update(deltaTime);
}

void boop::SceneManager::Render()
{
	/*for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}*/
	m_Scenes[m_ActiveSceneId]->Render();
}

boop::SceneManager::SceneManager()
{
}

boop::SceneManager::~SceneManager()
{
	/*delete m_pActiveScene;
	m_pActiveScene = nullptr;*/
}

boop::Scene& boop::SceneManager::AddScene(const std::string& name)
{
	//const auto& scene = std::make_unique<Scene>(name);
	/*auto& scene = m_Scenes.emplace_back(std::make_unique<Scene>(name));
	return *scene;*/

	auto scene = std::make_unique<Scene>(name);
	auto& ref = *scene;
	m_Scenes.emplace_back(std::move(scene));
	return ref;
}

void boop::SceneManager::ChangeScene(const std::string& toSceneName)
{
	for (int i = 0; i < m_Scenes.size(); ++i)
	{
		if (m_Scenes[i]->GetName() == toSceneName)
		{
			m_ActiveSceneId = i;
		}
	}
}

boop::Scene* boop::SceneManager::GetActiveScene()
{
	return m_Scenes[m_ActiveSceneId].get();
}
