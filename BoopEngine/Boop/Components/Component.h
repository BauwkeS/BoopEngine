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
		Component(GameObject* pOwner) :
			m_pOwner{ pOwner } {}

	public:
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void FixedUpdate(float deltaTime) =0;
		virtual void Update(float deltaTime) = 0;
		virtual void LateUpdate(float deltaTime) = 0;
		virtual void Render() const = 0;

		void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }
			GameObject* GetOwner() const { return m_pOwner; }

			virtual std::unique_ptr<Component> Clone() const = 0;
	};
}