#pragma once

#include <string>
#include <d3d9.h>
#include "d3dx9tex.h"

class TextGameObject2D {
public:
	TextGameObject2D(std::string text, int x, int y, ID3DXFont* pFont );
	TextGameObject2D(std::string text, int x, int y, int height, u_int width, LPDIRECT3DDEVICE9 pDevice);
	~TextGameObject2D();

	HRESULT Draw();

	void SetText(std::string text);
	void SetText(int text);

private:
	RECT mRect;
	ID3DXFont* mPFont;
	std::string mText;
};