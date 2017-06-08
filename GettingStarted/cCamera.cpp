#include "cCamera.h"
#include "global.h"

cCamera::cCamera()
{
	mWidth = 800;
	mHeight = 600;
	mZoomSpeed = 20.f;
	mMinDistance = 5.f;
	mDistance = 20.f;
	mMaxDistance = 30.f;
	mOffset = glm::vec3(0.f,207.f, -1.f);
	mOffset = glm::normalize(mOffset);
	mMinPitch = 0.f;
	mMaxPitch = 20.f;
	mPitch = 0.f;
	mRotate = 0.f;
	mRotateSpeed = 0.002f;
}

cCamera::~cCamera()
{

}

void cCamera::GetProjectionMatrix(glm::mat4& projOut)
{
	// set up the projection matrix
	projOut = glm::perspective(0.8f, (float)mWidth / (float)mHeight, 0.1f, 100.f);
}

void cCamera::GetViewMatrix(glm::mat4& viewOut)
{
	viewOut = mViewMatrix;
}

void cCamera::GetEyePosition(glm::vec4& eyeOut)
{
	eyeOut.x = mViewMatrix[3].x;
	eyeOut.y = mViewMatrix[3].y;
	eyeOut.z = mViewMatrix[3].z;
	eyeOut.w = 1.f;
}

void cCamera::WindowResize(int width, int height)
{
	mWidth = width;
	mHeight = height;
}

void cCamera::Update(float dt)
{
	bool pressUp = glfwGetKey(gWindow, GLFW_KEY_UP) == GLFW_PRESS;
	bool pressDown = glfwGetKey(gWindow, GLFW_KEY_DOWN) == GLFW_PRESS;
	if (pressDown != pressUp)
	{
		float zoomSpeed = mZoomSpeed;
		if (pressUp) zoomSpeed *= -1.f;
		mDistance += zoomSpeed * dt;
		if (mDistance < mMinDistance) mDistance = mMinDistance;
		if (mDistance > mMaxDistance) mDistance = mMaxDistance;
	}

	//If player presses Q or E, add or subtract a fixed amount
	//To the rotation of the camera
	bool pressQ = glfwGetKey(gWindow, GLFW_KEY_E) == GLFW_PRESS;
	bool pressE = glfwGetKey(gWindow, GLFW_KEY_Q) == GLFW_PRESS;
	if (pressQ != pressE)
	{

		float rotateSpeed=mRotateSpeed;
		if (pressQ) rotateSpeed = rotateSpeed*-1.f;
		mRotate += rotateSpeed;
	}

	bool press1 = glfwGetKey(gWindow, GLFW_KEY_1) == GLFW_PRESS;
	bool press2 = glfwGetKey(gWindow, GLFW_KEY_2) == GLFW_PRESS;
	if (press1 != press2)
	{
		float zoomSpeed = mZoomSpeed;
		if (press2) zoomSpeed *= -1.f;
		mPitch += zoomSpeed * dt;
		if (mPitch < mMinPitch) mPitch = mMinPitch;
		if (mPitch > mMaxPitch) mPitch = mMaxPitch;






	}

	UpdateView();
}

void cCamera::UpdateView()
{
	glm::vec3 up(0.f, 1.f, 0.f);
	
	// set up the view matrix
	glm::vec3 target(mTargetTranform[3].x, mTargetTranform[3].y , mTargetTranform[3].z);
	glm::vec4 offset(mOffset.x, mOffset.y, mOffset.z, 0.f);
	offset = mTargetTranform * offset;
	offset = glm::normalize(offset) * mDistance;
	glm::vec3 eye(target.x + offset.x, target.y + offset.y, target.z + offset.z);
	target.y += +mPitch;
	mViewMatrix = glm::lookAtRH(eye, target, up);
	
}

void cCamera::SetTargetTransform(glm::mat4& targetTransform)
{
	glm::vec3 up(0.f, 1.f, 0.f);
	
	mTargetTranform = targetTransform;
	//Rotate the camera
	mTargetTranform = glm::rotate(mTargetTranform, mRotate, up);
}

void cCamera::SetMinDistance(float dist)
{
	mMinDistance = dist;
}

void cCamera::SetMaxDistance(float dist)
{
	mMaxDistance = dist;
}

void cCamera::setStartDistance(float dist)
{
	mDistance = dist;
}