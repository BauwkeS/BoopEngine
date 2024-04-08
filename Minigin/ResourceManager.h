#pragma once
#include <filesystem>
#include <string>
#include <memory>
#include "Singleton.h"

namespace boop
{
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:


		void Init(const std::filesystem::path& data);
		std::unique_ptr<Texture2D> LoadTexture(const std::string& file) const;
		std::unique_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;
	private:
		friend class Singleton<ResourceManager>;

		~ResourceManager();
		ResourceManager();
		std::filesystem::path m_dataPath;
	};
}
