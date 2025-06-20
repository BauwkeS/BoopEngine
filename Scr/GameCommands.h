#pragma once

#include "../BoopEngine/Boop/Input/Command.h"
#include "../BoopEngine/Boop/DeltaTime.h"

#include "Components/Player.h"
#include <iostream>
#include <memory>
#include <glm/ext/vector_float2.hpp>
#include "Components/Health.h"
#include "Level.h"
#include "GameLoader.h"

#include "../BoopEngine/Boop/Scene/Scene.h"
#include "../BoopEngine/Boop/Scene/SceneManager.h"
#include "../BoopEngine/Boop/Input/InputManager.h"
#include "../BoopEngine/Boop/Renderer.h"
#include "../BoopEngine/Boop/GameObject.h"
#include "../BoopEngine/Boop/Components/TextComponent.h"
#include "../BoopEngine/Boop/Components/TextureComponent.h"
#include "Components/Bullet.h"

#include "../BoopEngine/Boop/Sound/ServiceLocator.h"


//COMMANDS HERE
namespace boop
{
	class Command;
	class SpriteComponent;
}

namespace booble
{
	//MOVEMENT
	class WalkCommand final : public boop::Command {
	private:
		boop::GameObject* m_pGameObject;
		glm::vec2 m_Speed;
		int m_WindowHeight{};
		int m_WindowWidth{};
		SDL_Rect m_ObjectSize{};
		boop::TextureComponent* m_pPlayerTexture{};
		boop::TextureComponent* m_pGunTexture{};
		Level* m_Player{};
	public:
		WalkCommand(boop::GameObject* component, glm::vec2 speed)
			: m_pGameObject{ component }, m_Speed{ speed } 
		{
			auto window = boop::Renderer::GetInstance().GetSDLWindow();
			SDL_GetWindowSize(window, &m_WindowWidth, &m_WindowHeight);

			m_pPlayerTexture = m_pGameObject->GetComponent<boop::TextureComponent>();
			m_pGunTexture = m_pGameObject->GetChildAt(1)->GetComponent<boop::TextureComponent>();
			m_ObjectSize = m_pPlayerTexture->GetTextureRect();
			m_Player = m_pGameObject->GetChildAt(0)->GetComponent<Level>();
		}
		~WalkCommand() { m_pGameObject = nullptr; delete m_pGameObject; m_pPlayerTexture = nullptr; delete m_pPlayerTexture; }

		void Execute() override {

			//move the player
			//you should not be allowed to go outside the game bounds!

			auto newXPos = m_pGameObject->GetLocalPosition().x + (m_Speed.x * boop::DeltaTime::GetInstance().GetDeltaTime());
			auto newYPos = m_pGameObject->GetLocalPosition().y + (m_Speed.y * boop::DeltaTime::GetInstance().GetDeltaTime());

			//check bounds of game and set player back if needed
			if (newXPos < 0 || newXPos > m_WindowWidth - m_ObjectSize.w
				|| newYPos < 0 || newYPos > m_WindowHeight - m_ObjectSize.h) return;

			//-------------
			//also check for collisions with the walls
			for (auto& wall : m_Player->GetCollisionObjects())
			{
				auto wallPos = wall->GetWorldPosition();
				glm::vec2 wallSize = wall->GetComponent<boop::TextureComponent>()->GetSize();
				SDL_Rect wallRect{ static_cast<int>(wallPos.x), static_cast<int>(wallPos.y),
					static_cast<int>(wallSize.x), static_cast<int>(wallSize.y) };

				m_ObjectSize.x = static_cast<int>(newXPos);
				m_ObjectSize.y = static_cast<int>(newYPos);

				//check if the rects intersect or not
				if (SDL_HasIntersection(&m_ObjectSize, &wallRect))
				{
					//you have collided!
					return;
				}
			}

			//if you are not colliding with anything, move player
			m_pGameObject->SetLocalPosition(newXPos, newYPos);

			m_pPlayerTexture->FlipTextureDir(m_Speed);
			

			if (m_Speed.x > 0) m_pGunTexture->GetOwner()->SetLocalPosition(-10, -8);
			else if (m_Speed.x < 0) m_pGunTexture->GetOwner()->SetLocalPosition(-6, -8);
			if (m_Speed.y > 0) m_pGunTexture->GetOwner()->SetLocalPosition(-8, -10);
			else if (m_Speed.y < 0) m_pGunTexture->GetOwner()->SetLocalPosition(-8, -6);

		};

