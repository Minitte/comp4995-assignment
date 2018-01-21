#pragma once

#include "IGameObject2D.h"

class BitmapGameObject : public GameCore::IGameObject2D {

public:

	BitmapGameObject(const char* bitmapPath);

	~BitmapGameObject();

	HRESULT Draw(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DSURFACE9* ppSurface);

private:

	const char* mPath;
	HBITMAP mHBitmap;
	BITMAP mBitmap;

};