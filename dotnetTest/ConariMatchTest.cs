using System;
using dotnetTest._svc;
using net.r_eg.Conari;
using net.r_eg.Conari.Types;
using Xunit;
using static dotnetTest._svc.TestHelper;

namespace dotnetTest
{
    public class ConariMatchTest
    {
        [Fact]
        public void matchTest1()
        {
            using var c = ConariX.Make(new(Library), out dynamic l);
            using var u = new NativeStruct<MatchResult>();

            Assert.True(l.match<bool>("system", "syStem", EngineOptions.F_ICASE | EngineOptions.F_MATCH_RESULT, u));
            Assert.Equal(n(0), u.Data.start);
            Assert.Equal(n(6), u.Data.end);

            Assert.False(l.match<bool>("system", "1", EngineOptions.F_NONE, u));
            Assert.Equal(MatchResult.npos, u.read().Data.start);

            Assert.True(l.matchOfs<bool>("number_str = '+12'", "str", n(5), EngineOptions.F_NONE, u));
            Assert.Equal(MatchResult.npos, u.read().Data.start);

            Assert.True(l.matchOfs<bool>("number_str = '+12'", "str", n(5), EngineOptions.F_MATCH_RESULT, u));
            u.read();
            Assert.Equal(n(7), u.Data.start);
            Assert.Equal(n(10), u.Data.end);

            Assert.False(l.matchOfs<bool>("number_str = '+12'", "str", n(8), EngineOptions.F_NONE, u));
            Assert.Equal(MatchResult.npos, u.read().Data.start);
        }

        [Fact]
        public void searchTest1()
        {
            using var c = ConariX.Make(new(Library), out dynamic l);
            Assert.False(l.searchEssC<bool>("system", "syStem", false));
            Assert.True(l.searchEssC<bool>("system", "syStem", true));

            Assert.True(l.searchEssC<bool>("number = '12'", "'+'", false));

            Assert.False(l.searchEssC<bool>("123", "4", true));
            Assert.True(l.searchEssC<bool>("123", "2", true));
        }
    }
}
