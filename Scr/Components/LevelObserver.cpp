#include "LevelObserver.h"
#include "../../BoopEngine/Boop/GameObject.h"
#include "../../BoopEngine/Boop/Scene/SceneManager.h"
#include "../GameCommands.h"

void LevelObserver::OnNotify(boop::Event event)
{
	if (event.id == boop::make_sdbm_hash("PlayerDied"))
	{
		auto changeScene = booble::ChangeScene("EndingScreen");
		changeScene.Execute();
	}

	if (event.id == boop::make_sdbm_hash("PlayerKillTank")
		|| event.id == boop::make_sdbm_hash("PlayerKillRecognizer"))
	{
		//check if there are no more players on the scene
		auto scene = boop::SceneManager::GetInstance().GetActiveScene();
		auto enemyInfo = scene->FindAllGameObjectByTag("enemy");

		int enemiesLeft = static_cast<int>(enemyInfo.size());
		
		for (auto& enemy : enemyInfo)
		{
			if (!enemy->IsGhost()) return;
			//no more enemies, cleared the level
			--enemiesLeft;
			
		}
		if (enemiesLeft <= 0)
		{
			auto goToNextLevel = booble::SkipLevel();
			goToNextLevel.Execute();
		}
	}
}
