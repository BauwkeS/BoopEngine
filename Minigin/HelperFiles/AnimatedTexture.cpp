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
	m_DstRect.x = static_cast<int>(300); //test
	m_DstRect.y = static_cast<int>(300); //test
}

boop::AnimatedTexture::~AnimatedTexture()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}

boop::Texture2D* boop::AnimatedTexture::GetTexture()
{
	return nullptr;
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
	/*m_DstRect.w =static_cast<int>(m_Scale * m_ScrRect.w);
	m_DstRect.h =static_cast<int>(m_Scale * m_ScrRect.h);*/
	m_DstRect.x =static_cast<int>(pos.x);
	m_DstRect.y =static_cast<int>(pos.y);
		m_ScrRect.x = (m_CurrentPic % m_Cols) * m_ScrRect.w;
		m_ScrRect.y = (m_CurrentPic / m_Cols) * m_ScrRect.h;
	}
}

void boop::AnimatedTexture::Render()
{
	//auto pos{ GetOwner()->GetWorldPosition() };

	/*SDL_Rect srcRect{};
	srcRect.x = static_cast<int>(std::round(m_ScrRect.x));
	srcRect.y = static_cast<int>(std::round(m_ScrRect.y));
	srcRect.w = static_cast<int>(std::round(m_ScrRect.w));
	srcRect.h = static_cast<int>(std::round(m_ScrRect.h));

	SDL_Rect dstRect{};
	dstRect.x = static_cast<int>(std::round(m_DstRect.x));
	dstRect.y = static_cast<int>(std::round(m_DstRect.y));
	dstRect.w = static_cast<int>(std::round(m_DstRect.w));
	dstRect.h = static_cast<int>(std::round(m_DstRect.h));*/

	boop::Renderer::GetInstance().RenderTexture(*m_pTexture, m_DstRect, m_ScrRect);

	//SDL_Rect destRect{};

	//const float epsilon{ 0.001f };
	//if (!(m_ScrRect.w > epsilon && m_ScrRect.h > epsilon)) // No srcRect specified
	//{
	//	// Use complete texture
	//	destRect.x = 0.0f;
	//	destRect.y = 0.0f;

	//	destRect.w = m_pTexture->GetSize().x;
	//	destRect.h = m_pTexture->GetSize().y;
	//}
	//else // srcRect specified
	//{
	//	
	//}
}
