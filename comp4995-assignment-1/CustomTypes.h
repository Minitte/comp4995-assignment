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

struct BoundingBox
{
	BoundingBox();

	bool isPointInside(D3DXVECTOR3& p);

	D3DXVECTOR3 min;
	D3DXVECTOR3 max;
};