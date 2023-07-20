// dllmain.h : Declaration of module class.

class CATLCopyHookHandlerModule : public ATL::CAtlDllModuleT< CATLCopyHookHandlerModule >
{
public :
	DECLARE_LIBID(LIBID_ATLCopyHookHandlerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLCOPYHOOKHANDLER, "{0c7a6dea-1288-4bc2-b8bd-00d2447556a7}")
};

extern class CATLCopyHookHandlerModule _AtlModule;
