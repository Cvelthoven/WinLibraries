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
	void InitClass();
	int InitGetOrSetRegistryValue(
		const string& strSection,
		const string& strKey);
	int SetRegistryKeyValue(
		const string& strSection,
		const string& strKey);
	void StringToLPCWSTR(
		const std::string& strInput);
	int UpdateRegistryKeyValue(
		const string& strKeyPath,
		const string& strKey,
		const string& strNewKeyValue);

	int
		iRegistryKeyValue;// possible value of the key only used when the key is an integer

	string
		strHive,			// name of the hive
		strMainBranch,		// name of the mainbranch 
		strDomain,			// name of the domain of the application
		strApplication,		// name of the application
		strSectionName,		// name of the section
		strKeyName,			// name of the key
		strRegistryKeyValue,// possible value of the key only used when the key is a string
		strRegistryRootPath,// Key path to application registry root without hive
		strRegistryFullPath;// Full path to the registry key currently searched/used

	HKEY
		hkHive = HKEY_LOCAL_MACHINE;// value for hive

	LPCWSTR
		lpSubKey,
		lpKey;

};

