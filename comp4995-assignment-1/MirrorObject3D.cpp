#include "MirrorObject3D.h"

MirrorObject3D::MirrorObject3D(MeshObject* pMeshObj)
	: GameObject() 
	, mPMeshObj(pMeshObj)
{
}

MirrorObject3D::~MirrorObject3D()
{
}

void MirrorObject3D::Act(int delta)
{
}

void MirrorObject3D::Draw(LPDIRECT3DDEVICE9 pDevice)
{

	//WORD numMats = mPMeshObj->getNumMaterials();
	LPD3DXMESH meshs = mPMeshObj->getMeshs();
	D3DMATERIAL9* mats = mPMeshObj->getMaterials();
	LPDIRECT3DTEXTURE9* texs = mPMeshObj->getTextures();

	LPDIRECT3DVERTEXBUFFER9 vertexBuff;
	meshs->GetVertexBuffer(&vertexBuff);
	DWORD numVert = meshs->GetNumVertices();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, true);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x1);
	pDevice->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	pDevice->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

	// disable writes to the depth and back buffers
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// draw the mirror to the stencil buffer
	pDevice->SetStreamSource(0, vertexBuff, 0, numVert);
	pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL); // wat
	pDevice->SetMaterial(&mats[0]);
	pDevice->SetTexture(0, texs[0]);
	D3DXMATRIXA16 trans;
	D3DXMatrixTranslation(&trans, mX, mY, mZ);
	pDevice->SetTransform(D3DTS_WORLD, &trans); // mirror position
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 18, 2);

	// re-enable depth writes
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	// position reflection for objects
	for (int i = 0; i < mReflectionObjects->size(); i++) {
		
		MeshGameObject3D* obj = (*mReflectionObjects)[i];
	
		// transforms
		D3DXMATRIX W, T, R;
		D3DXPLANE plane(0.0f, 0.0f, 1.0f, 0.0f); // xy plane
		D3DXMatrixReflect(&R, &plane);
		D3DXMatrixTranslation(&T, 
			obj->GetX(), obj->GetY(), obj->GetZ()); // actually suppose to be the objects.....
		W = T * R;

		//pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		
		pDevice->SetTransform(D3DTS_WORLD, &W);

		MeshObject* meshsObjRef = obj->GetPMeshObj();

		// render
		for (DWORD i = 0; i < meshsObjRef->getNumMaterials(); i++)
		{

			LPD3DXMESH meshsRef = meshsObjRef->getMeshs();
			D3DMATERIAL9* matsRef = meshsObjRef->getMaterials();
			LPDIRECT3DTEXTURE9* texsRef = meshsObjRef->getTextures();

			pDevice->SetMaterial(&matsRef[i]);
			pDevice->SetTexture(0, texsRef[i]);
			pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
			meshsRef->DrawSubset(i);
		}

	}

	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, false);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	
}

void MirrorObject3D::SetReflectionList(std::vector<MeshGameObject3D*>* reflectionObjects)
{
	mReflectionObjects = reflectionObjects;
}
