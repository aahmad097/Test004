// dllmain.h : Declaration of module class.

class CATLDataHandlerModule : public ATL::CAtlDllModuleT< CATLDataHandlerModule >
{
public :
	DECLARE_LIBID(LIBID_ATLDataHandlerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLDATAHANDLER, "{31646168-cc0b-4376-8ca1-a05a3e7de1a6}")
};

extern class CATLDataHandlerModule _AtlModule;
