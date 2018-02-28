#pragma once

#include <d3dx9.h>

class GameCamera {
public:
	GameCamera(D3DXVECTOR3 position, D3DXVECTOR3 lookAt, LPDIRECT3DDEVICE9 pDevice);

	// moves the camera by the given xyz
	void Translate(float x, float y, float z);

	// sets the position of the camera
	void SetPosition(D3DXVECTOR3 position);

	// sets the position of the camera
	void SetPosition(float x, float y, float z);

	// makes the camera look at xyz position
	void LookAt(float x, float y, float z);

	// rotates the camera around the xyz axis
	void Rotate(float x, float y, float z);

	// actions and updates before rendering
	void Act();

	// updates the camera position
	void UpdateCamera();

	// enables or disables the controls
	void SetEnableControls(bool enableControl);

	// getter for enable control bol
	bool GetEnableControls();

private:

	// enable or disable the manual camera controls
	bool mEnableControl;

	// world position of camera
	float mPosX, mPosY, mPosZ;

	// where the camera is looking at
	float mLookX, mLookY, mLookZ;

	// where the camera is looking at
	float mYaw, mPitch, mRoll;

	// the up vector of camera
	D3DXVECTOR3 mUp;

	// pointer to device
	LPDIRECT3DDEVICE9 mPDevice;
};