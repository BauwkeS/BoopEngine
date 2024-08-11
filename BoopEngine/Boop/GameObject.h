#pragma once
#include <memory>
#include <iostream>
#include <vector>
#include <concepts>
#include "HelperFiles/Transform.h"
#include "Components/Component.h"

namespace boop
{
	class GameObject final
	{
	private:
		//Transform m_Transform{};
		std::vector<std::unique_ptr<boop::Component>> m_pComponents{};
		GameObject* m_pParent{};
		std::vector<GameObject*> m_pChildren{};

		glm::vec3 m_LocalPosition{};
		glm::vec3 m_WorldPosition{};
		bool m_PositionIsDirty;

		std::string m_Tag; //tag
	public:
		//TAG INFO
		void SetTag(const std::string& tag);
		const std::string& GetTag() const;


		virtual void FixedUpdate(float deltaTime);
		virtual void Update(float deltaTime);
		virtual void LateUpdate(float deltaTime);

		virtual void Render() const;

		void RemoveComponent(int componentIdx);
		void SetLocalPosition(float x, float y);

		GameObject() : m_pParent(nullptr), m_LocalPosition(glm::vec3{}), m_WorldPosition(glm::vec3{}), m_PositionIsDirty(false)
		{};
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//---

		void SetParent(GameObject* parent, bool keepWorldPosition= true);
		void RemoveChild(GameObject* child);
		void AddChild(GameObject* child);
		GameObject* GetParent() const { return m_pParent; }
		GameObject* GetChildAt(int index) const;
		bool IsChild(GameObject* parent) const;
		void SetPositionDirty();
		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetWorldPosition();
		void UpdateWorldPosition();

		//--
		//stolen template from Mendel Debrabandere -> to be improved by myself pls

		template <class T, typename... Args>
		T* AddComponent(GameObject* owner, const Args&... args)
		{
			static_assert(std::is_base_of<Component, T>(), "T needs to be derived from the Component class");


		/*	if (HasComponent<T>())
			{
				std::cout << "Trying to add an already existing component\n";
				return nullptr;
			}*/

			std::unique_ptr<T> pComponent{};

			if (owner == nullptr)
			{
				pComponent = std::make_unique<T>(this, args...);
			}
			else pComponent = std::make_unique<T>(owner, args...);


			//pComponent->Initialize();

			T* rawPtr = pComponent.get();
			m_pComponents.emplace_back(std::move(pComponent));

			return rawPtr;
		}
		template <typename T>
		T* AddComponent(std::unique_ptr<T> component) {
			static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");

			T* rawPtr = component.get();
			component->SetOwner(this);
			m_pComponents.emplace_back(std::move(component));
			return rawPtr;
		}

		Component* AddMadeComp(std::unique_ptr<Component> comp)
		{
			/*if (comp->GetOwner())
			{
				auto raw = comp.get();
				m_pComponents.emplace_back(std::move(comp));
				return(raw);
			}
			else {
				comp->SetOwner(this);
				auto raw = comp.get();
				m_pComponents.emplace_back(std::move(comp));
				return(raw);
			}*/
			if (!comp->GetOwner()) {
				comp->SetOwner(this);
			}
			Component* rawPtr = comp.get();
			m_pComponents.emplace_back(std::move(comp));
			return rawPtr;
			
		}

		////template <class T>
		//void AddAlreadyMadeComponent(GameObject* owner, Component* comp)
		//{
		////	static_assert(std::is_base_of<Component, T>(), "T needs to be derived from the Component class");


		///*	if (HasComponent<T>())
		//	{
		//		std::cout << "Trying to add an already existing component\n";
		//		return nullptr;
		//	}*/

		//	std::unique_ptr<decltype(comp)> pComponent = std::make_unique<decltype(comp)>(comp);

		//	if (owner == nullptr) 
		//	{
		//		pComponent->SetOwner(this);
		//	}
		//	else pComponent->SetOwner(owner);


		//	//pComponent->Initialize();

		//	//T* rawPtr = pComponent.get();
		//	m_pComponents.emplace_back(std::move(pComponent));

		//	//return rawPtr;
		//}

		template <class T>
		bool RemoveComponent();

		template <class T>
		T* GetComponent() const;

		template <class T>
		bool HasComponent() const;


		//----
	//Clone function
		std::unique_ptr<GameObject> Clone() const
		{
			auto clonedObject = std::make_unique<GameObject>();

			// Copy all relevant data
			clonedObject->m_LocalPosition = this->m_LocalPosition;
			clonedObject->m_WorldPosition = this->m_WorldPosition;
			clonedObject->m_PositionIsDirty = this->m_PositionIsDirty;

			if (!this->m_Tag.empty()) clonedObject->m_Tag = this->m_Tag;

			// Clone components
			for (const auto& component : m_pComponents) {
				if (component) {
					clonedObject->AddComponent(component->Clone());
				}
			}
			// Handle parent-child relationships
			if (m_pParent) {
				clonedObject->SetParent(m_pParent, true);  // Assuming you want to keep the world position
			}
			for (auto* child : m_pChildren) {
				auto clonedChild = child->Clone();
				clonedChild->SetParent(clonedObject.get(), true); // Re-establish parent-child relationships
				clonedObject->AddChild(clonedChild.get());
			}

			//return std::move(clonedObject);
			return clonedObject;
		}

	};

	template <class T>
	inline bool GameObject::RemoveComponent()
	{
		static_assert(std::is_base_of<Component, T>(), "T needs to be derived from the Component class");

		for (auto it = m_pComponents.begin(); it != m_pComponents.end(); ++it)
		{
			if (dynamic_cast<T*>(it->get()) != nullptr)
			{
				m_pComponents.erase(it);
				return true;
			}
		}
		return false;
	}

	template<class T>
	inline T* boop::GameObject::GetComponent() const
	{
		static_assert(std::is_base_of<Component, T>(), "T needs to be derived from the Component class");

		for (const auto& component : m_pComponents)
		{
			if (dynamic_cast<T*>(component.get()))
				return dynamic_cast<T*>(component.get());
		}

		return nullptr;
	}

	template <class T>
	inline bool boop::GameObject::HasComponent() const
	{
		static_assert(std::is_base_of<Component, T>(), "T needs to be derived from the Component class");

		for (const auto& component : m_pComponents)
		{
			if (dynamic_cast<T*>(component.get()))
				return true;
		}
		return false;
	}

	
}