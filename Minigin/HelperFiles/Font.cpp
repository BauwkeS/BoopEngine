#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* boop::Font::GetFont() const {
	return m_font;
}

boop::Font::Font(const std::string& fullPath, unsigned int size) : m_font(nullptr),
m_Path{fullPath}, m_Size{size}
{
	m_font = TTF_OpenFont(fullPath.c_str(), size);
	if (m_font == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

boop::Font::~Font()
{
	TTF_CloseFont(m_font);
}

boop::Font::Font(const Font& other)
    : Font(other.m_Path, other.m_Size)
{
}