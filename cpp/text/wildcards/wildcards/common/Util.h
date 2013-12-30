// sandbox - cpp/text/wildcards
// b0da341, 0100295,  - bitbucket.org/3F/flightsdc/commits/b0da3416478c55f184d65fde1eec8e06c3689d68

/*
  * Copyright (c) 2013 Developed by reg <entry.reg@gmail.com>
  * 
  * Distributed under the Boost Software License, Version 1.0
  * (see accompanying file LICENSE or a copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef WILDCARDS_COMMON_UTIL__H
#define WILDCARDS_COMMON_UTIL__H

#include "typedefs.h"

using namespace std;

namespace net { namespace r_eg { namespace text { namespace wildcards {

    class Util
    {
    public:

        inline static tstring uppercase(tstring str) throw()
        {
            transform(str.begin(), str.end(), str.begin(), towupper);
            return str;
        };

        inline static tstring lowercase(tstring str) throw()
        {
            transform(str.begin(), str.end(), str.begin(), towlower);
            return str;
        };

        static tstring strReplace(const tstring& replace, const tstring& replacement, tstring str)
        {
            size_t pos  = 0;
            while((pos  = str.find(replace, pos)) != tstring::npos){
                str.replace(pos, replace.length(), replacement);
                pos += replacement.length();
            }
            return str;
        };

    protected:
        Util(void){};

    };

}}}}

#endif // WILDCARDS_COMMON_UTIL__H