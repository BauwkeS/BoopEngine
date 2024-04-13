#pragma once
#include <string>
#include <memory>
#include <glm/ext/scalar_constants.hpp>
#include "glm/vec3.hpp"
#include "GameObject.h"
#include "HelperFiles/Transform.h"
#include "HelperFiles/Font.h"
#include "HelperFiles/Texture2D.h"

namespace boop
{
	class RotatorComponent final : public Component
	{
	private:
		float m_Angle{112};
		float m_Speed{};
		float m_Radius{};
		glm::vec3 m_Position{};

	public:
		void Update(float deltaTime) override {
			constexpr float fullCircle = 2 * glm::pi<float>();
			
			m_Angle += deltaTime * m_Speed;
			
			if (m_Angle > fullCircle) m_Angle =-fullCircle;

			const glm::vec3 position = glm::vec3(
				glm::cos(m_Angle) * m_Radius,
				glm::sin(m_Angle) * m_Radius, 0);
			
			GetOwner()->SetLocalPosition(m_Position + position);
		}
		void FixedUpdate(float deltaTime) override { deltaTime = 1; };
		void LateUpdate(float deltaTime) override { deltaTime = 1; };
		void Render() const override {};

		void SetAngle(float angle) { m_Angle = glm::radians(angle); }
		void SetPosition(glm::vec3 pos) { m_Position = pos; }

		RotatorComponent(boop::GameObject* const ownerPtr, float speed, float radius) :
			Component(ownerPtr), m_Speed{ speed }, m_Radius{ radius } {}
		virtual ~RotatorComponent() {};
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

	};
}