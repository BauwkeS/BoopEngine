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

void boop::GameObject::FixedUpdate()
{
	for (const std::unique_ptr<boop::Component>& component : m_pComponents)
	{
		if (!component) continue;
		if (component->ToDelete() || component->IsGhost()) continue;

		component->FixedUpdate();
	}

	for (const std::unique_ptr<boop::GameObject>& gameObj : m_pChildren)
	{
		if (!gameObj) continue;
		if (gameObj->ToDelete() || gameObj->IsGhost()) continue;

		gameObj->FixedUpdate();
	}
}

void boop::GameObject::Update()
{
	for (const std::unique_ptr<boop::Component>& component : m_pComponents)
	{
		if (!component) continue;
		if (component->ToDelete() || component->IsGhost()) continue;

		component->Update();
	}
	for (const std::unique_ptr<boop::GameObject>& gameObj : m_pChildren)
	{
		if (!gameObj) continue;
		if (gameObj->ToDelete() || gameObj->IsGhost()) continue;

		gameObj->Update();
	}
}

void boop::GameObject::Render() const
{
	for (const std::unique_ptr<boop::Component>& component : m_pComponents)
	{
		if (!component) continue;
		if (component->ToDelete() || component->IsGhost()) continue;

		component->Render();
	}
	for (const std::unique_ptr<boop::GameObject>& gameObj : m_pChildren)
	{
		if (!gameObj) continue;
		if (gameObj->ToDelete() || gameObj->IsGhost()) continue;

		gameObj->Render();
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
	SetLocalPosition(glm::vec2(x, y));

}

void boop::GameObject::SetLocalPosition(const glm::vec2& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}

void boop::GameObject::SetToDelete()
{
	m_ToDelete = true;

	//children and components are also deleted
	for (const std::unique_ptr<boop::Component>& component : m_pComponents)
	{
		if (!component)
			continue;

		component->SetToDelete();
	}
	for (const std::unique_ptr<boop::GameObject>& gameComp : m_pChildren)
	{
		if (!gameComp)
			continue;

		gameComp->SetToDelete();
	}
}

void boop::GameObject::SetParent(GameObject* parent, bool keepWorldPosition)
{
	if (IsChild(parent) || parent == this || m_pParent == parent)
		return; // Prevent setting as parent if it causes a cycle or self-parenting

	if (parent == nullptr)
	{
		SetLocalPosition(GetWorldPosition());
	}

	if (keepWorldPosition)
		SetLocalPosition(GetWorldPosition() - (parent ? parent->GetWorldPosition() : glm::vec2{}));
	SetPositionDirty();

	if (m_pParent)
		m_pParent->RemoveChild(this); // Remove from the current parent

	m_pParent = parent;

	if (m_pParent)
		m_pParent->AddChild(this);
}


void boop::GameObject::CleanupDeletion()
{
	//children and components are deleted
	for (int i = 0; i < m_pComponents.size(); ++i)
	{
		RemoveComponent(i);
	}
	for (const std::unique_ptr<boop::GameObject>& gameComp : m_pChildren)
	{
		if (!gameComp)
			continue;

		RemoveChild(gameComp.get());
	}
}

void boop::GameObject::SetAsGhost()
{
	m_IsGhost = !m_IsGhost; // Set the object as a ghost (not rendered, but still exists in the scene)
	for (const std::unique_ptr<boop::Component>& component : m_pComponents)
	{
		if (!component) continue;
		component->SetAsGhost(); // Recursively set all components as ghosts
	}
	for (const std::unique_ptr<boop::GameObject>& gameObj : m_pChildren)
	{
		if (!gameObj) continue;
		gameObj->SetAsGhost(); // Recursively set children as ghosts
	}
}

void boop::GameObject::RemoveChild(GameObject* child)  
{  
	auto it = std::ranges::remove_if(m_pChildren,  
	                                 [&](const std::unique_ptr<GameObject>& pChild) { return pChild.get() == child; }).begin();  
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
	return m_pChildren[index].get();
}

bool boop::GameObject::IsChild(GameObject* parent) const
{
	for (const auto& child : m_pChildren) {
		if (parent == child.get()) return true;
		if (!m_pChildren.empty()) {
			if (child->IsChild(parent)) return true;
		}
	}
	
	return false;
}

void boop::GameObject::SetPositionDirty()
{
	for (auto& child : m_pChildren) {
		child->SetPositionDirty(); //so all the children have it too
	}
	m_PositionIsDirty = true;
}

const glm::vec2& boop::GameObject::GetWorldPosition()
{
	if (m_PositionIsDirty) UpdateWorldPosition();
	return m_WorldPosition;
}

const glm::vec2& boop::GameObject::GetLocalPosition()
{
	return m_LocalPosition;
}

void boop::GameObject::UpdateWorldPosition()
{
	if (m_PositionIsDirty) {
		if (m_pParent == nullptr) m_WorldPosition = m_LocalPosition;
		else m_WorldPosition = m_pParent->GetWorldPosition() + m_LocalPosition;
	}
	m_PositionIsDirty = false;
}
