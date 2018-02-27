#include "MeshGameObject3D.h"

MeshGameObject3D::MeshGameObject3D(MeshObject* pMeshObj)
	:mPMeshObj(pMeshObj)
{
}

MeshGameObject3D::~MeshGameObject3D()
{
	
}

void MeshGameObject3D::draw(LPDIRECT3DDEVICE9 pDevice)
{

	DWORD numMats = mPMeshObj->getNumMaterials();
	LPD3DXMESH meshs = mPMeshObj->getMeshs();
	D3DMATERIAL9* mats = mPMeshObj->getMaterials();
	LPDIRECT3DTEXTURE9* texs = mPMeshObj->getTextures();

	// Meshes are divided into subsets, one for each material. Render them in
	// a loop
	for (DWORD i = 0; i < numMats; i++)
	{
		// Set the material and texture for this subset
		pDevice->SetMaterial(&mats[i]);
		pDevice->SetTexture(0, texs[i]);

		// Draw the mesh subset
		meshs->DrawSubset(i);
	}
}
