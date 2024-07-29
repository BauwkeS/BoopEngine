#pragma once
#include <vector>
#include <string>
#include <memory>
#include "HelperFiles/Singleton.h"

namespace boop
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& AddScene(const std::string& name);
		void ChangeScene(const std::string& toSceneName);
		Scene& GetActiveScene();

		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void Render();

	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		~SceneManager();
		std::vector<std::unique_ptr<Scene>> m_Scenes;

		//std::unique_ptr<Scene> m_pActiveScene;
		int m_ActiveSceneId{};
	};
}
