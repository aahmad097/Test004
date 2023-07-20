// InfotipHandler.h : Declaration of the CInfotipHandler

#pragma once
#include "resource.h"       // main symbols
#include "ATLInfotipHandler_i.h"
#include "shlobj_core.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CInfotipHandler

class ATL_NO_VTABLE CInfotipHandler :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CInfotipHandler, &CLSID_InfotipHandler>,
	public IQueryInfo
{
public:
	CInfotipHandler()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)

BEGIN_COM_MAP(CInfotipHandler)
	COM_INTERFACE_ENTRY(IQueryInfo)
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

	HRESULT GetInfoTip(DWORD dwFlags, _Outptr_ PWSTR* ppwszTip) override;
	HRESULT GetInfoFlags(_Out_ DWORD* pdwFlags) override;

};

OBJECT_ENTRY_AUTO(__uuidof(InfotipHandler), CInfotipHandler)
