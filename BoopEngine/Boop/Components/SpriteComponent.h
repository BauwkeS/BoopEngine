#pragma once
#include <string>
#include <memory>
#include "Component.h"
#include "../HelperFiles/AnimatedTexture.h"


namespace boop
{
	class Collision;

	class SpriteComponent : public Component
	{
	public:
		SpriteComponent();
		SpriteComponent(boop::GameObject* const ownerPtr, AnimatedTexture* const texture, Collision* collision=nullptr);
		SpriteComponent(boop::GameObject* const ownerPtr, const std::string texture, const int cols, const int rows, 
			const float frameSec, const int startPicIndex, const int AmountPics, const float scale, Collision* collision = nullptr);
		~SpriteComponent() override;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void FixedUpdate(float deltaTime) override { deltaTime = 1; }
		void LateUpdate(float deltaTime) override { deltaTime = 1; }
		void Update(float deltaTime) override;
		void Render() const override;

		void MoveSprite(glm::ivec2 pos);

		void SetTexture(AnimatedTexture* const texture);
		AnimatedTexture* GetTexture(){return m_pTexture;}
		Collision* GetCollision() const { return m_pCollision; }
	
		virtual std::unique_ptr<Component> Clone() const override
		{
			// Create a new comp with the same info
			std::unique_ptr<SpriteComponent> spriteComponent
				= std::make_unique<SpriteComponent>(this->GetOwner(),
				m_pTexture,
				m_pCollision);
			return std::move(spriteComponent);
		}

		//void SetFramesSec(float sec);
	private:
		//std::unique_ptr<boop::Texture2D> m_TexturePtr;
		AnimatedTexture* m_pTexture;
		Collision* m_pCollision;
		
	};
}

