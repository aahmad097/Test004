// dllmain.h : Declaration of module class.

class CATLIconOverlayHandlerModule : public ATL::CAtlDllModuleT< CATLIconOverlayHandlerModule >
{
public :
	DECLARE_LIBID(LIBID_ATLIconOverlayHandlerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLICONOVERLAYHANDLER, "{65e96ab0-91ba-4001-b469-c01fcf83f7cc}")
};

extern class CATLIconOverlayHandlerModule _AtlModule;
