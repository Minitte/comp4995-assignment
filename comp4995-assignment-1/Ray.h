#pragma once

#include <d3dx9.h>

class Ray 
{
public:
	D3DXVECTOR3 origin;
	D3DXVECTOR3 direction;

	void Transform(D3DXMATRIX* T);
};