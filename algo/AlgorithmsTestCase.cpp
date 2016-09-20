/*
* The MIT License (MIT)
*
* Copyright (c) 2013, 2014, 2016  Denis Kuzmin <entry.reg@gmail.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include "stdafx.h"
#include "Algorithms.h"
#include "Meter.h"
#include "Util.h"

namespace net { namespace r_eg { namespace regXwild {

void AlgorithmsTestCase::analysis(const string& caption, const tstring& data, const tstring& filter, int iterations, talgorithm method, Algorithms& alg)
{
    Meter meter;
    //int results = 0;
    //int max     = 110;

    //for(int total = 0; total < max; ++total){
        meter.start();
        for(int i = 0; i < iterations; ++i){
            if((alg.*method)(data, filter)){
                //...
            }
        }
    //    results += meter.delta();
    //}
    //TRACE(caption << "~" << (results / max) << "ms\n");
    TRACE(caption << "~" << meter.delta() << "ms\n");
}

void AlgorithmsTestCase::analysis()
{
    tstring data    = _T("#//Anime/Kyoto Animation/Clannad TV -/Suzumiya Haruhi/Lucky Star/Full Metal Panic Fumoffu/P.A. Works/Angel Beats!/A-1 Pictures/Ano Hi Mita Hana no Namae wo Bokutachi wa Mada Shira nai/Макото Синкай [2002] Kanojo to kanojo no neko/ Kino no Tabi @ ... World/White Fox/Врата Штайнера (Врата Штейна (Steins Gate))/SHAFT/Maho Shojo Madoka Magica"); //340
    tstring filter  = _T("nime**haru*02*Magica");
    int lim         = 10000;

    Algorithms alg;

    //result: 10000: ~58ms
    analysis("Find + Find: ", data, filter + _T("*"), lim, &Algorithms::findFindFind, alg);

    //result: 10000: ~57ms
    analysis("Iterator + Find: ", data, filter, lim, &Algorithms::findIteratorFind, alg);
 
    //result: 10000: ~59ms
    analysis("Getline + Find: ", data, filter, lim, &Algorithms::findGetlineFind, alg);
  
    //result: 10000: ~165ms
    analysis("Iterator + Substr: ", data, filter + _T("*"), lim, &Algorithms::findIteratorSubstr, alg);
 
    //result: 10000: ~136ms
    analysis("Iterator + Iterator: ", data, filter + _T("*"), lim, &Algorithms::findIteratorIterator, alg);

    //result: 10000: ~53ms
    analysis("main :: based on Iterator + Find: ", data, filter, lim, &Algorithms::main, alg);

    //result: 10000: ~50ms
    analysis("Final algorithm - EXT version: ", data, filter, lim, &Algorithms::finalExt, alg);

    //result: 10000: ~50ms
    analysis("Final algorithm - ESS version: ", data, filter, lim, &Algorithms::finalEss, alg);

    TRACE("\n-----------\n");
    
    //result: 10000: ~64063ms
    TRACE("regexp-c++11(search):");
    analysis(" ", data, Util::strReplace((tstring)_T("*"), (tstring)_T(".*"), filter), lim, &Algorithms::findRegexpCpp11s, alg);
    
    //result: 10000: ~34ms
    TRACE("regexp-c++11(only with ^match$ like a '==' - rapid but unusable):");
    analysis(" ", data, Util::strReplace((tstring)_T("*"), (tstring)_T(".*"), filter), lim, &Algorithms::findRegexpCpp11m, alg);
    
    //result: 10000: ~64329ms
    TRACE("regexp-c++11(match*):");
    analysis(" ", data, _T(".*") + Util::strReplace((tstring)_T("*"), (tstring)_T(".*"), filter) + _T(".*?"), lim, &Algorithms::findRegexpCpp11m, alg);

}



/* TODO: All tests below was before main library to support main logic from errors and typos, 
        i.e. it used only for current algo !  

        All Unit-tests see in regXwildTest.
*/

void AlgorithmsTestCase::assertsMainModeAny()
{
    tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

    // should be found:
    assert(alg.main(data, _T("protection of various")) == true);      // __ __ __
    assert(alg.main(data, _T("pro*system")) == true);                 // __ * __
    assert(alg.main(data, _T("*pro*system*")) == true);               // * __ * __ *
    assert(alg.main(data, _T("project**various")) == true);           // __ ** __
    assert(alg.main(data, _T("new*7*systems")) == true);              // __ * __ * __
    assert(alg.main(data, _T("")) == true);                           // empty

    // should not be found:
    assert(alg.main(data, _T("project 12 and")) == false);            // __ _x_ __
    assert(alg.main(data, _T("new*express")) == false);               // __ * _x_
    assert(alg.main(data, _T("tes*ting*project")) == false);          // __ * _x_ * __
    assert(alg.main(data, _T("testing*project*and")) == false);       // _x_ * __ * __
    assert(alg.main(data, _T("now*is*completely")) == false);         // _x_ * _x_ * _x_
    assert(alg.main(data, _T("protection*project*new")) == false);    // backwards __ * __ * __
    assert(alg.main(data, _T("**open**close")) == false);             // ** _x_ ** _x_
}

