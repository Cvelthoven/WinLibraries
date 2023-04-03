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
			switch (UpdateRegistryKeyValue(strSection, strKey, strRegistryKeyValue))
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
	//DWORD
	//	KeyValueLen = 0,
	//	KeyValueDataType = 0;

	int
		iRC = 1;

//	string
//		strSubKey,
//		strKeyPath = "",	// Key path to the key with the hiv
//		strKeyValue,
//		strRC = "";
//
////	HKEY
//		hkHive;

	//LPCWSTR
	//	lpSubKey,
	//	lpKey = 0;

	//-----------------------------------------------------------------------------------
	//
	//	Init instance information
	//
	if (InitGetOrSetRegistryValue(strSection, strKey) != 0)
	{
		return 1;
	}

	//-----------------------------------------------------------------------------------
	//
	//	Convert strings to LPCWSTR
	//
//	StringToLPCWSTR(strRegistryFullPath);
////	std::wstring temp = std::wstring(strKeyPath.begin(), strKeyPath.end());
////	lpSubKey = temp.c_str();
//
//	std::wstring temp2 = std::wstring(strKey.begin(), strKey.end());
//	lpKey = temp2.c_str();
//
////	LPCWSTR lpSubKey = StringToLPCWSTR(strRegistryRootPath, strSection);
////	LPCWSTR lpKey = StringToLPCWSTR(strKey);
//
//	//-----------------------------------------------------------------------------------
//	//
//	//	Set default value when key is not found
//	strRegistryKeyValue = strRC;
//	iRegistryKeyValue = 0;
//
	////-----------------------------------------------------------------------------------
	////
	////	Open the registry key
	////
	//if (RegOpenKeyEx(
	//		hkHive,
	//		lpSubKey,
	//		0,
	//		KEY_READ,
	//		&hkHive
	//	) != ERROR_SUCCESS)
	//{
	//	return 1;
	//}
	////-----------------------------------------------------------------------------------
	////
	////	Get the size of registry key
	////
	//if (RegGetValue(
	//		hkHive,
	//		NULL,
	//		lpKey,
	//		RRF_RT_REG_SZ,
	//		&KeyValueDataType,
	//		NULL,
	//		&KeyValueLen
	//	) != ERROR_SUCCESS)
	//{
	//	RegCloseKey(hkHive);
	//	return 1;
	//}

	////-----------------------------------------------------------------------------------
	////
	////	Allocate memory for result
	//LPWSTR KeyValue = (LPWSTR)malloc(KeyValueLen);


	////-----------------------------------------------------------------------------------
	////
	////	Retrieve key value
	////	- KeyValueDataType:
	////		- REG_NONE = 0 
	////		- REG_SZ = 1 (null terminated string)
	////		- REG_BINARY = 3
	////		- REG_DWORD = 4 (32-bit number)
	////
	//if (RegGetValue(
	//	hkHive,
	//	NULL,
	//	lpKey,
	//	RRF_RT_REG_SZ,
	//	&KeyValueDataType,
	//	KeyValue,
	//	&KeyValueLen
	//		) == ERROR_SUCCESS)

	//	//-----------------------------------------------------------------------------------
	//	//
	//	//	Return value of key
	//	//
	//{
	//	//-------------------------------------------------------------------------------
	//	//
	//	//	Return the value based on type
	//	char strTemp[255];
	//	char DefChar = ' ';
	//	iRC = 1;
	//	switch (KeyValueDataType)
	//	{
	//		//-------------------------------------------------------------------------------
	//		//
	//		//	Return string value
	//	case REG_SZ:
	//		WideCharToMultiByte(CP_ACP, 0, KeyValue, -1, strTemp, 255, &DefChar, NULL);
	//		strRegistryKeyValue = strTemp;
	//		iRC = 0;
	//		break;
	//		//-------------------------------------------------------------------------------
	//		//
	//		//	Return long value
	//	case REG_DWORD:
	//		iRegistryKeyValue = KeyValue[0];
	//		iRC = 0;
	//		break;
	//	default:
	//		break;
	//	}

	//	//-------------------------------------------------------------------------------------
	//	//
	//	//	Close registry key 
	//	//	Cleanup
	//	//
	//	RegCloseKey(hkHive);
	//	free(KeyValue);
	//}
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


	return 1;
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
//		- StringToLPCWSTR: the converted stringLPCWSTR StringToLPCWSTR(
void StringToLPCWSTR(
	const std::string& strInput)
{
	//--------------------------------------------------------------------------------------
	// 
	//	local variables
	// 

	LPCWSTR lpResult;

	//--------------------------------------------------------------------------------------
	//	Get size of input string buffer
	//
	string strTemp = strInput;
	std::wstring temp = std::wstring(strInput.begin(), strInput.end());
	lpResult = temp.c_str();

//	iStrLen = MultiByteToWideChar(CP_UTF8, 0, strTemp.c_str(), -1, nullptr, 0);
//	if (iStrLen == 0)
//	{
//		return nullptr;
//	}

	//-----------------------------------------------------------------------------------
	// 
	// Convert input string to LPCWSTR
	// 
//	auto buffer = new wchar_t(iStrLen);
//	MultiByteToWideChar(CP_UTF8, 0, strTemp.c_str(), -1, buffer, iStrLen);
//	return buffer;

}


//	code example from ChatGPT
// 
// #include <Windows.h>
//#include <string>
//
//// Converts a std::string to a LPCWSTR
//LPCWSTR StringToLPCWSTR(const std::string& str)
//{
//	int bufferLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
//	if (bufferLen == 0) {
//		return nullptr;
//	}
//
//	auto buffer = new wchar_t[bufferLen];
//	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buffer, bufferLen);
//
//	return buffer;
//}
//
//int main()
//{
//	std::string myString = "Hello, World!";
//
//	LPCWSTR myLpcwstr = StringToLPCWSTR(myString);
//
//	// Use the myLpcwstr pointer here...
//
//	// Remember to delete the allocated buffer when you're done with it
//	delete[] myLpcwstr;
//
//	return 0;
//}



