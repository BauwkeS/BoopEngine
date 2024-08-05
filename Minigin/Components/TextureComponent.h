#pragma once
#include <string>
#include "Component.h"
#include "HelperFiles/Texture2D.h"

namespace boop
{
	class TextureComponent final : public Component
	{
	public:
		TextureComponent(boop::GameObject* const ownerPtr, std::string texture);
		TextureComponent();
		~TextureComponent() = default;

		TextureComponent(const TextureComponent& other);
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void FixedUpdate(float deltaTime) override { deltaTime = 1; };
		void Update(float deltaTime) override { deltaTime = 1; };
		void LateUpdate(float deltaTime) override { deltaTime = 1; };
		void Render() const override;
	private:
		//std::unique_ptr<boop::Texture2D> m_TexturePtr;
		boop::Texture2D* m_TexturePtr{};
		std::string m_TextureString{};
	};
}

