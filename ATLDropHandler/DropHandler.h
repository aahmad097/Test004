// DropHandler.h : Declaration of the CDropHandler

#pragma once
#include "resource.h"       // main symbols



#include "ATLDropHandler_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CDropHandler

class ATL_NO_VTABLE CDropHandler :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDropHandler, &CLSID_DropHandler>,
	public IPersistFile,
	public IDropTarget
{
public:
	CDropHandler()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CDropHandler)
	COM_INTERFACE_ENTRY(IPersistFile)
	COM_INTERFACE_ENTRY(IDropTarget)
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

	// Inherited via IDropTarget
	HRESULT DragEnter(
		IDataObject* pDataObj,
		DWORD       grfKeyState,
		POINTL      pt,
		DWORD* pdwEffect
	) override;
	HRESULT DragLeave() override;
	HRESULT DragOver(
		DWORD  grfKeyState,
		POINTL pt,
		DWORD* pdwEffect
	) override;
	HRESULT Drop(
		IDataObject* pDataObj,
		DWORD       grfKeyState,
		POINTL      pt,
		DWORD* pdwEffect
	) override;

	// Inherited via IPersistFile
	HRESULT __stdcall GetClassID(CLSID* pClassID) override;
	HRESULT __stdcall IsDirty(void) override;
	HRESULT __stdcall Load(LPCOLESTR pszFileName, DWORD dwMode) override;
	HRESULT __stdcall Save(LPCOLESTR pszFileName, BOOL fRemember) override;
	HRESULT __stdcall SaveCompleted(LPCOLESTR pszFileName) override;
	HRESULT __stdcall GetCurFile(LPOLESTR* ppszFileName) override;


};

OBJECT_ENTRY_AUTO(__uuidof(DropHandler), CDropHandler)
