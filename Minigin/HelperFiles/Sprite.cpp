#include "Sprite.h"
#include "Texture.h"
#include <iostream>

boop::Sprite::Sprite(const std::string& filename, int nrCols, int nrRows, float frameSec, float scale) :
	m_Cols{ nrCols },
	m_Rows{ nrRows },
	m_FrameSec{ frameSec },
	m_AccuSec{ 0.f },
	m_ActFrame{ 1 },
	m_Scale{ scale },
	m_ScrRect{ (glm::vec4{0,0,0,0 }) },
	m_DesRect{ (glm::vec4{0,0,0,0 }) },
	m_Filename{ filename }
{
	m_pTexture = new Texture(m_Filename);
	m_ScrRect.x = (m_ActFrame % m_Cols) * m_ScrRect.z;
	m_ScrRect.y = (m_Rows + 1) * m_ScrRect.w;
	m_ScrRect.z = GetFrameWidth();
	m_ScrRect.w = GetFrameHeight();
}

boop::Sprite::~Sprite() {
	delete m_pTexture;
	m_pTexture = nullptr;
}

void boop::Sprite::Update(float elapsedSec, const glm::vec2& pos) {
	m_AccuSec += elapsedSec;
	if (m_AccuSec > m_FrameSec) {
		++m_ActFrame %= m_Cols * m_Rows;
		m_AccuSec -= m_FrameSec;
	}

	ModifyRect(pos);
}
void boop::Sprite::Draw() {

	m_pTexture->Draw(m_DesRect, m_ScrRect);
	//utils::FillRect(m_DesRect);
	//std::cout << m_DesRect.bottom << std::endl;
}
float boop::Sprite::GetFrameWidth() {
	return m_pTexture->GetWidth() / m_Cols;
}
float boop::Sprite::GetFrameHeight() {
	return m_pTexture->GetHeight() / m_Rows;
}

float boop::Sprite::GetFrameSec()
{
	return m_FrameSec;
}

void boop::Sprite::SetScrRect(glm::vec4 scr) {
	m_ScrRect = scr;
}

void boop::Sprite::SetDestRect(glm::vec4 dstr) {
	m_DesRect = dstr;
}

glm::vec4 boop::Sprite::GetDestRect() const
{
	return m_DesRect;
}

void boop::Sprite::SetScrRectColsRows(float cols, float whichRow, float maxCols, float maxRows) {

	m_ScrRect.z = m_pTexture->GetWidth() / maxCols;
	m_ScrRect.w = m_pTexture->GetHeight() / maxRows;
	m_Rows = static_cast<int>(whichRow);
	m_Cols = static_cast<int>(cols);
	m_ScrRect.x = (m_ActFrame % static_cast<int>(cols)) * m_ScrRect.z;
	m_ScrRect.y = (whichRow)*m_ScrRect.w;


	//std::cout << "m_ActFrame: " << m_ActFrame << std::endl;

	//std::cout << "m_Cols: " << m_Cols << std::endl;
	//std::cout << "m_Rows: " << m_Rows << std::endl;
	//std::cout << "cols: " << cols << std::endl;
	//std::cout << "whichRow: " << whichRow << std::endl;

	//std::cout << "m_ScrRect.left: " << m_ScrRect.left << std::endl;
	//std::cout << "m_ScrRect.bottom: " << m_ScrRect.bottom << std::endl;
	//std::cout << "m_ScrRect.width: " << m_ScrRect.width << std::endl;
	//std::cout << "m_ScrRect.height: " << m_ScrRect.height << std::endl;
}

void boop::Sprite::SetActFrame(float frame) {
	m_ActFrame = static_cast<int>(frame);
}

void boop::Sprite::SetFrameSec(float frameSec)
{
	m_FrameSec = frameSec;
}

void boop::Sprite::ModifyRect(const glm::vec2& pos) {
	m_DesRect.z = m_ScrRect.z * m_Scale;
	m_DesRect.w = m_ScrRect.w * m_Scale;
	m_DesRect.x = pos.x;
	m_DesRect.y = pos.y;
}

void boop::Sprite::UpdateSpriteSheet(std::string imagePath, int cols, int rows)
{
	if (m_pTexture)
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	m_Rows = rows;
	m_Cols = cols;
	m_pTexture = new Texture(imagePath);

	/*if (!m_Initialized)
	{
		m_Initialized = true;

		SetDstRect(m_SpawnPoint);

		m_HitBox = Rectf{ m_DstRect.left, m_DstRect.bottom, m_HitBoxSize, m_HitBoxSize };
	}*/
}

void boop::Sprite::SetScale(float scale) {
	m_Scale = scale;
}