#include "MirrorObject3D.h"

MirrorObject3D::MirrorObject3D(CUSTOMVERTEX vertices[], int numVertice)
	: GameObject()
	, mVertices(vertices)
	, mNumVertice(numVertice)
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

	LPDIRECT3DVERTEXBUFFER9 vertexBuff;
	pDevice->CreateVertexBuffer(mNumVertice * sizeof(CUSTOMVERTEX), 0, D3DFVF_NORMAL, D3DPOOL_MANAGED, &vertexBuff, NULL);

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
	pDevice->SetStreamSource(0, vertexBuff, 0, mNumVertice);
	pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL); // wat
	//pDevice->SetMaterial(&mats[0]);
	//pDevice->SetTexture(0, texs[0]);
	D3DXMATRIXA16 trans;
	D3DXMatrixTranslation(&trans, mX, mY, mZ);
	pDevice->SetTransform(D3DTS_WORLD, &trans); // mirror position
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, mNumVertice / 3);

	// re-enable depth writes
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	pDevice->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

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

		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		
		pDevice->SetTransform(D3DTS_WORLD, &W);

		MeshObject* meshsObjRef = obj->GetPMeshObj();

		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		// render
		for (DWORD i = 0; i < meshsObjRef->getNumMaterials(); i++)
		{

			LPD3DXMESH meshsRef = meshsObjRef->getMeshs();
			D3DMATERIAL9* matsRef = meshsObjRef->getMaterials();
			LPDIRECT3DTEXTURE9* texsRef = meshsObjRef->getTextures();

			pDevice->SetMaterial(&matsRef[i]);
			pDevice->SetTexture(0, texsRef[i]);
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
