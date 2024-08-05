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
	public:
		virtual void FixedUpdate(float deltaTime);
		virtual void Update(float deltaTime);
		virtual void LateUpdate(float deltaTime);

		virtual void Render() const;

		void RemoveComponent(int componentIdx);
		void SetLocalPosition(float x, float y);

		GameObject() = default;
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

		void AddMadeComp(std::unique_ptr<Component> comp)
		{
			m_pComponents.emplace_back(std::move(comp));
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