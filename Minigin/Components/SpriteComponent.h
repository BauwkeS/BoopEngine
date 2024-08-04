#pragma once
#include <string>
#include "Component.h"
#include "HelperFiles/AnimatedTexture.h"

namespace boop
{
	class SpriteComponent final : public Component
	{
	public:
		SpriteComponent(boop::GameObject* const ownerPtr, AnimatedTexture* const texture);
		SpriteComponent(boop::GameObject* const ownerPtr, const std::string texture, const int cols, const int rows, 
			const float frameSec, const int startPicIndex, const int AmountPics, const float scale);
		~SpriteComponent() override
		{
			delete m_pTexture;
			m_pTexture = nullptr;
		}

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void FixedUpdate(float deltaTime) override { deltaTime = 1; }
		void LateUpdate(float deltaTime) override { deltaTime = 1; }
		void Update(float deltaTime) override;
		void Render() const override;

		void SetTexture(AnimatedTexture* const texture);
		AnimatedTexture* GetTexture(){return m_pTexture;}
		//void SetFramesSec(float sec);
	private:
		//std::unique_ptr<boop::Texture2D> m_TexturePtr;
		AnimatedTexture* m_pTexture;

	};
}

