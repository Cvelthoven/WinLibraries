#pragma once
#include <Windows.h>
//---------------------------------------------------------------------------------------
// Main.h
// 
// This is the main header file for the application of the main window.
// This file contains the class definition for the main window.
// 
//---------------------------------------------------------------------------------------
class Main
{
public:
	Main();
	//~Main();
//---------------------------------------------------------------------------------------
// Test the functions of the encryption class
//
	int Encrypt(const WCHAR* lInputString, WCHAR* lOutputString);
	int Decrypt();
};

