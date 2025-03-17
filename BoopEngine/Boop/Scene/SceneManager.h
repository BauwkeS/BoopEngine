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
		Scene* GetActiveScene();
		Scene* GetScene(const std::string& name);

		void FixedUpdate();
		void Update();
		void Render();

	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		~SceneManager();
		std::vector<std::unique_ptr<Scene>> m_Scenes;

		int m_ActiveSceneId{};
	};
}
