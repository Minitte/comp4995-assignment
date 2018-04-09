#include "CustomTypes.h"

BoundingBox::BoundingBox()
{
	// infinite small 
	min.x = INFINITY;
	min.y = INFINITY;
	min.z = INFINITY;

	max.x = -INFINITY;
	max.y = -INFINITY;
	max.z = -INFINITY;
}

bool BoundingBox::isPointInside(D3DXVECTOR3 & p)
{
	if (p.x >= min.x && p.y >= min.y && p.z >= min.z &&
		p.x <= max.x && p.y <= max.y && p.z <= max.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}
