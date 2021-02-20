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

namespace net { namespace r_eg { namespace regXwild { namespace core { namespace EXT {

    class AlgorithmExt
    {
    public:

        // TODO: consider upgrading to modern enum class or enum struct
        enum MetaOperation
        {
            FLUSH   = 0,
            ANY     = 1,
            ANYSP   = 2,
            SPLIT   = 4,
            ONE     = 8,
            START   = 16,
            END     = 32,
            EOL     = 64,
        };

        // TODO: consider upgrading to modern enum class or enum struct
        enum MetaSymbols
        {
            MS_ANY      = _T('*'),
            MS_ANYSP    = _T('>'), //as [^/\\]+
            MS_SPLIT    = _T('|'),
            MS_ONE      = _T('?'),
            MS_START    = _T('^'),
            MS_END      = _T('$'),
        };

        bool main(const tstring& text, const tstring& filter, bool ignoreCase);

    protected:

        struct Mask
        {
            MetaOperation curr;
            MetaOperation prev;
            Mask(): curr(FLUSH), prev(FLUSH) { };
        };

        /**
         * to wildcards
         */
        struct Item
        {
            tstring curr;
            udiff_t pos;
            udiff_t left;
            udiff_t delta;
            Mask mask;
            tstring prev;
            Item(): pos(0), left(0), delta(0) { };
        };

        /**
         * to words
         */
        struct Words 
        {
            udiff_t found;
            udiff_t left;

#pragma warning(push)
#pragma warning(disable: 26495)
            Words(): left(0) { };
#pragma warning(pop)
        };

        /**
         * Working with an interval:
         *      _______
         * {word} ... {word}
         */
        udiff_t _handlerInterval(Item& item, Words& words, const tstring& text);

    private:

        inline tstring _lowercase(tstring str) throw()
        {
            transform(str.begin(), str.end(), str.begin(), __toxlower);
            return str;
        };
    };

}}}}}