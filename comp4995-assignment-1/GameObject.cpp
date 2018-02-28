#include "GameObject.h"

GameObject::GameObject()
	: mX(0), mY(0), mZ(0)
	, mRotationX(0), mRotationY(0), mRotationZ(0)
	, mScaleX(1), mScaleY(1), mScaleZ(1)
{
}

GameObject::GameObject(float x, float y, float z)
	: mX(x), mY(y), mZ(z)
	, mRotationX(0), mRotationY(0), mRotationZ(0)
	, mScaleX(1), mScaleY(1), mScaleZ(1)
{
}

inline void GameObject::Translate(float x, float y, float z)
{
	mX += x;
	mY += y;
	mZ += z;
}

inline void GameObject::SetX(float x)
{
	mX = x;
}

inline void GameObject::SetY(float y)
{
	mY = y;
}

inline void GameObject::SetZ(float z)
{
	mZ = z;
}

inline void GameObject::RotateX(float rot)
{
	mRotationX += rot;
}

inline void GameObject::RotateY(float rot)
{
	mRotationY += rot;
}

inline void GameObject::RotateZ(float rot)
{
	mRotationZ += rot;
}

inline void GameObject::SetRotationX(float rot)
{
	mRotationX = rot;
}

inline void GameObject::SetRotationY(float rot)
{
	mRotationY = rot;
}

inline void GameObject::SetRotationZ(float rot)
{
	mRotationZ = rot;
}

inline void GameObject::ScaleX(float scale)
{
	mScaleX += scale;
}

inline void GameObject::ScaleY(float scale)
{
	mScaleY += scale;
}

inline void GameObject::ScaleZ(float scale)
{
	mScaleZ += scale;
}

inline void GameObject::SetScaleX(float scale)
{
	mScaleX = scale;
}

inline void GameObject::SetScaleY(float scale)
{
	mScaleY = scale;
}

inline void GameObject::SetScaleZ(float scale)
{
	mScaleZ = scale;
}
