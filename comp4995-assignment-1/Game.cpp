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
		mPDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

		if (mPDevice == nullptr)
		{
			mWindow->SetError("Cannot render because there is no device");
		}

		// baboon
		mBitmapSurface = new BitmapSurface("assets/best_bg.bmp");
		mBitmapSurface->InitSurface(mPDevice);

		// fps counter
		mFpsText = new TextGameObject2D("?", 0, 0, 32, 16, mPDevice);

		// game objects
		mGameObj = new std::vector<MeshGameObject3D*>();

		MeshObject* tigerMesh = new MeshObject(mPDevice, "assets/tiger.x");
		MeshGameObject3D* tigerObj = new MeshGameObject3D(tigerMesh);
		mGameObj->push_back(tigerObj);
	}

	Game::~Game()
	{
		for (int i = 0; i < mGameObj->size(); i++) 
		{
			delete (*mGameObj)[i];
		}

		delete mGameObj;
		delete mBitmapSurface;
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
		if (GetAsyncKeyState(VK_ESCAPE)) {
			PostQuitMessage(0);
		}
	}

	void Game::Render()
	{
		LPDIRECT3DSURFACE9 pBackSurf = 0;

		//clear the display arera with colour black, ignore stencil buffer
		//mPDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 25), 1.0f, 0);

		// Clear the backbuffer and the zbuffer
		mPDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

		// renders the surface of baboon
		RenderSurface();

		SetupView();

		// render scene
		mPDevice->BeginScene();

		// render 3d stuff
		for (int i = 0; i < mGameObj->size(); i++) {
			(*mGameObj)[i]->draw(mPDevice);
		}

		// fps counter
		mFpsText->Draw();

		mPDevice->EndScene();

		//swap over buffer to primary surface
		mPDevice->Present(NULL, NULL, NULL, NULL);
	}

	void Game::SetupView()
	{
		// For our world matrix, we will just leave it as the identity
		D3DXMATRIXA16 matWorld;
		//D3DXMatrixRotationY(&matWorld, timeGetTime() / 1000.0f);
		D3DXMatrixRotationY(&matWorld, 0.0f);
		mPDevice->SetTransform(D3DTS_WORLD, &matWorld);

		// Set up our view matrix. A view matrix can be defined given an eye point,
		// a point to lookat, and a direction for which way is up. Here, we set the
		// eye five units back along the z-axis and up three units, look at the 
		// origin, and define "up" to be in the y-direction.
		D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
		D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
		mPDevice->SetTransform(D3DTS_VIEW, &matView);

		// For the projection matrix, we set up a perspective transform (which
		// transforms geometry from 3D view space to 2D viewport space, with
		// a perspective divide making objects smaller in the distance). To build
		// a perpsective transform, we need the field of view (1/4 pi is common),
		// the aspect ratio, and the near and far clipping planes (which define at
		// what distances geometry should be no longer be rendered).
		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
		mPDevice->SetTransform(D3DTS_PROJECTION, &matProj);
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

}
