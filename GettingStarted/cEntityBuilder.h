#ifndef _cEntityBuilder_HG_
#define _cEntityBuilder_HG_

#include <string>
#include "iEntity.h"

class cEntityBuilder
{
public:
	~cEntityBuilder();

	static cEntityBuilder* getInstance(void);

	// optional destructor method
	// (This is sort of dubious, in that you could forget to call it)
	static void shutDown(void);

	iEntity* CreateEntity(std::string type, iEntity* pDecoratedEntity = 0);

private:
	cEntityBuilder();

	static cEntityBuilder* m_pTheOneThing;

};

#endif 
