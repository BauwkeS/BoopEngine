#pragma once
#include <memory>
#include <iostream>
#include <vector>
#include "Components/Component.h"
#include "glm/vec2.hpp"

namespace boop
{
	class GameObject final
	{
	private:
		//Transform m_Transform{};
		std::vector<std::unique_ptr<boop::Component>> m_pComponents{};
		GameObject* m_pParent{};
		std::vector<std::unique_ptr<GameObject>> m_pChildren{};

		glm::vec2 m_LocalPosition{};
		glm::vec2 m_WorldPosition{};
		bool m_PositionIsDirty;

		bool m_ToDelete{ false };

		std::string m_Tag; //tag
		bool m_IsPersistent{ false }; //persistent = stays between levels

		//only used for private functions of SetParent
		void RemoveChild(GameObject* child);
		void AddChild(GameObject* child);
		bool IsChild(GameObject* parent) const;


		void UpdateWorldPosition();
		void SetPositionDirty();

	public:
		//TAG INFO
		void SetTag(const std::string& tag);
		const std::string& GetTag() const;
		void SetPersistent(bool isPersistent=true) { m_IsPersistent = isPersistent; }
		const bool& IsPersistent() const { return m_IsPersistent; }


		void FixedUpdate();
		void Update();

		void Render() const;

		void RemoveComponent(int componentIdx);
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec2& pos);

		GameObject() : m_pParent(nullptr), m_LocalPosition(glm::vec2{}), m_WorldPosition(glm::vec2{}), m_PositionIsDirty(false)
		{}
		//to-do add function to add gameobject with a parent
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//--

		void SetToDelete();
		bool ToDelete() const { return m_ToDelete; }
		void CleanupDeletion();

		//---

		void SetParent(GameObject* parent, bool keepWorldPosition= true);
		GameObject* GetParent() const { return m_pParent; }
		GameObject* GetChildAt(int index) const;
		
		const glm::vec2& GetWorldPosition();
		const glm::vec2& GetLocalPosition();
		
		const std::vector<std::unique_ptr<Component>>& GetAllComponents() const {
			return m_pComponents;
		}

		template <class T, typename... Args>
		//T* AddComponent(GameObject* owner, const Args&... args)
		T* AddComponent(const Args&... args)
		{
			static_assert(std::is_base_of<Component, T>(), "T needs to be derived from the Component class");

		/*	std::unique_ptr<T> pComponent{};

			if (owner == nullptr)
			{
				pComponent = std::make_unique<T>(this, args...);
			}
			else pComponent = std::make_unique<T>(owner, args...);*/

			//-- updated version:
			// Always use 'this' as the owner
			auto pComponent = std::make_unique<T>(this, args...);


			T* rawPtr = pComponent.get();
			m_pComponents.emplace_back(std::move(pComponent));

			return rawPtr;
		}

		Component* AddComponent(std::unique_ptr<Component> component) {
			if (!component) return nullptr;
			Component* rawPtr = component.get();
			m_pComponents.emplace_back(std::move(component));
			return rawPtr; // Return raw pointer for convenience
		}

		template <class T> 
		bool RemoveComponent();

		template <class T>
		T* GetComponent() const;

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

	
}
