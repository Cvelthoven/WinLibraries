//---------------------------------------------------------------------------------------
//
//	MainWindow.h
//
//---------------------------------------------------------------------------------------
//
//	Header files
//
//---------------------------------------------------------------------------------------
using namespace std;
#include "MainWindow.h"
#include "WinLibDevRegistry.h"
#include <string>

//---------------------------------------------------------------------------------------
//
//	Constructors
MainWindow::MainWindow()
{
	//-----------------------------------------------------------------------------------
	//
	//	Test WinLibRegistry class
	WinLibRegistry();
	
}

//---------------------------------------------------------------------------------------
//
//	Public Functions
//
//---------------------------------------------------------------------------------------



//---------------------------------------------------------------------------------------
//
//	Private Functions
//
//---------------------------------------------------------------------------------------
//
//	WinLibRegistry
//	Test function for the WinLibRegistry class
//
//---------------------------------------------------------------------------------------
void MainWindow::WinLibRegistry()
{
	int
		iRC;

	string
		strHive = "HKEY_CURRENT_USER",
		strMainBranch = "SOFTWARE",
		strDomain = "CVelthoven.com",
		strApplication = "WinLibBuiltApp",
		strSection = "Builtsection01",
		strKey = "BuiltKey01",
		strKeyValue;


	//-----------------------------------------------------------------------------------
	//
	//	Create class instance
	//
	WinLibDevRegistry* clsRegistry = new WinLibDevRegistry(&strHive, &strMainBranch, &strDomain, &strApplication);

	//--------------------------------------------------------------------------------------
	//
	//	Retrieve registry key
	//
	iRC = clsRegistry->GetRegistryKeyValue(strSection, strKey, strKeyValue);

	//--------------------------------------------------------------------------------------
	//
	//	Update registry key
	//
	if (iRC == 1)
	{
		iRC = clsRegistry->SetRegistryKeyValue(strSection, strKey, strKeyValue);
	}

}
