#include "TimeEx.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <implot.h>

TimeExComp::TimeExComp(boop::GameObject* const ownerPtr)
	: Component(ownerPtr)
{
	const auto window = SDL_GL_GetCurrentWindow();
	m_Renderer = SDL_GetRenderer(window);
	//Imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui_ImplSDL2_InitForSDLRenderer(window, m_Renderer);
	ImGui_ImplSDLRenderer2_Init(m_Renderer);

	//ImPlot::CreateContext();
}

TimeExComp::~TimeExComp()
{
	//Imgui
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void TimeExComp::Update(float)
{
	////imgui input
	//SDL_Event e;
	//while (SDL_PollEvent(&e))
	//{
	//	//process event for IMGUI
	//	ImGui_ImplSDL2_ProcessEvent(&e);
	//}
}

void TimeExComp::Render() const
{
	//Imgui
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_Renderer);
}
