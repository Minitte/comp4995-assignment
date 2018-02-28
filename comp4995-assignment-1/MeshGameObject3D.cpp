#include "MeshGameObject3D.h"

MeshGameObject3D::MeshGameObject3D(MeshObject* pMeshObj)
	: mPMeshObj(pMeshObj)
	, mX(0), mY(0), mZ(0)
	, mXAngle(0), mYAngle(0), mZAngle(0)
{
	CalculateTransform();
}

MeshGameObject3D::MeshGameObject3D(MeshObject* pMeshObj, float x, float y, float z)
	: mPMeshObj(pMeshObj)
	, mX(x), mY(y), mZ(z)
	, mXAngle(0), mYAngle(0), mZAngle(0)
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
		mInputHandler->Act(delta, this);
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

void MeshGameObject3D::Translate(float x, float y, float z)
{
	mX += x;
	mY += y;
	mZ += z;
	
	CalculateTransform();
}

void MeshGameObject3D::SetPosition(float x, float y, float z)
{
	mX = x;
	mY = y;
	mZ = z;

	CalculateTransform();
}

void MeshGameObject3D::Rotate(float xAngle, float yAngle, float zAngle)
{
	mXAngle += xAngle;
	mYAngle += yAngle;
	mZAngle += zAngle;

	CalculateTransform();
}

void MeshGameObject3D::SetXRotation(float angle)
{
	mXAngle = angle;

	CalculateTransform();
}

void MeshGameObject3D::SetYRotation(float angle)
{
	mYAngle = angle;

	CalculateTransform();
}

void MeshGameObject3D::SetZRotation(float angle)
{
	mZAngle = angle;

	CalculateTransform();
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
	if (mXAngle != 0) 
	{
		D3DXMatrixRotationX(&rot, mXAngle);
		D3DXMatrixMultiply(&mTransform, &mTransform, &rot);
	}

	if (mYAngle != 0)
	{
		D3DXMatrixRotationY(&rot, mYAngle);
		D3DXMatrixMultiply(&mTransform, &mTransform, &rot);
	}

	if (mZAngle != 0)
	{
		D3DXMatrixRotationZ(&rot, mZAngle);
		D3DXMatrixMultiply(&mTransform, &mTransform, &rot);
	}

	D3DXMATRIXA16 trans;
	D3DXMatrixTranslation(&trans, mX, mY, mZ);
	D3DXMatrixMultiply(&mTransform, &mTransform, &trans);
}


