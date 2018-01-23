#include "BitmapSurface.h"

BitmapSurface::BitmapSurface(char * bitmapPath)
	: mPath(bitmapPath)
{
	mHBitmap = (HBITMAP)LoadImage(NULL, bitmapPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(mHBitmap, sizeof(BITMAP), &mBitmap);
}

HRESULT BitmapSurface::InitSurface(LPDIRECT3DDEVICE9 pDevice)
{
	HRESULT result;

	//create surface for bitmap
	result = pDevice->CreateOffscreenPlainSurface(mBitmap.bmWidth, mBitmap.bmHeight, D3DFMT_X8R8G8B8, D3DPOOL_SCRATCH, &mSurface, NULL);

	if (FAILED(result)) {
		return E_FAIL;
	}

	//load bitmap onto surface
	result = D3DXLoadSurfaceFromFile(mSurface, NULL, NULL, mPath, NULL, D3DX_DEFAULT, 0, NULL);

	if (FAILED(result)) {
		return E_FAIL;
	}

	return S_OK;
}

LPDIRECT3DSURFACE9 BitmapSurface::getSurface()
{
	return mSurface;
}
