#include "Game.h"

namespace GameCore {

	GameCore::Game::Game(GameWindow* pWindow)
		: mWindow(pWindow)
		, mFrames(0)
	{
		mGO2D = new std::vector<IGameObject2D*>();
		mBitmapBG = new BitmapGameObject("baboon.bmp");

		mFPSText = "0";

		// create font
		mFont = 0;
		D3DXCreateFont(pWindow->GetDevice(), 40, 40, FW_NORMAL, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, "Arial", &mFont);
		SetRect(&mFpsRect, 1, 1, 100, 100);
	}

	int Game::GameLoop()
	{
		Render();

		if (GetAsyncKeyState(VK_ESCAPE)) {
			PostQuitMessage(0);
		}

		return S_OK;
	}

	int Game::Render()
	{
		HRESULT result;
		LPDIRECT3DSURFACE9 pBackSurf = 0;
		LPDIRECT3DSURFACE9 pSurface = 0;
		LPDIRECT3DDEVICE9 pDevice;
		LARGE_INTEGER startTime, endTime, freq, frameTime;

		//QueryPerformanceFrequency(&freq);
		//QueryPerformanceCounter(&startTime);

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

		// set the bitmap on surface
		result = mBitmapBG->Draw(pDevice, &pSurface);
		if (FAILED(result)) {
			mWindow->SetError("could not load bitmap surface");
		}

		// copy to surface
		result = D3DXLoadSurfaceFromSurface(pBackSurf, NULL, NULL, pSurface, NULL, NULL, D3DX_FILTER_TRIANGLE, 0);
		if (FAILED(result)) {
			mWindow->SetError("did not copy surface");
		}

		pSurface->Release();
		pSurface = 0;

		pBackSurf->Release();//release lock
		pBackSurf = 0;

		// draw fps
		RECT rect;
		SetRect(&rect, 0, 0, 100, 100);
		mFont->DrawTextA(NULL, "Hello World", -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 0));

		pDevice->Present(NULL, NULL, NULL, NULL);//swap over buffer to primary surface

		//QueryPerformanceCounter(&endTime);
		//frameTime.QuadPart = endTime.QuadPart - startTime.QuadPart;

		//frameTime.QuadPart *= 1000;
		//frameTime.QuadPart /= freq.QuadPart;

		//mTime.QuadPart += frameTime.QuadPart;
		//mFrames++;

		//if (mTime.QuadPart >= 1000) {
		//	mFPSText = std::to_string(mFrames).c_str();
		//	mFrames = 0;
		//	mTime.QuadPart -= 0;
		//	//std::cout << mFPSText << std::endl;
		//}

		return S_OK;
	}

	void Game::DisposeGameObjects()
	{
		mGO2D->clear();

		delete mGO2D;

		// and other stuff
	}

}
