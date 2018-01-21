#pragma once

#include "IGameObject2D.h"

class BitmapGameObject : public GameCore::IGameObject2D {

public:

	BitmapGameObject(char* bitmapPath);

	~BitmapGameObject();

	HRESULT Draw(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DSURFACE9* ppSurface);

private:

	char* mPath;
	HBITMAP mHBitmap;
	BITMAP mBitmap;

};