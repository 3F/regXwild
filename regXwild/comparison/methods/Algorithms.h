// sandbox - cpp/text/wildcards
// b0da341, 0100295,  - bitbucket.org/3F/flightsdc/commits/b0da3416478c55f184d65fde1eec8e06c3689d68

/*
  * Copyright (c) 2013 Developed by reg <entry.reg@gmail.com>
  * 
  * Distributed under the Boost Software License, Version 1.0
  * (see accompanying file LICENSE or a copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef WILDCARDS_CMP_METHODS_ALGORITHMS__H
#define WILDCARDS_CMP_METHODS_ALGORITHMS__H

#include "../../common/typedefs.h"

namespace net { namespace r_eg { namespace regXwild {

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

    protected:
        void _assertsMain();
    };

    typedef bool(Algorithms::*talgorithm)(const tstring&, const tstring&);


    class AlgorithmsTestCase
    {
    public:

        void assertsMainModeAny();
        void assertsMainModeSplit();
        void assertsMainModeOne();
        void analysis();
        void analysis(const string& caption, const tstring& data, const tstring& filter, int iterations, talgorithm method, Algorithms& alg);

    protected:
        Algorithms alg;
    };

}}}

#endif // WILDCARDS_CMP_METHODS_ALGORITHMS__H