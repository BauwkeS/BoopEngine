#include "LevelObserver.h"
#include "../../BoopEngine/Boop/GameObject.h"
#include "../GameCommands.h"

void LevelObserver::OnNotify(boop::Event event)
{
	if (event.id == boop::make_sdbm_hash("PlayerDied"))
	{
		auto changeScene = booble::ChangeScene("EndingScreen");
		changeScene.Execute();
	}
}
