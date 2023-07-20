// dllmain.h : Declaration of module class.

class CATLInfotipHandlerModule : public ATL::CAtlDllModuleT< CATLInfotipHandlerModule >
{
public :
	DECLARE_LIBID(LIBID_ATLInfotipHandlerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLINFOTIPHANDLER, "{8d635abc-2db0-4659-a334-f014ea0c99aa}")
};

extern class CATLInfotipHandlerModule _AtlModule;
