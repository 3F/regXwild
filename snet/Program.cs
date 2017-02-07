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
            Console.WriteLine("[ v{0} - SHA-1 {1}] \n", ConariVersion.S_NUM_REV, ConariVersion.BRANCH_SHA1);
#if DEBUG
            Console.WriteLine("\nUse Release cfg.\n\n");

#else

            Analyzer anl = new Analyzer();
            anl.Calc();

            Console.WriteLine("\nDone.");

#endif
            Console.ReadKey();
        }
    }
}
