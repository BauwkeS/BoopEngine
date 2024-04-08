#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

boop::GameObject::~GameObject() = default;

void boop::GameObject::Update(){}

void boop::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void boop::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void boop::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
