//---------------------------------------------------------------------------------------
//
//	LibRegistry.h
//
//---------------------------------------------------------------------------------------
#pragma once

#ifdef LIBREGISTRY_EXPORTS
#define LIBREGISTRY __declspec(dllexport)
#else
#define LIBREGISTRY __declspec(dllimport)
#endif

//---------------------------------------------------------------------------------------
//
//	Header files
//
//---------------------------------------------------------------------------------------
using namespace std;// needed for default header files
#include <string>

class LibRegistry 
{
//---------------------------------------------------------------------------------------
//
//	Public declarations
//
//---------------------------------------------------------------------------------------
public:
	LibRegistry(
		string& strAplicationDomain,
		string& strAplicationName);

	int GetRegistryKeyValue(
		const string& strSection,
		const string& strKey,
		string& strRegKeyValue);

//---------------------------------------------------------------------------------------
//
//	Private declarations
//
//---------------------------------------------------------------------------------------
private:
	string
		strAplDomain,
		strAplName,
		strRegistryKeyPath;

};
