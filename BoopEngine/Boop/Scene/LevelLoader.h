#pragma once
#include <string>
#include <map>
#include <memory>
#include <stdexcept>

#include "../HelperFiles/Singleton.h"
#include "../Input/InputManager.h"

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
		using GameObjectInfo = std::pair<std::unique_ptr<boop::GameObject>, LevelLayer>;
		std::map<int, GameObjectInfo> m_GameComponents{};
		std::vector<std::string> m_ImportantTags{};
	public:
		LevelLoader() = default;
		~LevelLoader() = default;
		LevelLoader(const LevelLoader& other) = delete;
		LevelLoader(LevelLoader&& other) = delete;
		LevelLoader& operator=(const LevelLoader& other) = delete;
		LevelLoader& operator=(LevelLoader&& other) = delete;

		void AssignGameObject(int index, std::unique_ptr<boop::GameObject> object, LevelLayer layer);
		void CreateLevel(std::string fileName, std::string sceneName);
		void SetImportantTags(std::vector<std::string> tags);
	};
}