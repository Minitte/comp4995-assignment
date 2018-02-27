#include "MeshObject.h"

MeshObject::MeshObject(LPDIRECT3DDEVICE9 pDevice, LPCTSTR xPath)
{
	LoadFromXFile(pDevice, xPath);
}

MeshObject::~MeshObject()
{
	if (mPMaterials != NULL)
		delete[] mPMaterials;

	if (mPTextures)
	{
		for (DWORD i = 0; i < mNumMaterials; i++)
		{
			if (mPTextures[i])
				mPTextures[i]->Release();
		}
		delete[] mPTextures;
	}
	if (mPMeshs != NULL)
		mPMeshs->Release();
}

int MeshObject::LoadFromXFile(LPDIRECT3DDEVICE9 pDevice, LPCTSTR xPath)
{
	HRESULT result;
	LPD3DXBUFFER pD3DXMtrlBuffer;

	// load from file
	result = D3DXLoadMeshFromX(xPath, D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&pD3DXMtrlBuffer, NULL,
		&mNumMaterials,
		&mPMeshs);

	if (FAILED(result))
	{
		return E_FAIL;
	}

	// extract materials and textures
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	mPMaterials = new D3DMATERIAL9[mNumMaterials];
	mPTextures = new LPDIRECT3DTEXTURE9[mNumMaterials];

	for (DWORD i = 0; i< mNumMaterials; i++)
	{
		// Copy the material
		mPMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		mPMaterials[i].Ambient = mPMaterials[i].Diffuse;

		mPTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
		{
			
			// If texture is not in current folder, try parent folder
			const TCHAR* strPrefix = TEXT("assets/");
			const int lenPrefix = lstrlen(strPrefix);
			TCHAR strTexture[MAX_PATH];
			lstrcpyn(strTexture, strPrefix, MAX_PATH);
			lstrcpyn(strTexture + lenPrefix, d3dxMaterials[i].pTextureFilename, MAX_PATH - lenPrefix);

			// Create the texture
			result = D3DXCreateTextureFromFile(pDevice, strTexture, &mPTextures[i]);
			if (FAILED(result))
			{
				return E_FAIL;
			}
		}
	}

	// Done with the material buffer
	pD3DXMtrlBuffer->Release();

	return S_OK;
}

LPD3DXMESH MeshObject::getMeshs()
{
	return mPMeshs;
}

D3DMATERIAL9 * MeshObject::getMaterials()
{
	return mPMaterials;
}

LPDIRECT3DTEXTURE9 * MeshObject::getTextures()
{
	return mPTextures;
}

DWORD MeshObject::getNumMaterials()
{
	return mNumMaterials;
}
