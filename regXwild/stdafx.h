/*
* The MIT License (MIT)
*
* Copyright (c) 2013-2021  Denis Kuzmin <x-3F@outlook.com> github/3F
* Copyright (c) regXwild contributors https://github.com/3F/regXwild
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#pragma once
#ifndef _RXW_STDAFX_
#define _RXW_STDAFX_

// L-42, helps to avoid std::length_error (or like) when Release <-> Debug
// This, however, will not resolve the case when user includes <string> (or iostream, etc) manually
// because the definitions may differ from the compiled module as compared to the end user environment.
#ifndef RXW_NO_NDEBUG_STRING

    #if _DEBUG
        #define __DEBUG_USR_D 1
        #undef _DEBUG
    #endif

    #ifndef NDEBUG
        #define _NDEBUG_USR_D 1
        #define NDEBUG 1
    #endif

    #include <string>

    #if _NDEBUG_USR_D
        #undef NDEBUG
        #undef _NDEBUG_USR_D
    #endif

    #if __DEBUG_USR_D
        #define _DEBUG 1
        #undef __DEBUG_USR_D
    #endif

#else

    #include <string>

#endif

#include <tchar.h>


// For transform() in internal _lowercase processing
#include <algorithm>

#if REGXWILD_COMPILE_PCH

    // Exclude rarely-used stuff from Windows headers
    #define WIN32_LEAN_AND_MEAN

    #include "targetver.h"

    // Only for DllMain
    #include <windows.h>

#endif

#endif // _RXW_STDAFX_