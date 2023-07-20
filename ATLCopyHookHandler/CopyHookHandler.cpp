// CopyHookHandler.cpp : Implementation of CCopyHookHandler

#include "pch.h"
#include "CopyHookHandler.h"


// CCopyHookHandler

UINT CCopyHookHandler::CopyCallback(HWND hwnd, UINT wFunc, UINT wFlags, PCTSTR pszSrcFile, DWORD dwSrcAttribs, LPCTSTR pszDestFile, DWORD dwDestAttribs)
{
	MessageBoxW(hwnd, L"CCopyHookHandler - CopyCallback", L"Call", MB_OK);
	wFlags = FOF_RENAMEONCOLLISION;

	return IDYES;
}
