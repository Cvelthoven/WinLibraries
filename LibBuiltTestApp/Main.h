//---------------------------------------------------------------------------------------
// Main.h
// 
// This is the main header file for the application of the main window.
// This file contains the class definition for the main window.
// 
//---------------------------------------------------------------------------------------
#pragma once

//---------------------------------------------------------------------------------------
//
// Include files of general use libraries
//
#include <Windows.h>

//---------------------------------------------------------------------------------------
//
// Class definition: Main
//
class Main
{
public:
	//-----------------------------------------------------------------------------------
	//
	// Constructor and destructor
	Main();
	//~Main();

	//-----------------------------------------------------------------------------------
	// Test the functions of the encryption class
	//
	int Encrypt(const WCHAR* lInputString, WCHAR* lOutputString, double* dRunTime);
	int Decrypt(const WCHAR* lInputString, WCHAR* lOutputString, double* dRunTime);
};

