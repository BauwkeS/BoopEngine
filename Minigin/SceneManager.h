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
		Scene& CreateScene(const std::string& name);

		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void Render();
		void Delete();

	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		~SceneManager();
		std::vector<std::unique_ptr<Scene>> m_scenes;
	};
}
