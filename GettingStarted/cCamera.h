#pragma once

#include "externals.h"

class cCamera
{
public:
	cCamera();
	~cCamera();

	void GetProjectionMatrix(glm::mat4& projOut);
	void GetViewMatrix(glm::mat4& viewOut);
	void GetEyePosition(glm::vec4& eyeOut);
	void WindowResize(int width, int height);

	void Update(float dt);
	void SetTargetTransform(glm::mat4& targetTransform);
	void SetMinDistance(float dist);
	void SetMaxDistance(float dist);
	void setStartDistance(float dist);
	void pitchCamera(float height);
private:
	void UpdateView();

	int mWidth;
	int mHeight;
	glm::mat4 mTargetTranform;

	glm::vec3 mOffset;
	float mZoomSpeed;
	float mDistance;
	float mMaxDistance;
	float mMinDistance;
	float mMaxPitch;
	float mMinPitch;
	float mPitch;
	glm::mat4 mViewMatrix;
	float mRotate;
	float mRotateSpeed;
};