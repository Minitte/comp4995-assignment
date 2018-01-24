
#include "GameWindow.h"

namespace GameCore {

	GameWindow::GameWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pstrCmdLine, int iCmdShow)
		: mPD3D(nullptr)
		, mPDevice(nullptr)
	{
		//MSG msg;

		RegisterWindow(hInstance);

		IniWindow(hInstance);

		//g_hWndMain = hWnd;//set our global window handle

		ShowWindow(mHandle, iCmdShow);
		UpdateWindow(mHandle);

		if (FAILED(IniGame())) {
			//initialize Game
			SetError("Initialization Failed");
			CloseGame();
			result = E_FAIL;
		}

		result = S_OK;
	}

	void GameWindow::RegisterWindow(HINSTANCE hInstance)
	{
		WNDCLASSEX wc;

		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.lpfnWndProc = (GameWindow::WndProc);
		wc.hInstance = hInstance;
		wc.hbrBackground = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hIconSm = LoadIcon(NULL, IDI_HAND);
		wc.hCursor = LoadCursor(NULL, IDC_CROSS);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = TEXT("test-game");

		RegisterClassEx(&wc);
	}

	HRESULT GameWindow::IniGame()
	{
		HRESULT r = 0;//return values

		mPD3D = Direct3DCreate9(D3D_SDK_VERSION);//COM object
		if (mPD3D == NULL) {
			SetError("Could not create IDirect3D9 object");
			return E_FAIL;
		}

		r = InitDirect3DDevice(mHandle, 1280, 720, FALSE, D3DFMT_X8R8G8B8, mPD3D, &mPDevice);
		if (FAILED(r)) {//FAILED is a macro that returns false if return value is a failure - safer than using value itself
			SetError("Initialization of the device failed");
			return E_FAIL;
		}

		return S_OK;
	}

	void GameWindow::SetError(char * szFormat, ...)
	{

		char szBuffer[1024];
		va_list pArgList;

		va_start(pArgList, szFormat);

		//_vsntprintf(szBuffer, sizeof(szBuffer) / sizeof(char), szFormat, pArgList);
		_vsntprintf_s(szBuffer, sizeof(szBuffer) / sizeof(char), szFormat, pArgList);

		va_end(pArgList);

		OutputDebugString(szBuffer);
		OutputDebugString("\n");
		printf("error!!");
	}

	HRESULT GameWindow::CloseGame()
	{
		//release resources. First display adapter because COM object created it, then COM object
		if (mPDevice != nullptr)
			mPDevice->Release();

		if (mPD3D != nullptr)
			mPD3D->Release();

		return S_OK;
	}

	LPDIRECT3DDEVICE9 GameWindow::GetDevice()
	{
		return mPDevice;
	}

	LRESULT CALLBACK GameWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	int GameWindow::InitDirect3DDevice(HWND hWndTarget, int Width, int Height, BOOL bWindowed, D3DFORMAT FullScreenFormat, LPDIRECT3D9 pD3D, LPDIRECT3DDEVICE9* ppDevice) {
		D3DPRESENT_PARAMETERS d3dpp;//rendering info
		D3DDISPLAYMODE d3ddm;//current display mode info
		HRESULT r = 0;

		if (*ppDevice)
			(*ppDevice)->Release();

		ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
		r = pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm);
		if (FAILED(r)) {
			SetError("Could not get display adapter information");
			return E_FAIL;
		}

		d3dpp.BackBufferWidth = Width;
		d3dpp.BackBufferHeight = Height;
		d3dpp.BackBufferFormat = bWindowed ? d3ddm.Format : FullScreenFormat;
		d3dpp.BackBufferCount = 1;
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//D3DSWAPEFFECT_COPY;
		d3dpp.hDeviceWindow = hWndTarget;
		d3dpp.Windowed = bWindowed;
		d3dpp.EnableAutoDepthStencil = TRUE;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
		d3dpp.FullScreen_RefreshRateInHz = 0;//default refresh rate
		d3dpp.PresentationInterval = bWindowed ? 0 : D3DPRESENT_INTERVAL_IMMEDIATE;
		d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

		r = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWndTarget, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, ppDevice);
		if (FAILED(r)) {
			SetError("Could not create the render device");
			return E_FAIL;
		}

		//	g_DeviceHeight = Height;
		//	g_DeviceWidth = Width;

		//	g_SavedPresParams = d3dpp;
		return S_OK;
	}

	void GameWindow::IniWindow(HINSTANCE hInstance)
	{
		mHandle = CreateWindowEx(NULL,
			TEXT("test-game"),
			TEXT("test-game"),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			512, 512,
			NULL,
			NULL,
			hInstance,
			NULL);
	}

}