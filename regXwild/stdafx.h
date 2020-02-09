#pragma once

#include <tchar.h>
#include <string>

#if REGXWILD_COMPILE_PCH

    // Exclude rarely-used stuff from Windows headers
    #define WIN32_LEAN_AND_MEAN

    #include "targetver.h"

    // Only for DllMain:
    #include <windows.h>

    #include <algorithm>

#endif