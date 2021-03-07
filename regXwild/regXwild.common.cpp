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

#include "stdafx.h"
#include "regXwild.h"
#include "regXwild.common.h"
#include "core\ESS\AlgorithmEss.h"
#include "core\EXT\AlgorithmExt.h"

namespace net { namespace r_eg { namespace regXwild { namespace common
{
    /// <summary>
    /// In a specified input, replaces first substring that match a specified pattern with a specified replacement string.
    /// </summary>
    /// <param name="input">
    /// The input string that will be modified if matched.
    /// Allocated memory must be enough for modified result.
    /// </param>
    /// <param name="pattern">Compatible pattern to match.</param>
    /// <param name="replacement">The replacement string.</param>
    /// <param name="options">A bitwise combination of the enumeration values that provide options for matching or modifications.</param>
    /// <returns>True if the match was successful.</returns>
    REGXWILD_API_L bool replace
    (
        rxwtypes::TCHAR* input,
        const rxwtypes::TCHAR* pattern,
        const rxwtypes::TCHAR* replacement,
        rxwtypes::flagcfg_t options
    )
    {
        return replaceOfs(input, pattern, replacement, 0, options);
    }

    /// <summary>
    /// In a specified input, replaces first substring that match a specified pattern with a specified replacement string.
    /// </summary>
    /// <param name="input">
    /// The input string that will be modified if matched.
    /// Allocated memory must be enough for modified result.
    /// </param>
    /// <param name="pattern">Compatible pattern to match.</param>
    /// <param name="replacement">The replacement string.</param>
    /// <param name="offset">The starting position to start matching.</param>
    /// <param name="options">A bitwise combination of the enumeration values that provide options for matching or modifications.</param>
    /// <returns>True if the match was successful.</returns>
    REGXWILD_API_L inline bool replaceOfs
    (
        rxwtypes::TCHAR* input,
        const rxwtypes::TCHAR* pattern,
        const rxwtypes::TCHAR* replacement,
        rxwtypes::udiff_t offset,
        rxwtypes::flagcfg_t options
    )
    {
        if(input == nullptr) return false;

        EssRxW rxw;
        rxwtypes::tstring _input = rxwtypes::tstring(input);

        if(!rxw.replace(_input, pattern, replacement, offset, static_cast<EssRxW::EngineOptions>(options))) {
            return false;
        }

        std::copy(_input.begin(), _input.end(), input);
        input[_input.length()] = '\0';

        return true;
    }

    /// <summary>
    /// Searches an input string for a substring that matches a pattern.
    /// </summary>
    /// <param name="input">The string to search for a match.</param>
    /// <param name="pattern">Compatible pattern to match.</param>
    /// <param name="options">A bitwise combination of the enumeration values that provide options for matching.</param>
    /// <param name="result">Information about the match.</param>
    /// <returns>True if the match was successful.</returns>
    REGXWILD_API_L bool match
    (
        const rxwtypes::TCHAR* input,
        const rxwtypes::TCHAR* pattern,
        rxwtypes::flagcfg_t options,
        EssRxW::MatchResult* result
    )
    {
        return matchOfs(input, pattern, 0, options, result);
    }

    /// <summary>
    /// Searches an input string for a substring that matches a pattern.
    /// </summary>
    /// <param name="input">The string to search for a match.</param>
    /// <param name="pattern">Compatible pattern to match.</param>
    /// <param name="offset">The starting position to start matching.</param>
    /// <param name="options">A bitwise combination of the enumeration values that provide options for matching.</param>
    /// <param name="result">Information about the match.</param>
    /// <returns>True if the match was successful.</returns>
    REGXWILD_API_L inline bool matchOfs
    (
        const rxwtypes::TCHAR* input,
        const rxwtypes::TCHAR* pattern,
        rxwtypes::udiff_t offset,
        rxwtypes::flagcfg_t options,
        EssRxW::MatchResult* result
    )
    {
        EssRxW rxw;
        return rxw.match(input, pattern, offset, static_cast<EssRxW::EngineOptions>(options), result);
    }

