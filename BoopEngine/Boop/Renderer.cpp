#include <stdexcept>
#include <cstring>
#include "Renderer.h"
#include "Scene/SceneManager.h"
#include "HelperFiles/Texture2D.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void boop::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void boop::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(m_renderer);
}

void boop::Renderer::Destroy()
{
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void boop::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, float scale, flipTexture flip) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	dst.w = static_cast<int>(scale * dst.w);
	dst.h = static_cast<int>(scale * dst.h);

	SDL_Rect scr{};
	scr.w = static_cast<int>(dst.w);
	scr.h = static_cast<int>(dst.h);

	const SDL_Point center{ dst.w / 2, dst.h / 2 };

	int angle = flip.vertical ? 90 : 0;

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &scr, &dst, angle, &center, static_cast<SDL_RendererFlip>(flip.horizontal));

}

void boop::Renderer::RenderTexture(const Texture2D& texture, SDL_Rect& dstRect, const SDL_Rect& scrRect, bool flipTexture) const
{
	const SDL_Point center{ dstRect.w / 2, dstRect.h / 2 };
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &scrRect, &dstRect, 0, &center, static_cast<SDL_RendererFlip>(flipTexture));

}

void boop::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

SDL_Renderer* boop::Renderer::GetSDLRenderer() const { return m_renderer; }

boop::Renderer::Renderer()
{
}

boop::Renderer::~Renderer()
{
}
