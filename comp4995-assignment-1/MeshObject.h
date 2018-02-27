#pragma once

#include <d3dx9.h>

class MeshObject {
public:
	// constructor
	MeshObject(LPDIRECT3DDEVICE9 pDevice, LPCTSTR xPath);

	// deconstructor
	~MeshObject();

	// loads mesh and texture from .x file
	int LoadFromXFile(LPDIRECT3DDEVICE9 pDevice, LPCTSTR xPath);

	LPD3DXMESH getMeshs();

	D3DMATERIAL9* getMaterials();

	LPDIRECT3DTEXTURE9* getTextures();

	DWORD getNumMaterials();

private:
	// pointer to structure holding all of the subsets of meshes
	LPD3DXMESH mPMeshs;

	// all of the materials
	D3DMATERIAL9* mPMaterials;

	// all of the texture
	LPDIRECT3DTEXTURE9* mPTextures;

	// number of materials
	DWORD mNumMaterials;
};