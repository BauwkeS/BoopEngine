#include "TextureComponent.h"
#include "../ResourceManager.h"
#include "../Renderer.h"
#include "../HelperFiles/Collision.h"
#include "../GameObject.h"


boop::TextureComponent::TextureComponent(boop::GameObject* const ownerPtr, std::string texture,
	float scale) :
	Component(ownerPtr),
	m_TextureString{texture},
	m_Scale{scale}
{
	m_TexturePtr = boop::ResourceManager::GetInstance().LoadTexture(texture);
	//m_pCollision = collision;
	//if (automaticCollision) {
	//	auto pos = GetOwner()->GetWorldPosition();
	//	auto size = m_TexturePtr->GetSize();
	//	SDL_Rect collisionRect = { static_cast<int>(pos.x),static_cast<int>(pos.y), size.x, size.y };

	//	//m_pCollision = new Collision(collisionRect);
	//}
}

boop::TextureComponent::TextureComponent() :
Component(nullptr)
{
	m_TexturePtr = nullptr;
}
//
//boop::TextureComponent::TextureComponent(const TextureComponent& other)
//	: Component(other.GetOwner()),
//	m_TextureString(other.m_TextureString)
//{
//	if (other.m_TexturePtr) {
//		m_TexturePtr = new Texture2D(*other.m_TexturePtr);
//	}
//	else {
//		m_TexturePtr = nullptr;
//	}
//
//	m_Scale = other.m_Scale;
//}

void boop::TextureComponent::Render() const
{
	if (m_TexturePtr)
	{
		auto pos{ GetOwner()->GetWorldPosition() };
		boop::Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y, m_Scale);
	}
}

SDL_Rect boop::TextureComponent::GetTextureRect()
{
	SDL_Rect rectReturn{};
	if (m_TexturePtr)
	{
		auto pos{ GetOwner()->GetWorldPosition() };
		auto size = m_TexturePtr->GetSize();
		rectReturn = SDL_Rect{ static_cast<int>(pos.x),static_cast<int>(pos.y),size.x,size.y };
	}
	return rectReturn;
}
