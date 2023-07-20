// ThumbnailImageHandler.h : Declaration of the CThumbnailImageHandler

#pragma once
#include "resource.h"       // main symbols
#include "ATLThumbnailImageHandler_i.h"
#include <thumbcache.h>


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CThumbnailImageHandler

class ATL_NO_VTABLE CThumbnailImageHandler :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CThumbnailImageHandler, &CLSID_ThumbnailImageHandler>,
	public IThumbnailProvider,
	public IInitializeWithStream
{
public:
	CThumbnailImageHandler()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(106)


	BEGIN_COM_MAP(CThumbnailImageHandler)
		COM_INTERFACE_ENTRY(IThumbnailProvider)
		COM_INTERFACE_ENTRY(IInitializeWithStream)
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

	HRESULT GetThumbnail(
		UINT          cx,
		HBITMAP* phbmp,
		WTS_ALPHATYPE* pdwAlpha
	) override;

	HRESULT Initialize(
		IStream* pstream,
		DWORD   grfMode
	) override;

};

OBJECT_ENTRY_AUTO(__uuidof(ThumbnailImageHandler), CThumbnailImageHandler)
