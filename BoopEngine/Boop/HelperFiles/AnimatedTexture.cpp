#include "AnimatedTexture.h"

#include "../Renderer.h"
#include "../ResourceManager.h"

boop::AnimatedTexture::AnimatedTexture(std::string texture, int cols, int rows, float frameSec, int startPicIndex, int AmountPics, float scale, bool flip)
	: m_Cols{cols},
	m_Rows{rows},
	m_CurrentPic{startPicIndex},
	m_StartPic{startPicIndex},
	m_AmountPic{AmountPics},
	m_AccuSec{0.f},
	m_Scale{scale},
	m_TextureName{texture},
	m_FliptTexture{flip},
	m_FrameSec{frameSec}
{
	if (m_AmountPic == 0) m_AmountPic = m_Cols * m_Rows;

	//TO-DO FIX THIS
	//auto textureTemp = boop::ResourceManager::GetInstance().LoadTexture(texture);
	//m_pTexture = textureTemp->Clone();

	m_ScrRect.w = static_cast<int>(m_pTexture->GetSize().x) / m_Cols;
	m_ScrRect.h = static_cast<int>(m_pTexture->GetSize().y) / m_Rows;
	m_ScrRect.x = (m_CurrentPic % m_Cols) * m_ScrRect.w;
	m_ScrRect.y = (m_CurrentPic / m_Cols) * m_ScrRect.h;

	m_DstRect.w = static_cast<int>(m_Scale * m_ScrRect.w);
	m_DstRect.h = static_cast<int>(m_Scale * m_ScrRect.h);
}

boop::Texture2D* boop::AnimatedTexture::GetTexture()
{
	return m_pTexture.get();
}

void boop::AnimatedTexture::Update(float deltaTime, glm::vec2 pos)
{
	m_AccuSec += deltaTime;
	if (m_AccuSec > m_FrameSec) {

		++m_CurrentPic %= m_Cols * m_Rows;
		m_AccuSec -= m_FrameSec;

		//make sure to not keep looping on
		if (m_CurrentPic >= m_AmountPic) m_CurrentPic = m_StartPic;

		//modify rect
		m_ScrRect.x = (m_CurrentPic % m_Cols) * m_ScrRect.w;
		m_ScrRect.y = (m_CurrentPic / m_Cols) * m_ScrRect.h;
	}
		m_DstRect.x =static_cast<int>(pos.x);
		m_DstRect.y =static_cast<int>(pos.y);
}

void boop::AnimatedTexture::ChangeTextureVars(const int cols, const int rows, const int AmountPics, bool flip, const int startPicIndex, float frameSec)
{
	m_Cols = cols;
	m_Rows = rows;
	m_AmountPic = AmountPics;
	m_StartPic = startPicIndex;
	m_FrameSec = frameSec;

	m_ScrRect.w = static_cast<int>(m_pTexture->GetSize().x) / m_Cols;
	m_ScrRect.h = static_cast<int>(m_pTexture->GetSize().y) / m_Rows;
	m_ScrRect.x = (m_CurrentPic % m_Cols) * m_ScrRect.w;
	m_ScrRect.y = (m_CurrentPic / m_Cols) * m_ScrRect.h;

	m_DstRect.w = static_cast<int>(m_Scale * m_ScrRect.w);
	m_DstRect.h = static_cast<int>(m_Scale * m_ScrRect.h);

	m_FliptTexture = flip;
}

void boop::AnimatedTexture::Render()
{
	boop::Renderer::GetInstance().RenderTexture(*m_pTexture, m_DstRect, m_ScrRect,m_FliptTexture);
}
