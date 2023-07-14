// dllmain.h : Declaration of module class.

class CATLIconHandlerModule : public ATL::CAtlDllModuleT< CATLIconHandlerModule >
{
public :
	DECLARE_LIBID(LIBID_ATLIconHandlerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLICONHANDLER, "{faa80735-1498-417f-ab1e-7fe0f5b412b3}")
};

extern class CATLIconHandlerModule _AtlModule;
