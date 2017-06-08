#ifndef _cNameValuePair_HG_
#define _cNameValuePair_HG_

#include <string>
#include <vector>


//Used to act as a mediator for entity objects
//Allowing them to use more functions than
//Just the ones defined in the entity interface
class cNameValuePair
{
public:
	typedef struct fvec4
	{
		fvec4() : x(0.0f), y(0.0f), z(0.0), w(1.0f) {};
		float x, y, z, w;
	} fvec4;
	cNameValuePair();
	cNameValuePair(const std::string &name);
	cNameValuePair(const std::string &name, fvec4 fVec4Value);
	cNameValuePair(const std::string &name, float fValue);
	cNameValuePair(const std::string &name, int iValue);
	cNameValuePair(const std::string &name, std::string sValue);
	
	std::string name;
	// ** The values **
	fvec4 fvec4Value;		// Can also be used for one float
	int iValue;
	std::string sValue;
	// ****************
	void Reset(void);
	};




#endif 








