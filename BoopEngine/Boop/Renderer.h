#pragma once
#include <SDL.h>
#include "HelperFiles/Singleton.h"
#include "HelperFiles/Texture2D.h"
namespace boop
{
	class Renderer final : public Singleton<Renderer>
	{
	public:

		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y, float scale = 1, flipTexture flipQuadrant = {}) const;
		void RenderTexture(const Texture2D& texture, SDL_Rect& dstRect ,const SDL_Rect& scrRect, bool flipTexture = false) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const;
		SDL_Window* GetSDLWindow() const { return m_window; }

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

	private:
		friend class Singleton<Renderer>;
		explicit Renderer();
		~Renderer();

		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};
	};
}

