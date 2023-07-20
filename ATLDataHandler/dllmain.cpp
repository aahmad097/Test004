// dllmain.cpp : Implementation of DllMain.

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "ATLDataHandler_i.h"
#include "dllmain.h"

CATLDataHandlerModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) MessageBoxW(NULL, L"CDataHandler - DLL Main", L"Call", MB_OK);
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved);
}
