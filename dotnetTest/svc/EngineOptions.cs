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

using System;

namespace dotnetTest.svc
{
    [Flags]
    internal enum EngineOptions: uint
    {
        F_NONE = 0,

        /// <summary>
        /// Ignore case sensitivity when matching.
        /// </summary>
        F_ICASE         = 0x001,

        /// <summary>
        /// Collect additional data for the MatchResult.
        /// </summary>
        F_MATCH_RESULT  = 0x002,

        /// <summary>
        /// Do not finish on first match.
        /// </summary>
        F_MATCH_ALL     = 0x004,

#if _RXW_FEATURE_MATCH_MAP
        /// <summary>
        /// Collect the positions of all occurrences 
        /// between each presented metasymbol.
        /// </summary>
        F_MATCH_MAP     = 0x008,
#endif

        /// <summary>
        /// Use MS_ANYSP as [^/]* (legacy).
        /// Otherwise as [^c]* where `c` is a symbol from the next presented symbol after MS_ANYSP.
        /// </summary>
        F_LEGACY_ANYSP  = 0x080,
    }
}