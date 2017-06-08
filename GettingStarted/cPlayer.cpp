#include "cPlayer.h"
#include "global.h"
#include "iWeapon.h"


float monkeySpinSpeed = 1.6f;
float monkeyMoveSpeed = 10.0f;


cPlayer::~cPlayer()
{

}



void cPlayer::GetTransform(glm::mat4& transform)
{

}

void cPlayer::GetMeshEntry(sMeshEntry& meshEntry)
{
	meshEntry = renderingInfo.MeshEntry;
}

void cPlayer::GetColour(glm::vec4& colour)
{
	colour = renderingInfo.Color;
}

void cPlayer::SetColour(glm::vec4 colour)
{
	renderingInfo.Color = colour;
}

void cPlayer::SetMeshEntry(sMeshEntry meshEntry)
{
	renderingInfo.MeshEntry = meshEntry;
}

void cPlayer::GetMatrix(glm::mat4& modelMat)
{
	modelMat = renderingInfo.matrix;
}
void cPlayer::SetMatrix(glm::mat4 modelMat)
{

	renderingInfo.matrix = modelMat;
}

void cPlayer::SetPlayerReference(iEntity* player)
{

}


void cPlayer::GetNormal(glm::mat4& normal)
{
	normal = renderingInfo.normal;
}
void cPlayer::SetNormal(glm::mat4 normal)
{
	renderingInfo.normal = normal;
}

//void cPlayer::Update(float dt)
void cPlayer::Update(float deltaTime)
{

	// camera controls:
	//    up / down = zoom in / zoom out
	//    left / right = pan left / pan right

	// movement controls:
	//    w / s  = forward / backward
	//    a / d  = turn left / turn right



	glm::vec3 up(0.f, 1.f, 0.f);
	//Turn left/Right
	bool pressA = (glfwGetKey(gWindow, GLFW_KEY_A) == GLFW_PRESS);
	bool pressD = (glfwGetKey(gWindow, GLFW_KEY_D) == GLFW_PRESS);
	if (pressA != pressD)
	{
		float speed = pressA ? monkeySpinSpeed : -monkeySpinSpeed;
		renderingInfo.matrix = glm::rotate(renderingInfo.matrix, speed * deltaTime, up);
		renderingInfo.normal = glm::rotate(renderingInfo.normal, speed*deltaTime, up);
	}
	//Move forwards
	bool pressW = (glfwGetKey(gWindow, GLFW_KEY_W) == GLFW_PRESS);
	bool pressS = (glfwGetKey(gWindow, GLFW_KEY_S) == GLFW_PRESS);
	if (pressW != pressS)
	{
		float speed = pressW ? monkeyMoveSpeed : -monkeyMoveSpeed;

		renderingInfo.matrix = glm::translate(renderingInfo.matrix, glm::vec3(0, 0, 1)*speed*deltaTime);
		//Stops player from going out of bounds
		
		if (renderingInfo.matrix[3].x > gAreaInfo.width)
			renderingInfo.matrix[3].x = gAreaInfo.width;
		else if (renderingInfo.matrix[3].x < -gAreaInfo.width)
			renderingInfo.matrix[3].x = -gAreaInfo.width;

		if (renderingInfo.matrix[3].z > gAreaInfo.height)
			renderingInfo.matrix[3].z = gAreaInfo.height;
		else if (renderingInfo.matrix[3].z < -gAreaInfo.height)
			renderingInfo.matrix[3].z = -gAreaInfo.height;

	}
	bool pressSpace = (glfwGetKey(gWindow, GLFW_KEY_SPACE) == GLFW_PRESS);
	if (pressSpace)
	{
 		renderingInfo.matrix[3].y += 1;
	}

	gCamera->SetTargetTransform(renderingInfo.matrix);
	gCamera->Update(deltaTime);


}

void cPlayer::ExecuteCommand(cNameValuePair NVPair)
{

}

void cPlayer::SetSpeed(float newSpeed)
{

}

glm::vec3 cPlayer::GetVelocity()
{
	return glm::vec3{ 0.f,0.f,1.f };
}

bool cPlayer::Attack()
{
	return false;
}