// IconHandler.h : Declaration of the CIconHandler

#pragma once
#include "resource.h"       // main symbols
#include "ATLIconHandler_i.h"
#include <shlobj_core.h>


using namespace ATL;


// CIconHandler

class ATL_NO_VTABLE CIconHandler :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIconHandler, &CLSID_IconHandler>,
	public IExtractIcon,
	public IPersistFile 
{
public:
	CIconHandler()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ICONHANDLER)


BEGIN_COM_MAP(CIconHandler)
	COM_INTERFACE_ENTRY(IPersistFile)
	COM_INTERFACE_ENTRY(IExtractIcon)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

private:

	HRESULT __stdcall GetIconLocation(
		UINT   uFlags,
		PWSTR  pszIconFile,
		UINT   cchMax,
		int* piIndex,
		UINT* pwFlags) override;

	HRESULT __stdcall Extract(
		_In_ PCWSTR  pszFile,
		UINT    nIconIndex,
		_Out_opt_ HICON* phiconLarge,
		_Out_opt_ HICON* phiconSmall,
		UINT    nIconSize) override;


	// Inherited via IPersistFile
	// Inherited via IPersistFile
	HRESULT __stdcall GetClassID(CLSID* pClassID) override;
	HRESULT __stdcall IsDirty(void) override;
	HRESULT __stdcall Load(LPCOLESTR pszFileName, DWORD dwMode) override;
	HRESULT __stdcall Save(LPCOLESTR pszFileName, BOOL fRemember) override;
	HRESULT __stdcall SaveCompleted(LPCOLESTR pszFileName) override;
	HRESULT __stdcall GetCurFile(LPOLESTR* ppszFileName) override;


};

OBJECT_ENTRY_AUTO(__uuidof(IconHandler), CIconHandler)
