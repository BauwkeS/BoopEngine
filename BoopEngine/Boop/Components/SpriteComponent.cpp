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
		//TO-DO FIX THIS
		//m_pTexture = texture->Clone();
		m_pTexture = std::move(texture);
	
	}
	SpriteComponent::SpriteComponent(boop::GameObject* const ownerPtr, std::string texture, int cols, int rows, float frameSec, int startPicIndex, int AmountPics, float scale)
		: Component(ownerPtr)
	{
		m_pTexture = std::make_unique<AnimatedTexture>(texture, cols, rows, frameSec, startPicIndex, AmountPics, scale);

	}
	void SpriteComponent::Update()
	{
		auto pos{ GetOwner()->GetWorldPosition() };
		m_pTexture->Update(pos);
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
