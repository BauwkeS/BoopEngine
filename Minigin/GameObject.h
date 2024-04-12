#pragma once
#include <memory>
#include <vector>
#include <concepts>
#include "HelperFiles/Transform.h"
#include "Components/Component.h"

namespace boop
{
	template<typename ComponentType>
	concept ComponentConcept = requires(ComponentType)
	{

		{ std::is_base_of<boop::Component, ComponentType>::value };
	};

	class GameObject final
	{
	private:
		//Transform m_Transform{};
		std::vector<std::unique_ptr<boop::Component>> m_pComponents;
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
		void SetPosition(float x, float y);

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		glm::vec3 GetPosition() const { return m_LocalPosition; }

		//---

		void SetParent(GameObject* parent, bool keepWorldPosition);
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
		//stolen template from Wannes -> to be improved by myself pls
		template <ComponentConcept ComponentType, typename... Args>
		void AddComponent(const Args&... args)
		{
			auto component{ std::make_unique<ComponentType>(this, args...) };
			bool componentAdded{ false };

			for (unsigned int compIdx = 0; compIdx < m_pComponents.size(); compIdx++)
			{
				if (m_pComponents[compIdx].get())
					continue;

				m_pComponents[compIdx] = std::move(component);
				componentAdded = true;
				break;
			}

			if (!componentAdded)
				m_pComponents.emplace_back(std::move(component));
		}


		template<ComponentConcept ComponentType>
		void RemoveComponent()
		{
			//use stl lib
			auto compPtr{ GetComponent<ComponentType>() };

			for (unsigned int compIdx = 0; compIdx < m_pComponents.size(); compIdx++)
			{
				if (m_pComponents[compIdx].get() != compPtr)
					continue;

				m_pComponents[compIdx].reset();
				return;
			}
		}

		template <ComponentConcept ComponentType>
		bool HasComponent()
		{
			//switch to using std::any_of
			for (int compIdx = 0; compIdx < m_pComponents.size(); compIdx++)
			{
				bool present{ dynamic_cast<ComponentType*>(m_pComponents[compIdx].get()) != nullptr };
				if (present)
					return true;
			}
			return false;
		}

		template <ComponentConcept ComponentType>
		ComponentType* const GetComponent()
		{
			//switch to using std::find_if
			for (unsigned int compIdx = 0; compIdx < m_pComponents.size(); compIdx++)
			{
				auto compPtr{ dynamic_cast<ComponentType*>(m_pComponents[compIdx].get()) };
				if (compPtr)
					return compPtr;
			}
			return nullptr;
		}
	};
}