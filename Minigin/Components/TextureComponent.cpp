#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"


boop::TextureComponent::TextureComponent(boop::GameObject* const ownerPtr, std::string texture) :
	Component(ownerPtr)
{
	m_TexturePtr = boop::ResourceManager::GetInstance().LoadTexture(texture);
}

boop::TextureComponent::TextureComponent() :
Component(nullptr)
{
	m_TexturePtr = nullptr;
}

void boop::TextureComponent::Render() const
{
	auto pos{ GetOwner()->GetWorldPosition() };
	boop::Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y);
}
