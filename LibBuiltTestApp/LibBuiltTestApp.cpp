// LibBuiltTestApp.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "LibBuiltTestApp.h"
//---------------------------------------------------------------------------------------
// Extra includes for the application.

// Project includes.
#include "Main.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
//---------------------------------------------------------------------------------------
// Global variables for the application.
//
WCHAR g_displayText[MAX_LOADSTRING] = L"Class test application";

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Encrypt(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	//--------------------------------------------------------------------------------------
	// Actual code for the application starts here.
	//
	
    //
	// Actual code for the application ends here.
    //
	//--------------------------------------------------------------------------------------

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LIBBUILTTESTAPP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LIBBUILTTESTAPP));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LIBBUILTTESTAPP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_LIBBUILTTESTAPP);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;

    HDC hdc;

    static const WCHAR* pInputText1 = L"Class test program"; // Example text to display
    WCHAR* context = NULL;

    int y = 5;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
			int iRC = 0;
            // Parse the menu selections:
            switch (wmId)
            {
            //----------------------------------------------------------------------------
            //
			// Class menu items.
            //
			//----------------------------------------------------------------------------
            //
			// Encryption menu items.
            //
            case ID_ENCRYPTION_ENCRYPT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ENCRYPTINPUTBOX), hWnd, Encrypt);
				break;
            case ID_ENCRYPTION_DECRYPT:
				break;
			
            //----------------------------------------------------------------------------
			// Default menu items.
            //
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			//---------------------------------------------------------------------------
			//
			// Search for end of line character and write line by line.
            //
			WCHAR* context = NULL;
			WCHAR* line = wcstok_s(g_displayText, L"\n", &context);
			while (line != NULL)
			{
                TextOut(hdc, 5, y, line, wcslen(line));
				y += 20;
				line = wcstok_s(NULL, L"\n", &context);
			}

			// End application-specific layout section.
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//---------------------------------------------------------------------------------------
//
// Message handler for the encryption input box.
//
INT_PTR CALLBACK Encrypt(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static WCHAR* pInputText = NULL;

	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			//------------------------------------------------------------------------------------
            // 
            // Get the text from the input box and convert to string
            //
			int iTextLength = GetWindowTextLength(GetDlgItem(hDlg, IDC_ENCRYPTINPUT));
			pInputText = new WCHAR[iTextLength + 1];
			GetWindowText(GetDlgItem(hDlg, IDC_ENCRYPTINPUT), pInputText, iTextLength + 1);
			EndDialog(hDlg, LOWORD(wParam));
            DialogEncryptInputBoxHandler(pInputText);

			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, IDCANCEL);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

//---------------------------------------------------------------------------------------
// 
// Dialog fuctions
//
//---------------------------------------------------------------------------------------
//
// Dialog function for the encryption input box.
//
//---------------------------------------------------------------------------------------
void DialogEncryptInputBoxHandler(const WCHAR *lInputString)
{
    static WCHAR* pOutputString = NULL;
	static WCHAR* pDisplayString = NULL;
    //-----------------------------------------------------------------------------------
	// 
	// Create an instance of the Main class.
	//
	Main* main = new Main();
    pOutputString = new WCHAR[MAX_LOADSTRING];
	main->Encrypt(lInputString, pOutputString);

	//-----------------------------------------------------------------------------------
	//
	// Update the display text.
    //
	pDisplayString = new WCHAR[MAX_LOADSTRING];
	wcscpy_s(pDisplayString, MAX_LOADSTRING, L"Input string: ");
    wcscat_s(pDisplayString, MAX_LOADSTRING, lInputString);
	wcscat_s(pDisplayString, MAX_LOADSTRING, L"\nOutput string: ");
    wcscat_s(pDisplayString, MAX_LOADSTRING, pOutputString);
	UpdateDisplayText(GetActiveWindow(), pDisplayString);

	//-----------------------------------------------------------------------------------
	//
	// Clean up.
	//
	delete[] pOutputString;
	delete[] pDisplayString;
	delete main;
	return;
}

//---------------------------------------------------------------------------------------
//
// Onther functions
//
//---------------------------------------------------------------------------------------
//
// Function to update the display text.
//
void UpdateDisplayText(HWND hWnd, const WCHAR* newText)
{
    wcscpy_s(g_displayText, MAX_LOADSTRING, newText);
    InvalidateRect(hWnd, NULL, TRUE);
}
