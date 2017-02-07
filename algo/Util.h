#pragma once

/*
* The MIT License (MIT)
*
* Copyright (c) 2013, 2014, 2016, 2017  Denis Kuzmin <entry.reg@gmail.com>
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

#include "typedefs.h"

using namespace std;

namespace net { namespace r_eg { namespace regXwild { 

    class Util
    {
    public:

        inline static tstring uppercase(tstring str) throw()
        {
            transform(str.begin(), str.end(), str.begin(), towupper);
            return str;
        };

        inline static tstring lowercase(tstring str) throw()
        {
            transform(str.begin(), str.end(), str.begin(), towlower);
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