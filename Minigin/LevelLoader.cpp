#include "LevelLoader.h"

#include <cassert>
#include <iostream>
#include <fstream>

#include "SceneManager.h"
#include "GameObject.h"



namespace level
{

	LevelLoader::LevelLoader(std::string fileName, std::string compName)
		: m_FileName{fileName},
		m_ComponentFileName{compName}
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

	template <typename ComponentType, typename ... Args>
	ComponentType LevelLoader::ConvertTo(const std::string& txt, const Args&... args)
	{
		switch (txt)
		{
		case "Sprite":
			return boop::SpriteComponent
			break;
		}
	}

	template <class C, typename ... Args>
	void LevelLoader::AssignComponent(int index, const Args&... args)
	{
		//check if the index is not used already, if it is then assert

		for (const auto& item : m_AssignedComponents)
		{
			static_assert(item.first == index && "index already in use");
		}


		C* pComponent = C(args...);

		/*if (owner == nullptr)
		{
			pComponent = std::make_unique<T>(this, args...);
		}
		else pComponent = std::make_unique<T>(owner, args...);*/


		//pComponent->Initialize();

		//C* rawPtr = pComponent.get();
		//m_pComponents.emplace_back();

		m_AssignedComponents.insert(std::pair(index, pComponent));
	}

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
					auto toAddComp = m_AssignedComponents.at(colChar);
					if (!toAddComp) static_assert(true, "cannot add component to level");

					auto go = std::make_unique<boop::GameObject>();

					go->AddAlreadyMadeComponent<>(nullptr, toAddComp);

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
