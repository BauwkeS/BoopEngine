#pragma once
#include <string>
#include <map>
#include <memory>
#include <utility> 
#include <stdexcept>


#include "../HelperFiles/Singleton.h"

namespace boop
{
	class GameObject;
	class Collision;
	class Component;

}

namespace level
{
	//Inspiration
	// https://www.youtube.com/watch?v=KrhDQAPMmvw
	// docu: https://cplusplus.com/doc/tutorial/files/#:~:text=Reading%20from%20a%20file%20can%20also%20be%20performed%20in%20the%20same%20way%20that%20we%20did%20with%20cin%3A

	//Plan
	// its grid based
	//open/stream file and get the information out of it
	//be able to bind a number to a gameobject/component
	//add a scene -> and add everything to the scene according to 
	//		that grid format you got


	//enum class CompType
	//{
	//	Sprite,
	//	Texture,
	//	Text
	//};

	class LevelLoader final : public boop::Singleton<LevelLoader>
	{
	public:

	private:

	/*	using LoadComponent = std::pair<CompType, boop::Component*>;
		std::map<int, LoadComponent> m_AssignedComponents{};

		std::unique_ptr<boop::Component> GetCompClass(LoadComponent value);*/


		std::map<int, std::unique_ptr<boop::GameObject>> m_GameComponents{};

	public:

		boop::GameObject* GetAssignedObjectPtr(int index)
		{
			return	m_GameComponents.at(index).get();
		}

		//void AssignSpriteComponent(int index, boop::GameObject* owner, const std::string& textureFileName,
		//	int cols, int rows, float frameSec, int startPicIndex,
		//	int amountPics, float scale = 1, boop::Collision* collision = nullptr);

		//void AssignTextComponent(int index, boop::GameObject* owner, const std::string& text,
		//	const std::string& font, unsigned int fontSize);

		//void AssignTextureComponent(int index, boop::GameObject* owner, const std::string& texture,
		//	float scale = 1, bool automaticCollision = false, boop::Collision* collision = nullptr);


		LevelLoader() = default;
		~LevelLoader() = default;
		LevelLoader(const LevelLoader& other) = delete;
		LevelLoader(LevelLoader&& other) = delete;
		LevelLoader& operator=(const LevelLoader& other) = delete;
		LevelLoader& operator=(LevelLoader&& other) = delete;

		//void AssignComponent(int index, boop::Component* comp);
		//void CreateLevelInScene(std::string fileName, std::string sceneName);



		void AssignGameObject(int index, std::unique_ptr<boop::GameObject> object);
		void CreateLevel(std::string fileName, std::string sceneName);


	};
}