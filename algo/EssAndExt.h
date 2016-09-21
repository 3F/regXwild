#pragma once

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

#include "typedefs.h"
#include "Meter.h"

#include "..\regXwild\regXwildAPI.h"

//#include "AlgorithmExt.h"
//#include "AlgorithmEss.h"

namespace net { namespace r_eg { namespace regXwild {

    struct IAnalysis
    {
        virtual bool search(const tstring& text, const tstring& filter) = 0;
    };
    typedef IAnalysis* IAnalysis_;

    class AnalysisEss: public IAnalysis
    {
    public:

        bool search(const tstring& text, const tstring& filter)
        {
            return searchEss(text, filter, true);
        }

    protected:
        //AlgorithmEss alg;

    };

    class AnalysisExt: public IAnalysis
    {
    public:

        bool search(const tstring& text, const tstring& filter)
        {
            return searchExt(text, filter);
        }

    protected:
        //AlgorithmExt alg;

    };

    class EssAndExt
    {
    public:

        /**
         * ESS vs EXT
         */
        void compare()
        {
            AnalysisExt algExt;
            AnalysisEss algEss;
    
            // 350
            tstring text = _T("JDK 6 for NetBeans 6.9 or newer, JDK 5 for NetBeans 6.8 or older (it must be 1.5.0 because NetBeans must be runnable on this version of JDK or newer, by using 1.5.0 you will ensure that you don't use APIs and features available only in JDK 6 or newer)/ Apache Ant 1.7.1/ Latest Mercurial release (at least 1.0.2), presupposing Python 2.5. 1 or later.");
            tstring filter;
            unsigned int iterations = 10000;

            /* ANY */

            filter = _T("*NetBeans*6*8*(*must*newer**only*1*1*0***later**");
            TRACE("[EXT::ANY] =~ " << analysis(&algExt, text, filter, iterations) << "ms\n");
            TRACE("[ESS::ANY] =~ " << analysis(&algEss, text, filter, iterations) << "ms\n");
            

            /* ANYSP */

            filter = _T("*NetBeans*6*8*(>must>newer>only*1*1*0***later**");
            TRACE("[EXT::ANYSP] =~ " << analysis(&algExt, text, filter, iterations) << "ms\n");
            TRACE("[ESS::ANYSP] =~ " << analysis(&algEss, text, filter, iterations) << "ms\n");

            /* ONE */

            filter = _T("NetBeans ?.*must*be?1**because*must be*Ant?1.7*or later");
            TRACE("[EXT::ONE] =~ " << analysis(&algExt, text, filter, iterations) << "ms\n");
            TRACE("[ESS::ONE] =~ " << analysis(&algEss, text, filter, iterations) << "ms\n");

            /* SPLIT */

            filter = _T("*NetBeans*6*8*(*must*newer*notfound*API*only|**only*1*1*0***later*notfound*NetBeans*6*8*|*NetBeans*6*8*(*must*newer**only*1*1*0***later**|*NetBeans*6*8*(>must>newer>only*1*1*0***later**|NetBeans ?.*must*be?1**because*must be*Ant?1.7*or later");
            TRACE("[EXT::SPLIT] =~ " << analysis(&algExt, text, filter, iterations) << "ms\n");
            TRACE("[ESS::SPLIT] =~ " << analysis(&algEss, text, filter, iterations) << "ms\n");

            /* BEGIN */
            filter = _T("^JDK 6");
            TRACE("[ESS::BEGIN] =~ " << analysis(&algEss, text, filter, iterations) << "ms\n");

            /* END */
            filter = _T("or later.$");
            TRACE("[ESS::END] =~ " << analysis(&algEss, text, filter, iterations) << "ms\n");

            /* MORE */
            filter = _T("NetBeans+must be+1.5");
            TRACE("[ESS::MORE] =~ " << analysis(&algEss, text, filter, iterations) << "ms\n");

            /* SINGLE */
            filter = _T("JDK # for NetBeans #");
            TRACE("[ESS::SINGLE] =~ " << analysis(&algEss, text, filter, iterations) << "ms\n");

        };

    protected:

        clock_t analysis(IAnalysis_ alg, const tstring& text, const tstring& filter, unsigned int iterations)
        {
            Meter meter;
            clock_t results     = 0;
            unsigned int max    = 50;

            for(unsigned int total = 0; total < max; ++total){
                meter.start();
                for(unsigned int i = 0; i < iterations; ++i){
                    if(alg->search(text, filter)){
                        //...
                    }
                }
                results += meter.delta();
            }
            return results / max;
        }
    };

}}}