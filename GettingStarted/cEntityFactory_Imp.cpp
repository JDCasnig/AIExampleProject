#include "cEntityFactory_Imp.h"


// HERE you include the SPECFIC classes
// ONLY here, NEVER in the .h file
#include "cPlayer.h"
#include "cEnemy.h"		
#include "cObserver.h"
#include "cHunter.h"
#include "Flocker.h"



// Returns a pointer to the INTERFACE type
// Take some well known type (like int, string)
//Used to make changes to EntityFActory without having to
//Change/recompile its interface
iEntity* cEntityFactory_Imp::CreateEntity(std::string typeOfEntity)
{
	iEntity* pEntityToReturn = 0;	// Or NULL or nullprt

	if (typeOfEntity == "Player")
	{
		pEntityToReturn = new cPlayer();

	}
	else if (typeOfEntity == "Enemy")
	{
		pEntityToReturn = new cEnemy();

	}
	else if (typeOfEntity == "Observer")
	{
		pEntityToReturn = new cObserver();
	}
	else if (typeOfEntity == "Hunter")
	{
		pEntityToReturn = new cHunter();
	}
	else if (typeOfEntity == "Flocker")
	{
		pEntityToReturn = new cFlocker();
		
	}

	// Increment the number of ships.
	this->m_HowManyEntitiesWereCreated++;

	return pEntityToReturn;
}

cEntityFactory_Imp::cEntityFactory_Imp()
{
	return;
}

cEntityFactory_Imp::~cEntityFactory_Imp()
{
	return;
}



