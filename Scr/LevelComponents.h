#include "../BoopEngine/Boop/Components/TextureComponent.h"
#include "../BoopEngine/Boop/HelperFiles/Collision.h"

namespace booble
{
	class Wall final 
	{
	private: 
		std::unique_ptr< boop::TextureComponent> m_Texture;
	public:
		Wall(boop::GameObject* const ownerPtr, std::string texture, float scale = 1)
		{
			m_Texture = std::make_unique<boop::TextureComponent>(ownerPtr, texture, scale, true);
		}
		boop::TextureComponent* GetSprite() const { return m_Texture.get(); }

	};

	class Platform final : public boop::TextureComponent
	{
	private:
		std::unique_ptr< boop::TextureComponent> m_Texture;
	public:
		Platform(boop::GameObject* const ownerPtr, std::string texture, float scale = 1)
		{
			m_Texture = std::make_unique<boop::TextureComponent>(ownerPtr, texture, scale, true);
			//gotta set that collision here yourself I rhink bestie
		}
		boop::TextureComponent* GetSprite() const { return m_Texture.get(); }

	};
}