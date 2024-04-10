#pragma once
#include <string>
#include <memory>
#include "Transform.h"

namespace boop
{
	class Texture2D;
	class GameObject 
	{
	public:
		virtual void FixedUpdate();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};
		//std::unique_ptr<Texture2D> m_texture{};
		Texture2D* m_texture{};
	};
}
