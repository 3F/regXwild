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

#include "stdafx.h"
#include "conf.h"
#include "typedefs.h"

namespace net { namespace r_eg { namespace regXwild { namespace core { namespace ESS
{
    using namespace net::r_eg::regXwild::rxwtypes;

    // TODO: consider upgrading to modern enum class
    namespace def
    {
        enum MetaOp: flagmeta_t
        {
            NONE    = 0,
            BOL     = 0x001,
            ANY     = 0x002,
            SPLIT   = 0x004,
            ONE     = 0x008,
            BEGIN   = 0x010,
            END     = 0x020,
            MORE    = 0x040,
            SINGLE  = 0x080,
            ANYSP   = 0x100,
            EOL     = 0x200,
        };

        enum MetaSymbols
        {
            MS_ANY      = _T('*'), // {0, ~}
            MS_SPLIT    = _T('|'), // str1 or str2 or ...
            MS_ONE      = _T('?'), // {0, 1}, ??? {0, 3}, ...
            MS_BEGIN    = _T('^'), // [str... or [str1... |[str2...
            MS_END      = _T('$'), // ...str] or ...str1]| ...str2]
            MS_MORE     = _T('+'), // {1, ~}, +++ {3, ~}, ...
            MS_SINGLE   = _T('#'), // {1}, ## {2}, ### {3}, ...
            MS_ANYSP    = _T('>'), // [^/]*str|[^/]*$ (legacy); [^{symbol}]*str|[^{symbol}]*$ for ('>' + {symbol})
        };
    }

}}}}}