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