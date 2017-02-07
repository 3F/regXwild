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

namespace net { namespace r_eg { namespace regXwild { namespace core { namespace ESS {

    class AlgorithmEss
    {
    public:

        enum MetaOperation
        {
            NONE    = 0x000,
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
            MS_ONE      = _T('?'), // {0, 1}, ??? - {0, 3}, ...
            MS_BEGIN    = _T('^'), // [str... or [str1... |[str2...
            MS_END      = _T('$'), // ...str] or ...str1]| ...str2]
            MS_MORE     = _T('+'), // {1, ~}
            MS_SINGLE   = _T('#'), // {1}
            MS_ANYSP    = _T('>'), // as [^/]*  //TODO: >\>/ i.e. '>' + {symbol}
        };

        /**
         * default symbol for special case
         * regexp equivalent search is a [^/]* (EXT version: [^/\\]+)
         */
        const static TCHAR ANYSP_CMP_DEFAULT = _T('/');

        /** entry for match cases */
        bool search(const tstring& text, const tstring& filter, bool ignoreCase = true);

    protected:

        struct Mask
        {
            MetaOperation curr;
            MetaOperation prev;
            Mask(): curr(BOL), prev(BOL){};
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
            unsigned short int overlay;

            /** enough of this.. */
            tstring prev;

            void reset()
            {
                pos = left = delta = overlay = 0;
                mask.curr = mask.prev = BOL;
                curr.clear();
                prev.clear();
            };
            Item(): pos(0), left(0), delta(0), overlay(0){};
        } item;

        /**
         * to words
         */
        struct Words
        {
            udiff_t found;
            udiff_t left;

            void reset()
            {
                found   = tstring::npos;
                left    = 0;
            };
            Words(): left(0){};
        } words;

        /**
         * Working with an interval:
         *      _______
         * {word} ... {word}
         */
        udiff_t interval();

        /** rewind to next SPLIT-block */
        bool rewindToNextBlock(tstring::const_iterator& it, bool delta = true);

    private:

        /** work with the target sequence (subject) */
        tstring _text;

        /** work with the pattern */
        tstring _filter;

        inline tstring _lowercase(tstring str) throw()
        {
            transform(str.begin(), str.end(), str.begin(), towlower);
            return str;
        };
    };

}}}}}