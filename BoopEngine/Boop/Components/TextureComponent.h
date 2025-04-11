#pragma once
#include <string>
#include <memory>
#include "Component.h"
#include "../HelperFiles/Texture2D.h"
#include "SDL_rect.h"

namespace boop
{
	class TextureComponent : public Component
	{
	public:
		TextureComponent(boop::GameObject* const ownerPtr, std::string texture, float scale=1);
		~TextureComponent() override = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void FixedUpdate() override { }
		void Update() override { }
		void Render() const override;

		SDL_Rect GetTextureRect() const;

		glm::vec2 GetSize() const
		{
			return m_TexturePtr->GetSize();
		}
	private:
		std::unique_ptr<Texture2D> m_TexturePtr{};
		std::string m_TextureString{};
		float m_Scale{};
	};
}

