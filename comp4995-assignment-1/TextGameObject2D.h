#pragma once

#include <string>
#include <d3d9.h>
#include "d3dx9tex.h"

class TextGameObject2D {
public:
	/**
		Constructor for a TextGameObject2D. This object holds the text to be drawn on a Draw call

		@param text - The text to be draw.
		@param x - the upper left corner x position of the text
		@param y - the upper left corner y position of the text
		@param pFont - a pointer to a font object which is used for drawing the text
	*/
	TextGameObject2D(std::string text, int x, int y, ID3DXFont* pFont );

	/**
		Constructor for a TextGameObject2D. This object holds the text to be drawn on a Draw call

		@param text - The text to be draw.
		@param x - the upper left corner x position of the text
		@param y - the upper left corner y position of the text
		@param height - the height of each character in the text
		@param width - the width of each character in the text
		@param pDevice - pointer to the device which is used to create a font object
	*/	
	TextGameObject2D(std::string text, int x, int y, int height, u_int width, LPDIRECT3DDEVICE9 pDevice);
	
	~TextGameObject2D();

	// draws text
	HRESULT Draw();
	
	// sets the text
	void SetText(std::string text);

	// converts the int to text
	void SetText(int text);

private:
	/** 
		The RECT struct that hold the information
	*/
	RECT mRect;

	/** 
		Pointer to a font object that is used for drawing the text
	*/
	ID3DXFont* mPFont;

	/** 
		Text to be draw on the screen
	*/
	std::string mText;
};