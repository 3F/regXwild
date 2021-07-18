using System;
using dotnetTest._svc;
using net.r_eg.Conari;
using net.r_eg.Conari.Types;
using Xunit;
using static dotnetTest._svc.TestHelper;

namespace dotnetTest
{
    public class ConariReplaceTest
    {
        [Fact]
        public void replaceTest1()
        {
            using var c = ConariX.Make(new(Library), out dynamic l);
            using var data = new NativeString<TCharPtr>("numberStr = '+12'");

            bool res = l.replace<bool>(data, "str*'+'", " = '008888';", EngineOptions.F_NONE);
            Assert.False(res);
            Assert.True("numberStr = '+12'" == data);

            res = l.replace<bool>(data, "str*'+'", " = '008888';", EngineOptions.F_ICASE);
            Assert.True(res);
            Assert.True("number = '008888';" == data);
        }

        [Fact]
        public void replaceTest2()
        {
            using var c = ConariX.Make(new(Library), out dynamic l);

            Assert.False(l.replace<bool>(IntPtr.Zero, "str*'+'", " = '008888';"));

            using var data = new NativeString<TCharPtr>("number_str = '+12'");
            Assert.False(l.replaceOfs<bool>(data, "_str*'+'", " = '';", n(7)));
            Assert.True(l.replaceOfs<bool>(data, "_str*'+'", " = '';", n(6)));
            Assert.True("number = '';" == data);
        }

        [Fact]
        public void replaceToTest1()
        {
            using var c = ConariX.Make(new(Library), out dynamic l);

            using(var to = new NativeString<TCharPtr>())
            {
                bool res = l.replaceTo<bool>("numberStr = '+12'", "str*'+'", " = '008888';", to, n(0), EngineOptions.F_ICASE);
                Assert.True(res);
                Assert.True("number = '008888';" == to);
            }

            using(var to = new NativeString<TCharPtr>())
            {
                bool res = l.replaceTo<bool>("numberStr = '+12'", "str*'+'", " = '008888';", to, n(0), EngineOptions.F_NONE);
                Assert.False(res);
            }
        }

        [Fact]
        public void replaceToTest2()
        {
            using var c = ConariX.Make(new(Library), out dynamic l);

            Assert.False(l.replaceTo<bool>(IntPtr.Zero, "'+'", "''", IntPtr.Zero));

            using var data = new NativeString<TCharPtr>("number_str = '+12'");
            Assert.True(l.replaceTo<bool>(data, "_str*'+'", " = '';", IntPtr.Zero, n(0)));
            Assert.True("number_str = '+12'" == data);

            Assert.False(l.replaceTo<bool>(data, "_str*'+'", " = '';", IntPtr.Zero, n(7), EngineOptions.F_ICASE));
            Assert.True("number_str = '+12'" == data);

            using var to = new NativeString<TCharPtr>();
            Assert.True(l.replaceTo<bool>(data, "_str*'+'", " = '';", to, n(6), EngineOptions.F_ICASE));
            Assert.True("number_str = '+12'" == data);
            Assert.True("number = '';" == to);
        }
    }
}
