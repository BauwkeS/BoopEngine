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
	class TextComponent final : public Component
	{
	private:
		bool m_needsUpdate;
		std::string m_text;
		Transform m_transform{};
		//std::unique_ptr<Font> m_font;
		Font* m_font;
		std::unique_ptr<Texture2D> m_textTexture;
		//boop::Texture2D* m_textTexture{};

	public:
		void Update(float deltaTime) override;
		void FixedUpdate(float deltaTime) override { deltaTime = 1; };
		void LateUpdate(float deltaTime) override { deltaTime = 1; };
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);
		TextComponent();
		TextComponent(boop::GameObject* const ownerPtr, const std::string& text = "NO TEXT GIVEN",
			const std::string& font = "Lingua.otf", unsigned int fontSize = 36);
		virtual ~TextComponent();
		TextComponent(const TextComponent& other);
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	};
}