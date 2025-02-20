#pragma once
#include <unordered_map>

#include "SceneManager.h"
#include "../GameObject.h"

namespace boop
{
	class Scene final
	{
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(std::unique_ptr<GameObject> object);
		void RemoveAll();

		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void Render() const;

		std::string GetName() const;
		std::vector<std::unique_ptr<GameObject>>& GetObjects();

		GameObject* FindGameObjectByTag(const std::string& tag) const;
		std::vector<GameObject*> FindAllGameObjectByTag(const std::string& tag) const;


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
		std::unordered_multimap<std::string, GameObject*> m_taggedObjects;

		static unsigned int m_idCounter;
	};

}
