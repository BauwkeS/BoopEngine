#include <stdexcept>
#include <SDL_ttf.h>
#include "../Renderer.h"
#include "../HelperFiles/Font.h"
#include "../HelperFiles/Texture2D.h"
#include <memory>
#include "TextComponent.h"
#include "../ResourceManager.h"

boop::TextComponent::TextComponent(boop::GameObject* const ownerPtr, const std::string& text,
	const std::string& font, unsigned int fontSize) :
	Component(ownerPtr),
	m_needsUpdate{ true },
	m_text{ text },
	m_textTexture{ nullptr }
{
	m_font = boop::ResourceManager::GetInstance().LoadFont(font, fontSize);
}

boop::TextComponent::~TextComponent()
{
}

boop::TextComponent::TextComponent(const TextComponent& other)
	:
	Component(other.GetOwner()),
	m_needsUpdate(other.m_needsUpdate),
	m_text(other.m_text),
	m_transform(other.m_transform)
{
	// Assuming that Font and Texture2D can be copied.
	if (other.m_font) {
		m_font = new Font(*other.m_font);
	}
	else {
		m_font = nullptr;
	}

	if (other.m_textTexture) {
		m_textTexture = std::make_unique<Texture2D>(*other.m_textTexture);
	}
	else {
		m_textTexture = nullptr;
	}
}

void boop::TextComponent::Update(float deltaTime)
{
	deltaTime = 1;
	if (m_needsUpdate)
	{
		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_unique<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void boop::TextComponent::Render() const
{
	if (m_textTexture != nullptr)
	{
		const auto& pos = m_transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void boop::TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void boop::TextComponent::SetPosition(const float x, const float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

boop::TextComponent::TextComponent()
	:
	Component(nullptr),
	m_needsUpdate{ true },
	m_text{ "" },
	m_textTexture{ nullptr }
{
	m_font = nullptr;
}