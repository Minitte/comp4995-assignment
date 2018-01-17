#pragma once

#include <Windows.h>
#include <d3d9.h>
#include "d3dx9tex.h"
#include <stdio.h>
#include <tchar.h>

namespace GameCore {

	class GameWindow {

	public:

		HRESULT result;

		GameWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pstrCmdLine, int iCmdShow);

		void RegisterWindow(HINSTANCE hInstance);

		HRESULT IniGame();

		void SetError(char* szFormat, ...);

		HRESULT CloseGame();

	private:

		static char* strAppName;

		HWND mHandle;
		LPDIRECT3D9 mPD3D; // COM object
		LPDIRECT3DDEVICE9 mPDevice; // graphics device

		static long CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
		int InitDirect3DDevice(HWND hWndTarget, int Width, int Height, BOOL bWindowed, D3DFORMAT FullScreenFormat, LPDIRECT3D9 pD3D, LPDIRECT3DDEVICE9* ppDevice);
		void IniWindow(HINSTANCE hInstance);
	};

}