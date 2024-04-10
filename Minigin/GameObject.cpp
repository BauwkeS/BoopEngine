#include <stdexcept>
#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <Components/Component.h>

void boop::GameObject::FixedUpdate(float deltaTime)
{
	for (const std::unique_ptr<boop::Component>& component : m_pComponents)
	{
		if (!component)
			continue;

		component->FixedUpdate(deltaTime);
	}
}

void boop::GameObject::Update(float deltaTime)
{
	for (const std::unique_ptr<boop::Component>& component : m_pComponents)
	{
		if (!component)
			continue;

		component->Update(deltaTime);
	}
}

void boop::GameObject::LateUpdate(float deltaTime)
{
	for (const std::unique_ptr<boop::Component>& component : m_pComponents)
	{
		if (!component)
			continue;

		component->LateUpdate(deltaTime);
	}
}

void boop::GameObject::Render() const
{
	for (const std::unique_ptr<boop::Component>& component : m_pComponents)
	{
		if (!component)
			continue;

		component->Render();
	}
}

void boop::GameObject::RemoveComponent(int componentIdx)
{
	if (m_pComponents.size() < componentIdx)
		throw std::runtime_error(std::string("Invalid component idx for removal"));

	m_pComponents[componentIdx].reset();
}

void boop::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}