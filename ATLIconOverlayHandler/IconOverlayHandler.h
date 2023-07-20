// IconOverlayHandler.h : Declaration of the CIconOverlayHandler

#pragma once
#include "resource.h"       // main symbols
#include "ATLIconOverlayHandler_i.h"
#include <shobjidl_core.h>


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CIconOverlayHandler

class ATL_NO_VTABLE CIconOverlayHandler :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CIconOverlayHandler, &CLSID_IconOverlayHandler>,
	public IShellIconOverlayIdentifier
{
public:
	CIconOverlayHandler()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(106)


	BEGIN_COM_MAP(CIconOverlayHandler)
		COM_INTERFACE_ENTRY(IShellIconOverlayIdentifier)
	END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

		HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	HRESULT GetOverlayInfo(
		LPWSTR pwszIconFile,
		int    cchMax,
		int* pIndex,
		DWORD* pdwFlags
	) override;

	HRESULT GetPriority(
		int* pPriority
	) override;

	HRESULT IsMemberOf(
		LPCWSTR pwszPath,
		DWORD   dwAttrib
	) override;
};

OBJECT_ENTRY_AUTO(__uuidof(IconOverlayHandler), CIconOverlayHandler)
