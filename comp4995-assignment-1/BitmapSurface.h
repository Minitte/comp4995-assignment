#pragma once

#include "d3dx9tex.h"

class BitmapSurface {

public:
	BitmapSurface(char* bitmapPath);

	// streches the surfaces that fits the back buffer
	HRESULT InitSurface(LPDIRECT3DDEVICE9 pDevice);

	// returns a surface that has the size of when InitSurface was called
	// if InitSurface was not called, nullptr will be returned
	LPDIRECT3DSURFACE9 getSurface();

private:
	LPDIRECT3DSURFACE9 mSurface;
	char* mPath;
	HBITMAP mHBitmap;
	BITMAP mBitmap;
};