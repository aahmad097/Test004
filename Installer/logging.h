#ifndef LOGGING_H
#define LOGGING_H
#endif

#include <windows.h>

#define LVL_INFO 0
#define LVL_WARNING 1
#define LVL_FATAL 2

namespace logging {

	void log(_In_ BYTE lvl, _In_ CONST WCHAR* str);

}