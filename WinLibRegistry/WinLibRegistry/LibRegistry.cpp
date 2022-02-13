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
int LibRegistry::GetRegistryKeyValue(
	const string& strSection,
	const string& strKey,
	string& strRegKeyValue)
{
	return 0;
}

