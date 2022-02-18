#include "MainWindow.h"
#include "LibRegistry.h"

#include <string>

//---------------------------------------------------------------------------------------
//
//	Constructors
MainWindow::MainWindow()
{
	string 
		strsection = "WinLibTest",
		strKey = "test01";

	LibRegistry* clApplicationSettings = new LibRegistry(strsection, strKey);
}

//---------------------------------------------------------------------------------------
//
//	Functions
//
//---------------------------------------------------------------------------------------
//
//	InitProgram
//
//---------------------------------------------------------------------------------------
