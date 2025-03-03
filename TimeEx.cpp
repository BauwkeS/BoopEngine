#include "TimeEx.h"

#include <array>
#include <chrono>
#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <implot.h>
#include <vector>

//implot github info:
//https://github.com/epezent/implot

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

	ImPlot::CreateContext();

	//m_ArrEx1 = new int[m_TimingSizeEx1] {};
}

TimeExComp::~TimeExComp()
{
	//Imgui
	ImPlot::DestroyContext();

	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void TimeExComp::Update(float)
{
}

void TimeExComp::Render() const
{
	//Imgui--

	//Start
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();


	//Render items
	//ImGui::ShowDemoWindow();
	//ImPlot::ShowDemoWindow();


	//Exercise 1
	Ex1();


	/*ImGui::Begin("Exercise 2");
	ImGui::Text("This is window B");
	ImGui::End();*/

	//End
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_Renderer);
}

void TimeExComp::Ex1() const
{

	ImGui::Begin("Exercise 1");


	////input field for amount of samples
	static int m_SamplesEx1{ 10 };
	ImGui::InputInt("# samples", &m_SamplesEx1);

	//confirm button to generate ex 1
	static int clicked = 0;
	if (ImGui::Button("Trash the cache"))
		clicked++;
	if (clicked & 1)
	{
		ImGui::SameLine();
		ImGui::Text("My pc broke while making this, please check my seperate project");
	}
	//	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	//	{
	//		std::vector<long long> averages{};
	//		for (int i = 0; i < m_TimingSizeEx1; i++)
	//		{
	//			auto timeNow = std::chrono::high_resolution_clock::now();
	//			for (int j = 0; j < 1000000; j += stepsize)
	//				 m_ArrEx1[i] *= 2;
	//				//arr->data()[j] *= 2;

	//			auto timeEnd = std::chrono::high_resolution_clock::now();
	//			const auto delta = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeNow).count();
	//			averages.emplace_back(delta);
	//		}

	//		//delete top and bottom
	//		std::vector<long long>::iterator lowestVal = std::ranges::min_element(averages);
	//		averages.erase(lowestVal);
	//		std::vector<long long>::iterator highestVal = std::ranges::max_element(averages);
	//		averages.erase(highestVal);
	//		//long long endResult{};
	//		const int newSize = m_TimingSizeEx1 - 2;
	//		int calculations[4]{};
	//		for (int c = 0; c <= newSize; ++c)
	//		{
	//			calculations[c] = static_cast<int>(averages.data()[c]);
	//		}

	//		
	//		/*for (auto average : averages)
	//		{
	//			
	//		}*/
	//		//auto result = endResult / (ex1Amount - 2);

	//		//std::cout << stepsize << " : " << endResult/ (averageCheck-2) << std::endl;

	//		ImPlot::PlotLine("f(x)", timings, calculations, 1001);
	//	}

	//	ImPlot::EndPlot();
	//	clicked = 0;
	//}

	ImGui::End();
}

void TimeExComp::Ex2() const
{
	const int size{ 100000 };
	//auto arr = new std::array<GameObject3D , size>{};
	auto arr = new std::array<GameObject3DAlt, size>{};

	for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		std::vector<long long> averages{};
		int averageCheck = 15;
		for (int i = 0; i < averageCheck; i++)
		{
			auto timeNow = std::chrono::high_resolution_clock::now();
			for (int j = 0; j < size; j += stepsize)
				arr->data()[j].id *= 2;

			auto timeEnd = std::chrono::high_resolution_clock::now();
			const auto delta = std::chrono::duration_cast<std::chrono::microseconds>(timeEnd - timeNow).count();
			averages.emplace_back(delta);
		}

		//delete top and bottom
		std::vector<long long>::iterator lowestVal = std::ranges::min_element(averages);
		std::vector<long long>::iterator highestVal = std::ranges::max_element(averages);
		averages.erase(lowestVal);
		averages.erase(highestVal);
		long long endResult{};
		for (auto average : averages)
		{
			endResult += average;
		}

		//std::cout << stepsize << " : " << endResult / (averageCheck - 2) << std::endl;
	}
}
