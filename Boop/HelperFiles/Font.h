#pragma once
#include <string>

struct _TTF_Font;
namespace boop
{
	/**
	 * Simple RAII wrapper for a _TTF_Font
	 */
	class Font final
	{
	public:
		_TTF_Font* GetFont() const;
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();

		Font(const Font & other);
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;
	private:
		_TTF_Font* m_font;
		std::string m_Path;
		unsigned int m_Size;
	};
}
