#include "cEntity.h"

class cPlayer : public cEntity
{
public:

	virtual ~cPlayer();

	virtual void GetTransform(glm::mat4& transform);
	virtual void GetMeshEntry(sMeshEntry& meshEntry);
	virtual void Update(float deltaTime);
	virtual void SetMeshEntry(sMeshEntry meshEntry);
	virtual void GetColour(glm::vec4& colour);
	virtual void SetColour(glm::vec4 colour);
	virtual void GetMatrix(glm::mat4& modelMat);
	virtual void SetMatrix(glm::mat4 modelMat);
	virtual void SetPlayerReference(iEntity* player);
	virtual void GetNormal(glm::mat4& normal);
	virtual void SetNormal(glm::mat4 normal);
	virtual void ExecuteCommand(cNameValuePair NVPair);
	virtual void SetSpeed(float newSpeed);
	virtual glm::vec3 GetVelocity();

	virtual bool Attack();
private:
	sRenderingInfo renderingInfo;
	cAreaInfo areaInfeo;
	iWeapon* weapon;
};