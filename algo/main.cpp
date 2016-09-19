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

/*

*/

#include "stdafx.h"

#include "Algorithms.h"
#include "EssAndExt.h"

using namespace net::r_eg::regXwild;


int _tmain(int argc, _TCHAR* argv[])
{

#if _DEBUG

    AlgorithmsTestCase algorithms;
    algorithms.assertsMainModeAny();
    algorithms.assertsMainModeSplit();
    algorithms.assertsMainModeOne();

    TRACE("Use Release cfg. Or better execute outside VS IDE algo.exe for comparison speed.");

#else

    /*

    Find + Find: ~58ms
    Iterator + Find: ~57ms
    Getline + Find: ~59ms
    Iterator + Substr: ~165ms
    Iterator + Iterator: ~136ms
    main :: based on Iterator + Find: ~53ms

    -----------
    regexp-c++11(search): ~64063ms
    regexp-c++11(only with ^match$ like a '==' - rapid but unusable): ~34ms
    regexp-c++11(match*): ~64329ms
    [EXT::ANY] =~ 54ms
    [ESS::ANY] =~ 55ms
    [EXT::ANYSP] =~ 60ms
    [ESS::ANYSP] =~ 59ms
    [EXT::ONE] =~ 56ms
    [ESS::ONE] =~ 56ms
    [EXT::SPLIT] =~ 92ms
    [ESS::SPLIT] =~ 94ms
    [ESS::BEGIN] =~ 38ms
    [ESS::END] =~ 39ms
    [ESS::MORE] =~ 44ms
    [ESS::SINGLE] =~ 43ms

    */

    AlgorithmsTestCase algorithms;
    algorithms.assertsMainModeAny();
    algorithms.assertsMainModeSplit();
    algorithms.assertsMainModeOne();
    algorithms.analysis();

    AlgorithmEssCmpExt cmpEss;
    cmpEss.compare();

    TRACE("done.");

#endif

    system("pause");
    return 0;
}

