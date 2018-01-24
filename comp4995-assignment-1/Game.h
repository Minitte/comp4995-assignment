#pragma once

#include <vector>
#include "IGameObject2D.h"
#include "BitmapSurface.h"
#include "GameWindow.h"
#include "TextGameObject2D.h"

namespace GameCore {
	class Game {
	public:

		Game(GameWindow* pWindow);
		~Game();

		// the game loop
		int GameLoop();

		// renders all game objects and surfaces
		int Render();

	private:
		GameWindow* mWindow;
		//std::vector<IGameObject2D*>* mGO2D;
		BitmapSurface* mBitmapSurface;

		// fps counter
		TextGameObject2D* mFpsText;
		LARGE_INTEGER mTime;
		int mFrames, mFPS;

	};
}
