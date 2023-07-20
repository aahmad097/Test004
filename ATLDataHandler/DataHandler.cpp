// DataHandler.cpp : Implementation of CDataHandler

#include "pch.h"
#include "DataHandler.h"


// CDataHandler

HRESULT __stdcall CDataHandler::GetClassID(CLSID* pClassID)
{
    MessageBoxW(NULL, L"CDataHandler::GetClassID", L"Call", MB_OK);
    return S_OK;
}

HRESULT __stdcall CDataHandler::IsDirty(void)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDataHandler::Load(LPCOLESTR pszFileName, DWORD dwMode)
{
    MessageBoxW(NULL, L"CDataHandler::Load", L"Call", MB_OK);
    return S_OK;
}

HRESULT __stdcall CDataHandler::Save(LPCOLESTR pszFileName, BOOL fRemember)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDataHandler::SaveCompleted(LPCOLESTR pszFileName)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDataHandler::GetCurFile(LPOLESTR* ppszFileName)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDataHandler::GetData(FORMATETC* pformatetcIn, STGMEDIUM* pmedium)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDataHandler::GetDataHere(FORMATETC* pformatetc, STGMEDIUM* pmedium)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDataHandler::QueryGetData(FORMATETC* pformatetc)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDataHandler::GetCanonicalFormatEtc(FORMATETC* pformatectIn, FORMATETC* pformatetcOut)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDataHandler::SetData(FORMATETC* pformatetc, STGMEDIUM* pmedium, BOOL fRelease)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDataHandler::EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC** ppenumFormatEtc)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDataHandler::DAdvise(FORMATETC* pformatetc, DWORD advf, IAdviseSink* pAdvSink, DWORD* pdwConnection)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDataHandler::DUnadvise(DWORD dwConnection)
{
    return E_NOTIMPL;
}

HRESULT __stdcall CDataHandler::EnumDAdvise(IEnumSTATDATA** ppenumAdvise)
{
    return E_NOTIMPL;
}
