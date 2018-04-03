#pragma once

#include <vector>
#include "BitmapSurface.h"
#include "GameWindow.h"
#include "TextGameObject2D.h"
#include "MeshGameObject3D.h"
#include "MirrorObject3D.h"
#include "MeshObject.h"
#include "GameCamera.h"
#include "BasicMeshInputHandler.h"


class MeshGameObject3D;

namespace GameCore {
	class Game {
	public:

		// constructor for the game engine
		Game(GameWindow* pWindow);

		// deconstructor / disposal of resources
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

		// creates a 3d mesh object
		MeshGameObject3D * Game::CreateMeshGameObject(MeshObject* mesh, float posX, float posY, float posZ, float rotX, float rotY, float rotZ);

	private:
		// window and device 
		GameWindow* mWindow;
		LPDIRECT3DDEVICE9 mPDevice;
		BitmapSurface* mBitmapSurface;

		// fps counter
		TextGameObject2D* mFpsText;
		LARGE_INTEGER mTime;
		int mFrames, mFPS;

		// game objects
		std::vector<GameObject*>* mGameObj;

		// 3d mesh game objects
		std::vector<MeshGameObject3D*>* mMeshObj;

		// camera
		GameCamera* mCamera;

		// input lift
		bool keyDown;

		// am light toggle
		bool mAmbientEnable;
		
		// mirror
		MirrorObject3D* mPMirrorObj;
	};
}
