// sandbox - cpp/text/wildcards
// b0da341, 0100295,  - bitbucket.org/3F/flightsdc/commits/b0da3416478c55f184d65fde1eec8e06c3689d68

#pragma once

#include "typedefs.hpp"
#include <time.h>

class Algorithms
{
public:
    static bool findGetlineFind(const tstring& text, const tstring& filter);
    static bool findIteratorFind(const tstring& text, const tstring& filter);
    static bool findRegexpCpp11m(const tstring& text, const tstring& filter);
    static bool findRegexpCpp11s(const tstring& text, const tstring& filter);
    static bool findFindFind(const tstring& text, const tstring& filter);
    static bool findIteratorSubstr(const tstring& text, const tstring& filter);
    static bool findIteratorIterator(const tstring& text, const tstring& filter);
    static bool main(const tstring& text, const tstring& filter);

    static void mainAsserts();

    static void startTime()
    {
        _started = clock();
    }

    static int deltaTime()
    {
        return clock() - _started;
    }

    template<class strType>
    static inline strType strReplace(const strType& replace, const strType& replacement, const strType& str)
    {
        strType _str    = str;
        size_t pos      = 0;
        while((pos = _str.find(replace, pos)) != strType::npos){
            _str.replace(pos, replace.length(), replacement);
            pos += replacement.length();
        }
        return _str;
    };

private:
    static int _started;

    Algorithms(void){};
    ~Algorithms(void){};
};