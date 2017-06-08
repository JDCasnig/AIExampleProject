#include "cEntityFactory.h"

#include "cEntityFactory_Imp.h"

// HERE you include the SPECFIC classes
// ONLY here, NEVER in the .h file
		


cEntityFactory::cEntityFactory()
{
	this->m_pImplementation = new cEntityFactory_Imp();
	return;
}

cEntityFactory::~cEntityFactory()
{
	delete this->m_pImplementation;
	return;
}


// Returns a pointer to the INTERFACE type
// Take some well known type (like int, string)
iEntity* cEntityFactory::CreateEntity(std::string typeOfEntity)
{
	return this->m_pImplementation->CreateEntity(typeOfEntity);
}
