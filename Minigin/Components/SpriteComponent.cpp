#include "SpriteComponent.h"
#include "HelperFiles/Collision.h"
#include "GameObject.h"

namespace boop
{
	SpriteComponent::SpriteComponent()
		: Component(nullptr)
	{
		m_pTexture = nullptr;
		m_pCollision = nullptr;
	}

	SpriteComponent::SpriteComponent(boop::GameObject* const ownerPtr, AnimatedTexture* const texture, Collision* collision)
		: Component(ownerPtr)
	{
		m_pTexture = texture;
		m_pCollision = collision;
	}
	SpriteComponent::SpriteComponent(boop::GameObject* const ownerPtr, std::string texture, int cols, int rows, float frameSec, int startPicIndex, int AmountPics, float scale, Collision* collision)
		: Component(ownerPtr)
	{
		m_pTexture = new AnimatedTexture(texture, cols, rows, frameSec, startPicIndex,  AmountPics, scale);
		m_pCollision = collision;
	}

	SpriteComponent::~SpriteComponent()
	{
		delete m_pTexture;
		m_pTexture = nullptr;
		delete m_pCollision;
		m_pCollision = nullptr;
	}

	//void SpriteComponent::FixedUpdate(float deltaTime)
	//{
	//	deltaTime;
	//	/*if (m_pCollision)
	//	{
	//		auto result = m_pCollision->CheckCollision();
	//		result;
	//	}*/
	//}

	void SpriteComponent::Update(float deltaTime)
	{
		auto pos{ GetOwner()->GetWorldPosition() };

		m_pTexture->Update(deltaTime, pos);
	}
	void SpriteComponent::Render() const
	{
		m_pTexture->Render();
	}

	void SpriteComponent::SetTexture(AnimatedTexture* const texture)
	{
		m_pTexture = texture;
	}
}
