#include <sstream>
#include <iomanip>
#include <format>
#include "FPSComponent.h"
#include "TextComponent.h"

boop::FPSComponent::FPSComponent(boop::GameObject* const ownerPtr) :
	Component(ownerPtr),
	m_TextCompPtr{ nullptr }
{
	GetOwner()->AddComponent<boop::TextComponent>();
	m_TextCompPtr = GetOwner()->GetComponent<boop::TextComponent>();
}

void boop::FPSComponent::Update(float deltaTime)
{
	m_AccuFrameTime += deltaTime;
	++m_NumFrameCalls;
	if (m_AccuFrameTime >= m_AvgSampleTime)
	{
		float currentFPS{ m_NumFrameCalls / m_AccuFrameTime };
		if (currentFPS == prevFPS)
			return;

		m_TextCompPtr->SetText(std::format("{:.1f}", currentFPS));

		m_AccuFrameTime = 0;
		m_NumFrameCalls = 0;
	}

}