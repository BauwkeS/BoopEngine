#include <stdexcept>
#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

void boop::GameObject::SetTag(const std::string& tag)
{
	m_Tag = tag;
}

const std::string& boop::GameObject::GetTag() const
{
	return m_Tag;
}

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

void boop::GameObject::SetLocalPosition(float x, float y)
{
	//m_Transform.SetLocalPosition(x, y, 0.0f);
	//m_LocalPosition = glm::vec3(x, y, 0.0f);
	SetLocalPosition(glm::vec3(x, y, 0.0f));

}

void boop::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}

//void boop::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
//{
//	if (IsChild(parent) || parent == this || m_pParent == parent) return;
//
//	if (parent == nullptr) SetLocalPosition(GetWorldPosition());
//	else {
//		if (keepWorldPosition) SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
//		SetPositionDirty();
//	}
//
//	if (m_pParent) m_pParent->RemoveChild(this);
//	m_pParent = parent;
//	if (m_pParent) m_pParent->AddChild(this);
//}
void boop::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (parent == nullptr || IsChild(parent) || parent == this || m_pParent == parent)
		return; // Prevent setting as parent if it causes a cycle or self-parenting

	if (keepWorldPosition)
		SetLocalPosition(GetWorldPosition() - (parent ? parent->GetWorldPosition() : glm::vec3{}));
	SetPositionDirty();

	if (m_pParent)
		m_pParent->RemoveChild(this); // Remove from the current parent

	m_pParent = parent;

	if (m_pParent)
		m_pParent->AddChild(this);
}


//void boop::GameObject::RemoveChild(GameObject* child)
//{
//	//m_pChildren.erase(std::remove(m_pChildren.begin(), m_pChildren.end(), child), m_pChildren.end());
//	std::erase(m_pChildren, child);
//}
void boop::GameObject::RemoveChild(GameObject* child)
{
	auto it = std::remove(m_pChildren.begin(), m_pChildren.end(), child);
	if (it != m_pChildren.end())
	{
		m_pChildren.erase(it, m_pChildren.end());
	}
}


void boop::GameObject::AddChild(GameObject* child)
{
	m_pChildren.emplace_back(child);
}

boop::GameObject * boop::GameObject::GetChildAt(int index) const
{
	return m_pChildren[index];
}

bool boop::GameObject::IsChild(GameObject* parent) const
{
	for (auto child : m_pChildren) {
		if (parent == child) return true;
		if (m_pChildren.size() > 0) {
			if (child->IsChild(parent)) return true;
		}
	}
	
	return false;
}

void boop::GameObject::SetPositionDirty()
{
	for (auto child : m_pChildren) {
		child->SetPositionDirty(); //so all the children have it too
	}
	m_PositionIsDirty = true;
}

const glm::vec3& boop::GameObject::GetWorldPosition()
{
	// TODO: insert return statement here
	if (m_PositionIsDirty) UpdateWorldPosition();
	return m_WorldPosition;
}

void boop::GameObject::UpdateWorldPosition()
{
	if (m_PositionIsDirty) {
		if (m_pParent == nullptr) m_WorldPosition = m_LocalPosition;
		else m_WorldPosition = m_pParent->GetWorldPosition() + m_LocalPosition;
	}
	m_PositionIsDirty = false;
}
