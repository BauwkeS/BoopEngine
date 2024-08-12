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
        if (m_IsGrounded)
        {
            m_IsJumping = true;
            m_IsGrounded = false;
        }
		m_VerticalVelocity = jumpForce;
        if (jumpForce == 0) m_IsJumping = false;
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
        //const auto* collisionComp = GetOwner()->GetComponent<CollisionComponent>();
        //if (!collisionComp)
        //    return;

        //// Check collision with platforms
        //const auto platform = collisionComp->CheckCollision("Platform");
        //if (platform)
        //{
        //    const auto& [platformPos, platformRect] = std::tuple{ platform->GetWorldPosition(), platform->GetComponent<CollisionComponent>()->GetCollisionRect() };
        //    const auto& ownPos = GetOwner()->GetWorldPosition();

        //    // Adjust player's position to be on top of the platform
        //    GetOwner()->SetLocalPosition({ ownPos.x, platformPos.y - platformRect.h, ownPos.z });

        //    m_IsGrounded = true;
        //    m_VerticalVelocity = 0.0f;
        //    return;
        //}

        //// Fallback to ground level at y = 0 if no platform collision detected
        //if (GetOwner()->GetWorldPosition().y >= 0.0f)
        //{
        //    auto pos = GetOwner()->GetWorldPosition();
        //    pos.y = 0.0f;
        //    GetOwner()->SetLocalPosition(pos);

        //    m_IsGrounded = true;
        //    m_VerticalVelocity = 0.0f;
        //}
        //else
        //{
        //    m_IsGrounded = false;
        //}


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

        for (const auto& object : boop::SceneManager::GetInstance().GetActiveScene()->FindAllGameObjectByTag("Wall"))
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

        //auto* owner = GetOwner();
        //auto* collisionComp = owner->GetComponent<boop::CollisionComponent>();
        //if (!collisionComp) return;

        //SDL_Rect playerRect = collisionComp->GetCollisionRect();
        //auto ownerPos = owner->GetWorldPosition();
        //playerRect.x = static_cast<int>(ownerPos.x);
        //playerRect.y = static_cast<int>(ownerPos.y);

        //float closestGroundY = std::numeric_limits<float>::max();
        //m_IsGrounded = false;

        //for (const auto& object : boop::SceneManager::GetInstance().GetActiveScene()->FindAllGameObjectByTag("Wall"))
        //{
        //    auto* otherCollisionComp = object->GetComponent<boop::CollisionComponent>();
        //    if (!otherCollisionComp) continue;

        //    SDL_Rect otherRect = otherCollisionComp->GetCollisionRect();
        //    auto otherPos = object->GetWorldPosition();
        //    otherRect.x = static_cast<int>(otherPos.x);
        //    otherRect.y = static_cast<int>(otherPos.y);

        //    bool isFallingOnto = m_VerticalVelocity >= 0 && playerRect.y + playerRect.h >= otherRect.y;
        //    bool isIntersecting = SDL_HasIntersection(&playerRect, &otherRect);

        //    //if (isIntersecting && isFallingOnto && otherRect.y > closestGroundY)
        //    if (isIntersecting && isFallingOnto && otherRect.y < closestGroundY)
        //    {
        //        closestGroundY = static_cast<float>(otherRect.y) - playerRect.h;
        //        m_IsGrounded = true;
        //    }
        //}

        //if (m_IsGrounded)
        //{
        //    owner->SetLocalPosition({ ownerPos.x, closestGroundY, ownerPos.z });
        //    m_VerticalVelocity = 0;
        //}
    }

}
