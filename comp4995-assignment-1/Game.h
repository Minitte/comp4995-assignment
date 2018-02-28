#pragma once

#include <vector>
#include "BitmapSurface.h"
#include "GameWindow.h"
#include "TextGameObject2D.h"
#include "MeshGameObject3D.h"
#include "MeshObject.h"
#include "GameCamera.h"
#include "BasicMeshInputHandler.h"


class MeshGameObject3D;

namespace GameCore {
	class Game {
	public:

		Game(GameWindow* pWindow);
		~Game();

		// ini game objects
		void IniGameObj();

		// the game loop
		int GameLoop();
		
		// actions and pre render calulations
		void Act(int delta);

		// renders all game objects and surfaces
		void Render();

		// setup view
		void SetupView();

		// copies and renders the surface
		int RenderSurface();

	private:
		GameWindow* mWindow;
		LPDIRECT3DDEVICE9 mPDevice;
		BitmapSurface* mBitmapSurface;


		// fps counter
		TextGameObject2D* mFpsText;
		LARGE_INTEGER mTime;
		int mFrames, mFPS;

		// 3d game objects
		std::vector<MeshGameObject3D*>* mGameObj;

		// camera
		GameCamera* mCamera;

		// input lift
		bool keyDown;
	};
}
