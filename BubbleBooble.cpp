#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "BubbleBooble.h"

#include "BoopEngine/Boop/Boop.h"
#include <msxml.h>
#include <utility>

#include "BoopEngine/Boop/Scene/LevelLoader.h"
#include "BoopEngine/Boop/Scene/SceneManager.h"
#include "BoopEngine/Boop/GameObject.h"
#include "BoopEngine/Boop/Components/TextureComponent.h"

namespace fs = std::filesystem;

void load()
{
	/*auto& scene = boop::SceneManager::GetInstance().AddScene("Demo");
	scene;*/
	//boop::GameObject* gameObjectPtr = nullptr;

	auto gameObjPtr =std::make_unique<boop::GameObject>();
	gameObjPtr->AddComponent(std::move(std::make_unique< boop::TextureComponent>(nullptr, "", 4.f)));
	level::LevelLoader::GetInstance().AssignGameObject(0, gameObjPtr.get());

	gameObjPtr = std::make_unique<boop::GameObject>();
	gameObjPtr->AddComponent(std::move(std::make_unique< boop::TextureComponent>(nullptr, "purpleBlock.png", 4.f)));
	level::LevelLoader::GetInstance().AssignGameObject(1, gameObjPtr.get());

	level::LevelLoader::GetInstance().CreateLevel("level1.txt", "Demo");

	//gameObjPtr->AddComponent(nullptr, "", 4);

	
	/*level::LevelLoader::GetInstance().AssignTextureComponent(0,
		nullptr, "", 4);
	level::LevelLoader::GetInstance().AssignTextureComponent(1,
		nullptr, "purpleBlock.png", 4);
	level::LevelLoader::GetInstance().AssignTextureComponent(2,
		nullptr, "stoneBlock.png", 4);
	level::LevelLoader::GetInstance().AssignSpriteComponent(3, nullptr, static_cast<std::string>("Avatar.png"), 7, 6, 0.2f, 0, 7, 4.f);
	
	level::LevelLoader::GetInstance().CreateLevelInScene("level1.txt", "Demo");*/

	boop::SceneManager::GetInstance().ChangeScene("Demo");


}

int main(int, char* []) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "../Data/";
#endif
	boop::Minigin engine(data_location);
	engine.Run(load);
	return 0;
	//boop::Minigin engine;
	//engine.Run();
	//return 0;
}
