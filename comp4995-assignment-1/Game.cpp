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

		MeshObject* airplaneMesh = new MeshObject(mPDevice, "assets/airplane2.x");
		MeshGameObject3D* airplaneObj = new MeshGameObject3D(airplaneMesh, -10, 0, 0);
		((GameObject*)airplaneObj)->RotateX(D3DXToRadian(-35.f));
		BasicMeshInputHandler* inputHandler = new BasicMeshInputHandler();
		airplaneObj->SetInputHandler(inputHandler);
		airplaneObj->CalculateTransform();
		mGameObj->push_back((GameObject*)airplaneObj);

		MeshObject* sphereMesh = new MeshObject(mPDevice, "assets/chair.x");
		MeshGameObject3D* sphereObj = new MeshGameObject3D(sphereMesh, 10, 0, 0);
		BasicMeshInputHandler* inputHandler2 = new BasicMeshInputHandler();
		sphereObj->SetInputHandler(inputHandler2);
		sphereObj->CalculateTransform();
		mGameObj->push_back((GameObject*)sphereObj);

		D3DXCOLOR colour = D3DCOLOR_RGBA(255, 0, 0, 0);
		D3DLIGHT9 light;
		ZeroMemory(&light, sizeof(light));

		light.Type = D3DLIGHT_SPOT;
		light.Ambient = colour * 0.4f;
		light.Diffuse = colour;
		light.Specular = colour * 0.4f;
		light.Range = 5;
		light.Position = D3DXVECTOR3(-10, 5, 0);
		light.Direction = D3DXVECTOR3(0, -1, 0);

		mPDevice->SetLight(0, &light);
		//mPDevice->LightEnable(0, TRUE);

		colour = D3DCOLOR_RGBA(0, 255, 0, 0);
		ZeroMemory(&light, sizeof(light));
		light.Type = D3DLIGHT_POINT;
		light.Ambient = colour * 0.4f;
		light.Diffuse = colour;
		light.Specular = colour * 0.4f;
		light.Range = 5;
		light.Position = D3DXVECTOR3(0, 0, 0);

		mPDevice->SetLight(1, &light);
		//mPDevice->LightEnable(1, TRUE);

		colour = D3DCOLOR_RGBA(255, 200, 100, 0);
		ZeroMemory(&light, sizeof(light));
		light.Type = D3DLIGHT_DIRECTIONAL;
		light.Ambient = colour * 0.4f;
		light.Diffuse = colour;
		light.Specular = colour * 0.4f;
		light.Direction = D3DXVECTOR3(1, 0, 0);

		mPDevice->SetLight(2, &light);
		//mPDevice->LightEnable(2, TRUE);
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

		if (GetAsyncKeyState('1') && !keyDown)
		{
			keyDown = true;
			mCamera->SetEnableControls(true);
			((MeshGameObject3D*)(*mGameObj)[0])->SetEnableHandler(false);
			((MeshGameObject3D*)(*mGameObj)[1])->SetEnableHandler(false);
		}

		if (GetAsyncKeyState('2') && !keyDown)
		{
			keyDown = true;
			mCamera->SetEnableControls(false);
			((MeshGameObject3D*)(*mGameObj)[0])->SetEnableHandler(true);
			((MeshGameObject3D*)(*mGameObj)[1])->SetEnableHandler(false);
		}

		if (GetAsyncKeyState('3') && !keyDown)
		{
			keyDown = true;
			mCamera->SetEnableControls(false);
			((MeshGameObject3D*)(*mGameObj)[0])->SetEnableHandler(false);
			((MeshGameObject3D*)(*mGameObj)[1])->SetEnableHandler(true);
		}

		if (GetAsyncKeyState('0') && !keyDown)
		{
			keyDown = true;
			if (!mAmbientEnable) {
				mPDevice->SetRenderState(D3DRS_AMBIENT, 0x00000000); // ?rgb
			}
			else 
			{
				mPDevice->SetRenderState(D3DRS_AMBIENT, 0x009a9a9aa); // ?rgb
			}
			mAmbientEnable = !mAmbientEnable;
		}

		if (GetAsyncKeyState('9') && !keyDown)
		{
			keyDown = true;
			BOOL enable;
			mPDevice->GetLightEnable(0, &enable);
			mPDevice->LightEnable(0, !enable);
		}

		if (GetAsyncKeyState('8') && !keyDown)
		{
			keyDown = true;
			BOOL enable;
			mPDevice->GetLightEnable(1, &enable);
			mPDevice->LightEnable(1, !enable);
		}

		if (GetAsyncKeyState('7') && !keyDown)
		{
			keyDown = true;
			BOOL enable;
			mPDevice->GetLightEnable(2, &enable);
			mPDevice->LightEnable(2, !enable);
		}

		if (!GetAsyncKeyState('3') && !GetAsyncKeyState('2') && !GetAsyncKeyState('1') && 
			!GetAsyncKeyState('0') && !GetAsyncKeyState('9') && !GetAsyncKeyState('8') && !GetAsyncKeyState('7')) {
			keyDown = false;
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

}