    /// <summary>
    /// In a specified input, replaces first substring that match a specified pattern with a specified replacement string.
    /// </summary>
    /// <param name="input">The string to search for a match.</param>
    /// <param name="pattern">Compatible pattern to match.</param>
    /// <param name="replacement">The replacement string.</param>
    /// <param name="to">Output string using pre-allocated memory if the match was successful, or null.</param>
    /// <param name="offset">The starting position to start matching.</param>
    /// <param name="options">A bitwise combination of the enumeration values that provide options for matching or modifications.</param>
    /// <returns>True if the match was successful.</returns>
    REGXWILD_API_L bool replaceTo
    (
        const rxwtypes::TCHAR* input,
        const rxwtypes::TCHAR* pattern,
        const rxwtypes::TCHAR* replacement,
        rxwtypes::TCHAR* to,
        rxwtypes::udiff_t offset,
        rxwtypes::flagcfg_t options
    )
    {
        if(input == nullptr) return false;

        EssRxW rxw;
        rxwtypes::tstring _input = rxwtypes::tstring(input);

        if(!rxw.replace(_input, pattern, replacement, offset, static_cast<EssRxW::EngineOptions>(options))) {
            return false;
        }

        if(to == nullptr) return true;

        std::copy(_input.begin(), _input.end(), to);
        to[_input.length()] = '\0';

        return true;
    }

    /**
    * To search substring in data with filter by the rules of ESS algorithm.
    * [char* / wchar_t*]
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @param ignoreCase To check data with no case sensitive rules if true.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API_L bool searchEssC(const rxwtypes::TCHAR* data, const rxwtypes::TCHAR* filter, bool ignoreCase)
    {
        return searchEss(data, filter, ignoreCase);
    }

    /**
    * To search substring in data with filter by the rules of ESS algorithm.
    * [string& / wstring&]
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @param ignoreCase To check data with no case sensitive rules if true.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API_L bool searchEss(const rxwtypes::tstring& data, const rxwtypes::tstring& filter, bool ignoreCase)
    {
        core::ESS::AlgorithmEss alg;

        return alg.search(data, filter, ignoreCase);
    }

    /**
    * To search substring in data with filter by the rules of ESS algorithm.
    * [string* / wstring*]
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @param ignoreCase To check data with no case sensitive rules if true.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API_L bool searchEssPtr(const rxwtypes::tstring* data, const rxwtypes::tstring* filter, bool ignoreCase)
    {
        return searchEss(*data, *filter, ignoreCase);
    }

    /**
    * To search substring in data with filter by the rules of EXT algorithm.
    * [char* / wchar_t*]
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @param ignoreCase To check data with no case sensitive rules if true.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API_L bool searchExtC(const rxwtypes::TCHAR* data, const rxwtypes::TCHAR* filter, bool ignoreCase)
    {
        return searchExt(data, filter, ignoreCase);
    }

    /**
    * To search substring in data with filter by the rules of EXT algorithm.
    * [string& / wstring&]
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @param ignoreCase To check data with no case sensitive rules if true.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API_L bool searchExt(const rxwtypes::tstring& data, const rxwtypes::tstring& filter, bool ignoreCase)
    {
        core::EXT::AlgorithmExt alg;

        return alg.main(data, filter, ignoreCase);
    }

    /**
    * To search substring in data with filter by the rules of EXT algorithm.
    * [string* / wstring*]
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @param ignoreCase To check data with no case sensitive rules if true.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API_L bool searchExtPtr(const rxwtypes::tstring* data, const rxwtypes::tstring* filter, bool ignoreCase)
    {
        return searchExt(*data, *filter, ignoreCase);
    }

    /**
    * obsolete due to RXWVersion
    * @return Returns current RXWVersion.product version of regXwild library.
    */
    REGXWILD_API_L const rxwtypes::TCHAR* versionString()
    {
        return /*vsSBE*/_T("1.4.0");
    }

}}}}