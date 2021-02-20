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
#ifndef _RXW_TYPEDEFS_
#define _RXW_TYPEDEFS_

#include "stdafx.h"

namespace net { namespace r_eg { namespace regXwild { namespace rxwtypes
{

#ifdef UNICODE

    typedef std::wstring tstring;
    #define __toxlower towlower

    typedef wchar_t TCHAR;
    #ifndef _T
        #define _T(x)  L ## x
    #endif // !_T

#else

    typedef std::string tstring;
    #define __toxlower tolower

    typedef char TCHAR;
    #ifndef _T
        #define _T(x)  x
    #endif // !_T

#endif

    typedef size_t udiff_t;
    typedef ptrdiff_t diff_t;

    typedef unsigned int flagcfg_t;

}}}}

#endif // _RXW_TYPEDEFS_