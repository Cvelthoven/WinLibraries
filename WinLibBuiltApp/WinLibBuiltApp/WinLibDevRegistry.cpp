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
	//-----------------------------------------------------------------------------------
	//
	// Set class instance values
	//
	//-----------------------------------------------------------------------------------
	strHive = "";
	strMainBranch = "";
	strDomain = "";
	strApplication = "";
	strRegistryKeyValue = "";// ensure empty string for posibble result

	//-----------------------------------------------------------------------------------
	//
	//	Initialize class values
	//
	//-----------------------------------------------------------------------------------
	InitClass();

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
	//-----------------------------------------------------------------------------------
	strHive				= *strHiveName;
	strMainBranch		= "";
	strDomain			= *strDomainName;
	strApplication		= *strApplicationName;
	strRegistryKeyValue = "";// ensure empty string for posibble result

	//-----------------------------------------------------------------------------------
	//
	//	Initialize class values
	//
	//-----------------------------------------------------------------------------------
	InitClass();

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
	//-----------------------------------------------------------------------------------
	strHive				= *strHiveName;
	strMainBranch		= *strMainBranchName;
	strDomain			= *strDomainName;
	strApplication		= *strApplicationName;
	strRegistryKeyValue = "";// ensure empty string for posibble result

	//-----------------------------------------------------------------------------------
//
//	Initialize class values
//
//-----------------------------------------------------------------------------------
	InitClass();

}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//	Public Functions
//
//---------------------------------------------------------------------------------------
//	GetRegistryKeyValue functions
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
//	SetRegistryKeyValue functions
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
		(strRegOriginalValue != strRegKeyValue))
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
	//wchar_t
		//KeyValue[255];
	DWORD
		KeyValueLen,
		KeyValueDataType;

	int
		iRC = 1;

	string
		strSubKey,
		strKeyValue,
		strRC = "";

	HKEY
		hkHive;

	LPCWSTR
		lpSubKey,
		lpKey = 0;

	//--------------------------------------------------------------------------------------
	//
	//	Ensure that the correct hive is used and set the hive key
	//
	if ((strHive == "HKEY_CURRENT_USER") || (strHive == "HKEY_LOCAL_MACHINE"))
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
		hkHive = 0;

	//--------------------------------------------------------------------------------------
	//
	//	Convert strings to LPCWSTR
	//
	if (strSection.length() > 0)
	{
		strRegistryRootPath = strRegistryRootPath + "\\" + strSection;
	}
	std::wstring temp = std::wstring(strRegistryRootPath.begin(), strRegistryRootPath.end());
	lpSubKey = temp.c_str();

	std::wstring temp2 = std::wstring(strKey.begin(), strKey.end());
	lpKey = temp2.c_str();

	//-----------------------------------------------------------------------------------
	//
	//	Set default value when key is not found
	strRegistryKeyValue = strRC;
	iRegistryKeyValue = 0;

	//-----------------------------------------------------------------------------------
	//
	//	Open the registry key
	//
	if (RegOpenKeyEx(
		hkHive,
		lpSubKey,
		0,
		KEY_READ,
		&hkHive
			) != ERROR_SUCCESS)
	{
		return 1;
	}
	//-----------------------------------------------------------------------------------
	//
	//	Get the size of registry key
	//
	if (RegGetValue(
		hkHive,
		NULL,
		lpKey,
		RRF_RT_REG_SZ,
		&KeyValueDataType,
		NULL,
		&KeyValueLen
			) != ERROR_SUCCESS)
	{
		RegCloseKey(hkHive);
		return 1;
	}

	//-----------------------------------------------------------------------------------
	//
	//	Allocate memory for result
	LPWSTR KeyValue = (LPWSTR)malloc(KeyValueLen);


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
		NULL,
		lpKey,
		RRF_RT_REG_SZ,
		&KeyValueDataType,
		KeyValue,
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
		iRC = 1;
		switch (KeyValueDataType)
		{
			//-------------------------------------------------------------------------------
			//
			//	Return string value
		case REG_SZ:
			WideCharToMultiByte(CP_ACP, 0, KeyValue, -1, strTemp, 255, &DefChar, NULL);
			strRegistryKeyValue = strTemp;
			iRC = 0;
			break;
			//-------------------------------------------------------------------------------
			//
			//	Return long value
		case REG_DWORD:
			iRegistryKeyValue = KeyValue[0];
			iRC = 0;
			break;
		default:
			break;
		}

		//-------------------------------------------------------------------------------------
		//
		//	Close registry key 
		//	Cleanup
		//
		RegCloseKey(hkHive);
		free(KeyValue);
	}
	//-----------------------------------------------------------------------------------------
	//
	//	Return empty string as error result
	//

	return iRC;
}

//---------------------------------------------------------------------------------------
//
//	SetRegistryKeyValue
//	- input:
//
// --------------------------------------------------------------------------------------
void WinLibDevRegistry::InitClass()
{
	//-----------------------------------------------------------------------------------
	//
	//	Set string to key without hive and key
	//
	//-----------------------------------------------------------------------------------
	strRegistryRootPath = "";
	if (strMainBranch.length() > 0)
	{
		strRegistryRootPath = strMainBranch;
	}
	if (strDomain.length() > 0)
	{
		strRegistryRootPath = strRegistryRootPath + "\\" + strDomain;
	}
	if (strApplication.length() > 0)
	{
		strRegistryRootPath = strRegistryRootPath + "\\" + strApplication;
	}
}


//---------------------------------------------------------------------------------------
//
//	SetRegistryKeyValue
//	- input:
//		- strAppDomain
//		- strAppName
//		- strSection
//		- strKey
//
//---------------------------------------------------------------------------------------
int WinLibDevRegistry::SetRegistryKeyValue(
	const string& strSection,
	const string& strKey)
{


	//-----------------------------------------------------------------------------------
//	LSTATUS RegSetKeyValueA(
//		[in]           HKEY    hKey,
//		[in, optional] LPCSTR  lpSubKey,
//		[in, optional] LPCSTR  lpValueName,
//		[in]           DWORD   dwType,
//		[in, optional] LPCVOID lpData,
//		[in]           DWORD   cbData
//	);

	return 0;
}
