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