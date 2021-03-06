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
#ifndef _RXW_CONF_
#define _RXW_CONF_

#include "stdafx.h"

// C linkage for comfortable work via Conari etc.
// https://github.com/3F/Conari/issues/3
#define TLINKAGE extern "C"

#define _CPP11_OR_ABOVE (__cplusplus >= 201103L || _MSVC_LANG >= 201103L)
#define RXW_CPP11_ENUM_CLASS _CPP11_OR_ABOVE

#if RXW_CPP11_ENUM_CLASS
    #define RXW_ENUM_CLASS enum class 
#else
    #define RXW_ENUM_CLASS enum 
#endif

#define _RXW_FEATURE_MATCH_RESULT 1
#define _RXW_FEATURE_MATCH_MAP 0

#include "declspec.h"

#endif // _RXW_CONF_