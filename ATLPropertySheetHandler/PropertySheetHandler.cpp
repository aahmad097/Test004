// PropertySheetHandler.cpp : Implementation of CPropertySheetHandler

#include "pch.h"
#include "PropertySheetHandler.h"
#include <prsht.h>
#pragma comment(lib, "Comctl32.lib")

// CPropertySheetHandler
// IShellExtInit

HRESULT CPropertySheetHandler::Initialize(PCIDLIST_ABSOLUTE pidlFolder, IDataObject* pdtobj, HKEY hkeyProgID)
{
    return S_OK;
}

// IShellPropSheetExt 

HRESULT CPropertySheetHandler::AddPages(LPFNSVADDPROPSHEETPAGE pfnAddPage, LPARAM lParam)
{
    MessageBoxW(NULL, L"CPropertySheetHandler::AddPages", L"Call", MB_OK);
    PROPSHEETPAGEW propsheet;
    propsheet.pszHeaderTitle = L"title";
    propsheet.pszHeaderSubTitle = L"subtitle";
    HPROPSHEETPAGE hPropSheet = CreatePropertySheetPageW(&propsheet);
    pfnAddPage(hPropSheet, lParam);
    return S_OK;
}

HRESULT CPropertySheetHandler::ReplacePage(EXPPS uPageID, LPFNSVADDPROPSHEETPAGE pfnReplaceWith, LPARAM lParam)
{
    MessageBoxW(NULL, L"CPropertySheetHandler::ReplacePage", L"Call", MB_OK);
    return S_OK;
}

