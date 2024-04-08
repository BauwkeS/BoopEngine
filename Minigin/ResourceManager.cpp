#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"

void boop::ResourceManager::Init(const std::filesystem::path& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

std::unique_ptr<boop::Texture2D> boop::ResourceManager::LoadTexture(const std::string& file) const
{
	const auto fullPath = m_dataPath/file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.string().c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}
	return std::make_unique<Texture2D>(texture);
}

std::unique_ptr<boop::Font> boop::ResourceManager::LoadFont(const std::string& file, unsigned int size) const
{
	const auto fullPath = m_dataPath/file;
	return std::make_unique<Font>(fullPath.string(), size);
}

boop::ResourceManager::~ResourceManager()
{
}

boop::ResourceManager::ResourceManager()
{
}
