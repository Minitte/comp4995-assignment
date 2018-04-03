#pragma once

#include <d3dx9.h>

class GameObject {

public:
	// default constructor
	GameObject();

	// constructor
	GameObject(float x, float y, float z);

	// act and pre render stuff
	virtual void Act(int delta) = 0;

	// render
	virtual void Draw(LPDIRECT3DDEVICE9 pDevice) = 0;

	// translate by x y z
	virtual inline void Translate(float x, float y, float z);

	// sets x
	virtual inline void SetX(float x);

	// sets y
	virtual inline void SetY(float y);

	// sets z
	virtual inline void SetZ(float z);

	// rotates around x-axis
	virtual inline void RotateX(float rot);
	
	// rotates around y-axis
	virtual inline void RotateY(float rot);

	// rotates around z-axis
	virtual inline void RotateZ(float rot);

	// sets Rotation x
	virtual inline void SetRotationX(float rot);

	// sets Rotation y
	virtual inline void SetRotationY(float rot);

	// sets Rotation z
	virtual inline void SetRotationZ(float rot);

	// change scaling in x direction
	virtual inline void ScaleX(float scale);

	// changes caling in y direction
	virtual inline void ScaleY(float scale);

	// change scaling in z direction
	virtual inline void ScaleZ(float scale);

	// sets scaling in x direction
	virtual inline void SetScaleX(float scale);

	// sets scaling in y direction
	virtual inline void SetScaleY(float scale);

	// sets scaling in z direction
	virtual inline void SetScaleZ(float scale);

	// gets the x position
	virtual inline float GetX();

	// gets the y position
	virtual inline float GetY();

	// gets the z position
	virtual inline float GetZ();

	// gets the x rotation
	virtual inline float GetRotationX();

	// gets the y rotation
	virtual inline float GetRotationY();

	// gets the z rotation
	virtual inline float GetRotationZ();

	// gets the x scale
	virtual inline float GetScaleX();

	// gets the y scale
	virtual inline float GetScaleY();

	// gets the z scale
	virtual inline float GetScaleZ();

protected:
	// translation
	float mX, mY, mZ;

	// rotation
	float mRotationX, mRotationY, mRotationZ;

	// scale
	float mScaleX, mScaleY, mScaleZ;
};