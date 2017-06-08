#include "cEntity.h"
//Flocker class
//Black monkey heads that move via flocking algorithm
class cFlocker : public cEntity
{
public:
	enum eEnemyState
	{
		STATE_FLEE,
		STATE_SEEK
	};
	cFlocker();
	virtual ~cFlocker();

	virtual void GetTransform(glm::mat4& transform);
	virtual void GetMeshEntry(sMeshEntry& meshEntry);
	virtual void SetMeshEntry(sMeshEntry meshEntry);
	virtual void GetColour(glm::vec4& colour);
	virtual void SetColour(glm::vec4 colour);
	virtual void GetMatrix(glm::mat4& modelMat);
	virtual void SetMatrix(glm::mat4 modelMat);
	virtual void SetPlayerReference(iEntity* player);
	virtual void GetNormal(glm::mat4& normal);
	virtual void SetNormal(glm::mat4 normal);
	virtual void Update(float deltaTime);
	virtual void ExecuteCommand(cNameValuePair NVPair);
	virtual void SetSpeed(float newSpeed);
	virtual glm::vec3 GetVelocity();
private:
	eEnemyState mState;
	sRenderingInfo renderingInfo;
	glm::vec3 playerPosition;
	iEntity* playerRef;
	int reactionTime;
	float monkeySpeed;
	cAreaInfo areaInfeo;
	int flockNum=0;
	glm::vec3 CalculateFlocking();
	glm::vec3 velocity;
};