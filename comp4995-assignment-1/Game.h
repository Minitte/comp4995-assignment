#pragma once

#include <vector>
#include "GameObject2D.h"
#include "GameWindow.h"

namespace GameCore {
	class Game {
	public:

		Game(GameWindow* pWindow);

		int GameLoop();

		int Render();

		void DisposeGameObjects();

	private:
		GameWindow* mWindow;
		std::vector<GameObject2D*>* mGO2D;
	};
}
