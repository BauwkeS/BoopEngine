#include <SDL.h>
#include "Texture2D.h"

#include <stdexcept>

#include "../Renderer.h"

boop::Texture2D::Texture2D(SDL_Texture* texture) :
	m_texture{ texture }
{
}

boop::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_texture);
}

glm::ivec2 boop::Texture2D::GetSize() const
{
	SDL_Rect dst{};
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

boop::Texture2D::Texture2D(const Texture2D& other)
{
	auto renderer = Renderer::GetInstance().GetSDLRenderer();
	if (!other.m_texture || !renderer) {
		m_texture = nullptr;
		return;
	}
	
	int width, height, access;
	Uint32 format;
	SDL_QueryTexture(other.m_texture, &format, &access, &width, &height);

	// Create a new texture with the same format, width, and height as the original
	m_texture = SDL_CreateTexture(renderer, format, SDL_TEXTUREACCESS_TARGET, width, height);

	if (!m_texture) {
		throw std::runtime_error("Failed to create texture copy: " + std::string(SDL_GetError()));
	}

	// Set the original texture as the rendering target and copy its content
	SDL_SetRenderTarget(renderer, m_texture);
	SDL_RenderCopy(renderer, other.m_texture, NULL, NULL);
	SDL_SetRenderTarget(renderer, NULL);
}


SDL_Texture* boop::Texture2D::GetSDLTexture() const
{
	return m_texture;
}


