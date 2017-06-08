#include "Flocker.h"
#include "global.h"



//float monkeySpinSpeed = 1.6f;
//float monkeyMoveSpeed = 10.0f;

cFlocker::cFlocker()
{
	//Randomized reaction speed and movement speed
	reactionTime = glm::linearRand(15, 30);
	monkeySpeed = (float)glm::linearRand(1, 4);
	velocity = { 0.f,0.f,1.f };
}

cFlocker::~cFlocker()
{

}


void cFlocker::GetTransform(glm::mat4& transform)
{

}


void cFlocker::GetMeshEntry(sMeshEntry& meshEntry)
{
	meshEntry = renderingInfo.MeshEntry;
}

void cFlocker::SetMeshEntry(sMeshEntry meshEntry)
{
	renderingInfo.MeshEntry = meshEntry;
}
void cFlocker::GetColour(glm::vec4& colour)
{
	colour = renderingInfo.Color;
}
void cFlocker::SetColour(glm::vec4 colour)
{
	renderingInfo.Color = colour;
}
void cFlocker::GetMatrix(glm::mat4& modelMat)
{
	modelMat = renderingInfo.matrix;
}
void cFlocker::SetMatrix(glm::mat4 modelMat)
{
	renderingInfo.matrix = modelMat;
}

void cFlocker::SetPlayerReference(iEntity* player)
{
	playerRef = player;
}

void cFlocker::GetNormal(glm::mat4& normal)
{
	normal = renderingInfo.normal;
}
void cFlocker::SetNormal(glm::mat4 normal)
{
	renderingInfo.normal = normal;
}

void cFlocker::Update(float deltaTime)
{
//	 is the player looking at me?
//	 yes -> move away! run!
	// no -> chase that player! get him!!
	glm::mat4 playerMat;
	glm::mat4 enemyAdjusted;

	playerRef->GetMatrix(playerMat);


	enemyAdjusted = renderingInfo.matrix - playerMat;

	
	glm::vec3 flockMovement = CalculateFlocking();
	renderingInfo.Color = glm::vec4(0.f, 0.f, 0.f, 1.f);
	glm::vec3 up(0.f, 1.f, 0.f);
	glm::vec3 enemyNormal = renderingInfo.matrix[2];


	velocity = flockMovement;

	
		glm::vec3 movementVec{ 0.f,0.f,3.f };//= renderingInfo.matrix[3];
	
	renderingInfo.Color = glm::vec4(0.f, 0.f, 0.f, 1.f);
	//glm::vec3 flockMovement = CalculateFlocking();
	renderingInfo.matrix = glm::translate(renderingInfo.matrix, velocity*deltaTime*monkeySpeed);// + glm::vec3(0.f,0.f,1.f)*deltaTime);
	//If the monkey would move out of bounds, stop it
	renderingInfo.matrix[3].y = 10.f;
	if (renderingInfo.matrix[3].x > areaInfeo.width)
		renderingInfo.matrix[3].x = areaInfeo.width;
	else if (renderingInfo.matrix[3].x < -areaInfeo.width)
		renderingInfo.matrix[3].x = -areaInfeo.width;

	if (renderingInfo.matrix[3].z > areaInfeo.height)
		renderingInfo.matrix[3].z = areaInfeo.height;
	else if (renderingInfo.matrix[3].z < -areaInfeo.height)
		renderingInfo.matrix[3].z = -areaInfeo.height;




}


void cFlocker::ExecuteCommand(cNameValuePair NVPair)
{

}

void cFlocker::SetSpeed(float newSpeed)
{
	monkeySpeed = newSpeed;
}


glm::vec3 cFlocker::CalculateFlocking()
{

	float flockingRadius = 5.f;
	glm::mat4 flocker;
	float x = 0;
	float z = 0;
	this->GetMatrix(flocker);
	int neighbourCount = 0;
	//Calculate the alignment portion of the flocking
	for (unsigned int i = 0; ::g_vec_Flockers.size() > i; i++)
	{
		if (this != ::g_vec_Flockers[i]) {
			glm::mat4 flockee;
			::g_vec_Flockers[i]->GetMatrix(flockee);
			float test = abs(glm::distance(flocker[3], flockee[3]));
			//std::cout << test << std::endl;
			if (test < flockingRadius)// && abs(glm::distance(flocker[3], flockee[3])) > 0.2f)
			{
				neighbourCount++;
				x += g_vec_Flockers[i]->GetVelocity().x;
				z += g_vec_Flockers[i]->GetVelocity().z;
			}


		}
	}
	//Return 0 if no neighbours nearby
		if (neighbourCount == 0)
		{
			return glm::vec3{ 0.f,0.f,0.f };
		}

		x = x / (float)neighbourCount;
		z = z / (float)neighbourCount;
		glm::vec3 flockAlignment{ x,0.f,z };
		flockAlignment = glm::normalize(flockAlignment);


		x = 0;
		z = 0;

		//Calculate cohesion protion of flocking
		for (unsigned int i = 0; ::g_vec_Flockers.size() > i; i++)
		{
			if (this != ::g_vec_Flockers[i]) {
				glm::mat4 flockee;
				::g_vec_Flockers[i]->GetMatrix(flockee);
				float test = abs(glm::distance(flocker[3], flockee[3]));
				if (test < flockingRadius);// && abs(glm::distance(flocker[3], flockee[3])) > 0.2f)
				{

					x += flockee[3].x;
					z += flockee[3].z;
				}

			}
			else
			{ int boo = 0; }
		}

		x = x / (float)neighbourCount;
		z = z / (float)neighbourCount;
		glm::vec3 flockCohesion{ x - flocker[3].x,0.f, z - flocker[3].z };
		flockCohesion = glm::normalize(flockCohesion);

		x = 0;
		z = 0;

		//Calculate seperation part of flocking
		for (unsigned int i = 0; ::g_vec_Flockers.size() > i; i++)
		{
			if (this != ::g_vec_Flockers[i]) {
				glm::mat4 flockee;
				
				::g_vec_Flockers[i]->GetMatrix(flockee);
				float test = abs(glm::distance(flocker[3], flockee[3]));
				if (test < flockingRadius);// && abs(glm::distance(flocker[3], flockee[3])) > 0.2f)
				{

					x += flocker[3].x - flockee[3].x;
					z += flocker[3].z - flockee[3].z;
				}

			}
		}
		x = x;// *-1.f;
		z = z;// *-1.f;
		x = x / (float)neighbourCount;
		z = z / (float)neighbourCount;
		glm::vec3 flockSeperation{ (float)x - flocker[3].x,0.f, (float)z - flocker[3].z };
		flockSeperation = glm::normalize(flockSeperation);

		//return flocking result
		glm::vec3 flockMovement = flockAlignment + flockCohesion*1.5f + flockSeperation;
		flockMovement.y = 0.f;
		return flockMovement;
	
}

glm::vec3 cFlocker::GetVelocity()
{
	return velocity;
}