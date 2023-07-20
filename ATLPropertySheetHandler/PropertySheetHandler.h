// PropertySheetHandler.h : Declaration of the CPropertySheetHandler

#pragma once
#include "resource.h"       // main symbols
#include "ATLPropertySheetHandler_i.h"
#include <shobjidl_core.h>


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CPropertySheetHandler

class ATL_NO_VTABLE CPropertySheetHandler :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPropertySheetHandler, &CLSID_PropertySheetHandler>,
	public IShellExtInit,
	public IShellPropSheetExt 
{
public:
	CPropertySheetHandler()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CPropertySheetHandler)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IShellPropSheetExt)
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

	// IShellExtInit

	HRESULT Initialize(
		PCIDLIST_ABSOLUTE pidlFolder,
		IDataObject* pdtobj,
		HKEY              hkeyProgID
	) override;

	// IShellPropSheetExt 

	HRESULT AddPages(
		LPFNSVADDPROPSHEETPAGE pfnAddPage,
		LPARAM                 lParam
	) override;

	HRESULT ReplacePage(
		EXPPS                  uPageID,
		LPFNSVADDPROPSHEETPAGE pfnReplaceWith,
		LPARAM                 lParam
	) override;


};

OBJECT_ENTRY_AUTO(__uuidof(PropertySheetHandler), CPropertySheetHandler)