		WalkCommand(const WalkCommand& other) = delete;
		WalkCommand(WalkCommand&& other) = delete;
		WalkCommand& operator=(const WalkCommand& other) = delete;
		WalkCommand& operator=(WalkCommand&& other) = delete;

	};

	//SHOOTING
	class ShootCommand final : public boop::Command {
	private:
		boop::GameObject* m_pGameObject;
		glm::vec2 m_Speed;
		boop::TextureComponent* m_pGunTexture{};
		Level* m_pLevel{};
	public:
		ShootCommand(boop::GameObject* component, glm::vec2 speed)
			: m_pGameObject{ component }, m_Speed{ speed }
		{
			m_pGunTexture = m_pGameObject->GetChildAt(1)->GetComponent<boop::TextureComponent>();
			m_pLevel = m_pGameObject->GetChildAt(0)->GetComponent<Level>();
		}
		~ShootCommand() { m_pGameObject = nullptr; delete m_pGameObject; m_pLevel = nullptr; delete m_pLevel; }

		void Execute() override {

			m_pGunTexture->FlipTextureDir(m_Speed);
			
			//create a bullet

			auto bullet = std::make_unique<boop::GameObject>();
			bullet->SetTag("bullet");
			bullet->AddComponent<Bullet>(m_Speed, m_pLevel);
			bullet->AddComponent<boop::TextureComponent>("BulletPlayer.png");

			// Set the position of the bullet relative to the gun
			auto gunSize = m_pGunTexture->GetSize();
			auto gunPos = m_pGunTexture->GetOwner()->GetWorldPosition();

			float mar = 3.f;

			float xOffset{};
			float yOffset{};

			if (m_Speed.x > 0)
			{
				xOffset = gunSize.x - mar;
				yOffset = gunSize.y / 3;
			}
			else if (m_Speed.x < 0)
			{
				xOffset = 0;
				yOffset = gunSize.y / 3;
			}
			if (m_Speed.y > 0)
			{
				xOffset = gunSize.x / 3 + mar;
				yOffset = gunSize.y - mar;
			}
			else if (m_Speed.y < 0)
			{
				xOffset = gunSize.x / 3 + mar;
				yOffset = 0;
			}

			bullet->SetLocalPosition(gunPos.x + xOffset, gunPos.y + yOffset);


			boop::SceneManager::GetInstance().GetActiveScene()->Add(std::move(bullet));
		};

		ShootCommand(const ShootCommand& other) = delete;
		ShootCommand(ShootCommand&& other) = delete;
		ShootCommand& operator=(const ShootCommand& other) = delete;
		ShootCommand& operator=(ShootCommand&& other) = delete;

	};

	//TEST
	class TestHitTank final : public boop::Command {
	private:
		boop::GameObject* m_pGameObject;
	public:
		TestHitTank(boop::GameObject* component)
			: m_pGameObject{ component } {
		}
		~TestHitTank() { m_pGameObject = nullptr; delete m_pGameObject; }

		void Execute() override {
			m_pGameObject->GetComponent<Level>()->SetHitTank();
		};

		TestHitTank(const TestHitTank& other) = delete;
		TestHitTank(TestHitTank&& other) = delete;
		TestHitTank& operator=(const TestHitTank& other) = delete;
		TestHitTank& operator=(TestHitTank&& other) = delete;

	};
	class TestHitRecognizer final : public boop::Command {
	private:
		boop::GameObject* m_pGameObject;
	public:
		TestHitRecognizer(boop::GameObject* component)
			: m_pGameObject{ component } {
		}
		~TestHitRecognizer() { m_pGameObject = nullptr; delete m_pGameObject; }

		void Execute() override {
			m_pGameObject->GetComponent<Level>()->SetHitRecognizer();
		};

		TestHitRecognizer(const TestHitRecognizer& other) = delete;
		TestHitRecognizer(TestHitRecognizer&& other) = delete;
		TestHitRecognizer& operator=(const TestHitRecognizer& other) = delete;
		TestHitRecognizer& operator=(TestHitRecognizer&& other) = delete;

	};


	//--------------------------------------
	//MAIN MENU
	//--------------------------------------
	class ChangeScene final : public boop::Command {
	private:
		std::string m_ToScene;
	public:
		ChangeScene(const std::string toScene)
			: m_ToScene{toScene} {
		}
		~ChangeScene() { }

