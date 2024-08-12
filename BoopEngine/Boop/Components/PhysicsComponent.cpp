#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "../GameObject.h"
#include "../Scene/SceneManager.h"
#include "../Scene/Scene.h"

namespace boop
{
	class CollisionComponent;

	PhysicsComponent::PhysicsComponent(GameObject* owner)
        : Component(owner)
    {
    }

    void PhysicsComponent::FixedUpdate(float deltaTime)
    {
        UpdatePhysics(deltaTime);
    }

    void PhysicsComponent::Update(float)
    {
    }

    void PhysicsComponent::LateUpdate(float)
    {
    }

    void PhysicsComponent::ApplyJump(float jumpForce)
    {
        if (jumpForce == 0) { m_IsJumping = false; }
        else
        {
            if (m_IsGrounded)
            {
                m_IsJumping = true;
                m_IsGrounded = false;
            }
            m_VerticalVelocity = jumpForce;
        }
    }

    std::unique_ptr<Component> PhysicsComponent::Clone() const
    {
        return std::make_unique<PhysicsComponent>(GetOwner());
    }

    void PhysicsComponent::UpdatePhysics(float deltaTime)
    {
        CheckGroundCollision();
        HandleVerticalMovement(deltaTime);
    }

    void PhysicsComponent::HandleVerticalMovement(float deltaTime)
    {
        // Apply gravity
        if (!m_IsGrounded && !m_IsJumping)
        {
            //m_VerticalVelocity += m_Gravity * deltaTime;
           m_VerticalVelocity = -200.f; //I want a linear fall speed
        }

        // Update position based on vertical velocity
        auto* owner = GetOwner();
        auto position = owner->GetWorldPosition();
        position.y -= (m_VerticalVelocity * deltaTime);

        // Update the position of the GameObject
        owner->SetLocalPosition(position);
    }

    void PhysicsComponent::CheckGroundCollision()
    {
        auto* owner = GetOwner();
        auto* collisionComp = owner->GetComponent<boop::CollisionComponent>();
        if (!collisionComp) return;

        SDL_Rect playerRect = collisionComp->GetCollisionRect();
        auto ownerPos = owner->GetWorldPosition();
        playerRect.x = static_cast<int>(ownerPos.x);
        playerRect.y = static_cast<int>(ownerPos.y);

        //get new rect with some padding for player
        SDL_Rect paddedRect = playerRect;
        ++paddedRect.w;
        ++paddedRect.h;

        float highestGroundY = std::numeric_limits<float>::lowest();
        m_IsGrounded = false;

        for (const auto& object : boop::SceneManager::GetInstance().GetActiveScene()->FindAllGameObjectByTag("Platform"))
        {
            auto* otherCollisionComp = object->GetComponent<boop::CollisionComponent>();
            if (!otherCollisionComp) continue;

            SDL_Rect otherRect = otherCollisionComp->GetCollisionRect();
            auto otherPos = object->GetWorldPosition();
            otherRect.x = static_cast<int>(otherPos.x);
            otherRect.y = static_cast<int>(otherPos.y);

            

            // Check if the player is falling onto the ground and intersecting
            bool isFallingOnto = m_VerticalVelocity <= 0 && playerRect.y + playerRect.h <= otherRect.y;
            bool isIntersecting = SDL_HasIntersection(&paddedRect, &otherRect);

          
            if (isIntersecting && isFallingOnto && otherRect.y > highestGroundY)
            {
                highestGroundY = static_cast<float>(otherRect.y);
                m_IsGrounded = true;
            }
        }

        if (m_IsGrounded)
        {
            // Adjust player's position to be on top of the ground
            owner->SetLocalPosition({ ownerPos.x, highestGroundY - playerRect.h, ownerPos.z });
            m_VerticalVelocity = 0;
        }
    }

}
