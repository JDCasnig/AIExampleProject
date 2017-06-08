#ifndef _cEntityFactory_Imp_HG_
#define _cEntityFactory_Imp_HG_

#include "cEntityFactory.h"

class cEntityFactory_Imp
{
public:
	cEntityFactory_Imp();
	~cEntityFactory_Imp();

	iEntity* CreateEntity(std::string typeOfEntity);


private:
	// 
	int m_HowManyEntitiesWereCreated;

};

#endif
