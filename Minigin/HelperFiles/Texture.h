#pragma once
#include <string>

// SDL and OpenGL Includes
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h> 
#include <SDL_image.h>
#include <glm/glm.hpp>

#include "Texture2D.h"

#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")

namespace boop
{
	class Texture final
	{
	public:
		explicit Texture(const std::string& imagePath);
		explicit Texture(const std::string& text, TTF_Font* pFont, const glm::vec4& textColor);
		explicit Texture(const std::string& text, const std::string& fontPath, int ptSize, const glm::vec4& textColor);
		Texture(const Texture& other) = delete;
		Texture& operator=(const Texture& other) = delete;
		Texture(Texture&& other) noexcept;
		Texture& operator=(Texture&& other) noexcept;
		~Texture();

		void Draw(const glm::vec2& dstBottomLeft, const glm::vec4& srcRect) const;
		void Draw(const glm::vec4& dstRect, const glm::vec4& srcRect) const;

		float GetWidth() const;
		float GetHeight() const;
		bool IsCreationOk() const;

	private:
		//DATA MEMBERS
		GLuint m_Id;
		float m_Width;
		float m_Height;
		bool m_CreationOk;

		Texture2D* m_TexturePtr;

		// FUNCTIONS
		void CreateFromImage(const std::string& path);
		void CreateFromString(const std::string& text, TTF_Font* pFont, const glm::vec4& textColor);
		void CreateFromString(const std::string& text, const std::string& fontPath, int ptSize, const glm::vec4& textColor);
		void CreateFromSurface(SDL_Surface* pSurface);
		SDL_Surface* STBImageLoad(const std::string& path);
		void DrawFilledRect(const glm::vec4& dstRect) const;
	};
}