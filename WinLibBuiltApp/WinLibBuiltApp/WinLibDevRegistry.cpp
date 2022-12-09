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
#include <Windows.h>
//#include <tchar.h>

//---------------------------------------------------------------------------------------
//
//	Constructors
//
//---------------------------------------------------------------------------------------
//
//	Default constructor
//
//---------------------------------------------------------------------------------------
WinLibDevRegistry::WinLibDevRegistry()
{

}

//---------------------------------------------------------------------------------------
//
//	Constructor with
//		- Hive
//		- Domainname
//		- Application name
// 
//
//---------------------------------------------------------------------------------------
WinLibDevRegistry::WinLibDevRegistry(
	string* strHiveName,
	string* strDomainName, 
	string* strApplicationName)
{
	//-----------------------------------------------------------------------------------
	//
	// Set class instance values
	//
	strHive				= *strHiveName;
	strMainBranch		= "";
	strDomain			= *strDomainName;
	strApplication		= *strApplicationName;
	strRegistryKeyValue = "";// ensure empty string for posibble result
}

//---------------------------------------------------------------------------------------
//
//	Constructor with
//		- Hive
//		- Main branch
//		- Domainname
//		- Application name
//
//---------------------------------------------------------------------------------------
WinLibDevRegistry::WinLibDevRegistry(
	string* strHiveName,
	string* strMainBranchName,
	string* strDomainName,
	string* strApplicationName)
{
	//-----------------------------------------------------------------------------------
	//
	// Set class instance values
	//
	strHive				= *strHiveName;
	strMainBranch		= *strMainBranchName;
	strDomain			= *strDomainName;
	strApplication		= *strApplicationName;
	strRegistryKeyValue = "";// ensure empty string for posibble result

}

//---------------------------------------------------------------------------------------
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
	//Retrieve key value
	//
	if (GetRegistryKeyValue(strSection, strKey) == 0)
	{
		strRegKeyValue = strRegistryKeyValue;
		return 1;
	}
	else
	{
		strRegKeyValue = "";
		return 0;
	}

}

//---------------------------------------------------------------------------------------
//
//	GetRegistryKeyValue
//	- input:
//		- strSection
//		- strKey
//	- output:
//		- GetRegistryKeyValue
//		- iRegistryKevValue
//
//---------------------------------------------------------------------------------------
int WinLibDevRegistry::GetRegistryKeyValue(
	const string& strSection,
	const string& strKey,
	int& iRegKeyValue)
{
	//-----------------------------------------------------------------------------------
	//
	//Retrieve key value
	//
	if (GetRegistryKeyValue(strSection, strKey) == 0)
	{
		iRegKeyValue = iRegistryKeyValue;
		return 1;
	}
	else
	{
		iRegKeyValue = 0;
		return 0;
	}

}

//---------------------------------------------------------------------------------------
//
//	SetRegistryKeyValue
//	- input:
//		- strSection
//		- strKey
//		- strRegKeyValue
//	- output:
//		- SetRegistryKeyValue
//
//---------------------------------------------------------------------------------------
int WinLibDevRegistry::SetRegistryKeyValue(
	const string& strSection,
	const string& strKey,
	const string& strRegKeyValue)
{
	int iRegistryValueFound = 0;// set to 1 if the registry value is found

	string strRegOriginalValue = "";// current registry value if found

	//-----------------------------------------------------------------------------------
	//
	//	Retrieve original registry value if exists
	//
	if (GetRegistryKeyValue(strSection, strKey) == 0)
	{
		strRegOriginalValue = strRegistryKeyValue;
		iRegistryValueFound = 1;
	}
	else
	{
		strRegOriginalValue = "";
	}

	//-----------------------------------------------------------------------------------
	//
	//	Compare new value with original value if found
	//
	if ((iRegistryValueFound == 1)&&
		(strRegOriginalValue != strRegistryKeyValue))
		{

		}
		else
			//---------------------------------------------------------------------------
			//
			//	Current key value is equel to the new value -> no action required
			//
			return 0;

	return 0;
}


//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//	Private Functions
//
//---------------------------------------------------------------------------------------
//
//	GetRegistryKeyValue
//	- input:
//		- strAppDomain
//		- strAppName
//		- strSection
//		- strKey
//
//---------------------------------------------------------------------------------------
int WinLibDevRegistry::GetRegistryKeyValue(
	const string& strSection,
	const string& strKey)
{
	//-----------------------------------------------------------------------------------
	//
	//	Local variables
	wchar_t
		KeyValue[255];
	DWORD
		KeyValueLen = sizeof(KeyValue),
		KeyValueDataType;
	string
		strSubKey,
		strKeyValue,
		strRC = "";
	HKEY
		hkHive;
	LPCWSTR
		lpSubKey,
		lpKey;

	//-----------------------------------------------------------------------------------
	//
	//	Set default value when key is not found
	strRegistryKeyValue = strRC;
	iRegistryKeyValue = 0;

	//-----------------------------------------------------------------------------------
	//
	//	Convert input strings to LPCSTR required in RegGetValue
	//
	strSubKey = strMainBranch + "\\" + strDomain + "\\" + strApplication;
	if (strSection.length() > 0)
	{
		strSubKey = strSubKey + "\\" + strSection;
	}

	std::wstring temp = std::wstring(strSubKey.begin(), strSubKey.end());
	lpSubKey = temp.c_str();
	std::wstring temp2 = std::wstring(strKey.begin(), strKey.end());
	lpKey = temp2.c_str();

	//-----------------------------------------------------------------------------------
	//
	//	Set hive value
	//	Only HKEY_CURRENT_USER or HKEY_LOCAL_MACHINE hives are accepted
	if ((strHive == "HKEY_CURRENT_USER")||(strHive == "HKEY_LOCAL_MACHINE"))
	{
		if (strHive == "HKEY_CURRENT_USER")
		{
			hkHive = HKEY_CURRENT_USER;
		}
		else
		{
			hkHive = HKEY_LOCAL_MACHINE;
		}
	}

	else
	{
		return 1;
	}

	//-----------------------------------------------------------------------------------
	//
	//	Retrieve key value
	//	- KeyValueDataType:
	//		- REG_NONE = 0 
	//		- REG_SZ = 1 (null terminated string)
	//		- REG_BINARY = 3
	//		- REG_DWORD = 4 (32-bit number)
	//
	if (RegGetValue(
		hkHive,
		lpSubKey,
		lpKey,
		RRF_RT_ANY,
		&KeyValueDataType,
		(PVOID)&KeyValue,
		&KeyValueLen
	) == ERROR_SUCCESS)

		//-----------------------------------------------------------------------------------
		//
		//	Return value of key
		//
	{
		//-------------------------------------------------------------------------------
		//
		//	Return the value based on type
		char strTemp[255];
		char DefChar = ' ';
		switch (KeyValueDataType)
		{
			//-------------------------------------------------------------------------------
			//
			//	Return string value
		case REG_SZ:
			WideCharToMultiByte(CP_ACP, 0, KeyValue, -1, strTemp, 255, &DefChar, NULL);
			strRegistryKeyValue = strTemp;
			return 0;
			break;
			//-------------------------------------------------------------------------------
			//
			//	Return long value
		case REG_DWORD:
			iRegistryKeyValue = KeyValue[0];
			return 0;
			break;
		default:
			break;
		}
	}
	//-----------------------------------------------------------------------------------
	//
	//	Return empty string as error result
	//

	return 1;
}

