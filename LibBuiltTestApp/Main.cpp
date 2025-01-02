//---------------------------------------------------------------------------------------
//
// Module: Main.cpp
//
// This is the entry point for building and testing the WinLibrary classes.
//
//---------------------------------------------------------------------------------------
//
// Include files of general use libraries
//
#include <cstring>
#include <Windows.h>

//---------------------------------------------------------------------------------------
//
// Include files of the project libraries
//
#include "Encryption.h"
#include "Main.h"
#include "Timer.h"


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
int Main::Encrypt(const WCHAR *lInputString, WCHAR *lOutputString, double *dRunTime)
{
	Timer EncryptTimer;

    // Convert WCHAR to unsigned char
    int input_len = wcslen(lInputString) * sizeof(WCHAR);
    unsigned char* input = reinterpret_cast<unsigned char*>(const_cast<WCHAR*>(lInputString));
    unsigned char output[128];
    int output_len;

    //-----------------------------------------------------------------------------------
    // 
	// Start the timer
    // 
	EncryptTimer.Start();

	//-----------------------------------------------------------------------------------
    // 
    // Actual encryption routine
    // 
    // AES key and IV (for demonstration purposes, use a secure method to generate and store these)
    //
    unsigned char key[32] = { 0 };
    unsigned char iv[16] = { 0 };

    Encryption encryption(key, iv);
    encryption.Encrypt(input, input_len, output, output_len);

	//-----------------------------------------------------------------------------------
    //
	// Stop the timer
    //
	EncryptTimer.Stop();

    //-----------------------------------------------------------------------------------
    // 
	// Prepare output
    // 
    // ----------------------------------------------------------------------------------
    // 
    // Convert unsigned char to WCHAR
    std::memcpy(lOutputString, output, output_len);
    lOutputString[output_len / sizeof(WCHAR)] = L'\0';

	//-----------------------------------------------------------------------------------
    //
	//  Get the elapsed time
    //
	*dRunTime = EncryptTimer.GetElapsedMilliseconds();

	return 0;
}

//---------------------------------------------------------------------------------------
// 
// Test Decrypt function.
//
int Main::Decrypt(const WCHAR* lInputString, WCHAR* lOutputString)
{
    // Convert WCHAR to unsigned char
    int input_len = wcslen(lInputString) * sizeof(WCHAR);
    unsigned char* input = reinterpret_cast<unsigned char*>(const_cast<WCHAR*>(lInputString));
    unsigned char output[128];
    int output_len;

    // AES key and IV (for demonstration purposes, use a secure method to generate and store these)
    unsigned char key[32] = { 0 };
    unsigned char iv[16] = { 0 };

    Encryption encryption(key, iv);
    encryption.Decrypt(input, input_len, output, output_len);

    // Convert unsigned char to WCHAR
    std::memcpy(lOutputString, output, output_len);
    lOutputString[output_len / sizeof(WCHAR)] = L'\0';

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
