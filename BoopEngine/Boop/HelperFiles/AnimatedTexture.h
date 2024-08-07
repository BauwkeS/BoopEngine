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
		float m_Scale;


	public:
		explicit AnimatedTexture(std::string texture, int cols, int rows, float frameSec, int startPicIndex, int AmountPics, float scale=1);

		AnimatedTexture(const AnimatedTexture& other);
		AnimatedTexture(AnimatedTexture&& other) = delete;
		AnimatedTexture& operator=(const AnimatedTexture& other) = delete;
		AnimatedTexture& operator=(AnimatedTexture&& other) = delete;
		~AnimatedTexture();

		Texture2D* GetTexture();
		
		void Render();
		void Update(float deltaTime, glm::vec2 pos);

		void SetFramesSec(float sec) { m_FrameSec = sec; }
		SDL_Rect GetDstRect() const { return m_DstRect; }
		void SetDstRect(SDL_Rect rect) { m_DstRect = rect; }

	protected:
		Texture2D* m_pTexture{};
		float m_FrameSec;
		SDL_Rect m_ScrRect{};
		SDL_Rect m_DstRect{};
	};
}