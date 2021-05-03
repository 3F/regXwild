/*
* The MIT License (MIT)
*
* Copyright (c) 2013-2021  Denis Kuzmin <x-3F@outlook.com> github/3F
* Copyright (c) regXwild contributors https://github.com/3F/regXwild
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
#include "regXwild.h"
#include "regXwild.common.h"

namespace net { namespace r_eg { namespace regXwild { namespace common { namespace ext
{
    /* Non thread safe */

    EssRxW* g_rxw;
    rxwtypes::tstring* g_input;

    ExtRxW* g_rxwExt;
    rxwtypes::tstring* g_inputExt;

    REGXWILD_API_L void matchInit(const rxwtypes::TCHAR* input)
    {
        g_rxw   = new EssRxW();
        g_input = new rxwtypes::tstring(input);
    }

    REGXWILD_API_L void matchClose()
    {
        delete g_input;
        delete g_rxw;
    }

    REGXWILD_API_L bool matchFast(const rxwtypes::TCHAR* pattern)
    {
        return g_rxw->match(*g_input, pattern, 0, EssRxW::EngineOptions::F_NONE, nullptr);
    }

    REGXWILD_API_L void extInit(const rxwtypes::TCHAR* input)
    {
        g_rxwExt    = new ExtRxW();
        g_inputExt  = new rxwtypes::tstring(input);
    }

    REGXWILD_API_L void extClose()
    {
        delete g_inputExt;
        delete g_rxwExt;
    }

    REGXWILD_API_L bool extFast(const rxwtypes::TCHAR* pattern)
    {
        return g_rxwExt->main(*g_inputExt, pattern, false);
    }

}}}}}