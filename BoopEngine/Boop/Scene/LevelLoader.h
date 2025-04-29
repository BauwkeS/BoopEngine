#pragma once
#include <string>
#include <map>
#include <memory>
#include <stdexcept>

#include "../HelperFiles/Singleton.h"
#include "../Input/InputManager.h"
#include "GameObjectType.h"

namespace boop
{
	enum struct keyState;
	class Command;
	class GameObject;
	class Collision;
	class Component;

}

namespace level
{
	// original Inspiration (has evolved)
	// https://www.youtube.com/watch?v=KrhDQAPMmvw
	// docu: https://cplusplus.com/doc/tutorial/files/#:~:text=Reading%20from%20a%20file%20can%20also%20be%20performed%20in%20the%20same%20way%20that%20we%20did%20with%20cin%3A

	enum class LevelLayer {
		STATIC, //background and level tiles
		DYNAMIC, //enemies, pickups, events
		PERSISTENT //objects that need to transfer between levels, eg: players
	};


	class LevelLoader final : public boop::Singleton<LevelLoader>
	{
	private:
		std::unordered_map<int, std::pair<std::unique_ptr<boop::GameObjectType>, LevelLayer>> m_GameObjectTypes;

		std::vector<std::unique_ptr<boop::GameObject>> m_StaticObjects{};
		std::vector<std::unique_ptr<boop::GameObject>> m_DynamicObjects{};
		std::vector<std::unique_ptr<boop::GameObject>> m_PersistentObjects{};

		void ClearVectors()
		{
			m_StaticObjects.clear();
			m_DynamicObjects.clear();
			m_PersistentObjects.clear();
		}
	public:
		LevelLoader() = default;
		~LevelLoader() = default;
		LevelLoader(const LevelLoader& other) = delete;
		LevelLoader(LevelLoader&& other) = delete;
		LevelLoader& operator=(const LevelLoader& other) = delete;
		LevelLoader& operator=(LevelLoader&& other) = delete;

		void CreateLevel(std::string fileName, std::string sceneName, int gridSize=32);

		boop::GameObjectType& RegisterType(int index, LevelLayer layer)
		{
			auto [it, inserted] = m_GameObjectTypes.emplace(
				index,
				std::make_pair(std::make_unique<boop::GameObjectType>(), layer)
			);

			if (!inserted) {
				throw std::runtime_error("Duplicate index registered");
			}

			return *(it->second.first); // Return reference to the stored object
		}

		//info for me: use & to chain down the commands to add component easily
	};
}