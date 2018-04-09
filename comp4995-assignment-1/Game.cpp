#include "Game.h"

namespace GameCore {

	GameCore::Game::Game(GameWindow* pWindow)
		: mWindow(pWindow)
		, mFrames(0)
	{
		// context device
		mPDevice = mWindow->GetDevice();
		// Turn on the zbuffer
		mPDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		// Turn on ambient lighting 
		mPDevice->SetRenderState(D3DRS_AMBIENT, 0x009a9a9a); // ?rgb
		// enables lighting
		mPDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		if (mPDevice == nullptr)
		{
			mWindow->SetError("Cannot render because there is no device");
		}

		IniGameObj();
		SetupView();
	}

	Game::~Game()
	{
		for (int i = 0; i < mGameObj->size(); i++) 
		{
			delete (*mGameObj)[i];
		}

		delete mGameObj;
		delete mBitmapSurface;
		delete mCamera;
	}

	void Game::IniGameObj()
	{
		// baboon
		mBitmapSurface = new BitmapSurface("assets/baboon.bmp");
		mBitmapSurface->InitSurface(mPDevice);

		// fps counter
		mFpsText = new TextGameObject2D("?", 0, 0, 32, 16, mPDevice);

		// game objects list
		mGameObj = new std::vector<GameObject*>();

		// 3d mesh game objects list
		mMeshObj = new std::vector<MeshGameObject3D*>();

		MeshObject* airplaneMesh = new MeshObject(mPDevice, "assets/airplane2.x");
		
		MeshGameObject3D* airplaneObj = CreateMeshGameObject(airplaneMesh, -10, 0, 0, D3DXToRadian(-35.f), 0, 0);
		BasicMeshInputHandler* inputHandler = new BasicMeshInputHandler();
		airplaneObj->SetInputHandler(inputHandler);
		mGameObj->push_back((GameObject*)airplaneObj);
		mMeshObj->push_back(airplaneObj);
		airplaneObj->SetEnableHandler(true);

		// mirror vertex
		CUSTOMVERTEX vert[] = {
		{ -1, 1, 0 },	// triangle 1
		{ 1, 1, 0 },	// t1
		{ 1, -1, 0 },	// t1
		{ -1, 1, 0 },	// triangle 2
		{ 1, -1, 0 },	// t2
		{ -1, -1, 0 },	// t2
		};

		mPMirrorObj = new MirrorObject3D(vert, 6);
		mGameObj->push_back(mPMirrorObj);
		mPMirrorObj->SetReflectionList(mMeshObj);
	}


	int Game::GameLoop()
	{
		LARGE_INTEGER startTime, endTime, freq, frameTime;

		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&startTime);

		Act(0);

		Render();

		QueryPerformanceCounter(&endTime);
		frameTime.QuadPart = endTime.QuadPart - startTime.QuadPart;

		frameTime.QuadPart *= 1000;
		frameTime.QuadPart /= freq.QuadPart;

		mTime.QuadPart += frameTime.QuadPart;
		mFrames++;

		if (mTime.QuadPart >= 500) {
			mFpsText->SetText(mFrames * 2);
			mFrames = 0;
			mTime.QuadPart -= 500;
		}

		return S_OK;
	}

	void Game::Act(int delta) 
	{
		if (GetAsyncKeyState(VK_ESCAPE)) 
		{
			PostQuitMessage(0);
		}

		for (int i = 0; i < mGameObj->size(); i++) {
			(*mGameObj)[i]->Act(delta);
		}

		mCamera->Act();
	}

	void Game::Render()
	{
		LPDIRECT3DSURFACE9 pBackSurf = 0;

		//clear the display arera with colour black, ignore stencil buffer
		//mPDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 25), 1.0f, 0);

		// Clear the backbuffer and the zbuffer
		mPDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(128, 128, 128), 1.0f, 0);

		// renders the surface of baboon
		// RenderSurface();

		// render scene
		mPDevice->BeginScene();

		//set vertex shading
		mPDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL); // DirectX9 version

		// render 3d stuff
		for (int i = 0; i < mGameObj->size(); i++) {
			(*mGameObj)[i]->Draw(mPDevice);
		}

		// fps counter
		mFpsText->Draw();

		mPDevice->EndScene();

		//swap over buffer to primary surface
		mPDevice->Present(NULL, NULL, NULL, NULL);
	}

	void Game::SetupView()
	{
		D3DXVECTOR3 vEyePt(0.0f, 10.0f, -30.0f);
		D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
		mCamera = new GameCamera(vEyePt, vLookatPt, mPDevice);
	}

	int Game::RenderSurface() 
	{
		HRESULT result;
		LPDIRECT3DSURFACE9 pBackSurf = 0;

		mPDevice = mWindow->GetDevice();

		//get pointer to backbuffer
		result = mPDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackSurf);
		if (FAILED(result)) {
			mWindow->SetError("Couldn't get backbuffer");
			return result;
		}

		// copy to surface
		//result = D3DXLoadSurfaceFromSurface(pBackSurf, NULL, NULL, mBitmapSurface->getSurface(), NULL, NULL, D3DX_FILTER_TRIANGLE, 0);
		result = mPDevice->UpdateSurface(mBitmapSurface->getSurface(), NULL, pBackSurf, NULL);
		if (FAILED(result)) {
			mWindow->SetError("did not copy surface");
			return result;
		}

		pBackSurf->Release();//release lock
		pBackSurf = 0;

		return S_OK;
	}

	MeshGameObject3D * Game::CreateMeshGameObject(MeshObject* mesh, float posX, float posY, float posZ, float rotX, float rotY, float rotZ)
	{

		MeshGameObject3D* meshObj = new MeshGameObject3D(mesh, posX, posY, posZ);
		meshObj->RotateX(rotX);
		meshObj->RotateY(rotY);
		meshObj->RotateZ(rotZ);
		meshObj->CalculateTransform();

		return meshObj;
	}

}
