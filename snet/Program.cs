using System;

namespace snet
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("https://github.com/3F/regXwild \n");
            Console.WriteLine(".NET version via Conari engine \n");
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
