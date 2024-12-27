//---------------------------------------------------------------------------------------
//
// Module: Main.cpp
//
// This is the entry point for building and testing the WinLibrary classes.
//
//---------------------------------------------------------------------------------------
#include "Main.h"
#include <Windows.h>

//---------------------------------------------------------------------------------------
//
// Main constructor
//
Main::Main()
{
	
}

//---------------------------------------------------------------------------------------
//
// Test the functions of the encryption class
// 
//---------------------------------------------------------------------------------------
// 
// Test Encrypt function.
//
int Main::Encrypt(const WCHAR *lInputString, WCHAR *lOutputString)
{
	wcscpy_s(lOutputString, wcslen(lInputString) + 1, lInputString);
	return 0;
	
}

//---------------------------------------------------------------------------------------
// 
// Test Decrypt function.
//
int Main::Decrypt()
{
	return 0;

}

//#include <string>
//#include <locale>
//#include <codecvt>
//
//// Function to convert WCHAR* to std::string
//std::string ConvertWCHARToString(const WCHAR* wstr)
//{
//    // Convert WCHAR* to std::wstring
//    std::wstring ws(wstr);
//
//    // Use wstring_convert to convert wstring to string
//    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
//    std::string str = converter.to_bytes(ws);
//
//    return str;
//}
