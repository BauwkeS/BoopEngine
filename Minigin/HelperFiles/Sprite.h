#include "Texture.h"

namespace boop
{
	class Sprite {
	private:
		int m_Cols;
		int m_Rows;
		float m_AccuSec;
		int m_ActFrame;
		float m_Scale;
		std::string m_Filename;

	protected:
		float m_FrameSec;
		Texture* m_pTexture;
		glm::vec4 m_ScrRect{};
		glm::vec4 m_DesRect{};


	public:
		Sprite(const std::string& filename, int nrCols, int nrRows, float frameSec, float scale);
		~Sprite();
		virtual void Update(float elapsedSec, const glm::vec2& pos);
		virtual void Draw();
		void ModifyRect(const glm::vec2& pos);
		float GetFrameWidth();
		float GetFrameHeight();
		float GetFrameSec();
		void SetScrRect(glm::vec4 scr);
		void SetDestRect(glm::vec4 dest);
		glm::vec4 GetDestRect() const;
		void SetScrRectColsRows(float cols, float whichRow, float maxCols, float maxRows);
		void SetActFrame(float frame);
		void SetFrameSec(float frameSec);
		void SetScale(float scale);
		void UpdateSpriteSheet(std::string imagePath, int cols, int rows);
	};
}