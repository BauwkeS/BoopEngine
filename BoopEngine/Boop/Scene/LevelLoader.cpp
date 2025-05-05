#include "LevelLoader.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <utility> 

#include "SceneManager.h"
#include "../Renderer.h"
#include "../GameObject.h"
#include "Scene.h"
#include "../Components/TextureComponent.h"


namespace level
{
	void LevelLoader::CreateLevel(std::string fileName, std::string sceneName)
	{
		//int windowHeight{};
		//int windowWidth{};

		//auto window = boop::Renderer::GetInstance().GetSDLWindow();
		//SDL_GetWindowSize(window, &windowWidth, &windowHeight);

		auto& scene = boop::SceneManager::GetInstance().AddScene(sceneName);
		std::ifstream gameFile("Data\\" + fileName);

		if (!gameFile.is_open())
		{
			throw std::runtime_error("Failed to open game file: " + fileName);
		}

		int colsRead = 0;
		int rowsRead = 0;
		float gridSize = 24;


		//fluid grid : to-do additions here
		//get file length to get columm size
		gameFile.seekg(0, gameFile.end);
		int fileLength = static_cast<int>(gameFile.tellg());
		gameFile.seekg(0, gameFile.beg);

		auto rowSize = std::count_if(std::istreambuf_iterator<char>{gameFile}, {}, [](char c) { return c == '\n'; });
		++rowSize; //add for last row that doesnt have an enter

		//rowSize = static_cast<float>(rowSize);
		float colSize = roundf(static_cast<float>(fileLength / rowSize));

		std::string rowLine;
		while (std::getline(gameFile, rowLine))
		{
			//fluid grid : to-do additions here
			// addition: size it with the game window size
			//colLine size
			



			//float widthToUse = gridSize * rowSize;
			//float heightToUse = gridSize * colSize;

			//how much space each grid NEEDS to take
			/*float perGridSizeX = widthToUse / gridSize;
			float perGridSizeY = heightToUse / gridSize;*/


			//how much space it will take now
			/*float gridBeingUsedX = widthToUse / rowSize;
			float gridBeingUsedY = heightToUse / colSize;*/

			//how much space it will take now
			//float scaleX = gridBeingUsedX / perGridSizeX;
			//float scaleX = (gridBeingUsedX > perGridSizeX) ? gridBeingUsedX/perGridSizeX  : gridBeingUsedX/ perGridSizeX;
			//float scaleY = (gridBeingUsedY > perGridSizeY) ? gridBeingUsedY/perGridSizeY  : gridBeingUsedY/ perGridSizeY;
			//float scaleY = gridBeingUsedY / perGridSizeY;

			//float offsetX = gridSize / rowSize;
			//float offsetY = gridSize / colSize;
			float offset = (colSize > rowSize) ? gridSize / colSize : gridSize / rowSize;
			//float offsetX = gridSize/widthToUse;
			//float offsetY = gridSize / heightToUse;
			offset = (roundf(offset * 10.f)) / 10.f;
			//offsetY = (round(offsetY * 10.f)) / 10.f;
			//scaleX = (roundf(scaleX * 10.f)) / 10.f;
			//scaleY = (roundf(scaleY * 10.f)) / 10.f;
			//offsetX = (roundf(offsetX * 10.f)) / 10.f;
			//offsetY = (roundf(offsetY * 10.f)) / 10.f;

			//size o fwidow / gridsize => amount per grid space
	
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
					
					/*auto x_pos = (gridSize/rowSize) * static_cast<float>(colsRead);
					auto y_pos = (gridSize / colSize) * static_cast<float>(rowsRead);
					newObj->SetLocalPosition(x_pos, y_pos);*/

					//if you have a texture, set it to the correct size
				/*	auto textureComp = newObj->GetComponent<boop::TextureComponent>();
					if (textureComp)
					{
						auto oldSize = textureComp->GetSize();
						if (oldSize.x != offset * gridSize)
						{
							textureComp->ResetSize(offset * gridSize, offset * gridSize);
						}
					}*/

					//	//auto scaleX = (oldSize.x > 0) ? (offset * gridSize) / oldSize.x : 1.f;
					//	//textureComp->SetScale(scaleX, scaleY);
					//	//textureComp->SetScale(offsetX, offsetY);
					//}

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