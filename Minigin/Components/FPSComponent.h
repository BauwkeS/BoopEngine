#pragma once
#include "Component.h"

namespace boop
{
	//add text component to owner, dont store it in this component
	//components should never own other components
	//results in no need to call text update/render
	class TextComponent;

	class FPSComponent final : public Component
	{
	public:
		FPSComponent(boop::GameObject* const ownerPtr);
		virtual ~FPSComponent() = default;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override { deltaTime = 1; };
		void LateUpdate(float deltaTime) override { deltaTime = 1; };
		void Render() const override {}
	private:
		TextComponent* m_TextCompPtr;
		float m_NumFrameCalls{};
		float m_AccuFrameTime{};
		float m_AvgSampleTime{ .2f };
		int m_DecimalPlaces{ 1 };
		float prevFPS{};
	};
}