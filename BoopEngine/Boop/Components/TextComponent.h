#pragma once
#include <string>
#include <memory>
#include "../GameObject.h"
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
		glm::vec3 m_position{};
		Font* m_font;
		std::unique_ptr<Texture2D> m_textTexture;

	public:
		void Update() override;
		void FixedUpdate() override { }
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
	};
}