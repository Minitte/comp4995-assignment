#pragma once

#include "MeshGameObject3D.h"
#include <vector>

class MirrorObject3D : public GameObject
{

public:

	MirrorObject3D(MeshObject* pMeshObj);

	virtual ~MirrorObject3D();

	// pre render actions and updates
	virtual void Act(int delta);

	// renders the mesh object
	virtual void Draw(LPDIRECT3DDEVICE9 pDevice);

	// sets the list of objects that would be reflected
	void SetReflectionList(std::vector<MeshGameObject3D*>* reflectionObjects);

private:
	// pointer to object holding mesh data
	MeshObject * mPMeshObj;

	// list of game objects to be reflected
	std::vector<MeshGameObject3D*>* mReflectionObjects;
};