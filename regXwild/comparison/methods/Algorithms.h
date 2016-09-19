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

#ifndef WILDCARDS_CMP_METHODS_ALGORITHMS__H
#define WILDCARDS_CMP_METHODS_ALGORITHMS__H

#include "../../common/typedefs.h"

namespace net { namespace r_eg { namespace regXwild {

    /**
     * comparison of implementations
     */
    class Algorithms
    {
    public:
        bool findGetlineFind(const tstring& text, const tstring& filter);
        bool findIteratorFind(const tstring& text, const tstring& filter);
        bool findRegexpCpp11m(const tstring& text, const tstring& filter);
        bool findRegexpCpp11s(const tstring& text, const tstring& filter);
        bool findFindFind(const tstring& text, const tstring& filter);
        bool findIteratorSubstr(const tstring& text, const tstring& filter);
        bool findIteratorIterator(const tstring& text, const tstring& filter);

        bool main(const tstring& text, const tstring& filter);

    protected:
        void _assertsMain();
    };

    typedef bool(Algorithms::*talgorithm)(const tstring&, const tstring&);


    class AlgorithmsTestCase
    {
    public:

        void assertsMainModeAny();
        void assertsMainModeSplit();
        void assertsMainModeOne();
        void analysis();
        void analysis(const string& caption, const tstring& data, const tstring& filter, int iterations, talgorithm method, Algorithms& alg);

    protected:
        Algorithms alg;
    };

}}}

#endif // WILDCARDS_CMP_METHODS_ALGORITHMS__H