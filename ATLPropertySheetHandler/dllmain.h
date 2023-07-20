// dllmain.h : Declaration of module class.

class CATLPropertySheetHandlerModule : public ATL::CAtlDllModuleT< CATLPropertySheetHandlerModule >
{
public :
	DECLARE_LIBID(LIBID_ATLPropertySheetHandlerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLPROPERTYSHEETHANDLER, "{96cb669e-8ca0-4038-ab9e-62df19f06171}")
};

extern class CATLPropertySheetHandlerModule _AtlModule;
