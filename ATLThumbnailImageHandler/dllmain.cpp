// dllmain.cpp : Implementation of DllMain.

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "ATLThumbnailImageHandler_i.h"
#include "dllmain.h"

CATLThumbnailImageHandlerModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) MessageBoxW(NULL, L"CThumbnailImageHandler - DLL Main", L"Call", MB_OK);
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved);
}
