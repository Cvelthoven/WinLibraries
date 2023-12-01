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
//		- Domain name
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
//		- Domain name
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
//
//	Destructor
//
//---------------------------------------------------------------------------------------
WinLibDevRegistry::~WinLibDevRegistry()
{
	if (lpSubKey != nullptr)
	{
		delete[] lpSubKey;
	}
	if (lpKey != nullptr)
	{
		delete[] lpKey;
	}
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
//		- GetRegistryKeyValue:
//			- 0: Registykey value retrieved
//			- 1: Unable to retrieve registrykey value
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
	// 
	int iRC = 0;

	//-----------------------------------------------------------------------------------
	// 
	//	Set class values
	// 
	iRC = InitGetOrSetRegistryValue(strSection, strKey);
	if (iRC != 0)

	{
		return iRC;
	}

	//-----------------------------------------------------------------------------------
	//
	//Retrieve key value
	//
	if (GetRegistryKeyValue() == 0)
	{
		strRegKeyValue = strRegistryKeyValue;
		return 0;
	}
	else
	{
		strRegKeyValue = "";
		return 1;
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
//			- 0: Registykey value retrieved
//			- 1: Unable to retrieve registrykey value
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
	if (GetRegistryKeyValue() == 0)
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
//		- SetRegistryKeyValue:
//			0: successfull value update (including possible creation of key)
//
//---------------------------------------------------------------------------------------
int WinLibDevRegistry::SetRegistryKeyValue(
	const string& strSection,
	const string& strKey,
	const string& strRegKeyValue)
{
	int iRC = 0,				// return value
		iRegistryValueFound = 0;// set to 1 if the registry value is found

	string strRegOriginalValue = "";// current registry value if found

	//-----------------------------------------------------------------------------------
	//
	//	Retrieve original registry value if exists
	//
	if (GetRegistryKeyValue(strSection, strKey, strRegOriginalValue) == 0)
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
			switch (UpdateRegistryKeyValue(strSection, strKey, strRegKeyValue))
			{
				case 0:
					iRC = 0;
					break;
				default:
					iRC = 0;
					break;
			}
		}
		else
			//---------------------------------------------------------------------------
			//
			//	Current key value is equel to the new value -> no action required
			//
			iRC = 0;

	return iRC;
}


//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
//
//	Private Functions
//
//---------------------------------------------------------------------------------------
//
//	GetRegistryKeyValue
//	- input for class values:
//		- strAppDomain
//		- strAppName
//		- strSection
//		- strKey
//	- Output:
//		- GetRegistryKeyValue:
//			- 0: Registykey value retrieved
//			- 1: Unable to retrieve registrykey value
//
//---------------------------------------------------------------------------------------
int WinLibDevRegistry::GetRegistryKeyValue()
{
	//-----------------------------------------------------------------------------------
	//
	//	Local variables
	DWORD
		KeyValueLen = 0,
		KeyValueDataType = 0;

	int
		iRC = 1;

	string
		strRC = "";

	//-----------------------------------------------------------------------------------
	//
	//	Set default value when key is not found
	strRegistryKeyValue = strRC;
	iRegistryKeyValue = 0;

	//-----------------------------------------------------------------------------------
	//
	//	Open the registry key
	//
	if (RegOpenKeyExW(
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
	if (RegGetValueW(
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
//	InitGetOrSetRegistryValue
//	- input:
//		- strSection
//		- strKey
//	- output:
//		- InitGetOrSetRegistryValue:
//			- 0: Init of values successfull
//			- 1: Init of values failed
//
// --------------------------------------------------------------------------------------
int WinLibDevRegistry::InitGetOrSetRegistryValue(
	const string& strSection,
	const string& strKey)
{
	//-----------------------------------------------------------------------------------
	//
	//	Copy strSection to strSectionName
	//	Copy strKey to strKeyName
	//	Set strRegistryFullPath
	//
	strRegistryFullPath = strRegistryRootPath;
	if (strSection.length() > 0)
	{
		strSectionName = strSection;
		strRegistryFullPath = strRegistryRootPath + "\\" + strSection;
	}
	else
	{
		strSectionName = "";
	}
	if (strKey.length() > 0)
	{
		strKeyName = strKey;
	}
	else
	{
		strKeyName = "";
	}

	//-----------------------------------------------------------------------------------
	//
	//	convert strRegistryFullPath to LPCWSTR lpSubKey
	//
	lpSubKey = StringToLPCWSTR(strRegistryFullPath);

	//-----------------------------------------------------------------------------------
	//
	//	convert strKeyName to LPCWSTR lpKey
	//
	lpKey = StringToLPCWSTR(strKeyName);

	//-----------------------------------------------------------------------------------
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


	return 0;
}


//---------------------------------------------------------------------------------------
//
//	SetRegistryKeyValue
//	- input:
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

//---------------------------------------------------------------------------------------
//
//	UpdateRegistryKeyValue
//	- input:
//		- strKeyPath	: full path to registry key without the hive
//		- strKey		: registry key name
//		- strNewKeyValue: new string value
//	- output:
//		- UpdateRegistryKeyValue:
//			- 0: update value succesful
//
//---------------------------------------------------------------------------------------
int WinLibDevRegistry::UpdateRegistryKeyValue(
	const string& strKeyPath,
	const string& strKey,
	const string& strNewKeyValue)
{
	int iRC = 0;// return code

	//-----------------------------------------------------------------------------------
	//
	//	Open key
	//

	return 0;
}

//---------------------------------------------------------------------------------------
//
//	LPCWSTR StringToLPCWSTR
//
//	Convert strings to LPCWSTR
//
//	Input:
//		- strInput: first part of the concatenated string
//			- may be an emptpy strings
//	Output:
//		- StringToLPCWSTR: the converted stringLPCWSTR StringToLPCWSTR
//
LPCWSTR WinLibDevRegistry::StringToLPCWSTR(
	const std::string& strInput)
{
	//--------------------------------------------------------------------------------------
	// 
	//	local variables
	//
	int iStrLen;
	LPWSTR lpResult;

	//--------------------------------------------------------------------------------------
	//	Get size of input string buffer
	//
	iStrLen = MultiByteToWideChar(CP_UTF8, 0, strInput.c_str(), -1, nullptr, 0);
	if (iStrLen == 0)
	{
		return nullptr;
	}

	//-----------------------------------------------------------------------------------
	// 
	// Convert input string to LPCWSTR
	// 
	lpResult = new wchar_t(iStrLen);
	MultiByteToWideChar(CP_UTF8, 0, strInput.c_str(), -1, lpResult, iStrLen);
	return lpResult;

}

