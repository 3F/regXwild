// sandbox - cpp/text/wildcards
// b0da341, 0100295,  - bitbucket.org/3F/flightsdc/commits/b0da3416478c55f184d65fde1eec8e06c3689d68
// based on {Iterator + Find}

/*
  * Copyright (c) 2013 Developed by reg <entry.reg@gmail.com>
  * 
  * Distributed under the Boost Software License, Version 1.0
  * (see accompanying file LICENSE or a copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#include "typedefs.hpp"

namespace reg { namespace sandbox { namespace cpp { namespace text { namespace wildcards {

    class AlgorithmExt
    {
    public:
        bool main(const tstring& text, const tstring& filter);

        AlgorithmExt(void)
        {
            _asserts();
        };
        ~AlgorithmExt(void){};

    protected:
        void _asserts();
    };

}}}}};