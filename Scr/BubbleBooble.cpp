#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "BubbleBooble.h"

#include "../BoopEngine/Boop/Boop.h"
#include <msxml.h>
#include <utility>

#include "GameLoader.h"

namespace fs = std::filesystem;

void load()
{
	booble::GameLoader::GetInstance().MakeGame();
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
