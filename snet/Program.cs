using System;
using net.r_eg.Conari;

namespace snet
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("\n https://github.com/3F/regXwild \n");

            Console.WriteLine(".NET version via Conari engine - github.com/3F/Conari");
            Console.WriteLine($"Used Conari version: {ConariVersion.S_NUM_REV}+{ConariVersion.BRANCH_SHA1}\n");
#if DEBUG
            Console.WriteLine("\nPlease compile it first for the `Release` configuration.\n\n");

#else

            Analyzer anl = new Analyzer();
            anl.Calc();

            Console.WriteLine("\nDone.");

#endif
            Console.ReadKey();
        }
    }
}
