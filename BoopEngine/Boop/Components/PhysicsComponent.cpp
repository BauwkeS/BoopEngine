//#include "PhysicsComponent.h"
//#include "CollisionComponent.h"
//#include "../GameObject.h"
//#include "../Scene/SceneManager.h"
//#include "../Scene/Scene.h"
//
//namespace boop
//{
//	class CollisionComponent;
//
//	PhysicsComponent::PhysicsComponent(GameObject* owner)
//        : Component(owner)
//    {
//    }
//
//    void PhysicsComponent::FixedUpdate(float deltaTime)
//    {
//        UpdatePhysics(deltaTime);
//    }
//
//    void PhysicsComponent::Update(float)
//    {
//    }
//
//    void PhysicsComponent::LateUpdate(float)
//    {
//    }
//
//    void PhysicsComponent::ApplyJump(float jumpForce)
//    {
//        if (jumpForce == 0) { m_IsJumping = false; }
//        else
//        {
//            if (m_IsGrounded)
//            {
//                m_IsJumping = true;
//                m_IsGrounded = false;
//            }
//            m_VerticalVelocity = jumpForce;
//        }
//    }
//
//    std::unique_ptr<Component> PhysicsComponent::Clone() const
//    {
//        return std::make_unique<PhysicsComponent>(GetOwner());
//    }
//
//    void PhysicsComponent::UpdatePhysics(float deltaTime)
//    {
//        auto* collisionComp = GetOwner()->GetComponent<CollisionComponent>();
//        if (collisionComp)
//        {
//            m_IsGrounded = collisionComp->CheckGroundCollision();
//        }
//
//        HandleVerticalMovement(deltaTime);
//    }
//
//    void PhysicsComponent::HandleVerticalMovement(float deltaTime)
//    {
//        // Apply gravity
//        if (!m_IsGrounded && !m_IsJumping)
//        {
//            //m_VerticalVelocity += m_Gravity * deltaTime;
//           m_VerticalVelocity = -200.f; //I want a linear fall speed
//        }
//
//        // Update position based on vertical velocity
//        auto* owner = GetOwner();
//        auto position = owner->GetWorldPosition();
//        position.y -= (m_VerticalVelocity * deltaTime);
//
//        // Update the position of the GameObject
//        owner->SetLocalPosition(position);
//    }
//
//    
//
//}
