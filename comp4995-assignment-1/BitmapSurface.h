#pragma once

#include "d3dx9tex.h"

class BitmapSurface {

public:
	BitmapSurface(char* bitmapPath);

	HRESULT InitSurface(LPDIRECT3DDEVICE9 pDevice);

	LPDIRECT3DSURFACE9 getSurface();

private:
	LPDIRECT3DSURFACE9 mSurface;
	char* mPath;
	HBITMAP mHBitmap;
	BITMAP mBitmap;
};