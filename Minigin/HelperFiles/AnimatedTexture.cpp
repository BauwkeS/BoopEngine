#include "AnimatedTexture.h"

#include "Renderer.h"
#include "ResourceManager.h"

boop::AnimatedTexture::AnimatedTexture(std::string texture, int cols, int rows, float frameSec, int startPicIndex, int AmountPics, float scale)
	: m_Cols{cols},
	m_Rows{rows},
	m_CurrentPic{startPicIndex},
	m_StartPic{startPicIndex},
	m_AmountPic{AmountPics},
	m_AccuSec{0.f},
	m_Scale{scale},
	m_FrameSec{frameSec}
{
	if (m_AmountPic == 0) m_AmountPic = m_Cols * m_Rows;

	m_pTexture = boop::ResourceManager::GetInstance().LoadTexture(texture);

	m_ScrRect.w = static_cast<int>(m_pTexture->GetSize().x) / m_Cols;
	m_ScrRect.h = static_cast<int>(m_pTexture->GetSize().y) / m_Rows;
	m_ScrRect.x = (m_CurrentPic % m_Cols) * m_ScrRect.w;
	m_ScrRect.y = (m_CurrentPic / m_Cols) * m_ScrRect.h;

	m_DstRect.w = static_cast<int>(m_Scale * m_ScrRect.w);
	m_DstRect.h = static_cast<int>(m_Scale * m_ScrRect.h);
}

boop::AnimatedTexture::AnimatedTexture(const AnimatedTexture& other)
	: m_Cols(other.m_Cols),
	m_Rows(other.m_Rows),
	m_CurrentPic(other.m_CurrentPic),
	m_StartPic(other.m_StartPic),
	m_AmountPic(other.m_AmountPic),
	m_AccuSec(other.m_AccuSec),
	m_Scale(other.m_Scale),
	m_FrameSec(other.m_FrameSec),
	m_ScrRect(other.m_ScrRect),
	m_DstRect(other.m_DstRect)
{
	if (other.m_pTexture) {
		m_pTexture = new Texture2D(*other.m_pTexture);
	}
	else {
		m_pTexture = nullptr;
	}
}

boop::AnimatedTexture::~AnimatedTexture()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

boop::Texture2D* boop::AnimatedTexture::GetTexture()
{
	return m_pTexture;
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
		//m_DstRect.w = (m_CurrentPic % m_Cols) * m_ScrRect.w;
		//m_DstRect.h = (m_CurrentPic / m_Cols) * m_ScrRect.h;
		m_ScrRect.x = (m_CurrentPic % m_Cols) * m_ScrRect.w;
		m_ScrRect.y = (m_CurrentPic / m_Cols) * m_ScrRect.h;
	}
		m_DstRect.x =static_cast<int>(pos.x);
		m_DstRect.y =static_cast<int>(pos.y);
}

void boop::AnimatedTexture::Render()
{
	//auto pos{ GetOwner()->GetWorldPosition() };
	//boop::Renderer::GetInstance().RenderTexture(*m_TexturePtr, pos.x, pos.y);

	boop::Renderer::GetInstance().RenderTexture(*m_pTexture, m_DstRect, m_ScrRect);
}
