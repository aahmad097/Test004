// dllmain.h : Declaration of module class.

class CATLThumbnailImageHandlerModule : public ATL::CAtlDllModuleT< CATLThumbnailImageHandlerModule >
{
public :
	DECLARE_LIBID(LIBID_ATLThumbnailImageHandlerLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_ATLTHUMBNAILIMAGEHANDLER, "{b9b449be-a0ff-4220-83cf-05cd4d02f6c9}")
};

extern class CATLThumbnailImageHandlerModule _AtlModule;
