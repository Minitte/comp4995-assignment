#include "Game.h"

namespace GameCore {

	GameCore::Game::Game(GameWindow* pWindow)
		: mWindow(pWindow)
		, mFrames(0)
	{
		//mGO2D = new std::vector<IGameObject2D*>();
		mBitmapSurface = new BitmapSurface("baboon.bmp");
		mBitmapSurface->InitSurface(pWindow->GetDevice());

		mFpsText = new TextGameObject2D("?", 0, 0, 32, 16, pWindow->GetDevice());
	}

	Game::~Game()
	{
		//mGO2D->clear();
		delete mBitmapSurface;
	}


	int Game::GameLoop()
	{

		LARGE_INTEGER startTime, endTime, freq, frameTime;

		QueryPerformanceFrequency(&freq);
		QueryPerformanceCounter(&startTime);

		Render();

		if (GetAsyncKeyState(VK_ESCAPE)) {
			PostQuitMessage(0);
		}

		QueryPerformanceCounter(&endTime);
		frameTime.QuadPart = endTime.QuadPart - startTime.QuadPart;

		frameTime.QuadPart *= 1000;
		frameTime.QuadPart /= freq.QuadPart;

		mTime.QuadPart += frameTime.QuadPart;
		mFrames++;

		if (mTime.QuadPart >= 1000) {
			mFpsText->SetText(mFrames);
			mFrames = 0;
			mTime.QuadPart -= 1000;
		}

		return S_OK;
	}

	int Game::Render()
	{
		HRESULT result;
		LPDIRECT3DSURFACE9 pBackSurf = 0;
		LPDIRECT3DDEVICE9 pDevice;

		pDevice = mWindow->GetDevice();

		if (pDevice == nullptr)
		{
			mWindow->SetError("Cannot render because there is no device");
			return E_FAIL;
		}

		//clear the display arera with colour black, ignore stencil buffer
		pDevice->Clear(0, 0, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 25), 1.0f, 0);

		//get pointer to backbuffer
		result = pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackSurf);
		if (FAILED(result)) {
			mWindow->SetError("Couldn't get backbuffer");
		}

		// copy to surface
		//result = D3DXLoadSurfaceFromSurface(pBackSurf, NULL, NULL, mBitmapSurface->getSurface(), NULL, NULL, D3DX_FILTER_TRIANGLE, 0);
		result = pDevice->UpdateSurface(mBitmapSurface->getSurface(), NULL, pBackSurf, NULL);
		if (FAILED(result)) {
			mWindow->SetError("did not copy surface");
		}

		pBackSurf->Release();//release lock
		pBackSurf = 0;

		// draw fps
		pDevice->BeginScene();
		mFpsText->Draw();
		pDevice->EndScene();

		//swap over buffer to primary surface
		pDevice->Present(NULL, NULL, NULL, NULL); 

		return S_OK;
	}

}
