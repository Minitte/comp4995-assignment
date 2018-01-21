#include "BitmapGameObject.h"

BitmapGameObject::BitmapGameObject(const char* bitmapPath)
	: IGameObject2D()
	, mPath(bitmapPath)
{
	mHBitmap = (HBITMAP)LoadImage(NULL, bitmapPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(mHBitmap, sizeof(BITMAP), &mBitmap);
}

BitmapGameObject::~BitmapGameObject()
{

	DeleteObject(mHBitmap);

}

HRESULT BitmapGameObject::Draw(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DSURFACE9* ppSurface)
{
	HRESULT result;

	//create surface for bitmap
	result = pDevice->CreateOffscreenPlainSurface(mBitmap.bmWidth, mBitmap.bmHeight, D3DFMT_X8R8G8B8, D3DPOOL_SCRATCH, ppSurface, NULL);

	if (FAILED(result)) {
		return E_FAIL;
	}

	//load bitmap onto surface
	result = D3DXLoadSurfaceFromFileA(*ppSurface, NULL, NULL, mPath, NULL, D3DX_DEFAULT, 0, NULL);

	if (FAILED(result)) {
		return E_FAIL;
	}

	return S_OK;
}
