#include "LevelLoader.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <utility> 

#include "SceneManager.h"
#include "../GameObject.h"
#include "Scene.h"


namespace level
{
	void LevelLoader::AssignGameObject(int index, std::unique_ptr<boop::GameObject> object, LevelLayer layer)
	{
		// Store the unique_ptr in the m_GameComponents map
		m_GameComponents.emplace(index, std::make_pair(std::move(object), layer));
	}

	//void LevelLoader::SetImportantTags(std::vector<std::string> tags)
	//{
	//	m_ImportantTags = std::move(tags);
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

		//components with a tag to load last:
		std::vector <std::unique_ptr<boop::GameObject>> renderLastComps{};

		std::string rowLine;
		while (std::getline(gameFile, rowLine))
		{
			for (const auto& colChar : rowLine)
			{

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

				//TO-DO
				if(index == 3)
				{
					int tset = 2;
					tset;
				}
				
				if (m_GameComponents.at(index).first.get())
				{
					auto clonedObject = std::move(m_GameComponents.at(index).first); //make clone function here
					clonedObject->SetLocalPosition(static_cast<float>(gridSize * colsRead), static_cast<float>(gridSize * rowsRead));

					/*		for (auto tag : m_ImportantTags)
					{
						if (clonedObject->GetTag() == tag) {
							renderLastComps.emplace_back(std::move(clonedObject));
							break;
						}

					}*/

					if(clonedObject) scene.Add(std::move(clonedObject));
				}
				
				//--
				++colsRead;
			}

			++rowsRead;
			colsRead = 0;
		}

		//now add the ones with important tags
		for (auto& renderLastComp : renderLastComps)
		{
			scene.Add(std::move(renderLastComp));
		}
	}
}