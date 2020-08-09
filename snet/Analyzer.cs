using System;
using net.r_eg.Conari;
using net.r_eg.Conari.Types;

namespace snet
{
    internal class Analyzer
    {
        protected int iterations;
        protected int average;

        public Analyzer(int iterations = 10000, int average = 4)
        {
            this.iterations = iterations;
            this.average    = average;
        }

        public void Calc()
        {
            string data     = "#//Anime/Kyoto Animation/Clannad TV -/Suzumiya Haruhi/Lucky Star/Full Metal Panic Fumoffu/P.A. Works/Angel Beats!/A-1 Pictures/Ano Hi Mita Hana no Namae wo Bokutachi wa Mada Shira nai/Макото Синкай [2002] Kanojo to kanojo no neko/ Kino no Tabi @ ... World/White Fox/Врата Штайнера (Врата Штейна (Steins Gate))/SHAFT/Maho Shojo Madoka Magica"; //340
            string filter   = "nime**haru*02*Magica";
            
            tryAlgo(data, filter);

            Console.WriteLine(Environment.NewLine);

            tryRegex(data, filter.Replace("*", ".*"));
        }

        public void tryAlgo(string data, string filter)
        {
            using(IConari l = new ConariL("regXwild.dll"))
            {
                Console.Write($"regXwild module: ");

#if RXW_UNICODE
                UnmanagedString.SType sType = UnmanagedString.SType.Unicode;
                Console.WriteLine($"Unicode");
#else
                UnmanagedString.SType sType = UnmanagedString.SType.Ansi;
                Console.WriteLine($"MultiByte");
#endif

                using(var uData = new UnmanagedString(data, sType))
                using(var uFilter = new UnmanagedString(filter, sType))
                {
                    Console.WriteLine($"\niterations({iterations}) x average({average})\n");

                    var alg = new Algorithms();

                    calcAlgo(" regXwild via Conari (Lambda) - ESS version: ", l, uData, uFilter, alg.regXwildEssLambda);
                    calcAlgo(" regXwild via Conari (DLR)- ESS version: ", l, uData, uFilter, alg.regXwildEssDLR);
                    calcAlgo(" regXwild via Conari (Lambda) - EXT version: ", l, uData, uFilter, alg.regXwildExtLambda);
                    calcAlgo(" regXwild via Conari (DLR) - EXT version: ", l, uData, uFilter, alg.regXwildExtDLR);
                }
            }
        }

        public void calcAlgo(string label, IConari l, WCharPtr data, WCharPtr filter, Func<WCharPtr, WCharPtr, IConari, bool> method)
        {
            var meter = new Meter();

            double results = 0;

            meter.start();

            results += meter.delta();

            for(int total = 0; total < average; ++total)
            {
                meter.start();
                for(int i = 0; i < iterations; ++i) {
                    if(method(data, filter, l)) {

                    }
                }
                results += meter.delta();
                Console.Write(".");
            }

            Console.WriteLine($"{label}{ms(results / average)}");
        }

        protected void tryRegex(string data, string filter)
        {
            tryRegex(true, data, filter);
            Console.WriteLine("\n-------\n");
            tryRegex(false, data, filter);
        }

        protected void tryRegex(bool compile, string data, string filter)
        {
            Console.WriteLine($".NET Regex. Compile: {compile} \niterations({iterations}) x average({average})\n");
            Console.WriteLine("Please wait for the result ...\n\n");

            calcRegex(compile, " .NET Regex engine: ", data, filter);
            calcRegex(compile, " .NET Regex engine(only as ^match$ like a simple '=='): ", data, "^" + filter + "$");
        }

        protected void calcRegex(bool compiled, string label, string data, string filter)
        {
            var alg     = new Algorithms();
            var meter   = new Meter();

            double results = 0;

            meter.start();

            alg.regexInitFilter(filter, compiled);

            results += meter.delta();

            for(int total = 0; total < average; ++total)
            {
                meter.start();
                for(int i = 0; i < iterations; ++i) {
                    if(alg.regexMatch(ref data)) {

                    }
                }
                results += meter.delta();
                Console.Write(".");
            }

            Console.WriteLine($"{label}{ms(results / average)}");
        }

        private string ms(double val)
        {
            return (val < 1) ? "< 1ms" : $"~{(int)val}ms";
        }
    }
}
