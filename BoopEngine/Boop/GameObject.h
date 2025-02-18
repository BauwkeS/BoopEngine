#pragma once
#include <memory>
#include <iostream>
#include <vector>
#include "Components/Component.h"
#include "glm/vec3.hpp"

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


		void FixedUpdate(float deltaTime);
		void Update(float deltaTime);
		void LateUpdate(float deltaTime);

		void Render() const;

		void RemoveComponent(int componentIdx);
		void SetLocalPosition(float x, float y);

		GameObject() : m_pParent(nullptr), m_LocalPosition(glm::vec3{}), m_WorldPosition(glm::vec3{}), m_PositionIsDirty(false)
		{}
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
		//original template from Mendel Debrabandere
		// -> has been modified/added on for my own project

		template <class T, typename... Args>
		T* AddComponent(GameObject* owner, const Args&... args)
		{
			static_assert(std::is_base_of<Component, T>(), "T needs to be derived from the Component class");

			std::unique_ptr<T> pComponent{};

			if (owner == nullptr)
			{
				pComponent = std::make_unique<T>(this, args...);
			}
			else pComponent = std::make_unique<T>(owner, args...);



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
			if (!comp->GetOwner()) {
				comp->SetOwner(this);
			}
			Component* rawPtr = comp.get();
			m_pComponents.emplace_back(std::move(comp));
			return rawPtr;
			
		}

		template <class T>
		bool RemoveComponent();

		template <class T>
		T* GetComponent() const;

		template <class T>
		bool HasComponent() const;


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
