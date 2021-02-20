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

namespace net { namespace r_eg { namespace regXwild { namespace core { namespace ESS {

    using namespace net::r_eg::regXwild::rxwtypes;

    class AlgorithmEss
    {
    public:

        RXW_ENUM_CLASS FlagsRxW: flagcfg_t
        {
            F_NONE = 0,

            /// <summary>
            /// Ignore case sensitivity when matching.
            /// </summary>
            F_ICASE = 0x001,
        };

        // TODO: consider upgrading to modern enum class or enum struct
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

        // TODO: consider upgrading to modern enum class or enum struct
        enum MetaSymbols
        {
            MS_ANY      = _T('*'), // {0, ~}
            MS_SPLIT    = _T('|'), // str1 or str2 or ...
            MS_ONE      = _T('?'), // {0, 1}, ??? {0, 3}, ...
            MS_BEGIN    = _T('^'), // [str... or [str1... |[str2...
            MS_END      = _T('$'), // ...str] or ...str1]| ...str2]
            MS_MORE     = _T('+'), // {1, ~}, +++ {3, ~}, ...
            MS_SINGLE   = _T('#'), // {1}, ## {2}, ### {3}, ...
            MS_ANYSP    = _T('>'), // as [^/]*  //TODO: >\>/ i.e. '>' + {symbol}
        };

        /**
         * default symbol for special case
         * regexp equivalent search is a [^/]* (EXT version: [^/\\]+)
         */
        const static TCHAR ANYSP_CMP_DEFAULT = _T('/');

        /// <summary>
        /// Basic search for occurrence using filter.
        /// </summary>
        /// <returns>True if found.</returns>
        REGXWILD_API bool search(const tstring& text, const tstring& filter, bool ignoreCase = true);

        /// <summary>
        /// Searches an input string for a substring that matches a pattern.
        /// </summary>
        /// <param name="input">The string to search for a match.</param>
        /// <param name="pattern">Compatible pattern to match.</param>
        /// <param name="options">A bitwise combination of the enumeration values that provide options for matching.</param>
        /// <returns>True if the match was successful.</returns>
        REGXWILD_API bool match(const tstring& input, const tstring& pattern, const FlagsRxW& options = FlagsRxW::F_NONE);

    protected:

        struct Mask
        {
            MetaOperation curr;
            MetaOperation prev;
            Mask(): curr(BOL), prev(BOL) { };
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

            unsigned short int mixpos; // ++??
            MetaOperation mixms;

            /** enough of this.. */
            tstring prev;

#pragma warning(push)
#pragma warning(disable: 26495)
            //NOTE: C26495; valid for `mixms` (the first use is possible only after `mixpos` that will init `mixms`)
            //              `curr`, `prev`
            Item(): pos(0), left(0), delta(0), overlay(0), mixpos(0)
            {

            };
#pragma warning(pop)

        };

        struct Words
        {
            udiff_t found;
            udiff_t left;

            Words(): found(tstring::npos), left(0) { };
        };

        /**
         * Working with an interval:
         *      _______
         * {word} ... {word}
         */
        udiff_t interval(const Item& item, const Words& words, const tstring& _text);

        /** rewind to next SPLIT-block */
        bool rewindToNextBlock(Item& item, Words& words, const tstring& _filter, tstring::const_iterator& it, bool delta = true);

    private:

#if RXW_CPP11_ENUM_CLASS

        friend flagcfg_t operator& (FlagsRxW l, FlagsRxW r)
        {
            return static_cast<flagcfg_t>(l) & static_cast<flagcfg_t>(r);
        }

        friend FlagsRxW operator| (FlagsRxW l, FlagsRxW r)
        {
            return static_cast<FlagsRxW>(static_cast<flagcfg_t>(l) | static_cast<flagcfg_t>(r));
        }

#endif

        inline tstring _lowercase(tstring str) throw()
        {
            transform(str.begin(), str.end(), str.begin(), __toxlower);
            return str;
        };
    };

}}}}}