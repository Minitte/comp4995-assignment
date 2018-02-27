#pragma once

#include "d3dx9tex.h"

class BitmapSurface {

public:
	/** 
		Constructor for a bitmap surface

		@param bitmapPath - the path of the bitmap
	*/
	BitmapSurface(char* bitmapPath);

	/**
		Initalizes the surface with the correct size from the backbuffer from device 9
	
		@param pDevice - a pointer to the device used by the game
	*/
	HRESULT InitSurface(LPDIRECT3DDEVICE9 pDevice);

	/**
		A getter function for the surface.
		
		@return A surface containing the bitmap will be returned if InitSurface was already called
				A null will be returned if InitSurface was not called properly first.
	*/
	LPDIRECT3DSURFACE9 getSurface();

private:
	LPDIRECT3DSURFACE9 mSurface;
	char* mPath;
	HBITMAP mHBitmap;
	BITMAP mBitmap;
};