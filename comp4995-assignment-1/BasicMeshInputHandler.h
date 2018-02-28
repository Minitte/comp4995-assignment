#pragma once

#include "GameObject.h"

class BasicMeshInputHandler {
public:

	virtual ~BasicMeshInputHandler();
	
	// actions and pre-render work 
	virtual int Act(int delta, GameObject* gameObj);

};