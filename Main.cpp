//#if _DEBUG
//#if __has_include(<vld.h>)
//#include <vld.h>
//#endif
//#endif
//
//#include "BubbleBooble.h"
//
//#include "BoopEngine/Boop/Boop.h"
//
//namespace fs = std::filesystem;
//
//int main(int, char* []) {
//#if __EMSCRIPTEN__
//	fs::path data_location = "";
//#else
//	fs::path data_location = "./Data/";
//	if (!fs::exists(data_location))
//		data_location = "../Data/";
//#endif
//	boop::Minigin engine(data_location);
//	engine.Run(load);
//	return 0;
//	//boop::Minigin engine;
//	//engine.Run();
//	//return 0;
//}
