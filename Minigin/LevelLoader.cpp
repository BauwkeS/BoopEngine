#include "LevelLoader.h"

#include <cassert>
#include <iostream>
#include <fstream>

#include "SceneManager.h"
#include "GameObject.h"
#include "Components/TextComponent.h"


namespace level
{

	LevelLoader::LevelLoader(std::string fileName)
		: m_FileName{fileName}
	//	m_ComponentFileName{compName}
	{
	}

	//void LevelLoader::AssignComponent(int index, boop::Component* comp)
	//{
	//	//check if the index is not used already, if it is then assert

	//	for (const auto& item : m_AssignedComponents)
	//	{
	//		assert(item.first == index && "index already in use");
	//	}

	//	m_AssignedComponents.insert(std::pair(index, comp));
	//}

	//template <int, class C, typename ... Args>
	//void boop::LevelLoader::AssignComponent(int index, class componentType, const Args&... args)
	//{
	//	//check if the index is not used already, if it is then assert

	//	for (const auto& item : m_AssignedComponents)
	//	{
	//		assert(item.first == index && "index already in use");
	//	}

	//	m_AssignedComponents.insert(std::pair(index, comp));
	//}

	/*template <typename ComponentType, typename ... Args>
	ComponentType LevelLoader::ConvertTo(const std::string& txt, const Args&... args)
	{
		switch (txt)
		{
		case "Sprite":
			return boop::SpriteComponent(args);
		case "Texture":
			return boop::TextureComponent(args);
		case "Text":
			return boop::TextComponent(args);
		}
	}*/

	//template <typename ... Args>
	//std::unique_ptr<boop::Component> LevelLoader::GetCompClass(int value)
	std::unique_ptr<boop::Component> LevelLoader::GetCompClass(LoadComponent value)
	{
		switch (value.first)
		{
			case CompType::Sprite:
			{
				boop::SpriteComponent* comp = dynamic_cast<boop::SpriteComponent*>(value.second);
				std::unique_ptr<boop::SpriteComponent> uniqueSprite = std::make_unique<boop::SpriteComponent>(*comp);
				return std::move(uniqueSprite);
			}
			case CompType::Text:
			{
				boop::TextComponent* comp = dynamic_cast<boop::TextComponent*>(value.second);
				std::unique_ptr<boop::TextComponent> uniquetext = std::make_unique<boop::TextComponent>(*comp);
				return std::move(uniquetext);
			}
			case CompType::Texture:
			{
				boop::TextureComponent* comp = dynamic_cast<boop::TextureComponent*>(value.second);
				std::unique_ptr<boop::TextureComponent> uniquetexture = std::make_unique<boop::TextureComponent>(*comp);
				return std::move(uniquetexture);
			}
			default:
				static_assert(true, "could not get component");
				return nullptr;
		}

	}

	template<typename ... Args>
	void LevelLoader::AssignComponent(int index, CompType compT, const Args&... args)
	{
		//check if the index is not used already, if it is then assert

		for (const auto& item : m_AssignedComponents)
		{
			static_assert(item.first == index && "index already in use");
		}

		switch (compT)
		{
		case CompType::Sprite :
			{
			boop::SpriteComponent * comp = boop::SpriteComponent(args...);
			m_AssignedComponents.insert(std::pair(index, std::pair(compT, comp)));
			break;
			}
		case CompType::Text:
			{
			boop::TextComponent* comp = boop::TextComponent(args...);
			m_AssignedComponents.insert(std::pair(index, std::pair(compT, comp)));
				break;
			}
		case CompType::Texture:
			{
			boop::TextureComponent* comp = boop::TextureComponent(args...);
			m_AssignedComponents.insert(std::pair(index, std::pair(compT, comp)));
				break;
			}
		}
	}

	//template <class C, typename ... Args>
	//void LevelLoader::AssignComponent(int index, const Args&... args)
	//{
	//	//check if the index is not used already, if it is then assert

	//	for (const auto& item : m_AssignedComponents)
	//	{
	//		static_assert(item.first == index && "index already in use");
	//	}

	//	switch (C(args...))
	//	{
	//	case 1:
	//	{
	//		auto type = m_AssignedComponents.at(value)->GetType();
	//		auto comp1 = std::make_unique<boop::SpriteComponent>(args...);
	//		auto comp1 = std::make_unique<boop::SpriteComponent>(args...);
	//		return (std::move(comp1));
	//	}
	//	case 2:
	//	{
	//		auto comp2 = std::make_unique<boop::TextureComponent>(args...);
	//		return (std::move(comp2));
	//	}
	//	case 3:
	//	{
	//		auto comp3 = std::make_unique<boop::TextComponent>(args...);
	//		return (std::move(comp3));
	//	}
	//	default:
	//	{
	//		return nullptr;

	//	}
	//	}


	//	C* pComponent = C(args...);

	//	/*if (owner == nullptr)
	//	{
	//		pComponent = std::make_unique<T>(this, args...);
	//	}
	//	else pComponent = std::make_unique<T>(owner, args...);*/


	//	//pComponent->Initialize();

	//	//C* rawPtr = pComponent.get();
	//	//m_pComponents.emplace_back();

	//	m_AssignedComponents.insert(std::pair(index, pComponent));
	//}

	void LevelLoader::CreateLevelInScene(std::string sceneName)
	{
		//plan:
		//load the level
		// for loop the grid bindings
		//for the index, look in the map and add the component to the scene



		auto& scene = boop::SceneManager::GetInstance().AddScene(sceneName);
		scene;

		std::ifstream gameFile;
		gameFile.open(m_FileName);

		int colsRead{};
		int RowsRead{};

		if (gameFile.is_open())
		{
			std::string rowLine{};
			while (std::getline(gameFile,rowLine))
			{
				for(const auto& colChar : rowLine)
				{
					LoadComponent toAddComp = m_AssignedComponents.at( static_cast<int>(colChar));

					if (!toAddComp.second) static_assert(true, "cannot add component to level");

					auto go = std::make_unique<boop::GameObject>();

				//	auto func(toAddComp);

					//go->AddComponent<func>(nullptr, toAddComp);
					go->AddMadeComp(GetCompClass(toAddComp));
					//--
					//https://en.cppreference.com/w/cpp/language/decltype
					//--

					//go->AddComponent<decltype(toAddComp)>();

					++colsRead;
				}

				++RowsRead;
			}
		}
		else static_assert(true, "game file could not be opened");


		gameFile.close();
	}
}
