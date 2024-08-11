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



namespace level
{
	//
	//void level::LevelLoader::AssignSpriteComponent(int index, boop::GameObject* owner, const std::string& textureFileName,
	//	int cols, int rows, float frameSec, int startPicIndex,
	//	int amountPics, float scale, boop::Collision* collision)
	//{
	//	auto comp = std::make_unique<boop::SpriteComponent>(owner, textureFileName, cols, rows, frameSec,
	//		startPicIndex, amountPics, scale, collision);
	//	m_AssignedComponents.emplace(index, std::make_pair(CompType::Sprite, comp.release()));
	//}
	//
	//void level::LevelLoader::AssignTextComponent(int index, boop::GameObject* owner, const std::string& text,
	//	const std::string& font, unsigned int fontSize)
	//{
	//	auto comp = std::make_unique<boop::TextComponent>(owner, text, font, fontSize);
	//	m_AssignedComponents.emplace(index, std::make_pair(CompType::Text, comp.release()));
	//}
	//
	//void level::LevelLoader::AssignTextureComponent(int index, boop::GameObject* owner, const std::string& texture,
	//	float scale, bool automaticCollision, boop::Collision* collision)
	//{
	//	auto comp = std::make_unique<boop::TextureComponent>(owner, texture, scale, automaticCollision, collision);
	//	m_AssignedComponents.emplace(index, std::make_pair(CompType::Texture, comp.release()));
	//}
	//
	//std::unique_ptr<boop::Component> LevelLoader::GetCompClass(LoadComponent value)
	//{
	//	switch (value.first)
	//	{
	//	case CompType::Sprite:
	//		return std::make_unique<boop::SpriteComponent>(*dynamic_cast<boop::SpriteComponent*>(value.second));
	//	case CompType::Text:
	//		return std::make_unique<boop::TextComponent>(*dynamic_cast<boop::TextComponent*>(value.second));
	//	case CompType::Texture:
	//		return std::make_unique<boop::TextureComponent>(*dynamic_cast<boop::TextureComponent*>(value.second));
	//	default:
	//		throw std::invalid_argument("Unknown component type");
	//	}
	//
	//}
	//
	//	void LevelLoader::CreateLevelInScene(std::string fileName, std::string sceneName)
	//	{
	//		//plan:
	//		//load the level
	//		// for loop the grid bindings
	//		//for the index, look in the map and add the component to the scene
	//
	//
	//
	//		auto& scene = boop::SceneManager::GetInstance().AddScene(sceneName);
	//		std::ifstream gameFile("Data\\" + fileName);
	//
	//		if (!gameFile.is_open())
	//		{
	//			throw std::runtime_error("Failed to open game file: " + fileName);
	//		}
	//
	//		int colsRead = 0;
	//		int rowsRead = 0;
	//		constexpr int gridSize = 32;
	//
	//		std::string rowLine;
	//		while (std::getline(gameFile, rowLine))
	//		{
	//			auto go = std::make_unique<boop::GameObject>();
	//			for (const auto& colChar : rowLine)
	//			{
	//				int index = colChar - '0';
	//				go = std::make_unique<boop::GameObject>();
	//
	//				if (index < 0 || index > 9)
	//				{
	//					throw std::runtime_error(
	//						"Invalid digit: " + std::to_string(index) + " (character: " + colChar + ")"
	//					);
	//				}
	//
	//				// Check if the component exists
	//				if (m_AssignedComponents.find(index) == m_AssignedComponents.end())
	//				{
	//					throw std::runtime_error(
	//						"Component not found for index: " + std::to_string(index) + " (character: " + colChar + ")"
	//					);
	//				}
	//
	//				LoadComponent toAddComp = m_AssignedComponents.at(index);
	//				if (!toAddComp.second)
	//				{
	//					throw std::runtime_error("Cannot add component to level");
	//				}
	//
	//				go->AddMadeComp(GetCompClass(toAddComp));
	//				go->SetLocalPosition(static_cast<float>(gridSize * colsRead), static_cast<float>(gridSize * rowsRead));
	//				scene.Add(std::move(go));
	//
	//				++colsRead;
	//			}
	//
	//			++rowsRead;
	//			colsRead = 0;
	//		}
	//	}
	void LevelLoader::AssignGameObject(int index, std::unique_ptr<boop::GameObject> object)
	{
		// Use the Clone method to create a deep copy of the GameObject
		//auto comp = object->Clone();  // Clone() should return std::unique_ptr<boop::Component>

		// Store the unique_ptr in the m_GameComponents map
		m_GameComponents.emplace(index, std::move(object));
	}

	//void LevelLoader::AssignCommands(int index, KeyboardCommandsMap* item)
	//{
	//	m_GameCommands.emplace(index, item);
	//}


	void LevelLoader::CreateLevel(std::string fileName, std::string sceneName)
	{
		//plan:
		//load the level
		// for loop the grid bindings
		//for the index, look in the map and add the component to the scene



		auto& scene = boop::SceneManager::GetInstance().AddScene(sceneName);
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
			for (const auto& colChar : rowLine)
			{
				// auto go = std::make_unique<boop::GameObject>();

				int index = colChar - '0';

				if (index < 0 || index > 9)
				{
					throw std::runtime_error(
						"Invalid digit: " + std::to_string(index) + " (character: " + colChar + ")"
					);
				}

				// Check if the component exists
				if (m_GameComponents.find(index) == m_GameComponents.end())
				{
					throw std::runtime_error(
						"Component not found for index: " + std::to_string(index) + " (character: " + colChar + ")"
					);
				}

				//go->AddComponent(goAdd.get());
				/*std::unique_ptr<boop::GameObject> goAdd = m_GameComponents.at(index)->Clone();
				goAdd->SetLocalPosition(static_cast<float>(gridSize * colsRead), static_cast<float>(gridSize * rowsRead));

				scene.Add(std::move(goAdd));*/
				if (index == 3)
				{
					int i = 0;
					i;
				}
				auto clonedObject = m_GameComponents.at(index)->Clone();
				clonedObject->SetLocalPosition(static_cast<float>(gridSize * colsRead), static_cast<float>(gridSize * rowsRead));

				scene.Add(std::move(clonedObject));

				//go->Clone(std::make_unique<boop::GameObject>(m_GameComponents.at(index)))



				/*LoadComponent toAddComp = m_AssignedComponents.at(index);
				if (!toAddComp.second)
				{
					throw std::runtime_error("Cannot add component to level");
				}

				go->AddMadeComp(GetCompClass(toAddComp));
				*/

				++colsRead;
			}

			++rowsRead;
			colsRead = 0;
		}

	}
}