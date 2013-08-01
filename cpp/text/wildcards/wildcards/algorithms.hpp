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

    /**
     * comparison of implementations
     */
    class Algorithms
    {
    public:
        bool findGetlineFind(const tstring& text, const tstring& filter);
        bool findIteratorFind(const tstring& text, const tstring& filter);
        bool findRegexpCpp11m(const tstring& text, const tstring& filter);
        bool findRegexpCpp11s(const tstring& text, const tstring& filter);
        bool findFindFind(const tstring& text, const tstring& filter);
        bool findIteratorSubstr(const tstring& text, const tstring& filter);
        bool findIteratorIterator(const tstring& text, const tstring& filter);

        bool main(const tstring& text, const tstring& filter);

        Algorithms(void)
        {
            _assertsMain();
        };

        ~Algorithms(void){};

    protected:
        void _assertsMain();
    };

    typedef bool(Algorithms::*talgorithm)(const tstring&, const tstring&);

}}}}};