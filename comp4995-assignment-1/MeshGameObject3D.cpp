#include "MeshGameObject3D.h"

MeshGameObject3D::MeshGameObject3D(MeshObject* pMeshObj)
	: mPMeshObj(pMeshObj)
	, GameObject()
{
	CalculateTransform();
}

MeshGameObject3D::MeshGameObject3D(MeshObject* pMeshObj, float x, float y, float z)
	: mPMeshObj(pMeshObj)
	, GameObject(x, y, z)
{
	CalculateTransform();
}

MeshGameObject3D::~MeshGameObject3D()
{
}

void MeshGameObject3D::Act(int delta)
{
	if (mEnableHandler) 
	{
		if (mInputHandler->Act(delta, this)) 
		{
			CalculateTransform();
		}
	}
}

void MeshGameObject3D::Draw(LPDIRECT3DDEVICE9 pDevice)
{

	DWORD numMats = mPMeshObj->getNumMaterials();
	LPD3DXMESH meshs = mPMeshObj->getMeshs();
	D3DMATERIAL9* mats = mPMeshObj->getMaterials();
	LPDIRECT3DTEXTURE9* texs = mPMeshObj->getTextures();

	

	pDevice->SetTransform(D3DTS_WORLD, &mTransform);

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

void MeshGameObject3D::SetInputHandler(BasicMeshInputHandler * handler)
{
	mInputHandler = handler;
}

void MeshGameObject3D::SetEnableHandler(bool enable)
{
	mEnableHandler = enable;
}

bool MeshGameObject3D::GetEnableHandler()
{
	return mEnableHandler;
}

void MeshGameObject3D::CalculateTransform()
{
	D3DXMatrixIdentity(&mTransform);

	D3DXMATRIXA16 rot;
	if (mRotationX != 0) 
	{
		D3DXMatrixRotationX(&rot, mRotationX);
		D3DXMatrixMultiply(&mTransform, &mTransform, &rot);
	}

	if (mRotationY != 0)
	{
		D3DXMatrixRotationY(&rot, mRotationY);
		D3DXMatrixMultiply(&mTransform, &mTransform, &rot);
	}

	if (mRotationZ != 0)
	{
		D3DXMatrixRotationZ(&rot, mRotationZ);
		D3DXMatrixMultiply(&mTransform, &mTransform, &rot);
	}

	D3DXMATRIXA16 trans;
	D3DXMatrixTranslation(&trans, mX, mY, mZ);
	D3DXMatrixMultiply(&mTransform, &mTransform, &trans);
}

MeshObject * MeshGameObject3D::GetPMeshObj()
{
	return mPMeshObj;
}


