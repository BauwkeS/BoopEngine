#include <string>
#include <map>
#include "Components/Component.h"
#include "Components/SpriteComponent.h"
#include "Components/TextureComponent.h"
#include "HelperFiles/Singleton.h"

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

	class LevelLoader final : public boop::Singleton<LevelLoader>
	{
	private:
		//file info
		std::string m_FileName;
		std::string m_ComponentFileName;

		//to put in info
		
		//make template class to put in that pair with arg
		//to then put the template thing into the map
		

		//using LoadComponent = std::pair<Component*, Args...>

		std::map<int, boop::Component*> m_AssignedComponents{};

		//Not the perfect way, but ways to parse the txt into code
	/*	template<typename ComponentType>
		ComponentType ConvertTo(const std::string& comp)
		{
			static_assert(false, "no conversion for this type yet");
		}*/

		template<typename ComponentType, typename... Args>
		ComponentType ConvertTo(const std::string& txt, const Args&... args);

		template<typename ... Args>
		std::unique_ptr<boop::Component> GetCompClass(int value, const Args&... args);

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
		LevelLoader(std::string fileName, std::string compName);

		~LevelLoader() = default;
		LevelLoader(const LevelLoader& other) = delete;
		LevelLoader(LevelLoader&& other) = delete;
		LevelLoader& operator=(const LevelLoader& other) = delete;
		LevelLoader& operator=(LevelLoader&& other) = delete;

		//void AssignComponent(int index, boop::Component* comp);
		void CreateLevelInScene(std::string sceneName);


		template<class C, typename ... Args>
		void AssignComponent(int index, const Args&... args);
		//struct AddingComp{};

	};

	
}
