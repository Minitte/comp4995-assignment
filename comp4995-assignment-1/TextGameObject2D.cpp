#include "TextGameObject2D.h"

TextGameObject2D::TextGameObject2D(std::string text, int x, int y, ID3DXFont* pFont)
	: mText(text)
	, mPFont(pFont)
{
	SetRect(&mRect, x, y, x + 100, y + 100);
}

TextGameObject2D::TextGameObject2D(std::string text, int x, int y, int height, u_int width, LPDIRECT3DDEVICE9 pDevice)
	: mText(text)
{
	SetRect(&mRect, x, y, x + 100, y + 100);
	D3DXCreateFont(pDevice, height, width, FW_NORMAL, 1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &mPFont);
}

TextGameObject2D::~TextGameObject2D()
{
	delete mPFont;
}

HRESULT TextGameObject2D::Draw()
{
	mPFont->DrawTextA(NULL, mText.c_str(), -1, &mRect, DT_CENTER, D3DCOLOR_XRGB(255, 255, 0));
	return S_OK;
}

void TextGameObject2D::SetText(std::string text)
{
	mText = text;
}

void TextGameObject2D::SetText(int text)
{
	mText = std::to_string(text);
}