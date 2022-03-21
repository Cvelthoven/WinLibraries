//---------------------------------------------------------------------------------------
//
//	WinLibDevRegistry.h
// 
// Class for development of the class functions
//
//---------------------------------------------------------------------------------------
#pragma once

//---------------------------------------------------------------------------------------
//
//	Header files
//
//---------------------------------------------------------------------------------------
using namespace std;
#include <string>
//---------------------------------------------------------------------------------------
//
//	MainWindow class definitions
//
//---------------------------------------------------------------------------------------
class WinLibDevRegistry
{
public:
	//-----------------------------------------------------------------------------------
	//
	//	Constructors and destructor
	//
	WinLibDevRegistry();
	WinLibDevRegistry(string* strDomainName, string* strApplicationName);
	~WinLibDevRegistry();

	//-----------------------------------------------------------------------------------
	//
	//	Public methodes
	//
	int GetRegistryKeyValue(
		const string& strSection,
		const string& strKey,
		string& strRegKeyValue);
	int GetRegistryKeyValue(
		const string& strSection,
		const string& strKey,
		int& iRegKeyValue);
	int SetRegistryKeyValue(
		const string& strSection,
		const string& strKey,
		const string& strRegKeyValue);


private:
	//-----------------------------------------------------------------------------------
	//
	//	Private methodes
	//
	int GetRegistryKeyValue(
		const string& strSection,
		const string& strKey);

	int
		iRegistryKeyValue;

	string
		strDomain,
		strApplication,
		strRegistryKeyValue;
};

