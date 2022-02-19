//---------------------------------------------------------------------------------------
//
//	WinLibDevRegistry.cpp
//
//---------------------------------------------------------------------------------------
//
//	Header files
//
//---------------------------------------------------------------------------------------
using namespace std;
#include "WinLibDevRegistry.h"
#include <string>

//---------------------------------------------------------------------------------------
//
//	Constructors
//
//---------------------------------------------------------------------------------------
WinLibDevRegistry::WinLibDevRegistry()
{

}

WinLibDevRegistry::WinLibDevRegistry(
	string* strDomainName, 
	string* strApplicationName)
{
	//-----------------------------------------------------------------------------------
	//
	// Set class instance values
	//
	strDomain = *strDomainName;
	strApplication = *strApplicationName;


}

//---------------------------------------------------------------------------------------
//
//	Public Functions
//
//---------------------------------------------------------------------------------------
//
//	GetRegistryKeyValue
//	- input:
//		- strSection
//		- strKey
//	- output:
//		- GetRegistryKeyValue
//		- strRegistryKevValue
//
//---------------------------------------------------------------------------------------
int WinLibDevRegistry::GetRegistryKeyValue(
	const string& strSection,
	const string& strKey,
	string& strRegKeyValue)
{
	//-----------------------------------------------------------------------------------
	//
	//	Local variables
	int
		iRC =0;

	//-----------------------------------------------------------------------------------
	//
	//Retrieve key value
	//
//	iRC = GetRegistryKeyValue(strSection, strKey);
//	strRegKeyValue = strRegistryKeyValue;
	return iRC;
}

//---------------------------------------------------------------------------------------
//
//	Private Functions
//
//---------------------------------------------------------------------------------------

