//---------------------------------------------------------------------------------------
//
//	LibRegistry
//
//---------------------------------------------------------------------------------------
#include "pch.h"
#include "LibRegistry.h"

#include <string>



//---------------------------------------------------------------------------------------
//
//	LibRegistry constructors
//
//---------------------------------------------------------------------------------------
LibRegistry::LibRegistry(
	string& strAplicationDomain,
	string& strAplicationName)
{
	strAplDomain = strAplicationDomain;
	strAplicationName = strAplicationName;

}

//---------------------------------------------------------------------------------------
//
//	Public class methodes
//
//---------------------------------------------------------------------------------------
//
//	GetRegistryKeyValue
//
//---------------------------------------------------------------------------------------
//
//	GetRegistryKeyValue returning a sting value
//
//---------------------------------------------------------------------------------------
int LibRegistry::GetRegistryKeyValue(
	const string& strSection,
	const string& strKey,
	string& strRegKeyValue)
{
	//-----------------------------------------------------------------------------------
	//
	//	Build registry path
	//
	strRegistryKeyPath = "SOFTWARE\\" + strAplDomain + "\\" + strAplName;
	if (strSection.length() > 0)
		strRegistryKeyPath = strRegistryKeyPath + "\\" + strSection;

	return 0;
}

//---------------------------------------------------------------------------------------
//
//	Private class methodes
//
//---------------------------------------------------------------------------------------
//
//	GetRegistryKeyValue
//
//---------------------------------------------------------------------------------------


