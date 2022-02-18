//---------------------------------------------------------------------------------------
//
//	LibRegistry.h
//
//---------------------------------------------------------------------------------------
#pragma once
//---------------------------------------------------------------------------------------
//
//	Header files
//
//---------------------------------------------------------------------------------------
//using namespace std;// needed for default header files
//#include <string>

#ifdef LIBREGISTRYDLL_EXPORTS
#define LIBREGISTRY_API __declspec(dllexport)
#else
#define LIBREGISTRY_API __declspec(dllimport)
#endif



class LIBREGISTRY_API LibRegistry
{
	virtual int GetRestrisryKeyValue() = 0;
};



//----------------  OLD CODE ------------------------------------------------------------------------------------
////Calculation.h
//#pragma once
//#ifdef CALCULATIONDLL_EXPORTS  
//#define CALCULATION_API __declspec(dllexport)   
//#else  
//#define CALCULATION_API __declspec(dllimport)   
//#endif  
//class  CALCULATION_API CalculationApi
//{
//public:
//    void Addition(void);
//    void Subtraction(void);
//    void Multiply(void);
//};



////---------------------------------------------------------------------------------------
////
////	LibRegistry.h
////
////---------------------------------------------------------------------------------------
//#pragma once
////---------------------------------------------------------------------------------------
////
////	Header files
////
////---------------------------------------------------------------------------------------
////using namespace std;// needed for default header files
////#include <string>
//
//#ifdef LIBREGISTRYDLL_EXPORTS
//#define LIBREGISTRY_API __declspec(dllexport)
//#else
//#define LIBREGISTRY_API __declspec(dllimport)
//#endif
//
//
//
//class LIBREGISTRY_API LibRegistry
//{
//	//---------------------------------------------------------------------------------------
//	//
//	//	Public declarations
//	//
//	//---------------------------------------------------------------------------------------
//public:
//
//	//LibRegistry(
//	//	string& strAplicationDomain,
//	//	string& strAplicationName);
//	//LibRegistry();
//	//void add(void);
//
//	//int GetRegistryKeyValue(
//	//	const string& strSection,
//	//	const string& strKey,
//	//	string& strRegKeyValue);
//
//	//---------------------------------------------------------------------------------------
//	//
//	//	Private declarations
//	//
//	//---------------------------------------------------------------------------------------
//private:
////	string
//		//strAplDomain,
//		//strAplName,
//		//strRegistryKeyPath;
//
//};