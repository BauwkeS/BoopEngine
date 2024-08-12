#pragma once

#include "Component.h"
#include "glm/vec3.hpp"

namespace boop
{
    class PhysicsComponent : public Component
    {
    public:
        explicit PhysicsComponent(GameObject* owner);

        void FixedUpdate(float deltaTime) override;
        void Update(float deltaTime) override;
        void LateUpdate(float deltaTime) override;
        void Render() const override {}

        void ApplyJump(float jumpStrength);
        bool IsOnGround()
        {
	        return m_IsGrounded;
        }

        std::unique_ptr<Component> Clone() const override;

    private:
        bool m_IsGrounded{ true };
        bool m_IsJumping{ false };
        float m_VerticalVelocity{ 0.0f };
        //const float m_Gravity{ -98.1f };

        void UpdatePhysics(float deltaTime);
        void CheckGroundCollision();
        void HandleVerticalMovement(float deltaTime);
    };
}
