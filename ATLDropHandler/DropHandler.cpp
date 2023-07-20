// DropHandler.cpp : Implementation of CDropHandler

#include "pch.h"
#include "DropHandler.h"


// CDropHandler

// IDropTarget
HRESULT CDropHandler::DragEnter(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    return S_OK;
}

HRESULT CDropHandler::DragLeave()
{
    return S_OK;
}

HRESULT CDropHandler::DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
    *pdwEffect = DROPEFFECT_COPY;
    return S_OK;
}

HRESULT CDropHandler::Drop(IDataObject* pDataObj, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
{
    *pdwEffect &= DROPEFFECT_COPY;
    return S_OK;
}

// IPersistFile
HRESULT __stdcall CDropHandler::GetClassID(CLSID* pClassID)
{
    MessageBoxW(NULL, L"CDropHandler::GetClassID", L"Call", MB_OK);
    return S_OK;
}

HRESULT __stdcall CDropHandler::IsDirty(void)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDropHandler::Load(LPCOLESTR pszFileName, DWORD dwMode)
{
    MessageBoxW(NULL, L"CDropHandler::Load", L"Call", MB_OK);
    return S_OK;
}

HRESULT __stdcall CDropHandler::Save(LPCOLESTR pszFileName, BOOL fRemember)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDropHandler::SaveCompleted(LPCOLESTR pszFileName)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDropHandler::GetCurFile(LPOLESTR* ppszFileName)
{
    return E_NOTIMPL;
}