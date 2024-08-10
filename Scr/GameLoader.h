#include "../BoopEngine/Boop/HelperFiles/Singleton.h"

namespace booble
{
	class GameLoader : public boop::Singleton<GameLoader>
	{
	private:

	public:
		void MakeGame();
	};
}