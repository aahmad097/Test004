#ifndef LOGGING_H
#define LOGGING_H
#endif

#include "logging.h"

#include <stdio.h>
#include <wchar.h>
#include <windows.h>

/*
#define LVL_INFO 0
#define LVL_WARNING 1
#define LVL_FATAL 2
*/


namespace logging {

	

	void log(_In_ BYTE lvl, _In_ CONST WCHAR* str) {

		CONST WCHAR* s = { 0 };
		
		switch (lvl) {

		case LVL_INFO :
			s = L"+";
			break;
		case LVL_WARNING :
			s = L"!";
			break;
		case LVL_FATAL :
			s = L"-";
			break;

		}

		wprintf(L"[%s] %s\n", s, str);
		if (lvl == LVL_FATAL) {

			TerminateProcess(GetCurrentProcess(), 0x1);

		}

	}

}