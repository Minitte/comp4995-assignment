#include "Game.h"

namespace GameCore {

	GameCore::Game::Game(GameWindow* pWindow)
		: mWindow(pWindow)
	{
		mGO2D = new std::vector<IGameObject2D*>();
	}

	int Game::GameLoop()
	{
		Render();

		if (GetAsyncKeyState(VK_ESCAPE))
			PostQuitMessage(0);

		return S_OK;
	}

	int Game::Render() 
	{
		HRESULT result;
		LPDIRECT3DSURFACE9 pBackSurf = 0;
		LPDIRECT3DSURFACE9 pSurface = 0;
		LPDIRECT3DDEVICE9 pDevice = mWindow->GetDevice();

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

		for (int i = 0; i < mGO2D->size(); i++) 
		{
			(*mGO2D)[i]->Draw(pDevice, pSurface);
		}

		return S_OK;
	}

	void Game::DisposeGameObjects()
	{
		mGO2D->clear();
		
		delete mGO2D;

		// and other stuff
	}

}
