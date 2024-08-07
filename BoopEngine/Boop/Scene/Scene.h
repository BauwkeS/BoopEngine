#pragma once
#include "SceneManager.h"
#include "../GameObject.h"

namespace boop
{
	class Scene final
	{
		//friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();

		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);
		void Render() const;

		std::string GetName() const;
		std::vector<std::unique_ptr<GameObject>>& GetObjects();

		Scene();
		explicit Scene(const std::string& name);
		~Scene();

		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:

		std::string m_name;
		std::vector<std::unique_ptr<GameObject>> m_objects{};

		static unsigned int m_idCounter;
	};

}