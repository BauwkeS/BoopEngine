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
		SpriteComponent(boop::GameObject* const ownerPtr, std::unique_ptr<AnimatedTexture> texture);
		SpriteComponent(boop::GameObject* const ownerPtr, const std::string texture, const int cols, const int rows, 
			const float frameSec, const int startPicIndex, const int AmountPics, const float scale);
		~SpriteComponent() override = default;

		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) = delete;

		void FixedUpdate(float deltaTime) override { deltaTime = 1; }
		void LateUpdate(float deltaTime) override { deltaTime = 1; }
		void Update(float deltaTime) override;
		void Render() const override;

		void MoveSprite(glm::ivec2 pos);
		AnimatedTexture* GetTexture(){return m_pTexture.get();}
		SDL_Rect GetTextureRect();
	
		virtual std::unique_ptr<Component> Clone() const override
		{
			// Create a new comp with the same info
			std::unique_ptr<SpriteComponent> spriteComponent
				= std::make_unique<SpriteComponent>(this->GetOwner(),
					std::move(this->m_pTexture->Clone()));
			return std::move(spriteComponent);
		}

	private:
		std::unique_ptr<AnimatedTexture> m_pTexture;
		glm::ivec2 m_MovingPos{};
	};
}

