#pragma once

class GameObject {

public:
	// default constructor
	GameObject();

	// constructor
	GameObject(float x, float y, float z);

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

protected:
	// translation
	float mX, mY, mZ;

	// rotation
	float mRotationX, mRotationY, mRotationZ;

	// scale
	float mScaleX, mScaleY, mScaleZ;
};