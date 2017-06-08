#ifndef _iEntity_HG_
#define _iEntity_HG_
#include "externals.h"
#include "LoadMesh.h"
#include "cNameValuePair.h"
struct sRenderingInfo
{
	glm::mat4 matrix;
	sMeshEntry MeshEntry;
	glm::vec4 Color;
	glm::mat4 normal;
	// ... whatever
};
//General interface class for game objects
class iEntity

{
public:
	virtual ~iEntity() {};

	virtual void GetTransform(glm::mat4& transform) = 0;
	virtual void GetMeshEntry(sMeshEntry& meshEntry) = 0;
	virtual void SetMeshEntry(sMeshEntry meshEntry) = 0;
	virtual void GetColour(glm::vec4& colour) = 0;
	virtual void SetColour(glm::vec4 colour) = 0;
	virtual void GetMatrix(glm::mat4& modelMat) = 0;
	virtual void SetMatrix(glm::mat4 modelMat) = 0;
	virtual void SetPlayerReference(iEntity* player) = 0;
	virtual void GetNormal(glm::mat4& normal) = 0;
	virtual void SetNormal(glm::mat4 normal) = 0;
	virtual void SetSpeed(float newSpeed) = 0;
	virtual glm::vec3 GetVelocity() = 0;
	//virtual void GetRenderingInfo(sRenderingInfo& renderingInfo) = 0;
	//virtual void GetColor(glm::vec4& color) = 0;
	//virtual void Update(float dt) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void ExecuteCommand(cNameValuePair NVPair) = 0;


};

#endif