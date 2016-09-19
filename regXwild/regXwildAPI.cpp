#include "stdafx.h"
#include "regXwild.h"
#include "regXwildAPI.h"
#include "core\ESS\AlgorithmEss.h"
#include "core\EXT\AlgorithmExt.h"

namespace net { namespace r_eg { namespace regXwild 
{

    /**
    * To search substring in data with filter by the rules of ESS algorithm.
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @param ignoreCase To check data with no case sensitive rules.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API bool searchEss(const tstring& data, const tstring& filter, bool ignoreCase)
    {
        core::ESS::AlgorithmEss alg;

        return alg.search(data, filter, ignoreCase);
    }
    
    /**
    * To search substring in data with filter by the rules of EXT algorithm.
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API bool searchExt(const tstring& data, const tstring& filter)
    {
        core::EXT::AlgorithmExt alg;

        return alg.main(data, filter);
    }

}}}