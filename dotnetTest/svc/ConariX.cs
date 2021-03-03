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
using System.Collections.Concurrent;
using net.r_eg.Conari.Types;

namespace dotnetTest.svc
{
    internal sealed class ConariX: net.r_eg.Conari.ConariX, IDisposable
    {
        private readonly ConcurrentBag<UnmanagedString> strings = new ConcurrentBag<UnmanagedString>();

        public IntPtr _T(string input)
        {
            UnmanagedString uns = new UnmanagedString
            (
                input,
#if RXW_UNICODE
                UnmanagedString.SType.Unicode
#else
                UnmanagedString.SType.Ansi
#endif
            );
            strings.Add(uns);
            return uns;
        }

        public ConariX(string lib, string prefix = null)
            : base(lib, prefix)
        {

        }

#region IDisposable

        private bool disposed;

        protected override void Dispose(bool _)
        {
            if(!disposed)
            {
                foreach(var s in strings) s.Dispose();

                base.Dispose(_);
                disposed = true;
            }
        }

#endregion
    }
}
