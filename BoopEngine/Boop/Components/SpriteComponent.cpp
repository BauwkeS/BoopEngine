#include "SpriteComponent.h"
#include "../GameObject.h"

namespace boop
{
	SpriteComponent::SpriteComponent()
		: Component(nullptr)
	{
		m_pTexture = nullptr;
	}

	SpriteComponent::SpriteComponent(boop::GameObject* const ownerPtr, std::unique_ptr<AnimatedTexture> texture)
		: Component(ownerPtr)
	{
		m_pTexture = texture->Clone();
	
	}
	SpriteComponent::SpriteComponent(boop::GameObject* const ownerPtr, std::string texture, int cols, int rows, float frameSec, int startPicIndex, int AmountPics, float scale)
		: Component(ownerPtr)
	{
		m_pTexture = std::make_unique<AnimatedTexture>(texture, cols, rows, frameSec, startPicIndex, AmountPics, scale);

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

	void SpriteComponent::MoveSprite(glm::ivec2 pos)
	{
		m_MovingPos = pos;
	}

	SDL_Rect SpriteComponent::GetTextureRect()
	{
		return m_pTexture->GetDstRect();
	}
}
