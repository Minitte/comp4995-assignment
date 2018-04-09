#include "Ray.h"

void Ray::Transform(D3DXMATRIX * T)
{
	// transform the ray's origin, w = 1.
	D3DXVec3TransformCoord(
		&origin,
		&origin,
		T);
	// transform the ray's direction, w = 0.
	D3DXVec3TransformNormal(
		&direction,
		&direction,
		T);
	// normalize the direction
	D3DXVec3Normalize(&direction, &direction);
}
