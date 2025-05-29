#pragma once
#include <vector>
#include <string>
#include <memory>
#include "../HelperFiles/Singleton.h"

namespace boop
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& AddScene(const std::string& name);
		void ChangeScene(const std::string& toSceneName);
		void ChangeScene(const int toSceneName);
		Scene* GetActiveScene();
		int GetActiveSceneId() const;
		Scene* GetScene(const std::string& name);

		void FixedUpdate();
		void Update();
		void Render();

	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		~SceneManager();
		std::vector<std::unique_ptr<Scene>> m_Scenes;

		void ChangeScenePersistency(int newScene);

		int m_ActiveSceneId{};
	};
}
