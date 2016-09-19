// sandbox - cpp/text/wildcards
// b0da341, 0100295,  - bitbucket.org/3F/flightsdc/commits/b0da3416478c55f184d65fde1eec8e06c3689d68

/*
  * Copyright (c) 2013 Developed by reg <entry.reg@gmail.com>
  * 
  * Distributed under the Boost Software License, Version 1.0
  * (see accompanying file LICENSE or a copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef WILDCARDS_COMMON_TYPEDEFS__H
#define WILDCARDS_COMMON_TYPEDEFS__H

#include <tchar.h>
#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <iostream>
#include <assert.h>

using namespace std;

namespace net { namespace r_eg { namespace regXwild { 

    #ifdef UNICODE

        typedef wstring tstring;
        typedef wstringstream tstringStream;

        //<tchar.h>
        //typedef wchar_t TCHAR;
        //#define _T(x)  L ## x

    #else

        typedef string tstring;
        typedef stringstream tstringStream;

        //<tchar.h>
        //typedef char TCHAR;
        //#define _T(x)  ## x

    #endif

    typedef vector<tstring> tstringList;
    typedef basic_regex<TCHAR> tregex;

#define TRACE(str){ std::cout << str; }

}}}

#endif // WILDCARDS_COMMON_TYPEDEFS__H