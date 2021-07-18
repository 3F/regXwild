using net.r_eg.Conari.Types;
using Xunit.Abstractions;
using Xunit.Sdk;

[assembly: Xunit.TestFramework
(
    nameof(dotnetTest) + "." + nameof(dotnetTest._svc) + "." + nameof(dotnetTest._svc.InitTests),
    nameof(dotnetTest)
)]

namespace dotnetTest._svc
{
    public class InitTests: XunitTestFramework
    {
        public InitTests(IMessageSink messageSink)
            : base(messageSink)
        {
#if RXW_UNICODE
            TCharPtr.Unicode = true;
#else
            TCharPtr.Unicode = false;
#endif
        }
    }
}
