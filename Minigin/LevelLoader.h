#pragma once
#include <string>
#include <map>
#include <memory>
#include <utility> 
#include <stdexcept>


#include "HelperFiles/Singleton.h"

namespace boop
{
	class GameObject;
	class Collision;
	class Component;
	class TextureComponent; 
	class TextComponent;
	class SpriteComponent;
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

	//class boop::Component;

		enum class CompType
		{
			Sprite,
			Texture,
			Text
		};

	class LevelLoader final : public boop::Singleton<LevelLoader>
	{
	public:

	private:
		//friend class Singleton<LevelLoader>;
		//file info
		//std::string m_FileName;
		//std::string m_ComponentFileName;

		//to put in info
		
		//make template class to put in that pair with arg
		//to then put the template thing into the map
		

		using LoadComponent = std::pair<CompType, boop::Component*>;
		std::map<int, LoadComponent> m_AssignedComponents{};

		std::unique_ptr<boop::Component> GetCompClass(LoadComponent value);


		//std::map<int, boop::Component*> m_AssignedComponents{};

		//Not the perfect way, but ways to parse the txt into code
	/*	template<typename ComponentType>
		ComponentType ConvertTo(const std::string& comp)
		{
			static_assert(false, "no conversion for this type yet");
		}*/

		/*template<typename ComponentType, typename... Args>
		ComponentType ConvertTo(const std::string& txt, const Args&... args);*/

	/*	template<typename ... Args>
		std::unique_ptr<boop::Component> GetCompClass(int value, const Args&... args);
		*/
		

		/*template<>
		boop::TextureComponent ConvertTo<boop::SpriteComponent>(const std::string& txt, boop::AnimatedTexture* const texture, boop::Collision* collision = nullptr);*/

		//template<class T>
		//auto func(T width, T height)
		//{
		//	//... 
		//	return typeid(width).name();
		//	//... 
		//}
	public:

		void AssignSpriteComponent(int index, boop::GameObject* owner, const std::string& textureFileName,
			int cols, int rows, float frameSec, int startPicIndex,
			int amountPics, float scale, boop::Collision* collision = nullptr);

		void AssignTextComponent(int index, boop::GameObject* owner, const std::string& text,
			const std::string& font, unsigned int fontSize);

		void AssignTextureComponent(int index, boop::GameObject* owner, const std::string& texture);


		LevelLoader() = default;
		~LevelLoader() = default;
		LevelLoader(const LevelLoader& other) = delete;
		LevelLoader(LevelLoader&& other) = delete;
		LevelLoader& operator=(const LevelLoader& other) = delete;
		LevelLoader& operator=(LevelLoader&& other) = delete;

		//void AssignComponent(int index, boop::Component* comp);
		void CreateLevelInScene(std::string fileName, std::string sceneName);


		/*template<typename ... Args>
		void AssignComponent(int index, CompType compT, const Args&... args);*/
		//template<class C, typename ... Args>
		//void AssignComponent(int index, const Args&... args);
		//struct AddingComp{};

		
	};

	
}

//
//template<typename ... Args>
//void level::LevelLoader::AssignComponent(int index, CompType compT, const Args&... args)
//{
//	//check if the index is not used already
//	if (m_AssignedComponents.find(index) != m_AssignedComponents.end()) {
//		throw std::runtime_error("Index already in use");
//	}
//
//
//	switch (compT)
//	{
//	case CompType::Sprite:
//	{
//		auto comp = std::make_unique<boop::SpriteComponent>(args...);
//		m_AssignedComponents.insert(std::make_pair(index, std::make_pair(compT, comp.get())));
//
//		break;
//	}
//	case CompType::Text:
//	{
//		auto comp = std::make_unique<boop::TextComponent>(args...);
//		m_AssignedComponents.insert(std::make_pair(index, std::make_pair(compT, comp.get())));
//
//		break;
//	}
//	case CompType::Texture:
//	{
//		auto comp = std::make_unique<boop::TextureComponent>(args...);
//		m_AssignedComponents.insert(std::make_pair(index, std::make_pair(compT, comp.get())));
//
//		break;
//	}
//	}
//
//	//std::unique_ptr<boop::Component> comp;
//
//	//switch (compT)
//	//{
//	//case CompType::Sprite:
//	//	comp = std::make_unique<boop::SpriteComponent>(std::forward<Args>(args)...);
//	//	break;
//	//case CompType::Text:
//	//	comp = std::make_unique<boop::TextComponent>(std::forward<Args>(args)...);
//	//	break;
//	//case CompType::Texture:
//	//	comp = std::make_unique<boop::TextureComponent>(std::forward<Args>(args)...);
//	//	break;
//	//default:
//	//	throw std::invalid_argument("Invalid component type");
//	//}
//
//	//// Insert the component into the map
//	//m_AssignedComponents.insert({ index, {compT, comp.release()} });
//
//}