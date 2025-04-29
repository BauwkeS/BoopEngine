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
	void LevelLoader::CreateLevel(std::string fileName, std::string sceneName)
	{
		auto& scene = boop::SceneManager::GetInstance().AddScene(sceneName);
		std::ifstream gameFile("Data\\" + fileName);

		if (!gameFile.is_open())
		{
			throw std::runtime_error("Failed to open game file: " + fileName);
		}

		int colsRead = 0;
		int rowsRead = 0;
		float gridSize = 30;

		//fluid grid : to-do additions here
		//get file length to get columm size
		gameFile.seekg(0, gameFile.end);
		int fileLength = static_cast<int>(gameFile.tellg());
		gameFile.seekg(0, gameFile.beg);

		std::string rowLine;
		while (std::getline(gameFile, rowLine))
		{
			//fluid grid : to-do additions here
			//colLine size
			float rowSize = static_cast<float>(rowLine.size()+1);
			float colSize = roundf(static_cast<float>(fileLength / rowSize));
			float offset = (colSize > rowSize) ? gridSize / colSize : gridSize / rowSize;
			offset = (roundf(offset * 10.f)) / 10.f;
	
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
				if (m_GameObjectTypes.find(index) == m_GameObjectTypes.end())
				{
					throw std::runtime_error(
						"Component not found for index: " + std::to_string(index) + " (character: " + colChar + ")"
					);
				}
				
				if (m_GameObjectTypes.at(index).first.get())
				{
					auto newObj = m_GameObjectTypes.at(index).first->Instantiate();

					//fluid grid : to-do additions here
					auto x_pos = (offset * gridSize) * static_cast<float>(colsRead);
					auto y_pos = (offset * gridSize) * static_cast<float>(rowsRead);
					newObj->SetLocalPosition(x_pos, y_pos);

					switch (m_GameObjectTypes.at(index).second)
					{
					case LevelLayer::STATIC:
						m_StaticObjects.emplace_back(std::move(newObj));
						break;
					case LevelLayer::DYNAMIC:
						m_DynamicObjects.emplace_back(std::move(newObj));
						break;
					case LevelLayer::PERSISTENT:
						m_PersistentObjects.emplace_back(std::move(newObj));
						if (m_UnderpersistentIndex != -1)
						{
							//put object behind persistent objects if needed
							auto extraObj = m_GameObjectTypes.at(m_UnderpersistentIndex).first->Instantiate();
							extraObj->SetLocalPosition(x_pos, y_pos);
							m_StaticObjects.emplace_back(std::move(extraObj));
						}
						break;
					}

				}
				
				//--
				++colsRead;
			}

			++rowsRead;
			colsRead = 0;
		}

		//now add everything in order of what is needed
		for (auto& staticComp : m_StaticObjects)
		{
			scene.Add(std::move(staticComp));
		}
		for (auto& dynamicComp : m_DynamicObjects)
		{
			scene.Add(std::move(dynamicComp));
		}
		for (auto& persistentComp : m_PersistentObjects)
		{
			scene.Add(std::move(persistentComp),true);
		}
		ClearVectors();
	}
}