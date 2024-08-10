#pragma once
#include "Texture2D.h"
#include <SDL_rect.h>
#include <string>
#include <memory>


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
		std::string m_TextureName{};


	public:
		explicit AnimatedTexture(std::string texture, int cols, int rows, float frameSec, int startPicIndex, int AmountPics, float scale=1);

		AnimatedTexture(const AnimatedTexture& other) = delete;
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
		void ChangeTextureVars(const int cols, const int rows, const int AmountPics, const int startPicIndex = 0);

		std::unique_ptr<AnimatedTexture> Clone() const {
			std::unique_ptr<AnimatedTexture> clonedTexture =
				std::make_unique<AnimatedTexture>(this->m_TextureName,
					this->m_Cols, this->m_Rows, this->m_FrameSec, this->m_StartPic,
					this->m_AmountPic, this->m_Scale);
			return std::move(clonedTexture);
		}

	protected:
		std::unique_ptr<Texture2D> m_pTexture{};
		float m_FrameSec;
		SDL_Rect m_ScrRect{};
		SDL_Rect m_DstRect{};
	};
}