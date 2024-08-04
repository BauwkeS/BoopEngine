#include "SpriteComponent.h"

#include "GameObject.h"

namespace boop
{
	SpriteComponent::SpriteComponent(boop::GameObject* const ownerPtr, AnimatedTexture* const texture)
		: Component(ownerPtr)
	{
		m_pTexture = texture;

	}
	SpriteComponent::SpriteComponent(boop::GameObject* const ownerPtr, std::string texture, int cols, int rows, float frameSec, int startPicIndex, int AmountPics, float scale)
		: Component(ownerPtr)
	{
		m_pTexture = new AnimatedTexture(texture, cols, rows, frameSec, startPicIndex,  AmountPics, scale);

	}
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
