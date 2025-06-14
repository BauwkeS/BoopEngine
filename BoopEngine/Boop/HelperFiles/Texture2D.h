#pragma once
#include <glm/vec2.hpp>
#include <memory>

struct SDL_Texture;
namespace boop
{
	struct flipTexture {
		bool horizontal{ false };
		bool vertical{ false };
	};

	class Texture2D final
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		glm::ivec2 GetSize() const;

		Texture2D(const Texture2D & other);
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

	private:
		SDL_Texture* m_texture;
	};
}
