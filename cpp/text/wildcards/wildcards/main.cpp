// sandbox - cpp/text/wildcards
// b0da341, 0100295,  - bitbucket.org/3F/flightsdc/commits/b0da3416478c55f184d65fde1eec8e06c3689d68

/*

[Intel Core2 Duo P8400 @ 2.26GHz]:

http://bitbucket.org/3F/flightsdc/commits/0fc73542e2bc8c77bd2fe794b0b1ce1abf090a0a#comment-337260

                                        |c icase          | без icase
----------------------------------------------------------------------------------
Iterator + Find                         | ~240ms (~222ms) | ~7ms
Getline + Find                          | ~296ms (~278ms) | ~63ms
Find + Find                             | ~250ms (~232ms) | ~17ms
Iterator + Substr                       | ~370ms (~352ms) | ~137ms
Iterator + Iterator                     | ~320ms (~302ms) | ~87ms
----------------------------------------------------------------------------------
regexp-c++11(regex_match! только ^str$) | ~970ms          | ~1163ms - среднее действ. выросло
regexp-c++11(regex_search)              | ~85279ms        | ~16426ms
regexp-c++11(regex_match c конечными .*)| ~91715ms        | ~19413ms - ограничение жадности для квантификатора дает сравнимые результаты 
----------------------------------------------------------------------------------

Data:
300 символов юникода, 10000 строк, Фильтр L"nime**haru*02*mkv"

*/

#include "comparison/methods/Algorithms.h"
#include "versions/simple/AlgorithmExt.h"

using namespace net::r_eg::text::wildcards;

int _tmain(int argc, _TCHAR* argv[])
{
    AlgorithmsTestCase algorithms;
    algorithms.assertsMainModeAny();
    algorithms.assertsMainModeSplit();
    algorithms.assertsMainModeOne();
    algorithms.analysis();


    //AlgorithmExtTestCase algExt;
    //algExt.assertsAny();
    //algExt.assertsAnySP();
    //algExt.assertsOne();
    //algExt.assertsSplit();

    system("pause");
    return 0;
}

