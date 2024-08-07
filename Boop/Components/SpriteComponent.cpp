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
		if (collision)m_pCollision = collision;
		else m_pCollision = new Collision(m_pTexture->GetDstRect());
		
	}
	SpriteComponent::SpriteComponent(boop::GameObject* const ownerPtr, std::string texture, int cols, int rows, float frameSec, int startPicIndex, int AmountPics, float scale, Collision* collision)
		: Component(ownerPtr)
	{
		m_pTexture = new AnimatedTexture(texture, cols, rows, frameSec, startPicIndex, AmountPics, scale);
		if (collision)m_pCollision = collision;
		else m_pCollision = new Collision(m_pTexture->GetDstRect());
		
	}

	SpriteComponent::~SpriteComponent()
	{
		delete m_pTexture;
		m_pTexture = nullptr;
		
	}

	SpriteComponent::SpriteComponent(const SpriteComponent& other)
		: Component(other.GetOwner())
	{
		if (other.m_pTexture)
		{
			m_pTexture = new AnimatedTexture(*other.m_pTexture);
		}
		if(other.m_pCollision)
		{
			m_pCollision = new Collision(*other.m_pCollision);
		}
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
