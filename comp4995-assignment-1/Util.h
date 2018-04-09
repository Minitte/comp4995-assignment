#pragma once

#include "GameObject.h"

//
// Colors
//
const D3DXCOLOR      WHITE(D3DCOLOR_XRGB(255, 255, 255));
const D3DXCOLOR      BLACK(D3DCOLOR_XRGB(0, 0, 0));
const D3DXCOLOR        RED(D3DCOLOR_XRGB(255, 0, 0));
const D3DXCOLOR      GREEN(D3DCOLOR_XRGB(0, 255, 0));
const D3DXCOLOR       BLUE(D3DCOLOR_XRGB(0, 0, 255));
const D3DXCOLOR     YELLOW(D3DCOLOR_XRGB(255, 255, 0));
const D3DXCOLOR       CYAN(D3DCOLOR_XRGB(0, 255, 255));
const D3DXCOLOR    MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

DWORD FtoDw(float f);

// Desc: Return random float in [lowBound, highBound] interval.
float GetRandomFloat(float lowBound, float highBound);


// Desc: Returns a random vector in the bounds specified by min and max.
void GetRandomVector(
	D3DXVECTOR3* out,
	D3DXVECTOR3* min,
	D3DXVECTOR3* max);

template<class T> void Release(T t)
{
	if (t)
	{
		t->Release();
		t = 0;
	}
}

template<class T> void Delete(T t)
{
	if (t)
	{
		delete t;
		t = 0;
	}
}