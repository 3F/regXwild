// sandbox - cpp/text/wildcards
// b0da341, 0100295,  - bitbucket.org/3F/flightsdc/commits/b0da3416478c55f184d65fde1eec8e06c3689d68

/*
  * Copyright (c) 2013 Developed by reg <entry.reg@gmail.com>
  * 
  * Distributed under the Boost Software License, Version 1.0
  * (see accompanying file LICENSE or a copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "typedefs.hpp"
#include "Algorithms.hpp"
#include "AlgorithmExt.hpp"
#include "Meter.hpp"
#include "Util.hpp"
#include <iostream>

using namespace reg::sandbox::cpp::text::wildcards;

void analysis(const string& caption, const tstring& data, const tstring& filter, int iterations, talgorithm method, Algorithms& alg)
{
    Meter meter;

    cout << caption;
    meter.start();
    for(int i = 0; i < iterations; ++i){
        if((alg.*method)(data, filter)){
            //...
        }
    }
    cout << meter.delta();
    cout << "\n";
}

void analysis()
{
    tstring data    = _T("F:/Кинотека/Anime/Kyoto Animation/Харухи Судзумии (Suzumiya Haruhi)/2009 Меланхолия Харухи Харухи 111Судзумии  Меланхолия Харухи Судзумии 2/Хрухи Судзумии 2/Харухи Судзумии (Suzumiya Haruhi)/2009 Меланхолия Харухи Судзумии 2/Suzumiya Haruhi no Yuuutsu (2009) - 02 [BD 720p x264]_12_AniDub(Ancord).mkv"); //300
    tstring filter  = _T("nime**haru*02*mkv");
    int lim         = 10000;

    Algorithms alg;

    //result: 10000: ~160ms
    analysis("Iterator + Find: ", data, filter, lim, &Algorithms::findIteratorFind, alg);
 
    //result: 10000: ~172ms
    analysis("Getline + Find: ", data, filter, lim, &Algorithms::findGetlineFind, alg);
 
    //result: 10000: ~153ms
    analysis("Find + Find: ", data, filter + _T("*"), lim, &Algorithms::findFindFind, alg);
  
    //result: 10000: ~263ms
    analysis("Iterator + Substr: ", data, filter + _T("*"), lim, &Algorithms::findIteratorSubstr, alg);
 
    //result: 10000: ~231ms
    analysis("Iterator + Iterator: ", data, filter + _T("*"), lim, &Algorithms::findIteratorIterator, alg);

    //result: 10000: ~56ms - unusable...
    analysis("regexp-c++11(match^$): ", data, Util::strReplace((tstring)_T("*"), (tstring)_T(".*"), filter), lim, &Algorithms::findRegexpCpp11m, alg);

    //result: 10000: ~81675ms
    analysis("regexp-c++11(search): ", data, Util::strReplace((tstring)_T("*"), (tstring)_T(".*"), filter), lim, &Algorithms::findRegexpCpp11s, alg);

    //result: 10000: ~89163ms
    analysis("regexp-c++11(match*): ", data, _T(".*") + Util::strReplace((tstring)_T("*"), (tstring)_T(".*"), filter) + _T(".*?"), lim, &Algorithms::findRegexpCpp11m, alg);

    cout << "\n-----------\n";
    //result: 10000: ~146ms
    analysis("main :: based on Iterator + Find: ", data, filter, lim, &Algorithms::main, alg);

    //https://bitbucket.org/3F/flightsdc/commits/0fc73542e2bc8c77bd2fe794b0b1ce1abf090a0a#comment-337260
    //https://bitbucket.org/3F/sandbox/commits/b04e5983716e0434ea1e6acb2a862e1dd2eadab5
}

int _tmain(int argc, _TCHAR* argv[])
{
    analysis();
 

    system("pause");
	return 0;
}

