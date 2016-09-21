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

#include "typedefs.h"

namespace net { namespace r_eg { namespace regXwild
{
    class Algorithms
    {
    public:

        /* candidates of main algorithm: */

        bool findGetlineFind(const tstring& text, const tstring& filter);
        bool findIteratorFind(const tstring& text, const tstring& filter);
        bool findRegexpCpp11m(const tstring& text, const tregex& filter);
        bool findRegexpCpp11s(const tstring& text, const tregex& filter);
        bool findFindFind(const tstring& text, const tstring& filter);
        bool findIteratorSubstr(const tstring& text, const tstring& filter);
        bool findIteratorIterator(const tstring& text, const tstring& filter);

        /* draft of main algorithm: */

        bool main(const tstring& text, const tstring& filter);
        void mainTest();

        /* final implementations: */

        bool finalEss(const tstring& data, const tstring& filter/*, bool ignoreCase*/);
        bool finalExt(const tstring& data, const tstring& filter);

    protected:

        void assertMainAny();
        void assertMainSplit();
        void assertMainOne();
    };

}}}