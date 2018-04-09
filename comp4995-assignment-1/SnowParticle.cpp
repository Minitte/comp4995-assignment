#include "SnowParticle.h"

SnowParticle::SnowParticle(BoundingBox* boundingBox, int numParticles)
{
	_boundingBox = *boundingBox;
	_size = 0.25f;
	_vbSize = 2048;
	_vbOffset = 0;
	_vbBatchSize = 512;

	for (int i = 0; i < numParticles; i++)
		addParticle();
}

void SnowParticle::resetParticle(Attribute* attribute)
{
	attribute->_isAlive = true;

	// get random x, z coordinate for the position of the snow flake.
	GetRandomVector(
		&attribute->_position,
		&_boundingBox.min,
		&_boundingBox.max);

	// no randomness for height (y-coordinate).  Snow flake
	// always starts at the top of bounding box.
	attribute->_position.y = _boundingBox.max.y;

	// snow flakes fall downwards and slightly to the left
	attribute->_velocity.x = GetRandomFloat(0.0f, 1.0f) * -3.0f;
	attribute->_velocity.y = GetRandomFloat(0.0f, 1.0f) * -10.0f;
	attribute->_velocity.z = 0.0f;

	// white snow flake
	attribute->_color = WHITE;
}

void SnowParticle::update(float timeDelta)
{
	std::list<Attribute>::iterator i;
	for (i = _particles.begin(); i != _particles.end(); i++)
	{
		i->_position += i->_velocity * timeDelta;

		// is the point outside bounds?
		if (_boundingBox.isPointInside(i->_position) == false)
		{
			// nope so kill it, but we want to recycle dead 
			// particles, so respawn it instead.
			resetParticle(&(*i));
		}
	}
}
