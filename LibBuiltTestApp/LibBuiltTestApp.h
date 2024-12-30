#pragma once

#include "resource.h"
#include <string>
#include <Windows.h>

void DialogEncryptInputBoxHandler(const WCHAR* lInputString);
void UpdateDisplayText(HWND hWnd, const WCHAR* newText);
