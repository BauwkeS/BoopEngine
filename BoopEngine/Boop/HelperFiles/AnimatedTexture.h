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
		bool m_FliptTexture{};

	public:
		explicit AnimatedTexture(std::string texture, int cols=1, int rows=1, float frameSec=1, int startPicIndex=0, int AmountPics=1, float scale=1, bool flip=false);

		AnimatedTexture(const AnimatedTexture& other) = delete;
		AnimatedTexture(AnimatedTexture&& other) = delete;
		AnimatedTexture& operator=(const AnimatedTexture& other) = delete;
		AnimatedTexture& operator=(AnimatedTexture&& other) = delete;
		~AnimatedTexture() = default;

		Texture2D* GetTexture();
		
		void Render();
		void Update(glm::vec2 pos);

		void SetFramesSec(float sec) { m_FrameSec = sec; }
		SDL_Rect GetDstRect() const { return m_DstRect; }
		void SetDstRect(SDL_Rect rect) { m_DstRect = rect; }
		void ChangeTextureVars(const int cols, const int rows, const int AmountPics, bool flip=false, const int startPicIndex = 0, float frameSec=0.2f);
		void SetFlipTexture(bool flip) { m_FliptTexture = flip; }
		bool IsTextureFlipped() { return m_FliptTexture; }

	protected:
		std::unique_ptr<Texture2D> m_pTexture{};
		float m_FrameSec;
		SDL_Rect m_ScrRect{};
		SDL_Rect m_DstRect{};
	};
}