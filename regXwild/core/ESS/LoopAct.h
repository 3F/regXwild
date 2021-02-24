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

#pragma once

#include "stdafx.h"
#include "conf.h"
#include "typedefs.h"

namespace net { namespace r_eg { namespace regXwild { namespace core { namespace ESS
{
    using namespace net::r_eg::regXwild::rxwtypes;

    RXW_ENUM_CLASS LoopAct: flagshort_t
    {
        Break                   = 0x01,
        Continue                = 0x02,
        IgnoreLoopExpression    = 0x04,
        ReturnTrue              = 0x08,
        ReturnFalse             = 0x10,
    };

#if RXW_CPP11_ENUM_CLASS

    inline flagcfg_t operator& (LoopAct l, LoopAct r)
    {
        return static_cast<flagcfg_t>(l) & static_cast<flagcfg_t>(r);
    }

    inline LoopAct operator| (LoopAct l, LoopAct r)
    {
        return static_cast<LoopAct>(static_cast<flagcfg_t>(l) | static_cast<flagcfg_t>(r));
    }

#endif

}}}}}