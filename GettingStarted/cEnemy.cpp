#include "cEnemy.h"
#include "global.h"



//float monkeySpinSpeed = 1.6f;
//float monkeyMoveSpeed = 10.0f;

cEnemy::cEnemy()
{
	//Randomized reaction speed and movement speed
	reactionTime = glm::linearRand(15, 30);
	monkeySpeed = (float)glm::linearRand(1, 4);
}

cEnemy::~cEnemy()
{

}


void cEnemy::GetTransform(glm::mat4& transform)
{

}


void cEnemy::GetMeshEntry(sMeshEntry& meshEntry)
{
	meshEntry = renderingInfo.MeshEntry;
}

void cEnemy::SetMeshEntry(sMeshEntry meshEntry)
{
	renderingInfo.MeshEntry = meshEntry;
}
void cEnemy::GetColour(glm::vec4& colour)
{
	colour = renderingInfo.Color;
}
void cEnemy::SetColour(glm::vec4 colour)
{
	renderingInfo.Color = colour;
}
void cEnemy::GetMatrix(glm::mat4& modelMat)
{
	modelMat = renderingInfo.matrix;
}
void cEnemy::SetMatrix(glm::mat4 modelMat)
{
	renderingInfo.matrix = modelMat;
}

void cEnemy::SetPlayerReference(iEntity* player)
{
	playerRef = player;
}

void cEnemy::GetNormal(glm::mat4& normal)
{
	normal = renderingInfo.normal;
}
void cEnemy::SetNormal(glm::mat4 normal)
{
	renderingInfo.normal = normal;
}

