#include "cNameValuePair.h"

void cNameValuePair::Reset(void)
{
	this->fvec4Value.x = this->fvec4Value.y = this->fvec4Value.z = this->fvec4Value.w = 0.0f;
	this->sValue = "";
	this->iValue = 0;
	return;
}

cNameValuePair::cNameValuePair()
{
	this->Reset();
	return;
}

cNameValuePair::cNameValuePair(const std::string &name)
{
	this->Reset();
	this->name = name;
	return;
}

cNameValuePair::cNameValuePair(const std::string &name, fvec4 fvec4Value)
{
	this->Reset();
	this->name = name;
	this->fvec4Value = fvec4Value;
	return;
}

cNameValuePair::cNameValuePair(const std::string &name, float fValue)
{
	this->Reset();
	this->name = name;
	this->fvec4Value.x = fValue;
	return;
}

cNameValuePair::cNameValuePair(const std::string &name, int iValue)
{
	this->Reset();
	this->name = name;
	this->iValue = iValue;
	return;
}

cNameValuePair::cNameValuePair(const std::string &name, std::string sValue)
{
	this->Reset();
	this->name = name;
	this->sValue = sValue;
	return;
}


