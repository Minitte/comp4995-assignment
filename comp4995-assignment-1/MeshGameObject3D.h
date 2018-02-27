#pragma once

#include <d3dx9.h>
#include "MeshObject.h"

// A class that stores and loads meshes with material/textures
class MeshGameObject3D {
public:
	// constructor
	MeshGameObject3D(MeshObject* pMeshObj);

	// deconstructor
	~MeshGameObject3D();

	// renders the mesh object
	void draw(LPDIRECT3DDEVICE9 pDevice);

private:
	// pointer to object holding mesh data
	MeshObject* mPMeshObj;
};