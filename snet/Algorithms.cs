using System;
using System.Text.RegularExpressions;
using net.r_eg.Conari;
using net.r_eg.Conari.Types;

namespace snet
{
    internal class Algorithms
    {
        protected Regex filter;

        public bool regXwildEssLambda(WCharPtr data, WCharPtr filter, IConari l)
        {
            return l.bind<Func<WCharPtr, WCharPtr, bool, bool>>("searchEssC")(data, filter, true);
        }

        public bool regXwildEssDLR(WCharPtr data, WCharPtr filter, IConari l)
        {
            return l.DLR.searchEssC<bool>(data, filter, true);
        }

        public bool regXwildExtLambda(WCharPtr data, WCharPtr filter, IConari l)
        {
            return l.bind<Func<WCharPtr, WCharPtr, bool, bool>>("searchExtC")(data, filter, true);
        }

        public bool regXwildExtDLR(WCharPtr data, WCharPtr filter, IConari l)
        {
            return l.DLR.searchExtC<bool>(data, filter, true);
        }

        public bool regexMatch(ref string data)
        {
            return filter.IsMatch(data);
        }

        public void regexInitFilter(string filter, bool compiled)
        {
            RegexOptions flags = RegexOptions.IgnoreCase;
            if(compiled) {
                flags |= RegexOptions.Compiled;
            }

            this.filter = new Regex(filter, flags);
        }
    }
}
