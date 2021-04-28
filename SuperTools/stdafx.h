// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//  are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		0x0601
#define _WIN32_WINNT	0x0601
#define _WIN32_IE	0x0700
#define _RICHEDIT_VER	0x0500

#define _CONVERSION_DONT_USE_THREAD_LOCALE

#include <WindowsX.h>

#include <atlbase.h>
#include <atlapp.h>

extern CAppModule _Module;

#include <Windows.h>
#include <atlwin.h>
#include <atlframe.h>
#include <atlstr.h>
#include <vector>

using namespace std;

#if defined _M_IX86
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif

#include "Utils.h"
#include "FsDisable.h"
#include "resource.h"
#include "st_error.h"

#include "MsgCenter.h"
