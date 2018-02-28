#include "BasicMeshInputHandler.h"

BasicMeshInputHandler::~BasicMeshInputHandler()
{
}

int BasicMeshInputHandler::Act(int delta, GameObject* gameObj)
{
	float movementSpeed = 0.25f;
	int numAction = 0;

	if (GetAsyncKeyState('W'))
	{
		numAction++;
		gameObj->Translate(0, 0, movementSpeed);
	}

	if (GetAsyncKeyState('A'))
	{
		numAction++;
		gameObj->Translate(-movementSpeed, 0, 0);
	}

	if (GetAsyncKeyState('S'))
	{
		numAction++;
		gameObj->Translate(0, 0, -movementSpeed);
	}

	if (GetAsyncKeyState('D'))
	{
		numAction++;
		gameObj->Translate(movementSpeed, 0, 0);
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		numAction++;
		gameObj->Translate(0, movementSpeed, 0);
	}

	if (GetAsyncKeyState(VK_CONTROL))
	{
		numAction++;
		gameObj->Translate(0, -movementSpeed, 0);
	}

	if (GetAsyncKeyState('Q'))
	{
		numAction++;
		gameObj->RotateY(-0.05f);
	}

	if (GetAsyncKeyState('E'))
	{
		numAction++;
		gameObj->RotateY(0.05f);
	}

	if (GetAsyncKeyState('R'))
	{
		numAction++;
		gameObj->RotateX(0.05f);
	}

	if (GetAsyncKeyState('F'))
	{
		numAction++;
		gameObj->RotateX(-0.05f);
	}

	if (GetAsyncKeyState('Z'))
	{
		numAction++;
		gameObj->RotateZ(0.05f);
	}

	if (GetAsyncKeyState('X'))
	{
		numAction++;
		gameObj->RotateZ(-0.05f);
	}

	return numAction;
}
