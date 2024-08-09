#include "LevelLoader.h"

#include <cassert>
#include <filesystem>
#include <iostream>
#include <fstream>

#include "SceneManager.h"
#include "../GameObject.h"
#include "Scene.h"
#include "../Components/TextComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TextureComponent.h"
#include "../Input/InputManager.h"



namespace level
{

	//LevelLoader::LevelLoader()
	////	: m_FileName{fileName}
	////	m_ComponentFileName{compName}
	//{
	//}

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
	

	//template<typename ... Args>
	//void LevelLoader::AssignComponent(int index, CompType compT, const Args&... args)
	//{
	//	//check if the index is not used already, if it is then assert

	//	for (const auto& item : m_AssignedComponents)
	//	{
	//		static_assert(item.first == index && "index already in use");
	//	}

	//	switch (compT)
	//	{
	//	case CompType::Sprite :
	//		{
	//		boop::SpriteComponent * comp = boop::SpriteComponent(args...);
	//		m_AssignedComponents.insert(std::pair(index, std::pair(compT, comp)));
	//		break;
	//		}
	//	case CompType::Text:
	//		{
	//		boop::TextComponent* comp = boop::TextComponent(args...);
	//		m_AssignedComponents.insert(std::pair(index, std::pair(compT, comp)));
	//			break;
	//		}
	//	case CompType::Texture:
	//		{
	//		boop::TextureComponent* comp = boop::TextureComponent(args...);
	//		m_AssignedComponents.insert(std::pair(index, std::pair(compT, comp)));
	//			break;
	//		}
	//	}
	//}

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

void level::LevelLoader::AssignSpriteComponent(int index, boop::GameObject* owner, const std::string& textureFileName,
	int cols, int rows, float frameSec, int startPicIndex,
	int amountPics, float scale, boop::Collision* collision)
{
	auto comp = std::make_unique<boop::SpriteComponent>(owner, textureFileName, cols, rows, frameSec,
		startPicIndex, amountPics, scale, collision);
	m_AssignedComponents.emplace(index, std::make_pair(CompType::Sprite, comp.release()));
}

void LevelLoader::AssignSpriteComponent(int index, boop::GameObject* owner, boop::SpriteComponent* comp)
{
	auto component = std::make_unique<boop::SpriteComponent>(*comp);
	component->SetOwner(owner);
	m_AssignedComponents.emplace(index, std::make_pair(CompType::Sprite, component.release()));
}

void level::LevelLoader::AssignTextComponent(int index, boop::GameObject* owner, const std::string& text,
                                             const std::string& font, unsigned int fontSize)
{
	auto comp = std::make_unique<boop::TextComponent>(owner, text, font, fontSize);
	m_AssignedComponents.emplace(index, std::make_pair(CompType::Text, comp.release()));
}

void level::LevelLoader::AssignTextureComponent(int index, boop::GameObject* owner, const std::string& texture,
	float scale, bool automaticCollision, boop::Collision* collision)
{
	auto comp = std::make_unique<boop::TextureComponent>(owner, texture, scale, automaticCollision, collision);
	m_AssignedComponents.emplace(index, std::make_pair(CompType::Texture, comp.release()));
}

void LevelLoader::AssignTextureComponent(int index, boop::TextureComponent* comp)
{
	auto component = std::make_unique<boop::TextureComponent>(*comp);
	m_AssignedComponents.emplace(index, std::make_pair(CompType::Texture, component.release()));
}

std::unique_ptr<boop::Component> LevelLoader::GetCompClass(LoadComponent value)
{
	switch (value.first)
	{
	case CompType::Sprite:
		return std::make_unique<boop::SpriteComponent>(*dynamic_cast<boop::SpriteComponent*>(value.second));
	case CompType::Text:
		return std::make_unique<boop::TextComponent>(*dynamic_cast<boop::TextComponent*>(value.second));
	case CompType::Texture:
		return std::make_unique<boop::TextureComponent>(*dynamic_cast<boop::TextureComponent*>(value.second));
	default:
		throw std::invalid_argument("Unknown component type");
	}


	/*
	switch (value.first)
	{
	 *case CompType::Sprite:
	{
		auto* comp = dynamic_cast<boop::SpriteComponent*>(value.second);
		if (comp)
		{
			return std::make_unique<boop::SpriteComponent>(*comp);
		}
		break;
	}
	case CompType::Text:
	{
		auto* comp = dynamic_cast<boop::TextComponent*>(value.second);
		if (comp)
		{
			return std::make_unique<boop::TextComponent>(*comp);
		}
		break;
	}
	case CompType::Texture:
	{
		auto* comp = dynamic_cast<boop::TextureComponent*>(value.second);
		if (comp)
		{
			return std::make_unique<boop::TextureComponent>(*comp);
		}
		break;
	}
	default:
		std::cerr << "Unknown component type" << std::endl;
	}
		return nullptr;*/

}

