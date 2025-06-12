#pragma once

namespace boop
{
	class GameObject;
	class Component
	{
	private:
		GameObject* m_pOwner{};
		bool m_ToDelete{ false };
		bool m_IsGhost{ false };

	protected:
		Component(GameObject* pOwner) :
			m_pOwner{ pOwner } {}

	public:
		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void FixedUpdate() =0;
		virtual void Update() = 0;
		virtual void Render() const = 0;

		//deletion
		bool ToDelete() const { return m_ToDelete; }
		void SetToDelete() { m_ToDelete = true; }
		//ghost
		bool IsGhost() const { return m_IsGhost; }
		void SetAsGhost() { m_IsGhost = !m_IsGhost; }

		GameObject* GetOwner() const { return m_pOwner; }
	};
}