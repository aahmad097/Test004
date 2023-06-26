// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
/// <summary>
/// Computer\HKEY_CLASSES_ROOT\VisioViewer.Viewer\shellex\IconHandler
/// </summary>
/// <param name="hModule"></param>
/// <param name="ul_reason_for_call"></param>
/// <param name="lpReserved"></param>
/// <returns></returns>
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    MessageBoxW(NULL, L"Via Icon Handler", L"Persistence", MB_OK);
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

