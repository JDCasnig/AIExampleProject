#ifndef _cEntityFactory_HG_
#define _cEntityFactory_HG_

// ONLY include the INTERFACE
// +++NEVER+++ the implementation (cpp) file
#include "iEntity.h"	

#include <string>

// DON'T #include this class
class cEntityFactory_Imp;

class cEntityFactory
{
public:
	cEntityFactory();
	~cEntityFactory();
	// Returns a pointer to the INTERFACE type
	// Take some a string
	iEntity* CreateEntity(std::string typeOfEntity);

private:
	// This is the last and only private thing we'll add
	//Pointer to implemntation 
	cEntityFactory_Imp* m_pImplementation;
};

#endif
