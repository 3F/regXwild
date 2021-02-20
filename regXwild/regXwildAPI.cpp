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
#include "regXwildAPI.h"
#include "core\ESS\AlgorithmEss.h"
#include "core\EXT\AlgorithmExt.h"

namespace net { namespace r_eg { namespace regXwild 
{

    /**
    * To search substring in data with filter by the rules of ESS algorithm.
    * [char* / wchar_t*]
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @param ignoreCase To check data with no case sensitive rules if true.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API bool searchEssC(const TCHAR* data, const TCHAR* filter, bool ignoreCase)
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
    REGXWILD_API bool searchEss(const tstring& data, const tstring& filter, bool ignoreCase)
    {
        core::ESS::AlgorithmEss alg;

        return alg.search(data, filter, ignoreCase);
    }

    /**
    * To search substring in data with filter by the rules of EXT algorithm.
    * [char* / wchar_t*]
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @param ignoreCase To check data with no case sensitive rules if true.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API bool searchExtC(const TCHAR* data, const TCHAR* filter, bool ignoreCase)
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
    REGXWILD_API bool searchExt(const tstring& data, const tstring& filter, bool ignoreCase)
    {
        core::EXT::AlgorithmExt alg;

        return alg.main(data, filter, ignoreCase);
    }

    /**
    * obsolete due to RXWVersion
    * @return Returns current RXWVersion.product version of regXwild library.
    */
    REGXWILD_API const TCHAR* versionString()
    {
        return /*vsSBE*/_T("1.3.0");
    }

}}}