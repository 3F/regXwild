#ifndef PROPERTY_GRID_WRAPPER_SAMPLE_STDAFX__H
#define PROPERTY_GRID_WRAPPER_SAMPLE_STDAFX__H

#define WINVER          0x0501
#define _WIN32_WINNT    0x0501
#define _WIN32_IE       0x0400
#define _RICHEDIT_VER   0x0100
#define _CRT_SECURE_NO_WARNINGS

#include <atlbase.h>
#include <atlapp.h>
#include <atlframe.h>
#include <atlctrls.h>
#include <atldlgs.h>
#include <atlctrlw.h>
#include <atlwin.h>

#if (_ATL_VER < 0x0700)
#include <atlimpl.cpp>
#endif

#endif // PROPERTY_GRID_WRAPPER_SAMPLE_STDAFX__H
