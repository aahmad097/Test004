// dllmain.h : Declaration of module class.

class CATLDropHandlerModule : public ATL::CAtlDllModuleT< CATLDropHandlerModule >
{
public :
	DECLARE_LIBID(LIBID_ATLDropHandlerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLDROPHANDLER, "{ffbdfc90-2fb9-43b7-afed-6bae7b41e8c3}")
};

extern class CATLDropHandlerModule _AtlModule;
