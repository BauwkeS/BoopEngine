#include "SceneManager.h"
#include "Scene.h"

void boop::SceneManager::FixedUpdate()
{
	/*for (auto& scene : m_Scenes)
	{
		scene->FixedUpdate(deltaTime);
	}*/
	m_Scenes[m_ActiveSceneId]->FixedUpdate();
}

void boop::SceneManager::Update()
{
	/*for(auto& scene : m_Scenes)
	{
		scene->Update(deltaTime);
	}*/
	m_Scenes[m_ActiveSceneId]->Update();
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
			//also move persistent objects if needed to the new scene
			auto persistentObj = m_Scenes[m_ActiveSceneId]->GetAllPersistentObjects();

			for (auto& obj : persistentObj)
			{
				m_Scenes[i]->Add(std::move(obj), true);
			}

			m_ActiveSceneId = i;
		}
	}
}

boop::Scene* boop::SceneManager::GetActiveScene()
{
	return m_Scenes[m_ActiveSceneId].get();
}

boop::Scene* boop::SceneManager::GetScene(const std::string& name)
{
	for (auto& scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			return scene.get();
		}
	}
	return nullptr;
}
