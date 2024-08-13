#pragma once
#include <string>
#include <memory>
#include "../GameObject.h"
#include "../HelperFiles/Transform.h"
#include "../HelperFiles/Font.h"
#include "../HelperFiles/Texture2D.h"

namespace boop
{
	class Texture2D;
	class TextComponent : public Component
	{
	private:
		bool m_needsUpdate;
		std::string m_text;
		Transform m_transform{};
		Font* m_font;
		std::unique_ptr<Texture2D> m_textTexture;

	public:
		void Update(float deltaTime) override;
		void FixedUpdate(float) override { }
		void LateUpdate(float) override { }
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		TextComponent();
		TextComponent(boop::GameObject* const ownerPtr, const std::string& text = "NO TEXT GIVEN",
			const std::string& font = "Lingua.otf", unsigned int fontSize = 36);
		~TextComponent() override;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual std::unique_ptr<Component> Clone() const override
		{
			std::unique_ptr<TextComponent> spriteComponent
				= std::make_unique<TextComponent>(this->GetOwner(),
					m_text);
			return std::move(spriteComponent);
		}

	};
}