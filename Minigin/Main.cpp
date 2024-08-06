#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
//#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

#include <glm/ext/scalar_constants.hpp>
#include "glm/vec3.hpp"

#include <filesystem>
#include <iostream>
#include <Components/TextureComponent.h>
#include <Components/TextComponent.h>
#include <Components/SpriteComponent.h>
#include <LevelLoader.h>
namespace fs = std::filesystem;

void load()
{
	//auto& scene = boop::SceneManager::GetInstance().AddScene("Demo");

	//boop::GameObject* gameObjectPtr = nullptr;
	
	level::LevelLoader::GetInstance().AssignSpriteComponent(0,
		nullptr, "purpleBlock.png",1,1,0,0,0,4);
	level::LevelLoader::GetInstance().AssignSpriteComponent(2,
		nullptr, "purpleBlock.png",1,1,0,0,0,4);
	level::LevelLoader::GetInstance().AssignSpriteComponent(1,
		nullptr, "stoneBlock.png",1,1,0,0,0,4);
	level::LevelLoader::GetInstance().CreateLevelInScene("level1.txt", "Demo");
	boop::SceneManager::GetInstance().ChangeScene("Demo");

	//auto go = std::make_unique<boop::GameObject>();

	// go->AddComponent<boop::TextureComponent>(nullptr,"BubbleBobbleLogo.png");
	/*scene.Add(std::move(go));
	go = std::make_unique<boop::GameObject>();
	go->AddComponent<boop::SpriteComponent>(nullptr, static_cast<std::string>("Avatar.png"), 7, 6, 0.2f, 0, 7, 4.f);
	go->SetLocalPosition(300.f, 300.f);*/
	//scene.Add(std::move(go));

	/*
	go = std::make_unique<boop::GameObject>();
	go->AddComponent<boop::TextureComponent>("logo.tga");
	go->SetLocalPosition(216, 180);

	go = std::make_unique<boop::GameObject>();
	go->AddComponent<boop::TextComponent>("Programming 4 Assignment");
	go->SetLocalPosition(80, 30);
	scene.Add(go);*/

	//go = std::make_unique<boop::GameObject>();

	
	//boop::AnimatedTexture texture{static_cast<std::string>("Avatar.png"), 7, 6, 0.2f, 0, 7, 4  };
	//go->AddComponent<boop::SpriteComponent>(nullptr, &texture);

	//FPS COMPONENT
	/*go = std::make_unique<boop::GameObject>();
	go->AddComponent<boop::FPSComponent>();
	scene.Add(go);*/

	//glm::vec3 center{ 200.f,200.f,0.f };
	//auto character{ std::make_unique<boop::GameObject>() };
	//character->AddComponent<boop::TextureComponent>("burger.png");
	//
	//auto charOrb{ std::make_unique <boop::GameObject>() };
	//charOrb->AddComponent<boop::TextureComponent>("burger.png");
	//charOrb->SetParent(character.get());
	//charOrb->SetLocalPosition(50, 50);

	//scene.Add(character);
	//scene.Add(charOrb);
	//charOrb = std::make_unique <boop::GameObject>();
	//charOrb->AddComponent<boop::TextureComponent>("burger.png");
	//charOrb->SetParent(character.get(), false);
	//scene.Add(charOrb);
	//charOrb = std::make_unique <boop::GameObject>();
	//charOrb->AddComponent<boop::TextureComponent>("burger.png");
	//charOrb->SetParent(character.get(), false);
	//scene.Add(charOrb);


	/*auto go = std::make_unique<boop::GameObject>();
	go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_unique<boop::GameObject>();
	go->SetTexture("logo.tga");
	go->SetLocalPosition(216, 180);
	scene.Add(go);

	auto font = boop::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_unique<boop::TextObject>("Programming 4 Assignment", font);
	to->SetLocalPosition(80, 20);
	scene.Add(to)*/
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	boop::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
