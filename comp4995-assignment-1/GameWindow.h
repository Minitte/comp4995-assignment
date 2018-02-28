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

		// constructor for a win32 window for the game
		GameWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pstrCmdLine, int iCmdShow);

		// sets an error to be reported
		void SetError(char* szFormat, ...);

		// cleans up resources of the window
		HRESULT CloseGame();

		// returns a pointer for device
		LPDIRECT3DDEVICE9 GetDevice();

	private:

		// handles and pointers to certain resources
		HWND mHandle;
		LPDIRECT3D9 mPD3D; // COM object
		LPDIRECT3DDEVICE9 mPDevice; // graphics device

		// wnd proc
		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		
		// window and device setup
		void RegisterWindow(HINSTANCE hInstance);
		void IniWindow(HINSTANCE hInstance);
		HRESULT IniGame();
		int InitDirect3DDevice(HWND hWndTarget, int Width, int Height, BOOL bWindowed, D3DFORMAT FullScreenFormat, LPDIRECT3D9 pD3D, LPDIRECT3DDEVICE9* ppDevice);
	};

}