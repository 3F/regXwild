/*
* The MIT License (MIT)
*
* Copyright (c) 2013-2014, 2016-2017, 2020  Denis Kuzmin < x-3F@outlook.com > GitHub/3F
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
#include "Analyzer.h"
#include "Meter.h"
#include "Util.h"

namespace net { namespace r_eg { namespace regXwild {

void Analyzer::calc(const string& label, refstr_t data, refstr_t filter, int iterations, talgo method, Algorithms& alg, int average)
{
    Meter meter;
    int results = 0;

    for(int total = 0; total < average; ++total)
    {
        meter.start();
        for(int i = 0; i < iterations; ++i)
        {
            if((alg.*method)(data, filter)) {
                //...
            }
        }
        results += meter.delta();
        TRACE(".");
    }

    DELTAINFO(label, results / average);
}

void Analyzer::calc(const string& label, refstr_t data, refstr_t filter, int iterations, tralgo method, Algorithms& alg, int average)
{
    Meter meter;
    int results = 0;

    meter.start();

    auto rfilter = tregex(
        filter,
        regex_constants::icase | regex_constants::optimize
    );

    results += meter.delta();
    DELTAINFO("\n\t* +time to create basic_regex from filter (icase | optimize): ", results);
    TRACE("\t* ");

    for(int total = 0; total < average; ++total)
    {
        meter.start();
        for(int i = 0; i < iterations; ++i) {
            if((alg.*method)(data, rfilter)) { }
        }
        results += meter.delta();
        TRACE(".");
    }

    DELTAINFO(label, results / average);
    TRACE("\n");
}

void Analyzer::calc()
{
    tstring data    = _T("#//Anime/Kyoto Animation/Clannad TV -/Suzumiya Haruhi/Lucky Star/Full Metal Panic Fumoffu/P.A. Works/Angel Beats!/A-1 Pictures/Ano Hi Mita Hana no Namae wo Bokutachi wa Mada Shira nai/Макото Синкай [2002] Kanojo to kanojo no neko/ Kino no Tabi @ ... World/White Fox/Врата Штайнера (Врата Штейна (Steins Gate))/SHAFT/Maho Shojo Madoka Magica"); //340
    tstring filter  = _T("nime**haru*02*Magica");
    int lim         = 10000;

    tryAlgo(data, filter, lim, 30);
    tryRegex(data, filter, lim, 1);
}

void Analyzer::tryAlgo(refstr_t data, refstr_t filter, int iterations, int average)
{
    int lim = iterations;
    Algorithms alg;

    TRACE(lim << " x " << average << "\n");

    calc(" Find + Find: ", data, filter + _T("*"), lim, &Algorithms::findFindFind, alg, average);
    calc(" Iterator + Find: ", data, filter, lim, &Algorithms::findIteratorFind, alg, average);
    calc(" Getline + Find: ", data, filter, lim, &Algorithms::findGetlineFind, alg, average);
    calc(" Iterator + Substr: ", data, filter + _T("*"), lim, &Algorithms::findIteratorSubstr, alg, average);
    calc(" Iterator + Iterator: ", data, filter + _T("*"), lim, &Algorithms::findIteratorIterator, alg, average);
    calc(" main :: based on Iterator + Find: ", data, filter, lim, &Algorithms::main, alg, average);

    TRACE("\n-----------\n");

    calc(" Final algorithm - EXT version: ", data, filter, lim, &Algorithms::finalExt, alg, average);
    calc(" Final algorithm - ESS version: ", data, filter, lim, &Algorithms::finalEss, alg, average);

    TRACE("-----------\n");
}

void Analyzer::tryRegex(refstr_t data, refstr_t filter, int iterations, int average)
{
    int lim = iterations;
    Algorithms alg;

    TRACE("\n" << lim << " x " << average << "\n");
    TRACE("The regex engine is much more slower (~30-90sec for 10000 iterations), please wait... \n\n");

    TRACE("regexp-c++11(regex_search): ");
    calc(" ", data, Util::strReplace((tstring)_T("*"), (tstring)_T(".*"), filter), lim, &Algorithms::findRegexpCpp11s, alg, average);

    TRACE("regexp-c++11(only as ^match$ like a simple '=='): ");
    calc(" ", data, Util::strReplace((tstring)_T("*"), (tstring)_T(".*"), filter), lim, &Algorithms::findRegexpCpp11m, alg, average);

    TRACE("regexp-c++11(regex_match with endings .*): ");
    calc(" ", data, _T(".*") + Util::strReplace((tstring)_T("*"), (tstring)_T(".*"), filter) + _T(".*?"), lim, &Algorithms::findRegexpCpp11m, alg, average);
}

}}}