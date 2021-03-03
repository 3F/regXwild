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

using System;
using net.r_eg.Conari.Types;

namespace dotnetTest.svc
{
    internal struct TCharPtr
    {
#if RXW_UNICODE
        private readonly WCharPtr data;
#else
        private readonly CharPtr data;
#endif

        [NativeType]
        public static implicit operator IntPtr(TCharPtr v) => v.data;
        public static implicit operator TCharPtr(IntPtr ptr) => new TCharPtr(ptr);
        public static implicit operator string(TCharPtr v) => v.data;

#if RXW_UNICODE
        public static implicit operator WCharPtr(TCharPtr v) => v.data;
        public TCharPtr(WCharPtr data) => this.data = data;
#else
        public static implicit operator CharPtr(TCharPtr v) => v.data;
        public TCharPtr(CharPtr data) => this.data = data;
#endif
    }
}
