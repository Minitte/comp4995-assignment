#pragma once

#include <d3dx9.h>
#include "MeshGameObject3D.h"

class MeshGameObject3D;

class BasicMeshInputHandler {
public:

	virtual ~BasicMeshInputHandler();
	
	virtual void Act(int delta, MeshGameObject3D* gameObj);

	void SetEnabled(bool enable);

private:
	bool mEnable;
};