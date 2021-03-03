using System;
using dotnetTest.svc;
using Xunit;
using static dotnetTest.svc.TestHelper;

namespace dotnetTest
{
    public class ConariMatchTest
    {
        [Fact]
        public void matchTest1()
        {
            using var c = NewConariX(out dynamic l);
            using var u = new NativeStruct<MatchResult>();

            Assert.True(l.match<bool>(c._T("system"), c._T("syStem"), EngineOptions.F_ICASE | EngineOptions.F_MATCH_RESULT, (IntPtr)u));
            Assert.Equal(0u, u.Data.start);
            Assert.Equal(6u, u.Data.end);

            Assert.False(l.match<bool>(c._T("system"), c._T("1"), EngineOptions.F_NONE, (IntPtr)u));
            Assert.Equal(MatchResult.npos, u.Read().Data.start);

            Assert.True(l.matchOfs<bool>(c._T("number_str = '+12'"), c._T("str"), 5u, EngineOptions.F_NONE, (IntPtr)u));
            Assert.Equal(MatchResult.npos, u.Read().Data.start);

            Assert.True(l.matchOfs<bool>(c._T("number_str = '+12'"), c._T("str"), 5u, EngineOptions.F_MATCH_RESULT, (IntPtr)u));
            u.Read();
            Assert.Equal(7u, u.Data.start);
            Assert.Equal(10u, u.Data.end);

            Assert.False(l.matchOfs<bool>(c._T("number_str = '+12'"), c._T("str"), 8u, EngineOptions.F_NONE, (IntPtr)u));
            Assert.Equal(MatchResult.npos, u.Read().Data.start);
        }

        [Fact]
        public void searchTest1()
        {
            using var c = NewConariX(out dynamic l);
            Assert.False(l.searchEssC<bool>(c._T("system"), c._T("syStem"), false));
            Assert.True(l.searchEssC<bool>(c._T("system"), c._T("syStem"), true));

            Assert.True(l.searchEssC<bool>(c._T("number = '12'"), c._T("'+'"), false));

            Assert.False(l.searchEssC<bool>(c._T("123"), c._T("4"), true));
            Assert.True(l.searchEssC<bool>(c._T("123"), c._T("2"), true));
        }
    }
}
