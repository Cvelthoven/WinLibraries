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
//		- Domainname
//		- Application name
//
//---------------------------------------------------------------------------------------
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
	iRC = GetRegistryKeyValue(strSection, strKey);
	strRegKeyValue = strRegistryKeyValue;
	return iRC;
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
	//	Local variables
	int
		iRC = 0;

	//-----------------------------------------------------------------------------------
	//
	//Retrieve key value
	//
	iRC = GetRegistryKeyValue(strSection, strKey);
	iRegKeyValue = iRegistryKeyValue;
	return iRC;
}

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
int SetRegistryKeyValue(
	const string& strSection,
	const string& strKey,
	const string& strRegKeyValue)
{

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
	strSubKey = "SOFTWARE\\" + strDomain + "\\" + strApplication;
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
	//	Retrieve key value
	//	- KeyValueDataType:
	//		- REG_NONE = 0 
	//		- REG_SZ = 1 (null terminated string)
	//		- REG_BINARY = 3
	//		- REG_DWORD = 4 (32-bit number)
	//
	if (RegGetValue(
		HKEY_CURRENT_USER,
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