void AlgorithmsTestCase::assertsMainModeSplit()
{
    tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

    // should be found:
    assert(alg.main(data, _T("protection of|new tes")) == true);       // __ __ | __ __
    assert(alg.main(data, _T("some project|of various")) == true);     // _x_ __ | __ __
    assert(alg.main(data, _T("various systems|new 237")) == true);     // __ __ | __ _x_
    assert(alg.main(data, _T("pro*12|new*system")) == true);           // __ * __ | __ *__
    assert(alg.main(data, _T("ject*new|pro*tems")) == true);           // __ * _x_ | __ * __
    assert(alg.main(data, _T("pro*tems|seems*and")) == true);          // __ * __ | _x_ * __
    assert(alg.main(data, _T("project*|new")) == true);                // __ *| __
    assert(alg.main(data, _T("various*|zeep")) == true);               // __ * | _x_
    assert(alg.main(data, _T("goo*|systems")) == true);                // _x_ * | __
    assert(alg.main(data, _T("project||protect")) == true);            // __ || __
    assert(alg.main(data, _T("|new||and|")) == true);                  // | __ || __ |
    assert(alg.main(data, _T("|fail|system")) == true);                // | _x_ | __
    assert(alg.main(data, _T("|12||true||")) == true);                 // | __ || _x_ ||
    assert(alg.main(data, _T("above|new|with")) == true);              // _x_ | __ | _x_
    assert(alg.main(data, _T("project**|new")) == true);               // __ **| __
    assert(alg.main(data, _T("zoom|*pro")) == true);                   // _x_ | * __
    assert(alg.main(data, _T("zoom|*pro**")) == true);                 // _x_ | *__ **
    assert(alg.main(data, _T("||")) == true);                          //empty
    assert(alg.main(data, _T("")) == true);                            //empty
    assert(alg.main(data, _T("||zoom||out||")) == true);               // ||_x_ || _x_ ||
    assert(alg.main(data, _T("|*|")) == true);                         // |*|
    assert(alg.main(data, _T("|long-term")) == true);                  // | _x_
    assert(alg.main(data, _T("long-term|")) == true);                  // _x_ |
    assert(alg.main(data, _T("*|*")) == true);                         // *|*
    assert(alg.main(data, _T("*|")) == true);                          // *|
    assert(alg.main(data, _T("|*")) == true);                          // |*
    assert(alg.main(data, _T("seems|open*and*star|*system")) == true); // _x_ | _x_ * __ * _x_ | * __

    // should not be found:        
    assert(alg.main(data, _T("above|fails|with")) == false);           // _x_ | _x_ | _x_
    assert(alg.main(data, _T("let*proj|project*deep")) == false);      // _x_ * __ | __ * _x_
    assert(alg.main(data, _T("operator*|*zeep")) == false);            // _x_ *|* _x_
    assert(alg.main(data, _T("some project|let*various")) == false);   // _x_ __ | _x_* __
    assert(alg.main(data, _T("some project|various*zoom")) == false);  // _x_ __ | __ * _x_
    assert(alg.main(data, _T("be|pen*and*star|*my*system")) == false); // _x_ | _x_ * __ * _x_ | * _x_ * __
}

void AlgorithmsTestCase::assertsMainModeOne()
{
    tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

    // should be found:
    assert(alg.main(data, _T("new*pro?ection")) == true);              // __ * [pro]ject ... [pro]t[ection]
    assert(alg.main(data, _T("????")) == true);
    assert(alg.main(data, _T("project?12")) == true);
    assert(alg.main(_T("system-17 fee also offers protection"), _T("system?17")) == true);

    // should not be found:
    assert(alg.main(data, _T("?pro?12?|seems?7")) == false);
    assert(alg.main(_T("system, installments range from 2 to 17"), _T("system?17")) == false);
    assert(alg.main(_T("system17 fee also"), _T("system?17")) == false);
    assert(alg.main(_T("my system17 fee also"), _T("system?17")) == false);
    assert(alg.main(_T("system_-17 fee also"), _T("system?17")) == false);
}

}}}