		void Execute() override {
			auto players = boop::SceneManager::GetInstance().GetActiveScene()->FindAllGameObjectByTag("level");
			for (auto& player : players)
			{
				player->GetParent()->GetComponent<BaseTank>()->ResetPosition();
			}

			boop::SceneManager::GetInstance().ChangeScene(m_ToScene);
			auto levels = boop::SceneManager::GetInstance().GetActiveScene()->FindAllGameObjectByTag("level");
			for (auto& level : levels)
			{
				level->GetComponent<Level>()->ResetPlayerCollision(boop::SceneManager::GetInstance().GetActiveScene());
			}
		};

		ChangeScene(const ChangeScene& other) = delete;
		ChangeScene(ChangeScene&& other) = delete;
		ChangeScene& operator=(const ChangeScene& other) = delete;
		ChangeScene& operator=(ChangeScene&& other) = delete;

	};

	class SkipLevel final : public boop::Command {
	private:

	public:
		SkipLevel()
		{
		}
		~SkipLevel() {}

		void Execute() override {

			auto activeScene = boop::SceneManager::GetInstance().GetActiveSceneId();
			int nextScene = (activeScene) % 3; // 3 is the number max of levels
			std::string nextSceneName = "level" + std::to_string(nextScene + 1); // level1, level2, level3
			ChangeScene(nextSceneName).Execute();

		};

		SkipLevel(const SkipLevel& other) = delete;
		SkipLevel(SkipLevel&& other) = delete;
		SkipLevel& operator=(const SkipLevel& other) = delete;
		SkipLevel& operator=(SkipLevel&& other) = delete;

	};


	class StartGame final : public boop::Command {
	private:
		GameLoader* m_pGameLoader;
	public:
		StartGame(GameLoader* component)
			: m_pGameLoader{ component } {
		}
		~StartGame() { }

		void Execute() override {
			m_pGameLoader->InitializeLevels();
			boop::SceneManager::GetInstance().ChangeScene("level1");
			auto levels = boop::SceneManager::GetInstance().GetActiveScene()->FindAllGameObjectByTag("level");
			for (auto& level : levels)
			{
				level->GetComponent<Level>()->ResetPlayerCollision(boop::SceneManager::GetInstance().GetActiveScene());
			}
			//set background music
			boop::ServiceLocator::GetSoundSystem()->StopAll();
			boop::ServiceLocator::GetSoundSystem()->PlayMusic("Background.wav", 0.5f);
		};

		StartGame(const StartGame& other) = delete;
		StartGame(StartGame&& other) = delete;
		StartGame& operator=(const StartGame& other) = delete;
		StartGame& operator=(StartGame&& other) = delete;

	};

	class ChangeGamemodeSelection final : public boop::Command {
	private:
		boop::GameObject* m_pGameObject;
		booble::GameLoader* m_pGameLoader;
	public:
		ChangeGamemodeSelection(boop::GameObject* component, booble::GameLoader* gameLoader)
			: m_pGameObject{ component }, m_pGameLoader{ gameLoader } {
		}
		~ChangeGamemodeSelection() { m_pGameObject = nullptr; delete m_pGameObject; }

		void Execute() override {
			int currentMode = m_pGameLoader->GetSelectedGamemode();
			int nextMode = (currentMode + 1) % 3; // 3 is the number of game modes
			m_pGameLoader->SetSelectedGamemode(nextMode);

			// Update the text
			std::string modeText;
			switch (static_cast<booble::GameMode>(nextMode)) {
			case booble::GameMode::SINGLEPLAYER:
				modeText = "SINGLEPLAYER";
				break;
			case booble::GameMode::MULTIPLAYER:
				modeText = "MULTIPLAYER";
				break;
			case booble::GameMode::COOP:
				modeText = "COOP";
				break;
			}

			m_pGameObject->GetComponent<boop::TextComponent>()->SetText("Gamemode: " + modeText);

		};

		ChangeGamemodeSelection(const ChangeGamemodeSelection& other) = delete;
		ChangeGamemodeSelection(ChangeGamemodeSelection&& other) = delete;
		ChangeGamemodeSelection& operator=(const ChangeGamemodeSelection& other) = delete;
		ChangeGamemodeSelection& operator=(ChangeGamemodeSelection&& other) = delete;

	};

};
