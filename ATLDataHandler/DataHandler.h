// DataHandler.h : Declaration of the CDataHandler

#pragma once
#include "resource.h"       // main symbols



#include "ATLDataHandler_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CDataHandler

class ATL_NO_VTABLE CDataHandler :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDataHandler, &CLSID_DataHandler>,
	public IPersistFile,
	public IDataObject
{
public:
	CDataHandler()
	{
	}

	DECLARE_REGISTRY_RESOURCEID(106)


	BEGIN_COM_MAP(CDataHandler)
		COM_INTERFACE_ENTRY(IPersistFile)
		COM_INTERFACE_ENTRY(IDataObject)
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

	// Inherited via IDataObject
	HRESULT STDMETHODCALLTYPE GetData(
		_In_  FORMATETC* pformatetcIn,
		_Out_  STGMEDIUM* pmedium) override;

	HRESULT STDMETHODCALLTYPE GetDataHere(
		_In_  FORMATETC* pformatetc,
		_Inout_  STGMEDIUM* pmedium) override;

	HRESULT STDMETHODCALLTYPE QueryGetData(
		__RPC__in_opt FORMATETC* pformatetc) override;

	HRESULT STDMETHODCALLTYPE GetCanonicalFormatEtc(
		__RPC__in_opt FORMATETC* pformatectIn,
		__RPC__out FORMATETC* pformatetcOut) override;

	HRESULT STDMETHODCALLTYPE SetData(
		_In_  FORMATETC* pformatetc,
		_In_  STGMEDIUM* pmedium,
		BOOL fRelease) override;

	HRESULT STDMETHODCALLTYPE EnumFormatEtc(
		DWORD dwDirection,
		__RPC__deref_out_opt IEnumFORMATETC** ppenumFormatEtc) override;

	HRESULT STDMETHODCALLTYPE DAdvise(
		__RPC__in FORMATETC* pformatetc,
		DWORD advf,
		__RPC__in_opt IAdviseSink* pAdvSink,
		__RPC__out DWORD* pdwConnection) override;

	HRESULT STDMETHODCALLTYPE DUnadvise(
		DWORD dwConnection) override;

	HRESULT STDMETHODCALLTYPE EnumDAdvise(
		__RPC__deref_out_opt IEnumSTATDATA** ppenumAdvise) override;

	// Inherited via IPersistFile
	HRESULT __stdcall GetClassID(CLSID* pClassID) override;
	HRESULT __stdcall IsDirty(void) override;
	HRESULT __stdcall Load(LPCOLESTR pszFileName, DWORD dwMode) override;
	HRESULT __stdcall Save(LPCOLESTR pszFileName, BOOL fRemember) override;
	HRESULT __stdcall SaveCompleted(LPCOLESTR pszFileName) override;
	HRESULT __stdcall GetCurFile(LPOLESTR* ppszFileName) override;

};

OBJECT_ENTRY_AUTO(__uuidof(DataHandler), CDataHandler)
