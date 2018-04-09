#pragma once

#include "ParticleSystem.h"

class SnowParticle : public PSystem
{
public:
	SnowParticle(BoundingBox* boundingBox, int numParticles);
	void resetParticle(Attribute* attribute);
	void update(float timeDelta);
};

class Firework : public PSystem
{
public:
	Firework(D3DXVECTOR3* origin, int numParticles);
	void resetParticle(Attribute* attribute);
	void update(float timeDelta);
	void preRender();
	void postRender();
};