using System;

namespace snet
{
    internal class Meter
    {
        private DateTime started;

        public void start()
        {
            started = DateTime.Now;
        }

        public double delta()
        {
            return (DateTime.Now - started).TotalMilliseconds;
        }
    }
}
