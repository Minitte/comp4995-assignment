#pragma once

#include <d3dx9.h>
#include "MeshGameObject3D.h"

class MeshGameObject3D;

class BasicMeshInputHandler {
public:

	virtual ~BasicMeshInputHandler();
	
	// actions and pre-render work 
	virtual void Act(int delta, MeshGameObject3D* gameObj);

	// changes the enable flag for the input handler
	void SetEnabled(bool enable);

private:
	bool mEnable;
};