	void LevelLoader::CreateLevelInScene(std::string fileName, std::string sceneName)
	{
		//plan:
		//load the level
		// for loop the grid bindings
		//for the index, look in the map and add the component to the scene



		auto& scene = boop::SceneManager::GetInstance().AddScene(sceneName);
		
		/*std::ifstream gameFile(fileName);
		auto test = std::filesystem::current_path();
		gameFile.open(fileName);
		if (!gameFile.is_open()) throw std::runtime_error("Failed to open game file: " + fileName);*/

		//std::ifstream gameFile(fileName);
		std::ifstream gameFile("Data\\" + fileName);

		if (!gameFile.is_open())
		{
			throw std::runtime_error("Failed to open game file: " + fileName);
		}

		int colsRead = 0;
		int rowsRead = 0;
		constexpr int gridSize = 32;

		std::string rowLine;
		while (std::getline(gameFile, rowLine))
		{
			auto go = std::make_unique<boop::GameObject>();
			
			for (const auto& colChar : rowLine)
			{
				int index = colChar - '0';
				go = std::make_unique<boop::GameObject>();
				/*if (m_AssignedComponents.find(index) == m_AssignedComponents.end())
				{
					throw std::runtime_error("Component not found for index: " + std::to_string(static_cast<int>(colChar)));
				}*/
				// Check if the index is within the valid range
				if (index < 0 || index > 9)
				{
					throw std::runtime_error(
						"Invalid digit: " + std::to_string(index) + " (character: " + colChar + ")"
					);
				}

				// Check if the component exists
				if (m_AssignedComponents.find(index) == m_AssignedComponents.end())
				{
					throw std::runtime_error(
						"Component not found for index: " + std::to_string(index) + " (character: " + colChar + ")"
					);
				}

				LoadComponent toAddComp = m_AssignedComponents.at(index);
				if (!toAddComp.second)
				{
					throw std::runtime_error("Cannot add component to level");
				}
				auto component = GetCompClass(toAddComp);
				boop::GameObject* owner = component->GetOwner();
				if (owner) {
					std::unique_ptr<boop::GameObject> newObj = std::make_unique<boop::GameObject>()
					owner->AddMadeComp(GetCompClass(toAddComp));
					owner->SetLocalPosition(static_cast<float>(gridSize * colsRead), static_cast<float>(gridSize * rowsRead));
				
					scene.Add(std::move(go));
				}
				else {
					go->AddMadeComp();
					go->SetLocalPosition(static_cast<float>(gridSize * colsRead), static_cast<float>(gridSize * rowsRead));

					scene.Add(std::move(go));
				}
			

				

				++colsRead;
			}

			++rowsRead;
			colsRead = 0;
		}

		//int colsRead{};
		//int rowsRead{};

		//constexpr int gridSize{ 32 };


		//if (!gameFile.is_open()) 
		//	throw std::runtime_error("Game file could not be opened: " + fileName);
		//
		//	std::string rowLine{};
		//	while (std::getline(gameFile,rowLine))
		//	{
		//		auto go = std::make_unique<boop::GameObject>();
		//		colsRead = 0;


		//		for(const auto& colChar : rowLine)
		//		{
		//		//	LoadComponent toAddComp = m_AssignedComponents.at( static_cast<int>(colChar));

		//		//	if (!toAddComp.second) static_assert(true, "cannot add component to level");


		//		////	auto func(toAddComp);
		//		//	//go->AddComponent<func>(nullptr, toAddComp);

		//		//	go = std::make_unique<boop::GameObject>();

		//		//	go->AddMadeComp(GetCompClass(toAddComp));
		//		//	go->SetLocalPosition(static_cast<float>(gridSize * colsRead),
		//		//		static_cast<float>(gridSize * rowsRead));
		//		//	scene.Add(go);
		//		//	//--
		//		//	//https://en.cppreference.com/w/cpp/language/decltype
		//		//	//--

		//		//	//go->AddComponent<decltype(toAddComp)>();

		//			try
		//			{
		//				auto it = m_AssignedComponents.find(static_cast<int>(colChar));
		//				if (it != m_AssignedComponents.end())
		//				{
		//					LoadComponent toAddComp = it->second;
		//					auto component = GetCompClass(toAddComp);
		//					if (component)
		//					{
		//						go->AddMadeComp(std::move(component));
		//					}
		//				}
		//				else
		//				{
		//					std::cerr << "Warning: Component with index " << static_cast<int>(colChar) << " not found" << std::endl;
		//				}
		//			}
		//			catch (const std::exception& e)
		//			{
		//				std::cerr << "Exception: " << e.what() << std::endl;
		//			}


		//			++colsRead;
		//		}

		//		go->SetLocalPosition(static_cast<float>(gridSize * colsRead),
		//			static_cast<float>(gridSize * rowsRead));

		//		scene.Add(std::move(go));
		//		++rowsRead;
		//	}
		//
		//	gameFile.close();
	}
}
