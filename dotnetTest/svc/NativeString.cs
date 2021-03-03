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
using System.Runtime.InteropServices;
using System.Text;
using net.r_eg.Conari.Types;

namespace dotnetTest.svc
{
    internal class NativeString<T>: IDisposable
        where T : struct
    {
        protected readonly IntPtr pointer;

        [NativeType]
        public static implicit operator IntPtr(NativeString<T> val) => val.pointer;

        public static implicit operator WCharPtr(NativeString<T> val) => val.pointer;
        public static implicit operator CharPtr(NativeString<T> val) => val.pointer;
        public static implicit operator TCharPtr(NativeString<T> val) => val.pointer;

        public NativeString(int buffer = 0x1F) => pointer = Marshal.AllocHGlobal(buffer);

        public NativeString(string str, int add = 0x1F) => pointer = AllocString(ref str, add);

        private IntPtr AllocString(ref string str, int buffer = 0)
        {
#if RXW_UNICODE
            //str.ToCharArray()
            byte[] data     = Encoding.Unicode.GetBytes(str);
            byte[] cNULL    = Encoding.Unicode.GetBytes("\0");
#else
            byte[] data     = Encoding.ASCII.GetBytes(str);
            byte[] cNULL    = Encoding.ASCII.GetBytes("\0");
#endif
            IntPtr addr = Marshal.AllocHGlobal(data.Length + Math.Max(0, buffer));

            Marshal.Copy(data, 0, addr, data.Length);
            Marshal.Copy(cNULL, 0, addr + data.Length, cNULL.Length);
            return addr;
        }

#region IDisposable

        private bool disposed = false;

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool _)
        {
            if(!disposed)
            {
                Marshal.FreeHGlobal(pointer);
                disposed = true;
            }
        }

        ~NativeString() => Dispose(false);

#endregion
    }
}
