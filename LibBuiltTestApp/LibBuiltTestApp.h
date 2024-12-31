#pragma once

#include "resource.h"
#include <string>
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK Encrypt(HWND, UINT, WPARAM, LPARAM);


void DialogEncryptInputBoxHandler(const WCHAR* lInputString);
void UpdateDisplayText(HWND hWnd, const WCHAR* newText);
