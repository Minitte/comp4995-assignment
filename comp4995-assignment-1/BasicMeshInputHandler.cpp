#include "BasicMeshInputHandler.h"

BasicMeshInputHandler::~BasicMeshInputHandler()
{
}

void BasicMeshInputHandler::Act(int delta, MeshGameObject3D* gameObj)
{
	float movementSpeed = 0.25f;

	if (GetAsyncKeyState('W'))
	{
		gameObj->Translate(0, 0, -movementSpeed);
	}

	if (GetAsyncKeyState('A'))
	{
		gameObj->Translate(movementSpeed, 0, 0);
	}

	if (GetAsyncKeyState('S'))
	{
		gameObj->Translate(0, 0, movementSpeed);
	}

	if (GetAsyncKeyState('D'))
	{
		gameObj->Translate(-movementSpeed, 0, 0);
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		gameObj->Translate(0, movementSpeed, 0);
	}

	if (GetAsyncKeyState(VK_CONTROL))
	{
		gameObj->Translate(0, -movementSpeed, 0);
	}

}

void BasicMeshInputHandler::SetEnabled(bool enable)
{
	mEnable = enable;
}
