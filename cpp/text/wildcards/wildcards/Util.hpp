// sandbox - cpp/text/wildcards
// b0da341, 0100295,  - bitbucket.org/3F/flightsdc/commits/b0da3416478c55f184d65fde1eec8e06c3689d68

/*
  * Copyright (c) 2013 Developed by reg <entry.reg@gmail.com>
  * 
  * Distributed under the Boost Software License, Version 1.0
  * (see accompanying file LICENSE or a copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#include "typedefs.hpp"

namespace reg { namespace sandbox { namespace cpp { namespace text { namespace wildcards {

    class Util
    {
    public:
        inline static const tstring uppercase(tstring p_str) throw()
        {
	        transform(p_str.begin(), p_str.end(), p_str.begin(), towupper);
	        return p_str;
        };

        template<class type>
        inline static type strReplace(const type& replace, const type& replacement, const type& str)
        {
            type _str   = str;
            size_t pos  = 0;
            while((pos  = _str.find(replace, pos)) != type::npos){
                _str.replace(pos, replace.length(), replacement);
                pos += replacement.length();
            }
            return _str;
        };

    private:
        Util(void){};
        ~Util(void){};
    };

}}}}};