#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "HelperFiles/Texture2D.h"
#include "HelperFiles/Font.h"

//not actually a manager -> it just loads files -> you can change this to store pointers to the textes
// => when one is called that exists you can already just give that pointer to it instead of making a new one


void boop::ResourceManager::Init(const std::filesystem::path& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

boop::Texture2D* boop::ResourceManager::LoadTexture(const std::string& file)
{
	//if it exist -> return what you have
	if (m_Textures.contains(file)) return m_Textures.at(file).get();
	if (file == "") return nullptr;
	//if it does not exist -> save it and return
	const auto fullPath = m_dataPath/file;
	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.string().c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	m_Textures[file] = std::make_unique<Texture2D>(texture);
	return m_Textures.at(file).get();
}

boop::Font* boop::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	//if it exist -> return what you have
	if (m_Fonts.contains(file)) return m_Fonts.at(file).get();

	//if it does not exist -> save it and return
	const auto fullPath = m_dataPath/file;
	m_Fonts.insert({ file,std::make_unique<Font>(fullPath.string(), size) });
	return m_Fonts.at(file).get();
}
