#pragma once
#include <memory>

namespace boop
{
	class GameObject;
	class Component
	{
	private:
		GameObject* m_pOwner{};

	protected:
		Component(GameObject* pOwner) : m_pOwner{ pOwner } {}
		GameObject* GetOwner() const { return m_pOwner; }

	public:
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		void FixedUpdate(float deltaTime) { deltaTime = 1; }
		void Update(float deltaTime) { deltaTime = 1; }
		void LateUpdate(float deltaTime) { deltaTime = 1; }
		virtual void Render() const=0;

		void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }
	};
}