#include "cEntityBuilder.h"

#include "cEntityFactory.h"
//#include "cWeaponFactory.h" 

//#include "iShip_BuilderAssign.h"	// Interface to ship weapon assignment

#include <iostream>
#include <sstream>
#include "global.h"

// "Fighter"
// "Battleship"


//static 
cEntityBuilder* cEntityBuilder::m_pTheOneThing = 0;		// NULL or nullptr

//Singleton pattern for EntityBuilder
cEntityBuilder* cEntityBuilder::getInstance(void)
{
	// Is the pointer still 0, NULL
	if (cEntityBuilder::m_pTheOneThing == 0)
	{	// Yup. 
		cEntityBuilder::m_pTheOneThing = new cEntityBuilder();
	}
	return cEntityBuilder::m_pTheOneThing;
}

//static 
void cEntityBuilder::shutDown(void)
{
	// Do we have an instance?
	if (cEntityBuilder::m_pTheOneThing != 0)
	{	// Yes, so get rid of it
		delete cEntityBuilder::m_pTheOneThing;
	}
	return;
}


cEntityBuilder::cEntityBuilder()
{
	std::cout << "cEntityBuilder::cEntityBuilder()" << std::endl;
	return;
}

cEntityBuilder::~cEntityBuilder()
{
	std::cout << "cEntityBuilder::~cEntityBuilder()" << std::endl;
	return;
}


//Bulder uses an abstract factory to create entity objects
//Objects are to be further modified when created as needed
iEntity* cEntityBuilder::CreateEntity(std::string type, iEntity* pDecoratedEntity /*= 0*/)
{
	iEntity* pTheEntity = 0;

	cEntityFactory* pEF = new cEntityFactory();

	if (type == "Player")
	{
	
		pTheEntity = pEF->CreateEntity("Player");
		pTheEntity->SetMeshEntry(monkeyMesh);
		pTheEntity->SetColour(glm::vec4(1, 1, 1, 1));
		pTheEntity->SetMatrix(gMonkeyMatrix);

	}
	if (type == "Enemy")
	{
		float xPos, zPos;
		xPos = (float)glm::linearRand(0, 10);
		zPos = (float)glm::linearRand(0, 10);
		if (xPos < 5)
		{
			xPos = -xPos - 5;
		}
		if (zPos < 5)
		{
			zPos = -zPos - 5;
		}
		pTheEntity = pEF->CreateEntity("Enemy");
		pTheEntity->SetMeshEntry(monkeyMesh);
		pTheEntity->SetColour(glm::vec4(.5, .5, .5, 1));
		pTheEntity->SetMatrix(glm::translate(gMonkeyMatrix, glm::vec3(xPos, 0.f, zPos)));
		pTheEntity->SetPlayerReference(player);
		

	}
	if (type == "Observer")
	{
		float xPos, zPos;
		xPos = (float)glm::linearRand(-gAreaInfo.height, gAreaInfo.height);
		zPos = (float)glm::linearRand(-gAreaInfo.width, gAreaInfo.width);

		pTheEntity = pEF->CreateEntity("Observer");
		pTheEntity->SetMeshEntry(monkeyMesh);
		pTheEntity->SetColour(glm::vec4(.5, 0.f, .5, 1));
		pTheEntity->SetMatrix(glm::translate(gMonkeyMatrix, glm::vec3(xPos, 0.f, zPos)));
		pTheEntity->SetPlayerReference(player);
	}
	if (type == "Hunter")
	{
		float xPos, zPos;
		xPos = (float)glm::linearRand(0, 10);
		zPos = (float)glm::linearRand(0, 10);
		
		if (xPos < 5)
		{
			xPos = -xPos - 5;
		}
		if (zPos < 5)
		{
			zPos = -zPos - 5;
		}
		pTheEntity = pEF->CreateEntity("Hunter");
		pTheEntity->SetMeshEntry(monkeyMesh);
		pTheEntity->SetColour(glm::vec4(.5, 0.f, .5, 1));
		pTheEntity->SetMatrix(glm::translate(gMonkeyMatrix, glm::vec3(xPos, 0.f, zPos)));
		pTheEntity->SetPlayerReference(player);
	}
	if (type == "Flocker")
	{
		float xPos, zPos;
		xPos = (float)glm::linearRand(0, 10);
		zPos = (float)glm::linearRand(0, 10);
		if (xPos < 5)
		{
			xPos = -xPos - 5;
		}
		if (zPos < 5)
		{
			zPos = -zPos - 5;
		}
		pTheEntity = pEF->CreateEntity("Flocker");
		pTheEntity->SetMeshEntry(monkeyMesh);
		pTheEntity->SetColour(glm::vec4(.5, 0.f, .5, 1));
		pTheEntity->SetMatrix(glm::translate(gMonkeyMatrix, glm::vec3(xPos, 3.f, zPos)));
		pTheEntity->SetPlayerReference(player);
		::g_vec_Flockers.push_back(pTheEntity);
	}
	delete pEF;
	return pTheEntity;
}