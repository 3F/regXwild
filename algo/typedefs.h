#pragma once

/*
* The MIT License (MIT)
*
* Copyright (c) 2013, 2014, 2016  Denis Kuzmin <entry.reg@gmail.com>
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

#include "stdafx.h"

using namespace std;

namespace net { namespace r_eg { namespace regXwild { 

    #ifdef UNICODE

        typedef wstring tstring;
        typedef wstringstream tstringStream;

        //<tchar.h>
        //typedef wchar_t TCHAR;
        //#define _T(x)  L ## x

    #else

        typedef string tstring;
        typedef stringstream tstringStream;

        //<tchar.h>
        //typedef char TCHAR;
        //#define _T(x)  ## x

    #endif

    typedef vector<tstring> tstringList;
    typedef basic_regex<TCHAR> tregex;

#define TRACE(str){ std::cout << str; }

}}}