#include "TextureComponent.h"
#include "../ResourceManager.h"
#include "../Renderer.h"
#include "../GameObject.h"


boop::TextureComponent::TextureComponent(boop::GameObject* const ownerPtr, std::string texture, float scale) :
	Component(ownerPtr),
	m_TextureString{texture},
	m_Scale{scale}
{
	if (!m_TextureString.empty())
	{
		m_TexturePtr = std::make_unique<Texture2D>(*boop::ResourceManager::GetInstance().LoadTexture(texture));
		//set the width and height from the texture created
		auto size = m_TexturePtr->GetSize();
		m_Width = static_cast<float>(size.x);
		m_Height = static_cast<float>(size.y);
	}
	else m_TexturePtr = nullptr;
}

void boop::TextureComponent::Render() const
{
	if (m_TexturePtr)
	{
		auto pos{ GetOwner()->GetWorldPosition() };

		boop::Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y, m_Scale, m_FlipTexture);
	}
}

SDL_Rect boop::TextureComponent::GetTextureRect() const
{
	SDL_Rect rectReturn{};
	if (m_TexturePtr)
	{
		auto pos{ GetOwner()->GetWorldPosition() };
		auto size = m_TexturePtr->GetSize();

		 rectReturn = SDL_Rect{ static_cast<int>(pos.x),static_cast<int>(pos.y),
			static_cast<int>(size.x * m_Scale),static_cast<int>(size.y * m_Scale) };
		
	}
	return rectReturn;
}

void boop::TextureComponent::ResetSize(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void boop::TextureComponent::ResetSize(float scale)
{
	m_Scale = scale;
}

void boop::TextureComponent::FlipTexture(flipTexture flip)
{
	m_FlipTexture = flip;
}

void boop::TextureComponent::FlipTextureDir(glm::vec2 dir)
{
	if (dir.x > 0)
	{
		m_FlipTexture={ false, false }; //right
	}
	else if (dir.x < 0)
	{
		m_FlipTexture={ true, false }; //left
	}
	if (dir.y > 0)
	{
		m_FlipTexture={ false, true }; //down
	}
	else if (dir.y < 0)
	{
		m_FlipTexture={ true, true }; //up
	}
}
