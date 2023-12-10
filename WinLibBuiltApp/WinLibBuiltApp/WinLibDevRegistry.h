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
#include <Windows.h>

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
	WinLibDevRegistry(string* strHiveName, string* strDomainName, string* strApplicationName);
	WinLibDevRegistry(string* strHiveName, string* strMainBranchName, string* strDomainName, string* strApplicationName);
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
	int GetRegistryKeyValue();
	void InitClass();
	int InitGetOrSetRegistryValue(
		const string& strSection,
		const string& strKey);
	int SetRegistryKeyValue(
		const string& strSection,
		const string& strKey);
	LPCWSTR StringToLPCWSTR(
		const std::string& strInput);
	void SetRegistryKeyValueInit(
		const string& strKeySectionPath,
		const string& strKey,
		const string& strNewRegKeyValue);
	int UpdateRegistryKeyValue(
		const string& strKeySectionPath,
		const string& strKey,
		const string& strNewRegKeyValue);

	int
		iKeyValue;// possible value of the key only used when the key is an integer

	string
		//-------------------------------------------------------------------------------
		//
		//	Root values
		//
		strHive,			// name of the hive
		strMainBranch,		// name of the mainbranch 
		strDomain,			// name of the domain of the application
		strApplication,		// name of the application

		//-------------------------------------------------------------------------------
		//
		//	Registry key values
		//
		strSectionName,	// name of the section
		strKeyName,		// name of the key
		strRootPath,	// Key path to application registry root without hive
		strFullPath,	// Full path to the registry key currently searched/used

		//-------------------------------------------------------------------------------
		//
		//	Registry key value
		//
		strKeyValue,// possible value of the key only used when the key is a string

		//-------------------------------------------------------------------------------
		//
		//	Values used when update the registry
		//
		strNewKey,			// New name of the key
		strNewSection,		// New name of the section
		strNewFullKeyPath,	// Full path to the registry key new searched/used

		//-------------------------------------------------------------------------------
		//
		//	New registry key value
		//
		strNewKeyValue;		// New value of the key only used when the key is a string


	HKEY
		hkHive = HKEY_LOCAL_MACHINE;// value for hive

	LPCWSTR
		lpSubKey = nullptr,
		lpKey = nullptr;

};

