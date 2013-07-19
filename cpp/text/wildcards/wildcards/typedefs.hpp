// sandbox - cpp/text/wildcards
// b0da341, 0100295,  - bitbucket.org/3F/flightsdc/commits/b0da3416478c55f184d65fde1eec8e06c3689d68

#pragma once

#include <string>
#include <tchar.h>
#include <vector>
#include <algorithm>
#include <regex>
#include <sstream>

using namespace std;

typedef vector<string> StringList;
typedef StringList::iterator StringIter;
typedef StringList::const_iterator StringIterC;
typedef vector<wstring> WStringList;

#ifdef UNICODE

    typedef wstring tstring;
    typedef WStringList TStringList;

    typedef basic_regex<char>    regex;
    typedef basic_regex<wchar_t> wregex;

    #define __T(x)  L ## x

    inline const tstring uppercase(tstring p_str) throw()
    {
	    transform(p_str.begin(), p_str.end(), p_str.begin(), towupper);
	    return p_str;
    }

#else

    typedef char TCHAR;
    #define __T(x)  ## x
    typedef string tstring;
    typedef StringList TStringList;

#endif

#define _T(x)       __T(x)
#define _TEXT(x)    __T(x)