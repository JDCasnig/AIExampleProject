#pragma once

#include "LoadMesh.h"
#include "cAreaInfo.h"
#include "iEntity.h"
#include "iWeapon.h"

class cEntity : public iEntity
{
public:

	virtual ~cEntity() {}
	
	virtual void GetTransform(glm::mat4& transform) = 0;
	virtual void GetMeshEntry(sMeshEntry& meshEntry) = 0;
	virtual void SetMeshEntry(sMeshEntry meshEntry) = 0;
	virtual void GetColour(glm::vec4& colour)= 0;
	virtual void SetColour(glm::vec4 colour)=0;
	virtual void GetMatrix(glm::mat4& modelMat) = 0;
	virtual void SetMatrix(glm::mat4 modelMat) = 0;
	virtual void SetPlayerReference(iEntity* player)=0;
	virtual void GetNormal(glm::mat4& normal) = 0;
	virtual void SetNormal(glm::mat4 normal) = 0;
	virtual void SetSpeed(float newSpeed) = 0;
	//virtual void GetRenderingInfo(sRenderingInfo& renderingInfo) = 0;
	//virtual void GetColor(glm::vec4& color) = 0;
	//virtual void Update(float dt) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void ExecuteCommand(cNameValuePair )=0;
	virtual glm::vec3 GetVelocity() = 0;
	
};
//
//class cEnemy : public cEntity
//{
//public:
//	enum eEnemyState
//	{
//		STATE_FLEE,
//		STATE_SEEK
//	};
//	cEnemy();
//	virtual ~cEnemy();
//
//	virtual void GetTransform(glm::mat4& transform);
//	virtual void GetMeshEntry(sMeshEntry& meshEntry) ;
//	virtual void SetMeshEntry(sMeshEntry meshEntry);
//	virtual void GetColour(glm::vec4& colour);
//	virtual void SetColour(glm::vec4 colour);
//	virtual void GetMatrix(glm::mat4& modelMat);
//	virtual void SetMatrix(glm::mat4 modelMat);
//	virtual void SetPlayerReference(cEntity* player);
//	virtual void GetNormal(glm::mat4& normal);
//	virtual void SetNormal(glm::mat4 normal);
//	virtual void Update(float deltaTime);
//private:
//	eEnemyState mState;
//	sRenderingInfo renderingInfo;
//	glm::vec3 playerPosition;
//	cEntity* playerRef;
//	int reactionTime;
//	float monkeySpeed;
//	cAreaInfo areaInfeo;
//};

//class cPlayer : public cEntity
//{
//public:
//
//	virtual ~cPlayer();
//	
//	virtual void GetTransform(glm::mat4& transform);
//	virtual void GetMeshEntry(sMeshEntry& meshEntry);
//	virtual void Update(float deltaTime);
//	virtual void SetMeshEntry(sMeshEntry meshEntry);
//	virtual void GetColour(glm::vec4& colour);
//	virtual void SetColour(glm::vec4 colour);
//	virtual void GetMatrix(glm::mat4& modelMat);
//	virtual void SetMatrix(glm::mat4 modelMat);
//	virtual void SetPlayerReference(cEntity* player);
//	virtual void GetNormal(glm::mat4& normal);
//	virtual void SetNormal(glm::mat4 normal);
//private:
//	sRenderingInfo renderingInfo;
//	cAreaInfo areaInfeo;
//};