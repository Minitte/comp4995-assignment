#pragma once

#include <d3dx9.h>

struct CUSTOMVERTEX
{
	float x, y, z;
};

struct BoundingSphere
{
	//BoundingSphere();
	D3DXVECTOR3 center;
	float radius;
};