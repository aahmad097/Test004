// dllmain.cpp : Implementation of DllMain.

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "ATLDropHandler_i.h"
#include "dllmain.h"

CATLDropHandlerModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) MessageBoxW(NULL, L"CDropHandler - DLL Main", L"Call", MB_OK);
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved);
}
