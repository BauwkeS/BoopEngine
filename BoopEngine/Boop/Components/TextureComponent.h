#pragma once
#include <string>
#include <memory>
#include "Component.h"
#include "../HelperFiles/Texture2D.h"
#include "SDL_rect.h"

namespace boop
{
	class Collision;

	class TextureComponent : public Component
	{
	public:
		TextureComponent(boop::GameObject* const ownerPtr, std::string texture, float scale=1);
		TextureComponent();
		~TextureComponent() = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void FixedUpdate(float deltaTime) override { deltaTime = 1; };
		void Update(float deltaTime) override { deltaTime = 1; };
		void LateUpdate(float deltaTime) override { deltaTime = 1; };
		void Render() const override;

		SDL_Rect GetTextureRect();

		virtual std::unique_ptr<Component> Clone() const override
		{
			std::unique_ptr<TextureComponent> spriteComponent
				= std::make_unique<TextureComponent>(this->GetOwner(),
					m_TextureString, m_Scale
					);
			return std::move(spriteComponent);
		}
	private:
		boop::Texture2D* m_TexturePtr{};
		std::string m_TextureString{};
		float m_Scale{};
	};
}

