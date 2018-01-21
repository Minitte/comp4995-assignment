
#include <iostream>
#include <Windows.h>
#include "GameWindow.h"
#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pstrCmdLine, int iCmdShow) {

	MSG msg;

	GameCore::GameWindow* window = new GameCore::GameWindow(hInstance, hPrevInstance, pstrCmdLine, iCmdShow);

	GameCore::Game* game = new GameCore::Game(window);


	while (TRUE) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			game->GameLoop();
		}
	}

}