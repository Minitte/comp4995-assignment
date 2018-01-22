#pragma once

#include <vector>
#include <string>
#include "IGameObject2D.h"
#include "BitmapGameObject.h"
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
		std::vector<IGameObject2D*>* mGO2D;
		BitmapGameObject* mBitmapBG;

		// fps counter
		ID3DXFont* mFont;
		RECT mFpsRect;
		LARGE_INTEGER mTime;
		int mFrames;
		const char* mFPSText;

	};
}
