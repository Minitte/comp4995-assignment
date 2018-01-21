#pragma once

#include <d3d9.h>
#include "d3dx9tex.h"

namespace GameCore {

	class IGameObject2D {

	public:

		virtual ~IGameObject2D();

		virtual void Draw(LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DSURFACE9 pSurface) = 0;
	};

}

