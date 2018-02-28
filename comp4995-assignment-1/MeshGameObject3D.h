#pragma once

#include <d3dx9.h>
#include "MeshObject.h"
#include "BasicMeshInputHandler.h"

class BasicMeshInputHandler;

// A class that stores and loads meshes with material/textures
class MeshGameObject3D {
public:
	// constructor with starting position as 0, 0, 0
	MeshGameObject3D(MeshObject* pMeshObj);

	// constructor with starting positions defined
	MeshGameObject3D(MeshObject* pMeshObj, float x, float y, float z);

	// deconstructor
	~MeshGameObject3D();

	// pre render actions and updates
	void Act(int delta);

	// renders the mesh object
	void Draw(LPDIRECT3DDEVICE9 pDevice);

	// moves game object in "meters"
	void Translate(float x, float y, float z);

	// sets game object's position in "meters"
	void SetPosition(float x, float y, float z);

	// rotates the gameobject by the angle given in radians
	void Rotate(float xAngle, float yAngle, float zAngle);

	// sets rotation angle around x-axis
	void SetXRotation(float angle);

	// sets rotation angle around y-axis
	void SetYRotation(float angle);

	// sets rotation angle around z-axis
	void SetZRotation(float angle);

	void SetInputHandler(BasicMeshInputHandler* handler);

	void SetEnableHandler(bool enable);

private:
	// Calulates the entire transform
	void CalculateTransform();

	// pointer to object holding mesh data
	MeshObject* mPMeshObj;

	// transform stuff
	float mX, mY, mZ;
	float mXAngle, mYAngle, mZAngle;
	D3DXMATRIXA16 mTransform;

	// input handler
	bool mEnableHandler;
	BasicMeshInputHandler* mInputHandler;
};