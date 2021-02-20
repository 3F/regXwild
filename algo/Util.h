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

#include "typedefs.h"

namespace net { namespace r_eg { namespace regXwild 
{
    using namespace std;
    using namespace net::r_eg::regXwild::rxwtypes;

    class Util
    {
    public:

        inline static tstring uppercase(tstring str) throw()
        {
            transform(str.begin(), str.end(), str.begin(), __toxupper);
            return str;
        };

        inline static tstring lowercase(tstring str) throw()
        {
            transform(str.begin(), str.end(), str.begin(), __toxlower);
            return str;
        };

        static tstring strReplace(const tstring& replace, const tstring& replacement, tstring str)
        {
            udiff_t pos = 0;
            while((pos = str.find(replace, pos)) != tstring::npos){
                str.replace(pos, replace.length(), replacement);
                pos += replacement.length();
            }
            return str;
        };

    protected:
        Util(void){};

    };

}}}