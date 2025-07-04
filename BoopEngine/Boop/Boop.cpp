#include <stdexcept>
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>

#if WIN32
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Boop.h"
#include "Input/InputManager.h"
#include "Scene/SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "DeltaTime.h"

SDL_Window* g_window{};

void LogSDLVersion(const std::string& message, const SDL_version& v)
{
#if WIN32
	std::stringstream ss;
	ss << message << (int)v.major << "." << (int)v.minor << "." << (int)v.patch << "\n";
	OutputDebugString(ss.str().c_str());
#else
	std::cout << message << (int)v.major << "." << (int)v.minor << "." << (int)v.patch << "\n";
#endif
}

#ifdef __EMSCRIPTEN__
#include "emscripten.h"

void LoopCallback(void* arg)
{
	static_cast<dae::Minigin*>(arg)->RunOneFrame();
}
#endif

//teacherss comment:
// Why bother with this? Because sometimes students have a different SDL version installed on their pc.
// That is not a problem unless for some reason the dll's from this project are not copied next to the exe.
// These entries in the debug output help to identify that issue.
void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	LogSDLVersion("We compiled against SDL version ", version);

	SDL_GetVersion(&version);
	LogSDLVersion("We linked against SDL version ", version);

	SDL_IMAGE_VERSION(&version);
	LogSDLVersion("We compiled against SDL_image version ", version);

	version = *IMG_Linked_Version();
	LogSDLVersion("We linked against SDL_image version ", version);

	SDL_TTF_VERSION(&version)
	LogSDLVersion("We compiled against SDL_ttf version ", version);

	version = *TTF_Linked_Version();
	LogSDLVersion("We linked against SDL_ttf version ", version);
}

boop::Minigin::Minigin(const std::filesystem::path &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);
	ResourceManager::GetInstance().Init(dataPath);
}

boop::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void boop::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;
	float fixedTimeStep{ 0.03333f }; //from Unity
	int msPerFrame{ 1000 / 165 };
	while (!m_quit)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		DeltaTime::GetInstance().SetDeltaTime(deltaTime);
		lastTime = currentTime;
		lag += deltaTime;

		m_quit = !InputManager::GetInstance().ProcessInput();
	
		while (lag >= fixedTimeStep)
		{
			SceneManager::GetInstance().FixedUpdate();
			lag -= fixedTimeStep;
		}
		SceneManager::GetInstance().Update();
		Renderer::GetInstance().Render();

		const auto sleepTime{ currentTime + std::chrono::milliseconds(msPerFrame) - std::chrono::high_resolution_clock::now() };

		std::this_thread::sleep_for(sleepTime);

	}
}

void boop::Minigin::RunOneFrame()
{
	
}
