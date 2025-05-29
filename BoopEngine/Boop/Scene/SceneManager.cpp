#include "SceneManager.h"
#include "Scene.h"

void boop::SceneManager::FixedUpdate()
{
	m_Scenes[m_ActiveSceneId]->FixedUpdate();
}

void boop::SceneManager::Update()
{
	m_Scenes[m_ActiveSceneId]->Update();
}

void boop::SceneManager::Render()
{
	m_Scenes[m_ActiveSceneId]->Render();
}

boop::SceneManager::SceneManager()
{
}

boop::SceneManager::~SceneManager()
{
}

void boop::SceneManager::ChangeScenePersistency(int i)
{
	//also move persistent objects if needed to the new scene
	auto persistentOld = m_Scenes[m_ActiveSceneId]->GetAllPersistentObjects(); //active persistent
	auto persistentNew = m_Scenes[i]->GetAllPersistentObjects(); //new persistent

	if (persistentOld.size() == 0)
	{
		//if there are no persistent objects in the old scene, just move the new ones
		for (auto& objNew : persistentNew)
		{
			m_Scenes[i]->Add(std::move(objNew), true);
		}
	}
	else {
		for (auto& objOld : persistentOld)
		{
			if (persistentNew.size() == 0)
			{
				//if there are no persistent objects in the new scene, just move the old ones
				m_Scenes[i]->Add(std::move(objOld), true);
				continue;
			}
			//check if the object is already in the new scene
			for (auto& objNew : persistentNew)
			{
				if (objOld->GetTag() == objNew->GetTag()) //its the same object
				{
					//move the old object to the new scene with correct vars
					//move the new object to the old scene -> when re-entering the scene, this object will hold the info it needs to do this process again correctly
					auto tempPos = objOld->GetLocalPosition();
					objOld->SetLocalPosition(objNew->GetLocalPosition());

					objNew->SetLocalPosition(tempPos);
					m_Scenes[m_ActiveSceneId]->Add(std::move(objNew), true);

					//objNew->SetToDelete();
					m_Scenes[i]->Add(std::move(objOld), true);

					//update the persistent vector
					persistentNew.erase(std::remove(persistentNew.begin(), persistentNew.end(), nullptr), persistentNew.end());

					break;
				}
			}
		}
	}
}

boop::Scene& boop::SceneManager::AddScene(const std::string& name)
{
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
			// Change persistency of the current scene
			ChangeScenePersistency(i);

			m_ActiveSceneId = i;
		}
	}
}

void boop::SceneManager::ChangeScene(const int toSceneName)
{
	// Change persistency of the current scene
	ChangeScenePersistency(toSceneName);

	m_ActiveSceneId = toSceneName;
}

boop::Scene* boop::SceneManager::GetActiveScene()
{
	return m_Scenes[m_ActiveSceneId].get();
}

int boop::SceneManager::GetActiveSceneId() const
{
	return m_ActiveSceneId;
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