void cEnemy::Update(float deltaTime)
{
	// is the player looking at me?
	// yes -> move away! run!
	// no -> chase that player! get him!!
	glm::mat4 playerMat;
	glm::mat4 enemyAdjusted;

	playerRef->GetMatrix(playerMat);


	enemyAdjusted = renderingInfo.matrix - playerMat;

	float answer = glm::dot(playerMat[2], enemyAdjusted[3]);






	//Delay state change based on reaction time

	if (answer > 0.f)
	{

		if (reactionTime < 1)
		{
			mState = STATE_FLEE;
			reactionTime = glm::linearRand(15, 30);;
		}
		if (mState == STATE_SEEK)
		{
			reactionTime--;
		}

	}
	else
	{
		if (reactionTime < 1)
		{
			mState = STATE_SEEK;
			reactionTime = glm::linearRand(15, 30);
		}
		if (mState == STATE_FLEE)
		{
			reactionTime--;
		}

	}








	if (mState == STATE_FLEE)
	{

		//Get normal vector for enemy
		//Get position of player character
		//Get enemy position
		//Adjust positions so that enemy is at the origin
		//create vector to new player position
		//normalize vector
		//get the angle of the turn required to have
		//the enemy face the player character
		glm::vec3 up(0.f, 1.f, 0.f);
		glm::vec3 enemyNormal = renderingInfo.matrix[2];
		glm::vec3 enemyPosition;
		glm::mat4 playerLoc;
		glm::vec3 playerPosition;
		playerRef->GetMatrix(playerLoc);
		playerPosition = playerLoc[3];
		enemyPosition = renderingInfo.matrix[3];
		playerPosition = playerPosition - enemyPosition;

		float dotAnswer = glm::dot(enemyNormal, playerPosition);
		float multAnswer = glm::length(enemyNormal)*glm::length(playerPosition);
		float fullAnswer = dotAnswer / multAnswer;

		//Capture floating point errors
		if (fullAnswer > 1)
		{
			fullAnswer = 1.f;;
		}
		else if (fullAnswer < -1)
		{
			fullAnswer = -1;
		}
		float pi = (float) 3.1415926535897;
		float		angle = glm::acos(fullAnswer);

		//If we're looking approximately at the player character
		if (angle > pi - .05 && angle < pi + .05)
		{
			angle = 0;
		}
		//Turn away from the player character
		//Twirl in a circle when terrified
		//Turn the monkey in a fixed degree based on 
		//the degree of the angle in radians
		else if (angle >= -1 * pi && angle < -0.5*pi)
		{
			if (angle + pi >0.1f)
				angle = -.1f;
		}

		else if (angle <= 0)
		{
			if (angle + .5*pi > 0.1f)
			{
				angle = -.1f;
			}
		}
		if (angle <= .5*pi)
		{
			if (angle >0.1f)
				angle = 0.1f;

		}
		else if (angle > .5*pi && angle <= 1.0*pi)
		{
			if (angle - .5*pi > 0.1f)
				angle = 0.1f;
			else angle = (float)(angle - .5*pi);

		}
		else if (angle <= 1.5*pi)
		{
			if (angle - pi > 0.1f)
				angle = -.1f;
			else angle = angle - pi;
		}
		else if (angle > 1.5*pi)
		{
			if (angle - 1.5*pi > 0.1f)
				angle = .1f;
			else angle = (float)(angle - 1.5*pi);
		}
		//Rotate Matrix
		renderingInfo.matrix = glm::rotate(renderingInfo.matrix, angle, up);



		//looking at me
		renderingInfo.Color = glm::vec4(0.f, 0.f, 1.f, 1.f);
		renderingInfo.matrix = glm::translate(renderingInfo.matrix, glm::vec3(0.f, 0.f, 1.f)*deltaTime*monkeySpeed);
		//If the monkey would move out of bounds, stop it
		if (renderingInfo.matrix[3].x > areaInfeo.width)
			renderingInfo.matrix[3].x = areaInfeo.width;
		else if (renderingInfo.matrix[3].x < -areaInfeo.width)
			renderingInfo.matrix[3].x = -areaInfeo.width;

		if (renderingInfo.matrix[3].z > areaInfeo.height)
			renderingInfo.matrix[3].z = areaInfeo.height;
		else if (renderingInfo.matrix[3].z < -areaInfeo.height)
			renderingInfo.matrix[3].z = -areaInfeo.height;
	}
	else if (mState == eEnemyState(STATE_SEEK))
	{
		//Not looking at me
		renderingInfo.Color = glm::vec4(1.f, 0.f, 0.f, 1.f);
		glm::vec3 up(0.f, 1.f, 0.f);
		glm::vec3 enemyNormal = renderingInfo.matrix[2];
		glm::vec3 enemyPosition;
		glm::mat4 playerLoc;
		glm::vec3 playerPosition;
		playerRef->GetMatrix(playerLoc);
		playerPosition = playerLoc[3];
		enemyPosition = renderingInfo.matrix[3];
		playerPosition = playerPosition - enemyPosition;

		float dotAnswer = glm::dot(enemyNormal, playerPosition);
		float multAnswer = glm::length(enemyNormal)*glm::length(playerPosition);
		float fullAnswer = dotAnswer / multAnswer;

		if (fullAnswer > 1)
		{
			fullAnswer = 1;
		}

		float angle = glm::acos(fullAnswer);

		//Get normal vector for enemy
		//Get position of player character
		//Get enemy position
		//Adjust positions so that enemy is at the origin
		//create vector to new player position
		//normalize vector
		//get the angle of the turn required to have
		//the enemy face the player character

		float pi = (float) 3.1415926535897;
		//If th monkey is already mostly looking at
		//The player, don't turn
		if (angle == 0)
		{

		}
		else if (angle < 0.008)
		{
			angle = 0;
		}
		//Else figure out which direction to turn
		//Turns a fixed amount per update
		else if (angle >= -1 * pi && angle < -0.5*pi)
		{
			if (angle + pi >0.1f)
				angle = -.1f;
		}

		else if (angle <= 0)
		{
			if (angle + .5*pi > 0.1f)
			{
				angle = .1f;
			}
		}
		if (angle <= .5*pi)
		{
			if (angle >0.1f)
				angle = -0.1f;
		}
		else if (angle > .5*pi && angle <= 1.0*pi)
		{
			if (angle - .5*pi >0.1f)
				angle = .1f;
		}
		else if (angle <= 1.5*pi)
		{
			if (angle - pi > 0.1f)
				angle = -.1f;
		}
		else if (angle > 1.5*pi)
		{
			if (angle - 1.5*pi > 0.1f)
				angle = -.1f;
		}

		//Rotate matrix
		renderingInfo.matrix = glm::rotate(renderingInfo.matrix, angle, up);

	}
	renderingInfo.matrix = glm::translate(renderingInfo.matrix, glm::vec3(0.f, 0.f, 1.f)*deltaTime*monkeySpeed);
	//If the monkey would move out of bounds, stop it
	if (renderingInfo.matrix[3].x > areaInfeo.width)
		renderingInfo.matrix[3].x = areaInfeo.width;
	else if (renderingInfo.matrix[3].x < -areaInfeo.width)
		renderingInfo.matrix[3].x = -areaInfeo.width;

	if (renderingInfo.matrix[3].z > areaInfeo.height)
		renderingInfo.matrix[3].z = areaInfeo.height;
	else if (renderingInfo.matrix[3].z < -areaInfeo.height)
		renderingInfo.matrix[3].z = -areaInfeo.height;




}


void cEnemy::ExecuteCommand(cNameValuePair NVPair)
{

}

void cEnemy::SetSpeed(float newSpeed)
{
	monkeySpeed = newSpeed;
}

glm::vec3 cEnemy::GetVelocity()
{
	return glm::vec3{ 0.f,0.f,1.f };
}