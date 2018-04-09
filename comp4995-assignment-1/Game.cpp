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

		// seed random number generator
		srand((unsigned int)time(0));

		//
		// Create Snow System.
		//
		BoundingBox boundingBox;
		boundingBox.min = D3DXVECTOR3(-25.0f, -25.0f, -25.0f);
		boundingBox.max = D3DXVECTOR3(25.0f, 25.0f, 25.0f);
		mSnowParticle = new SnowParticle(&boundingBox, 100);
		mSnowParticle->init(mPDevice, "assets/baboon.bmp");
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

		MeshObject* chairMesh = new MeshObject(mPDevice, "assets/sphere.x");
		MeshGameObject3D* chairObj = CreateMeshGameObject(chairMesh, 10, 0, 0, 0, 0, 0);
		BasicMeshInputHandler* inputHandler2 = new BasicMeshInputHandler();
		chairObj->SetInputHandler(inputHandler2);
		mGameObj->push_back((GameObject*)chairObj);
		mMeshObj->push_back(chairObj);

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

		if (GetAsyncKeyState(VK_LBUTTON)) {
			
			POINT pt;

			GetCursorPos(&pt);

			ScreenToClient(mWindow->GetHandle(), &pt);

			ShootScreenRay(pt.x, pt.y);
		}

		for (int i = 0; i < mGameObj->size(); i++) {
			(*mGameObj)[i]->Act(delta);
		}

		mSnowParticle->update(0.1f);

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

		// reset world
		D3DXMATRIX resetMat;
		D3DXMatrixIdentity(&resetMat);
		mPDevice->SetTransform(D3DTS_WORLD, &resetMat);

		// snow particle
		mSnowParticle->render();

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

	Ray Game::CalcPickingRay(int x, int y)
	{
		float px = 0.0f;
		float py = 0.0f;

		D3DVIEWPORT9 vp;
		mPDevice->GetViewport(&vp);

		D3DXMATRIX proj;
		mPDevice->GetTransform(D3DTS_PROJECTION, &proj);

		px = (((2.0f*x) / vp.Width) - 1.0f) / proj(0, 0);
		py = (((-2.0f*y) / vp.Height) + 1.0f) / proj(1, 1);

		Ray ray;
		ray.origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ray.direction = D3DXVECTOR3(px, py, 1.0f);

		return ray;
	}

	bool Game::RaySphereIntersectionTest(Ray * ray, BoundingSphere * sphere)
	{
		D3DXVECTOR3 v = ray->origin - sphere->center;
		float b = 2.0f * D3DXVec3Dot(&ray->direction, &v);
		float c = D3DXVec3Dot(&v, &v) - (sphere->radius * sphere->radius);

		// find the discriminant
		float discriminant = (b * b) - (4.0f * c);

		// test for imaginary number
		if (discriminant < 0.0f)
		{
			return false;
		}

		discriminant = sqrtf(discriminant);

		float s0 = (-b + discriminant) / 2.0f;
		float s1 = (-b - discriminant) / 2.0f;

		// if a solution is >= 0, then we intersected the sphere
		if (s0 >= 0.0f || s1 >= 0.0f)
		{
			return true;
		}

		return false;
	}

	void Game::ShootScreenRay(int x, int y)
	{
		// compute the ray in view space given the clicked screen point
		Ray ray = CalcPickingRay(x, y);
		// transform the ray to world space
		D3DXMATRIX view;
		mPDevice->GetTransform(D3DTS_VIEW, &view);
		D3DXMATRIX viewInverse;
		D3DXMatrixInverse(&viewInverse, 0, &view);
		ray.Transform(&viewInverse);

		// test for a hit
		for (int i = 0; i < mMeshObj->size(); i++) {
			float posX = (*mMeshObj)[i]->GetX();
			float posY = (*mMeshObj)[i]->GetY();
			float posZ = (*mMeshObj)[i]->GetZ();

			BoundingSphere bSphere;
			bSphere.radius = 1.f;
			bSphere.center = D3DXVECTOR3(posX, posY, posZ);

			(*mMeshObj)[i]->SetEnableHandler(false);

			if (RaySphereIntersectionTest(&ray, &bSphere)) 
			{
				for (int j = i; j < mMeshObj->size(); j++) {
					(*mMeshObj)[j]->SetEnableHandler(false);
				}

				mCamera->SetEnableControls(false);
				(*mMeshObj)[i]->SetEnableHandler(true);
				return;
			}

			mCamera->SetEnableControls(true);
		}
	}

	

}
