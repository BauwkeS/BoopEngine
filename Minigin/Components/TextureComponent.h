#pragma once
#include <string>
#include "Component.h"
#include "Texture2D.h"

namespace boop
{
	class TextureComponent final : public Component
	{
	public:
		TextureComponent(boop::GameObject* const ownerPtr, std::string texture);
		~TextureComponent() = default;

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void Render() const override;
	private:
		//std::unique_ptr<boop::Texture2D> m_TexturePtr;
		boop::Texture2D* m_TexturePtr{};
	};
}

