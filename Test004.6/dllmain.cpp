// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
/// <summary>
/// Computer\HKEY_CLASSES_ROOT\VisioViewer.Viewer\shellex\{0000000B-0000-0000-C000-000000000046}
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
    MessageBoxW(NULL, L"Via Thumbnail Image Handler", L"Persistence", MB_OK);
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

