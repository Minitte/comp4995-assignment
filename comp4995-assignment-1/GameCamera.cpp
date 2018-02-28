#include "GameCamera.h"

GameCamera::GameCamera(D3DXVECTOR3 position, D3DXVECTOR3 lookAt, LPDIRECT3DDEVICE9 pDevice)
	: mPosX(position.x), mPosY(position.y), mPosZ(position.z)
	, mLookX(lookAt.x), mLookY(lookAt.y), mLookZ(lookAt.z)
	, mPDevice(pDevice)
{
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	mUp = vUpVec;
	UpdateCamera();
}

void GameCamera::Translate(float x, float y, float z)
{
	mPosX += x;
	mPosY += y;
	mPosZ += z;
	mLookX += x;
	mLookY += y;
	mLookZ += z;
	UpdateCamera();
}

void GameCamera::SetPosition(D3DXVECTOR3 position)
{
	mPosX = position.x;
	mPosY = position.y;
	mPosZ = position.z;
	UpdateCamera();
}

void GameCamera::SetPosition(float x, float y, float z)
{
	mPosX = x;
	mPosY = y;
	mPosZ = z;
	UpdateCamera();
}

void GameCamera::LookAt(float x, float y, float z)
{
	mLookX = x;
	mLookY = y;
	mLookZ = z;
	UpdateCamera();
}

void GameCamera::Act()
{
	// ignore input handling if manual controls is disabled 
	if (!mEnableControl) {
		return;
	}

	float movementSpeed = 0.25f;
	if (GetAsyncKeyState('W'))
	{
		Translate(0, 0, -movementSpeed);
	}

	if (GetAsyncKeyState('A'))
	{
		Translate(movementSpeed, 0, 0);
	}

	if (GetAsyncKeyState('S'))
	{
		Translate(0, 0, movementSpeed);
	}

	if (GetAsyncKeyState('D'))
	{
		Translate(-movementSpeed, 0, 0);
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		Translate(0, movementSpeed, 0);
	}

	if (GetAsyncKeyState(VK_CONTROL))
	{
		Translate(0, -movementSpeed, 0);
	}
}

void GameCamera::UpdateCamera()
{
	// For our world matrix, we will just leave it as the identity
	D3DXMATRIXA16 matWorld;
	//D3DXMatrixRotationY(&matWorld, timeGetTime() / 1000.0f);
	D3DXMatrixRotationY(&matWorld, 0.0f);
	mPDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the 
	// origin, and define "up" to be in the y-direction.
	D3DXVECTOR3 pos(mPosX, mPosY, mPosZ);
	D3DXVECTOR3 look(mLookX, mLookY, mLookZ);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &pos, &look, &mUp);
	mPDevice->SetTransform(D3DTS_VIEW, &matView);

	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	mPDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void GameCamera::SetEnableControls(bool enableControl)
{
	mEnableControl = enableControl;
}

bool GameCamera::GetEnableControls()
{
	return mEnableControl;
}
