#include "TextureComponent.h"
#include "../ResourceManager.h"
#include "../Renderer.h"
#include "../GameObject.h"


boop::TextureComponent::TextureComponent(boop::GameObject* const ownerPtr, std::string texture,
	float scale) :
	Component(ownerPtr),
	m_TextureString{texture},
	m_Scale{scale}
{
	if (!m_TextureString.empty()) m_TexturePtr = std::make_unique<Texture2D>(*boop::ResourceManager::GetInstance().LoadTexture(texture));
	else m_TexturePtr = nullptr;
}

void boop::TextureComponent::Render() const
{
	if (m_TexturePtr)
	{
		auto pos{ GetOwner()->GetWorldPosition() };
		boop::Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y, m_Scale);
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
