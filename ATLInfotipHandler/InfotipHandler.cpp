// InfotipHandler.cpp : Implementation of CInfotipHandler

#include "pch.h"
#include "InfotipHandler.h"


// CInfotipHandler
// There is a bug where this doesnt get called ??
HRESULT CInfotipHandler::GetInfoTip(DWORD dwFlags, PWSTR* ppwszTip)
{
   
    dwFlags = QITIPF_DEFAULT;
    const WCHAR* str = L":atredis_bird:";
    PWSTR* ppstr = (PWSTR*)CoTaskMemAlloc(sizeof(str));
    if (ppstr) {
        memcpy(ppstr, str, sizeof(str));
        ppwszTip = ppstr;
        return S_OK;
    }
    else {
        ppwszTip = NULL;
        return S_FALSE;
    }

}

HRESULT CInfotipHandler::GetInfoFlags(DWORD* pdwFlags)
{
    pdwFlags = NULL;
    return S_OK;

}
