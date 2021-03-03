using System;
using dotnetTest.svc;
using Xunit;
using static dotnetTest.svc.TestHelper;

namespace dotnetTest
{
    public class ConariReplaceTest
    {
        [Fact]
        public void replaceTest1()
        {
            using var c = NewConariX(out dynamic l);
            using var data = new NativeString<TCharPtr>("numberStr = '+12'");

            bool res = l.replace<bool>((IntPtr)data, c._T("str*'+'"), c._T(" = '008888';"), EngineOptions.F_NONE);
            Assert.False(res);
            Assert.Equal("numberStr = '+12'", (TCharPtr)data);

            res = l.replace<bool>((IntPtr)data, c._T("str*'+'"), c._T(" = '008888';"), EngineOptions.F_ICASE);
            Assert.True(res);
            Assert.Equal("number = '008888';", (TCharPtr)data);
        }

        [Fact]
        public void replaceTest2()
        {
            using var c = NewConariX(out dynamic l);
            c.Cache = false; // because of diff signatures 3 -> 5 / https://github.com/3F/Conari/issues/10#issue-202540865

            Assert.False(l.replace<bool>(IntPtr.Zero, c._T("str*'+'"), c._T(" = '008888';")));

            using var data = new NativeString<TCharPtr>("number_str = '+12'");
            Assert.False(l.replaceOfs<bool>((IntPtr)data, c._T("_str*'+'"), c._T(" = '';"), 7u));
            Assert.True(l.replaceOfs<bool>((IntPtr)data, c._T("_str*'+'"), c._T(" = '';"), 6u));
            Assert.Equal("number = '';", (TCharPtr)data);
        }

        [Fact]
        public void replaceToTest1()
        {
            using var c = NewConariX(out dynamic l);

            using(var to = new NativeString<TCharPtr>())
            {
                bool res = l.replaceTo<bool>(c._T("numberStr = '+12'"), c._T("str*'+'"), c._T(" = '008888';"), (IntPtr)to, (ulong)0, EngineOptions.F_ICASE);
                Assert.True(res);
                Assert.Equal("number = '008888';", (TCharPtr)to);
            }

            using(var to = new NativeString<TCharPtr>())
            {
                bool res = l.replaceTo<bool>(c._T("numberStr = '+12'"), c._T("str*'+'"), c._T(" = '008888';"), (IntPtr)to, (ulong)0, EngineOptions.F_NONE);
                Assert.False(res);
            }
        }

        [Fact]
        public void replaceToTest2()
        {
            using var c = NewConariX(out dynamic l);
            c.Cache = false;

            Assert.False(l.replaceTo<bool>(IntPtr.Zero, c._T("'+'"), c._T("''"), IntPtr.Zero));

            using var data = new NativeString<TCharPtr>("number_str = '+12'");
            Assert.True(l.replaceTo<bool>((IntPtr)data, c._T("_str*'+'"), c._T(" = '';"), IntPtr.Zero, (ulong)0));
            Assert.Equal("number_str = '+12'", (TCharPtr)data);

            Assert.False(l.replaceTo<bool>((IntPtr)data, c._T("_str*'+'"), c._T(" = '';"), IntPtr.Zero, (ulong)7, EngineOptions.F_ICASE));
            Assert.Equal("number_str = '+12'", (TCharPtr)data);

            using(var to = new NativeString<TCharPtr>())
            {
                Assert.True(l.replaceTo<bool>((IntPtr)data, c._T("_str*'+'"), c._T(" = '';"), (IntPtr)to, (ulong)6, EngineOptions.F_ICASE));
                Assert.Equal("number_str = '+12'", (TCharPtr)data);
                Assert.Equal("number = '';", (TCharPtr)to);
            }
        }
    }
}
