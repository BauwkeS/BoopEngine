#pragma once
#include <string>
#include "Component.h"
#include "HelperFiles/Texture2D.h"

namespace boop
{
	class SpriteComponent final : public Component
	{
	public:
		SpriteComponent(boop::GameObject* const ownerPtr, std::string texture);
		~SpriteComponent() = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void FixedUpdate(float deltaTime) override { deltaTime = 1; };
		void Update(float deltaTime) override { deltaTime = 1; };
		void LateUpdate(float deltaTime) override { deltaTime = 1; };
		void Render() const override;
	private:
		//std::unique_ptr<boop::Texture2D> m_TexturePtr;
		boop::Texture2D* m_TexturePtr{};

		//Class to use for animated sprites -> you will need:
		// - texture in texture class
	};
}

