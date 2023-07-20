// IconOverlayHandler.cpp : Implementation of CIconOverlayHandler

#include "pch.h"
#include "IconOverlayHandler.h"


// CIconOverlayHandler

HRESULT CIconOverlayHandler::GetOverlayInfo(LPWSTR pwszIconFile, int cchMax, int* pIndex, DWORD* pdwFlags)
{
    *pdwFlags = ISIOI_ICONFILE;
    return S_OK;
}

HRESULT CIconOverlayHandler::GetPriority(int* pPriority)
{
    *pPriority = 100;
    return S_OK;
}

HRESULT CIconOverlayHandler::IsMemberOf(LPCWSTR pwszPath, DWORD dwAttrib)
{
    return S_OK;
}
