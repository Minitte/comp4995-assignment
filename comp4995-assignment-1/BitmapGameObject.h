#pragma once

#include "GameObject2D.h";

class BitmapGameObject : public GameCore::GameObject2D {

public:

	BitmapGameObject(const char* bitmapPath);

	~BitmapGameObject();

	void Draw(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DSURFACE9 pSurface);

private:

	HBITMAP mHBitmap;

};