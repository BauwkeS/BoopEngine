//#include <stdexcept>
//#include <SDL_ttf.h>
//#include "TextObject.h"
//#include "Renderer.h"
//#include "Font.h"
//#include "Texture2D.h"
//
//boop::TextObject::TextObject(const std::string& text, std::unique_ptr<Font>& font)
//	: m_needsUpdate(true), m_text(text), m_font(std::move(font)), m_textTexture(nullptr), Component(nullptr)
//{ }
//
//boop::TextObject::~TextObject()
//{
//}
//
//void boop::TextObject::Update(float deltaTime)
//{
//	if (m_needsUpdate)
//	{
//		const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
//		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
//		if (surf == nullptr) 
//		{
//			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
//		}
//		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
//		if (texture == nullptr) 
//		{
//			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
//		}
//		SDL_FreeSurface(surf);
//		m_textTexture = std::make_unique<Texture2D>(texture);
//		m_needsUpdate = false;
//	}
//}
//
//void boop::TextObject::Render() const
//{
//	if (m_textTexture != nullptr)
//	{
//		const auto& pos = m_transform.GetPosition();
//		Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
//	}
//}
//
//// This implementation uses the "dirty flag" pattern
//void boop::TextObject::SetText(const std::string& text)
//{
//	m_text = text;
//	m_needsUpdate = true;
//}
//
//void boop::TextObject::SetPosition(const float x, const float y)
//{
//	m_transform.SetPosition(x, y, 0.0f);
//}
//
//
