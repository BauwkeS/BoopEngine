#pragma once
#include <string>
#include "Component.h"
#include "../HelperFiles/AnimatedTexture.h"


namespace boop
{
	class Collision;

	class SpriteComponent final : public Component
	{
	public:
		SpriteComponent();
		SpriteComponent(boop::GameObject* const ownerPtr, AnimatedTexture* const texture, Collision* collision=nullptr);
		SpriteComponent(boop::GameObject* const ownerPtr, const std::string texture, const int cols, const int rows, 
			const float frameSec, const int startPicIndex, const int AmountPics, const float scale, Collision* collision = nullptr);
		~SpriteComponent() override;

		SpriteComponent(const SpriteComponent& other);
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void FixedUpdate(float deltaTime) override { deltaTime = 1; }
		void LateUpdate(float deltaTime) override { deltaTime = 1; }
		void Update(float deltaTime) override;
		void Render() const override;

		void SetTexture(AnimatedTexture* const texture);
		AnimatedTexture* GetTexture(){return m_pTexture;}
		Collision* GetCollision() const { return m_pCollision; }

		//void SetFramesSec(float sec);
	private:
		//std::unique_ptr<boop::Texture2D> m_TexturePtr;
		AnimatedTexture* m_pTexture;
		Collision* m_pCollision;
		
	};
}

