#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"


boop::TextureComponent::TextureComponent(boop::GameObject* const ownerPtr, std::string texture) :
	Component(ownerPtr),
	m_TextureString{texture}
{
	m_TexturePtr = boop::ResourceManager::GetInstance().LoadTexture(texture);
}

boop::TextureComponent::TextureComponent() :
Component(nullptr)
{
	m_TexturePtr = nullptr;
}

boop::TextureComponent::TextureComponent(const TextureComponent& other)
	: Component(other.GetOwner()),
	m_TextureString(other.m_TextureString)
{
	if (other.m_TexturePtr) {
		m_TexturePtr = new Texture2D(*other.m_TexturePtr);
	}
	else {
		m_TexturePtr = nullptr;
	}
}

void boop::TextureComponent::Render() const
{
	auto pos{ GetOwner()->GetWorldPosition() };
	boop::Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y);
}
