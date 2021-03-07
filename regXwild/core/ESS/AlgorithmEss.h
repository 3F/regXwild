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
#include "def.h"
#include "EngineOptions.h"
#include "MatchResult.h"
#include "LoopAct.h"

namespace net { namespace r_eg { namespace regXwild { namespace core { namespace ESS
{
    using namespace net::r_eg::regXwild::rxwtypes;

    class AlgorithmEss
    {
    public:

        /// <summary>
        /// In a specified input, replaces first substring that match a specified pattern with a specified replacement string.
        /// </summary>
        /// <param name="input">The input string that will be modified if matched.</param>
        /// <param name="pattern">Compatible pattern to match.</param>
        /// <param name="replacement">The replacement string.</param>
        /// <param name="options">A bitwise combination of the enumeration values that provide options for matching or modifications.</param>
        /// <returns>True if the match was successful.</returns>
        REGXWILD_API bool replace(tstring& input, const tstring& pattern, const tstring& replacement, const EngineOptions& options = EngineOptions::F_NONE);

        /// <summary>
        /// In a specified input, replaces first substring that match a specified pattern with a specified replacement string.
        /// </summary>
        /// <param name="input">The input string that will be modified if matched.</param>
        /// <param name="pattern">Compatible pattern to match.</param>
        /// <param name="replacement">The replacement string.</param>
        /// <param name="offset">The starting position to start matching.</param>
        /// <param name="options">A bitwise combination of the enumeration values that provide options for matching or modifications.</param>
        /// <returns>True if the match was successful.</returns>
        REGXWILD_API bool replace(tstring& input, const tstring& pattern, const tstring& replacement, udiff_t offset, const EngineOptions& options = EngineOptions::F_NONE);

        /// <summary>
        /// [Obsolete] This method is obsolete and can be removed in future major versions. Please use `match()`.
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
        /// <param name="result">Information about the match.</param>
        /// <returns>True if the match was successful.</returns>
        REGXWILD_API bool match(const tstring& input, const tstring& pattern, const EngineOptions& options = EngineOptions::F_NONE, MatchResult* result = nullptr);

        /// <summary>
        /// Searches an input string for a substring that matches a pattern.
        /// </summary>
        /// <param name="input">The string to search for a match.</param>
        /// <param name="pattern">Compatible pattern to match.</param>
        /// <param name="offset">The starting position to start matching.</param>
        /// <param name="options">A bitwise combination of the enumeration values that provide options for matching.</param>
        /// <param name="result">Information about the match.</param>
        /// <returns>True if the match was successful.</returns>
        REGXWILD_API bool match(const tstring& input, const tstring& pattern, udiff_t offset, const EngineOptions& options = EngineOptions::F_NONE, MatchResult* result = nullptr);

#if _CPP11_OR_ABOVE
        using EngineOptions = core::ESS::EngineOptions;
        using MatchResult = core::ESS::MatchResult;
#else
        typedef core::ESS::EngineOptions EngineOptions;
        typedef core::ESS::MatchResult MatchResult;
#endif

    protected:

        /**
         * (legacy) symbol for special case
         * regex equivalent is [^/]*str|[^/]*$ (EXT version: [^/\\]+)
         */
        const static TCHAR ANYSP_CMP_DEFAULT = _T('/');

        struct Mask
        {
            def::MetaOp curr;
            def::MetaOp prev;
#pragma warning(push)
#pragma warning(disable: 26812) // enum^
            Mask()
                : curr(def::MetaOp::BOL), prev(def::MetaOp::BOL)
            {

            }
#pragma warning(pop)
        };

        struct ItStr
        {
            tstring::const_iterator begin;
            tstring::const_iterator c;
            tstring::const_iterator end;

            void reset() { c = begin; }

            ItStr(const tstring& str)
                : begin(str.cbegin()), end(str.cend())
            {
                reset();
            }
        };

        struct Item
        {
            tstring curr;
            udiff_t pos;
            udiff_t left;
            udiff_t delta;
            Mask mask;
            unsigned short int overlay;

            unsigned short int mixpos; // ++??
            def::MetaOp mixms;

            tstring prev;
            def::MetaOp bems;

#if _RXW_FEATURE_MATCH_RESULT
            bool shiftms;
#endif
            TCHAR anysp;
            MatchResult* mres;
            const EngineOptions* flags;

            ItStr it;
            const tstring& input;

#pragma warning(push)
#pragma warning(disable: 26495)
            //NOTE: C26495; valid for `mixms` (the first use is possible only after `mixpos` that will init `mixms`)
            //              `curr`, `prev`
            Item(const tstring& input)
                : input(input), pos(0), left(0), delta(0), overlay(0), mixpos(0), 
                  anysp(NULL), bems(def::NONE), it(input)
#if _RXW_FEATURE_MATCH_RESULT
                , shiftms(false)
#endif
            {

            }
#pragma warning(pop)

        };

        struct FWord
        {
            udiff_t found;
            udiff_t left;
            udiff_t roff;

            udiff_t len;
            const tstring& text;

            //initial offset
            const udiff_t& offset;

            bool rewind(udiff_t opt = 0)
            {
                left = offset + opt;

                if(left == _rewound) return false;
                _rewound = left;
                return true;
            }

#pragma warning(push)
#pragma warning(disable: 26495)
            //NOTE: C26495; valid for `roff`
            FWord(const tstring& input, const udiff_t& offset)
                : found(tstring::npos), offset(offset), left(offset), text(input), len(input.length())
            {

            }
#pragma warning(pop)

        private:
            // to detect an unknown looping
            udiff_t _rewound;
        };

        /** {word}<- ... ->{word} */
        udiff_t parseInterval(Item& item, FWord& word, const EngineOptions& options);

        /** jump to the next SPLIT block */
        bool jumpRight(Item& item, FWord& word, bool delta = true);

        LoopAct loop(Item& item, FWord& word, const EngineOptions& options);

    private:

        inline bool cmp(const tstring& a, const tstring& b, size_t pos = 0, size_t len = tstring::npos) const;
        inline TCHAR getSPChar(const Item& item, const EngineOptions& options) const;

        bool _replace
        (
            tstring& input, 
            const tstring& pattern, 
            const tstring& replacement, 
            udiff_t offset, 
            const EngineOptions& options, 
            MatchResult& result
        );

        /* EngineOptions::F_MATCH_RESULT -> */

        inline bool set(MatchResult* result, const EngineOptions& options, udiff_t start, udiff_t end);
        inline void reset(MatchResult* result);
        inline LoopAct unsetMatch(Item& item);
        inline void setStart(Item& item, udiff_t start);
        inline void shiftStart(udiff_t start, Item& item);
        LoopAct setEnd(Item& item, const FWord& word);
        inline bool isOnResult(const MatchResult* result, const EngineOptions& options);
        inline bool isEqPrev(const tstring& input, const Item& item, udiff_t len);
        inline bool convertToBool(LoopAct act);

        /* <- EngineOptions::F_MATCH_RESULT */

        inline tstring _lowercase(tstring str) throw()
        {
            transform(str.begin(), str.end(), str.begin(), __toxlower);
            return str;
        };
    };

}}}}}