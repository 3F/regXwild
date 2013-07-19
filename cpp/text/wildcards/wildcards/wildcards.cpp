// sandbox - cpp/text/wildcards
// b0da341, 0100295,  - bitbucket.org/3F/flightsdc/commits/b0da3416478c55f184d65fde1eec8e06c3689d68

#include "algorithms.hpp"
#include <iostream>

void analysis(string caption, bool(*method)(const tstring&, const tstring&), int iterations, tstring& data, tstring& filter)
{
    cout << caption;
    Algorithms::startTime();
    for(int i = 0; i < iterations; ++i){
        if(method(data, filter)){

        }
    }
    cout << Algorithms::deltaTime();
    cout << "\n";
}

int _tmain(int argc, _TCHAR* argv[])
{
    Algorithms::mainAsserts();

    tstring data    = _T("F:/Кинотека/Anime/Kyoto Animation/Харухи Судзумии (Suzumiya Haruhi)/2009 Меланхолия Харухи Харухи 111Судзумии  Меланхолия Харухи Судзумии 2/Хрухи Судзумии 2/Харухи Судзумии (Suzumiya Haruhi)/2009 Меланхолия Харухи Судзумии 2/Suzumiya Haruhi no Yuuutsu (2009) - 02 [BD 720p x264]_12_AniDub(Ancord).mkv"); //300
    tstring filter  = _T("nime**haru*02*mkv");
    int maxRc       = 10000;
 
    // -------
 
    //result: 10000: ~240ms
    analysis("Iterator + Find: ", &Algorithms::findIteratorFind, maxRc, data, filter);
  
    // -------
 
    //result: 10000: ~296ms
    analysis("Getline + Find: ", &Algorithms::findGetlineFind, maxRc, data, filter);
 
    // -------
 
    //result: 10000: ~250ms
    analysis("Find + Find: ", &Algorithms::findFindFind, maxRc, data, filter + _T("*"));
 
    // -------
 
    //result: 10000: ~370ms
    analysis("Iterator + Substr: ", &Algorithms::findIteratorSubstr, maxRc, data, filter + _T("*"));
 
    // -------
 
    //result: 10000: ~320ms
    analysis("Iterator + Iterator: ", &Algorithms::findIteratorIterator, maxRc, data, filter + _T("*"));

    // -------
    //result: 10000: ~970ms
    analysis("regexp-c++11(match^$): ", &Algorithms::findRegexpCpp11m, maxRc, data, Algorithms::strReplace((tstring)_T("*"), (tstring)_T(".*"), filter));

    //result: 10000: ~970ms
    analysis("regexp-c++11(search): ", &Algorithms::findRegexpCpp11s, maxRc, data, Algorithms::strReplace((tstring)_T("*"), (tstring)_T(".*"), filter));

    //result: 10000: ~970ms
    analysis("regexp-c++11(match*): ", &Algorithms::findRegexpCpp11m, maxRc, data, _T(".*") + Algorithms::strReplace((tstring)_T("*"), (tstring)_T(".*"), filter) + _T(".*?"));
    
    // -------

    cout << "\n-----------\n";
    analysis("main :: based on Iterator + Find: ", &Algorithms::main, maxRc, data, filter);


    system("pause");
	return 0;
}

