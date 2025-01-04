//---------------------------------------------------------------------------------------
// 
// LibBuiltTestApp.h : Headers of functions in LibBuiltTestApp.
//
//---------------------------------------------------------------------------------------
#pragma once

//---------------------------------------------------------------------------------------
//
// Include files of general use libraries
//
#include "resource.h"
#include <string>
#include <Windows.h>

//---------------------------------------------------------------------------------------
//
// Function prototype of the dialog box handler.
//
void DialogEncryptInputBoxHandler(const WCHAR* lInputString);
//---------------------------------------------------------------------------------------
//
// Function prototype of the function to update the display text.
//
void UpdateDisplayText(HWND hWnd, const WCHAR* newText);
