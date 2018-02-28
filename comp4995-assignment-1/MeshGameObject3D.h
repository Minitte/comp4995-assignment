#pragma once

#include "MeshObject.h"
#include "BasicMeshInputHandler.h"
#include "GameObject.h"

// A class that stores and loads meshes with material/textures
class MeshGameObject3D : GameObject{
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

	// sets the input handler for this game object
	void SetInputHandler(BasicMeshInputHandler* handler);

	// sets the flag to enable or disable the input handler
	void SetEnableHandler(bool enable);

	// gets the bool value that enable or disables 
	bool GetEnableHandler();

	// Calulates the entire transform
	void CalculateTransform();

private:
	// pointer to object holding mesh data
	MeshObject* mPMeshObj;
	
	// transform matrix
	D3DXMATRIXA16 mTransform;

	// input handler
	bool mEnableHandler;
	BasicMeshInputHandler* mInputHandler;
};