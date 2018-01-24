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
	LPDIRECT3DSURFACE9 pBackSurf = 0;
	LPDIRECT3DSURFACE9 pBitmapSurf = 0;
	D3DSURFACE_DESC desc;

	result = pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackSurf);
	if (FAILED(result)) {
		return E_FAIL;
	}

	pBackSurf->GetDesc(&desc);

	//create surface for bitmap
	result = pDevice->CreateOffscreenPlainSurface(mBitmap.bmWidth, mBitmap.bmHeight, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &pBitmapSurf, NULL);
	if (FAILED(result)) {
		return E_FAIL;
	}

	//load bitmap onto surface
	result = D3DXLoadSurfaceFromFile(pBitmapSurf, NULL, NULL, mPath, NULL, D3DX_DEFAULT, 0, NULL);
	if (FAILED(result)) {
		return E_FAIL;
	}

	// init mSurface
	result = pDevice->CreateOffscreenPlainSurface(desc.Width, desc.Height, D3DFMT_X8R8G8B8, D3DPOOL_SYSTEMMEM, &mSurface, NULL);
	if (FAILED(result)) {
		return E_FAIL;
	}

	// stretch and copy
	result = D3DXLoadSurfaceFromSurface(mSurface, NULL, NULL, pBitmapSurf, NULL, NULL, D3DX_FILTER_TRIANGLE, 0);
	if (FAILED(result)) {
		return E_FAIL;
	}

	pBackSurf->Release();
	pBitmapSurf->Release();

	return S_OK;
}

LPDIRECT3DSURFACE9 BitmapSurface::getSurface()
{
	return mSurface;
}
