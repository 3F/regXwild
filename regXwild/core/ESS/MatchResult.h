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

    struct MatchResult
    {
        static const udiff_t npos = static_cast<udiff_t>(-1);

        /// <summary>
        /// Position of the first occurrence or MatchResult::npos.
        /// It also will be MatchResult::npos if not EngineOptions::F_MATCH_RESULT.
        /// </summary>
        udiff_t start;

        /// <summary>
        /// Position of the last occurrence.
        /// Valid only if `MatchResult::start` != MatchResult::npos.
        /// </summary>
        udiff_t end;

#if _RXW_FEATURE_MATCH_MAP
        /// <summary>
        /// The positions of all occurrences between each presented metasymbol.
        /// Use EngineOptions::F_MATCH_MAP to activate it.
        /// </summary>
        matchmap_t map;
#endif

#pragma warning(push)
#pragma warning(disable: 26495)
        //NOTE: C26495; valid for `start`
        MatchResult(): start(npos)
        {

        };
#pragma warning(pop)
    };

}}}}}