// sandbox - cpp/text/wildcards
// b0da341, 0100295,  - bitbucket.org/3F/flightsdc/commits/b0da3416478c55f184d65fde1eec8e06c3689d68

/*
  * Copyright (c) 2013 Developed by reg <entry.reg@gmail.com>
  * 
  * Distributed under the Boost Software License, Version 1.0
  * (see accompanying file LICENSE or a copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#pragma once
#include <time.h>

namespace reg { namespace sandbox { namespace cpp { namespace text { namespace wildcards {

    class Meter
    {
    public:
        void start()
        {
            _started = clock();
        }

        int delta()
        {
            return clock() - _started;
        }

        Meter(void){};
        ~Meter(void){};
    
    private:
        int _started;
    };

}}}}};