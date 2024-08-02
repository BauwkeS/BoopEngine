#pragma once
#include "Texture2D.h"
#include <SDL_rect.h>
#include <string>


namespace boop
{
	class AnimatedTexture final
	{
	private:
		int m_Cols;
		int m_Rows;
		int m_CurrentPic{};
		int m_StartPic{};
		int m_AmountPic{};
		float m_AccuSec;
		//int m_ActFrame;
		float m_Scale;


	public:
		explicit AnimatedTexture(std::string texture, int cols, int rows, float frameSec, int startPicIndex, int AmountPics, float scale);

		AnimatedTexture(const AnimatedTexture& other) = delete;
		AnimatedTexture& operator=(const AnimatedTexture& other) = delete;
		AnimatedTexture(AnimatedTexture&& other) noexcept;
		AnimatedTexture& operator=(AnimatedTexture&& other) noexcept;
		~AnimatedTexture();

		Texture2D* GetTexture();
		
		void Render();
		void Update(float deltaTime, glm::vec2 pos);

	protected:
		Texture2D* m_pTexture{};
		float m_FrameSec;
		SDL_Rect m_ScrRect{};
		SDL_Rect m_DstRect{};
	};
}