#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "HelperFiles/TextObject.h"
#include "Scene.h"

#include <filesystem>
#include <Components/TextureComponent.h>
namespace fs = std::filesystem;

void load()
{
	auto& scene = boop::SceneManager::GetInstance().CreateScene("Demo");


	auto go = std::make_unique<boop::GameObject>();

	go->AddComponent<boop::TextureComponent>("background.tga");
	scene.Add(go);

	go = std::make_unique<boop::GameObject>();
	go->AddComponent<boop::TextureComponent>("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	/*go = std::make_unique<boop::GameObject>();
	go->AddComponent<boop::TextComponent>("Programming 4 Assignment");
	go->SetPosition(80, 30);
	scene.Add(go);

	go = std::make_unique<boop::GameObject>();
	go->AddComponent<boop::FPSComponent>();
	scene.Add(go);*/

	/*auto go = std::make_unique<boop::GameObject>();
	go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_unique<boop::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = boop::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_unique<boop::TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to)*/;
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
