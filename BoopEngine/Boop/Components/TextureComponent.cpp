#include "TextureComponent.h"
#include "../ResourceManager.h"
#include "../Renderer.h"
#include "../HelperFiles/Collision.h"
#include "../GameObject.h"


boop::TextureComponent::TextureComponent(boop::GameObject* const ownerPtr, std::string texture,
	float scale, bool automaticCollision, Collision* collision) :
	Component(ownerPtr),
	m_TextureString{texture},
	m_Scale{scale}
{
	if (texture != "") {
		m_TexturePtr = boop::ResourceManager::GetInstance().LoadTexture(texture);
		if(collision) m_pCollision = std::make_unique<Collision>(collision->GetCollisionRect());
		if (automaticCollision) {
			glm::vec3 pos{};
			if (GetOwner()) pos = GetOwner()->GetWorldPosition();
			auto size = m_TexturePtr->GetSize();
			SDL_Rect collisionRect = { static_cast<int>(pos.x),static_cast<int>(pos.y), size.x, size.y };

			m_pCollision = std::make_unique<Collision>(collisionRect);
		//	m_pCollision->SetCollisionRect(collisionRect);
		}

	}
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

	m_Scale = other.m_Scale;
	if(other.GetCollision()) m_pCollision = std::make_unique<Collision>(other.GetCollision()->GetCollisionRect());
}

void boop::TextureComponent::LateUpdate(float deltaTime)
{
	if (m_TexturePtr) {

	deltaTime;
	UpdateCollision();
	}
}

void boop::TextureComponent::Render() const
{
	if (m_TexturePtr)
	{
		auto pos{ GetOwner()->GetWorldPosition() };
		
		boop::Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y, m_Scale);
	}
}

void boop::TextureComponent::UpdateCollision()
{
	glm::vec3 pos{};
	if (GetOwner()) pos = GetOwner()->GetWorldPosition();
	auto size = m_TexturePtr->GetSize();
	SDL_Rect collisionRect = { static_cast<int>(pos.x),static_cast<int>(pos.y), size.x, size.y };
	m_pCollision->SetCollisionRect(collisionRect);
}
