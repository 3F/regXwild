#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\regXwild\regXwild.common.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace net::r_eg::regXwild;


namespace regXwildTest
{
    namespace regXwild = net::r_eg::regXwild;
    using namespace regXwild::rxwtypes;
    using namespace regXwild::common;

    TEST_CLASS(EssBeginEndTest)
    {
    public:

        TEST_METHOD(msBeginTest1)
        {
            tstring data = _T("00123");
            Assert::AreEqual(false, searchEss(data, _T("^0#2")));
            Assert::AreEqual(false, searchEss(data, _T("^0##3")));
            Assert::AreEqual(false, searchEss(data, _T("^01")));
            Assert::AreEqual(true, searchEss(data, _T("^00#2")));
            Assert::AreEqual(false, searchEss(data, _T("^012")));
            Assert::AreEqual(true, searchEss(data, _T("^0012")));
            Assert::AreEqual(false, searchEss(data, _T("^0021")));

            data = _T("0123");
            Assert::AreEqual(false, searchEss(data, _T("^0#3")));
            Assert::AreEqual(true, searchEss(data, _T("^0#2")));
        }

        TEST_METHOD(msBeginTest2)
        {
            tstring data = _T("00123");
            Assert::AreEqual(true, searchEss(data, _T("^0*2")));
            Assert::AreEqual(true, searchEss(data, _T("^00*2")));
            Assert::AreEqual(true, searchEss(data, _T("^001*2")));
            Assert::AreEqual(false, searchEss(data, _T("^0012*2")));

            Assert::AreEqual(true, searchEss(data, _T("^0+2")));
            Assert::AreEqual(true, searchEss(data, _T("^00+2")));
            Assert::AreEqual(false, searchEss(data, _T("^001+2")));

            Assert::AreEqual(false, searchEss(data, _T("^0?2")));
            Assert::AreEqual(true, searchEss(data, _T("^00?2")));
            Assert::AreEqual(true, searchEss(data, _T("^001?2")));
            Assert::AreEqual(false, searchEss(data, _T("^0012?2")));
        }

        TEST_METHOD(msBeginTest3)
        {
            tstring data = _T("001234");
            Assert::AreEqual(true, searchEss(data, _T("^00+?2")));
            Assert::AreEqual(true, searchEss(data, _T("^00+?3")));
            Assert::AreEqual(false, searchEss(data, _T("^00+?4")));
            Assert::AreEqual(true, searchEss(data, _T("^0+?2")));
            Assert::AreEqual(false, searchEss(data, _T("^0+?3")));

            Assert::AreEqual(true, searchEss(data, _T("^0#?2")));
            Assert::AreEqual(true, searchEss(data, _T("^00#?2")));
            Assert::AreEqual(false, searchEss(data, _T("^001#?2")));
        }

        TEST_METHOD(msBeginTest4)
        {
            tstring data = _T("00123");
            Assert::AreEqual(false, searchEss(data, _T("^0##3")));
            Assert::AreEqual(true, searchEss(data, _T("^00##3")));

            Assert::AreEqual(true, searchEss(data, _T("^0++3")));
            Assert::AreEqual(true, searchEss(data, _T("^00++3")));
            Assert::AreEqual(false, searchEss(data, _T("^001++3")));

            Assert::AreEqual(true, searchEss(data, _T("^0??2")));
            Assert::AreEqual(false, searchEss(data, _T("^0??3")));

            Assert::AreEqual(true, searchEss(data, _T("0???2")));
            Assert::AreEqual(true, searchEss(data, _T("^0???2")));
            Assert::AreEqual(true, searchEss(data, _T("^0???3")));
        }

        TEST_METHOD(msBeginTest5)
        {
            Assert::AreEqual(true, rxw.match(_T("00123"), _T("^0>/3"), EssRxW::FlagsRxW::F_NONE));
            Assert::AreEqual(false, rxw.match(_T("00/123"), _T("^0>/3"), EssRxW::FlagsRxW::F_NONE));

            Assert::AreEqual(false, rxw.match(_T("0123"), _T("^1>/3"), EssRxW::FlagsRxW::F_NONE));
            Assert::AreEqual(false, rxw.match(_T("0123"), _T("^0>/0"), EssRxW::FlagsRxW::F_NONE));
            Assert::AreEqual(true, rxw.match(_T("0123"), _T("^0>/1"), EssRxW::FlagsRxW::F_NONE));
            Assert::AreEqual(false, rxw.match(_T("0/123"), _T("^0>/1"), EssRxW::FlagsRxW::F_NONE));
        }

        TEST_METHOD(msEndTest1)
        {
            tstring data = _T("32100");
            Assert::AreEqual(false, searchEss(data, _T("10$")));
            Assert::AreEqual(false, searchEss(data, _T("2#0$"))); //Failed
            Assert::AreEqual(true, searchEss(data, _T("2#00$")));
            Assert::AreEqual(false, searchEss(data, _T("210$")));
            Assert::AreEqual(true, searchEss(data, _T("2100$")));
            Assert::AreEqual(false, searchEss(data, _T("1200$")));
        }

        TEST_METHOD(msEndTest2)
        {
            tstring data = _T("32100");
            Assert::AreEqual(true, searchEss(data, _T("2*0$")));
            Assert::AreEqual(true, searchEss(data, _T("2*00$")));
            Assert::AreEqual(true, searchEss(data, _T("2*100$")));
            Assert::AreEqual(false, searchEss(data, _T("2*2100$"))); //Failed

            Assert::AreEqual(true, searchEss(data, _T("2+0$")));
            Assert::AreEqual(true, searchEss(data, _T("2+00$")));
            Assert::AreEqual(false, searchEss(data, _T("2+100$"))); //Failed

            Assert::AreEqual(false, searchEss(data, _T("2?0$"))); // Failed
            Assert::AreEqual(true, searchEss(data, _T("2?00$")));
            Assert::AreEqual(true, searchEss(data, _T("2?100$")));
            Assert::AreEqual(false, searchEss(data, _T("2?2100$"))); // Failed
        }

        TEST_METHOD(msEndTest3)
        {
            tstring data = _T("32100");
            Assert::AreEqual(true, searchEss(data, _T("2?+0$")));
            Assert::AreEqual(false, searchEss(data, _T("2?+00$"))); // Failed

            Assert::AreEqual(true, searchEss(data, _T("2?#0$")));
            Assert::AreEqual(true, searchEss(data, _T("2?#00$")));
            Assert::AreEqual(false, searchEss(data, _T("2?#100$"))); // Failed
        }

        TEST_METHOD(msEndTest4)
        {
            tstring data = _T("32100");
            Assert::AreEqual(false, searchEss(data, _T("3##0$"))); // Failed
            Assert::AreEqual(true, searchEss(data, _T("3##00$")));

            Assert::AreEqual(true, searchEss(data, _T("3++0$")));
            Assert::AreEqual(true, searchEss(data, _T("3++00$")));
            Assert::AreEqual(false, searchEss(data, _T("3++100$"))); // Failed

            Assert::AreEqual(true, searchEss(data, _T("2??0$")));
            Assert::AreEqual(false, searchEss(data, _T("3??0$"))); // Failed
            Assert::AreEqual(true, searchEss(data, _T("2???0$")));
            Assert::AreEqual(true, searchEss(data, _T("3???0$")));
        }

        TEST_METHOD(msEndTest5)
        {
            Assert::AreEqual(true, rxw.match(_T("00123"), _T("0>/3$"), EssRxW::FlagsRxW::F_NONE));
            Assert::AreEqual(false, rxw.match(_T("00/123"), _T("0>/3$"), EssRxW::FlagsRxW::F_NONE)); // Failed

            Assert::AreEqual(false, rxw.match(_T("0123"), _T("0>/2$"), EssRxW::FlagsRxW::F_NONE));
            Assert::AreEqual(false, rxw.match(_T("0123"), _T("3>/3$"), EssRxW::FlagsRxW::F_NONE)); // Failed
            Assert::AreEqual(true, rxw.match(_T("0123"), _T("2>/3$"), EssRxW::FlagsRxW::F_NONE));
            Assert::AreEqual(false, rxw.match(_T("012/3"), _T("2>/3$"), EssRxW::FlagsRxW::F_NONE)); // Failed
        }
        
        TEST_METHOD(filterBeginTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            Assert::AreEqual(true, searchEss(data, _T("^new")));
            Assert::AreEqual(true, searchEss(data, _T("^new*")));
            Assert::AreEqual(true, searchEss(data, _T("^new*pro?ection")));
        }

        TEST_METHOD(filterBeginTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // split
            {
                Assert::AreEqual(true, searchEss(data, _T("notfound|^new*pro?ection")));
                Assert::AreEqual(true, searchEss(data, _T("notfound|^")));
                Assert::AreEqual(true, searchEss(data, _T("notfound|^|")));
                Assert::AreEqual(true, searchEss(data, _T("^|notfound")));
                Assert::AreEqual(true, searchEss(data, _T("|^|notfound")));

                Assert::AreEqual(true, searchEss(data, _T(" ^new|notfound|^new")));
                Assert::AreEqual(true, searchEss(data, _T(" ^new|^new|notfound")));
                Assert::AreEqual(true, searchEss(data, _T("^new|*^new|notfound")));

                Assert::AreEqual(true, searchEss(data, _T("^*new*|notfound|^new")));
                Assert::AreEqual(true, searchEss(data, _T("^*n0ew*|notfound|^new")));
            }
        }

        TEST_METHOD(filterBeginTest3)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // MS combination
            {
                // *
                {
                    Assert::AreEqual(true, searchEss(datam, _T("^*systems")));
                    Assert::AreEqual(true, searchEss(data, _T("^*new")));
                    Assert::AreEqual(true, searchEss(data, _T("^**new")));
                }
                // >
                {
                    Assert::AreEqual(true, searchEss(data, _T("^>new")));
                    Assert::AreEqual(true, searchEss(data, _T("^>**new")));
                    Assert::AreEqual(true, searchEss(data, _T("^>>new")));
                    Assert::AreEqual(true, searchEss(data, _T("^>systems")));
                }

                //TODO: implement ?,+,# and combination
                {
                    //// ?
                    //{
                    //    Assert::AreEqual(true, searchEss(datam, _T("^?ain")));
                    //    Assert::AreEqual(true, searchEss(datam, _T("^?main")));
                    //}
                    //// +
                    //{
                    //    Assert::AreEqual(true, searchEss(datam, _T("^+ain")));
                    //    Assert::AreEqual(true, searchEss(datam, _T("^+in")));
                    //}
                    //// #
                    //{
                    //    Assert::AreEqual(true, searchEss(datam, _T("^#ain")));
                    //    Assert::AreEqual(true, searchEss(datam, _T("^##in")));
                    //}
                }
            }
        }

        TEST_METHOD(filterBeginTest4)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // _^word
            {
                Assert::AreEqual(false, searchEss(data, _T("systems^")));
                Assert::AreEqual(false, searchEss(data, _T("*systems^")));
                Assert::AreEqual(false, searchEss(data, _T("*systems*^")));
                Assert::AreEqual(false, searchEss(data, _T("*systems* ^")));
                Assert::AreEqual(false, searchEss(data, _T("*systems* ^ ")));
                Assert::AreEqual(false, searchEss(data, _T("*systems*^*")));
                Assert::AreEqual(false, searchEss(data, _T("new^pro?ection")));
                Assert::AreEqual(false, searchEss(data, _T("pro^ection")));
                Assert::AreEqual(false, searchEss(data, _T("*^new*pro?ection")));
                Assert::AreEqual(false, searchEss(data, _T(" *^new*pro?ection")));
                Assert::AreEqual(false, searchEss(data, _T("* ^new*pro?ection")));
                Assert::AreEqual(false, searchEss(data, _T(" * ^new*pro?ection")));
                Assert::AreEqual(false, searchEss(data, _T(" ^new*pro?ection")));
            }
        }

        TEST_METHOD(filterBeginTest5)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // ^_word
            {
                Assert::AreEqual(false, searchEss(data, _T("^ new*pro?ection")));
                Assert::AreEqual(false, searchEss(data, _T(" ^ new*pro?ection")));
                Assert::AreEqual(false, searchEss(data, _T("some^new*pro?ection")));
                Assert::AreEqual(false, searchEss(data, _T("some ^new*pro?ection")));
                Assert::AreEqual(false, searchEss(data, _T("some*^new*pro?ection")));
                Assert::AreEqual(false, searchEss(data, _T("sys*^new*pro?ection")));
            }
        }

        TEST_METHOD(filterBeginTest6)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // split
            {
                Assert::AreEqual(false, searchEss(data, _T("notfound|^ new")));
                Assert::AreEqual(false, searchEss(data, _T("notfound| ^new*pro?ection")));
                Assert::AreEqual(false, searchEss(data, _T("notfound| ^new")));
                Assert::AreEqual(false, searchEss(data, _T("notfound| ^")));
                Assert::AreEqual(false, searchEss(data, _T(" ^ |notfound")));
                Assert::AreEqual(false, searchEss(data, _T("^ |notfound")));
                Assert::AreEqual(false, searchEss(data, _T(" ^ * |notfound")));
                Assert::AreEqual(false, searchEss(data, _T(" ^notfound* |notfound|not^*found")));
                Assert::AreEqual(false, searchEss(data, _T("*systems*^|notfound|systems^")));
                Assert::AreEqual(false, searchEss(data, _T("*systems*^|notfound")));
                Assert::AreEqual(false, searchEss(data, _T("*systems*^|notfound|systems0*^")));
            }
        }

        TEST_METHOD(filterBeginTest7)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // MS combination
            {
                Assert::AreEqual(false, searchEss(data, _T("^^new")));
                Assert::AreEqual(false, searchEss(data, _T("systems>^")));
                Assert::AreEqual(false, searchEss(data, _T(">^new")));
                Assert::AreEqual(false, searchEss(data, _T("sys*^*^new*pro?ection")));
                Assert::AreEqual(false, searchEss(data, _T("*^*^new*pro?ection")));
                Assert::AreEqual(false, searchEss(data, _T("*^new")));
                Assert::AreEqual(false, searchEss(data, _T("systems>^*")));

                // *
                {
                    Assert::AreEqual(false, searchEss(datam, _T("^*notfound")));
                }
                // >
                {
                    Assert::AreEqual(false, searchEss(datam, _T("^>is")));
                }

                //TODO: implement ?,+,# and combination
                {
                    //// ?
                    //{
                    //    Assert::AreEqual(false, searchEss(datam, _T("^?in")));
                    //}
                    //// +
                    //{
                    //    Assert::AreEqual(false, searchEss(datam, _T("^+main")));
                    //}
                    //// #
                    //{
                    //    Assert::AreEqual(false, searchEss(datam, _T("^#main")));
                    //    Assert::AreEqual(false, searchEss(datam, _T("^##ain")));
                    //    Assert::AreEqual(false, searchEss(datam, _T("^##main")));
                    //}
                }
            }
        }
        
        TEST_METHOD(filterEndTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // word$
            {
                Assert::AreEqual(true, searchEss(data, _T("systems$")));
                Assert::AreEqual(true, searchEss(data, _T("*systems$")));
                Assert::AreEqual(true, searchEss(data, _T(" * systems$")));
                Assert::AreEqual(true, searchEss(data, _T("*tems$")));
                Assert::AreEqual(true, searchEss(data, _T("new*pro?ection*systems$")));
            }
        }

        TEST_METHOD(filterEndTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // ^word$
            {
                Assert::AreEqual(true, searchEss(data, _T("^new*systems$")));
                Assert::AreEqual(true, searchEss(datam, _T("^main systems 1272/is ok$")));
                Assert::AreEqual(true, searchEss(datam, _T("^main*is ok$")));

            }
        }

        TEST_METHOD(filterEndTest3)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // split
            {
                Assert::AreEqual(true, searchEss(data, _T("dwarf|*tems$")));
                Assert::AreEqual(true, searchEss(data, _T("dwarf|getting|tems$")));
                Assert::AreEqual(true, searchEss(datam, _T("^old*is ok$|^main*ok$")));
                Assert::AreEqual(true, searchEss(datam, _T("^main|*ok$")));
                Assert::AreEqual(true, searchEss(datam, _T("*ok$|^main")));
                Assert::AreEqual(true, searchEss(datam, _T("^old*is ok|main*ok$")));
                Assert::AreEqual(true, searchEss(data, _T("*systems$|notfound")));
                Assert::AreEqual(true, searchEss(data, _T("systems$|notfound")));
                Assert::AreEqual(true, searchEss(data, _T("project*systems$|notfound")));
                Assert::AreEqual(true, searchEss(data, _T("project*systems$|notfound")));
                Assert::AreEqual(true, searchEss(data, _T("new*project*systems$|notfound")));
                Assert::AreEqual(true, searchEss(data, _T("systems$ |notfound|systems$")));
                Assert::AreEqual(true, searchEss(data, _T("systems$ |systems$|notfound")));
                Assert::AreEqual(true, searchEss(data, _T("systems$|systems$*|notfound")));
                Assert::AreEqual(true, searchEss(data, _T("*systems*$|notfound|systems$")));
            }
        }

        TEST_METHOD(filterEndTest4)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // MS combination
            {
                //TODO: implement *,>,?,+,# and combination
                {
                    //// *
                    //{
                    //    Assert::AreEqual(true, searchEss(data, _T("systems*$")));
                    //    Assert::AreEqual(true, searchEss(data, _T("systems**$")));
                    //    Assert::AreEqual(true, searchEss(datam, _T("main*$")));
                    //    Assert::AreEqual(true, searchEss(datam, _T("main**$")));
                    //    Assert::AreEqual(true, searchEss(data, _T("systems*$")));
                    //    Assert::AreEqual(true, searchEss(data, _T("project*$")));
                    //    Assert::AreEqual(true, searchEss(datam, _T("^main*$")));
                    //    {
                    //        Assert::AreEqual(true, searchEss(data, _T("^*new*$")));
                    //        Assert::AreEqual(true, searchEss(data, _T("^*$")));
                    //        Assert::AreEqual(true, searchEss(data, _T("^*$")));
                    //        Assert::AreEqual(true, searchEss(datam, _T("^*1272*$")));
                    //    }
                    //}
                    //// >
                    //{
                    //    Assert::AreEqual(true, searchEss(data, _T("systems>$")));
                    //    Assert::AreEqual(true, searchEss(data, _T("systems>*$")));
                    //    Assert::AreEqual(true, searchEss(data, _T("various>$")));
                    //    Assert::AreEqual(true, searchEss(data, _T("various>*$")));
                    //    Assert::AreEqual(true, searchEss(data, _T("various>>$")));
                    //}

                    //// ?
                    //{
                    //    Assert::AreEqual(true, searchEss(data, _T("system?$")));
                    //    Assert::AreEqual(true, searchEss(data, _T("systems?$")));
                    //}
                    //// +
                    //{
                    //    Assert::AreEqual(true, searchEss(data, _T("system+$")));
                    //    Assert::AreEqual(true, searchEss(data, _T("syste+$")));
                    //}
                    //// #
                    //{
                    //    Assert::AreEqual(true, searchEss(data, _T("system#$")));
                    //    Assert::AreEqual(true, searchEss(data, _T("syste##$")));
                    //}
                }
            }
        }

        TEST_METHOD(filterEndTest5)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            Assert::AreEqual(false, searchEss(datam, _T("m^a$in")));
            Assert::AreEqual(false, searchEss(data, _T("notfound$systems")));
            Assert::AreEqual(false, searchEss(data, _T("systems*new$")));
            Assert::AreEqual(false, searchEss(data, _T("$*new")));
            Assert::AreEqual(false, searchEss(data, _T("$new")));
        }

        TEST_METHOD(filterEndTest6)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // ^,$
            {
                Assert::AreEqual(false, searchEss(datam, _T("^main$")));
                Assert::AreEqual(false, searchEss(datam, _T("^1272$")));
                Assert::AreEqual(false, searchEss(data, _T("^ $")));
                Assert::AreEqual(false, searchEss(datam, _T("$main systems 1272/is ok^")));
                Assert::AreEqual(true, searchEss(datam, _T("^main systems 1272/is ok$")));
                Assert::AreEqual(false, searchEss(datam, _T("^$main systems 1272/is ok^$")));
                Assert::AreEqual(false, searchEss(datam, _T("^$main")));
                Assert::AreEqual(false, searchEss(datam, _T("^*$$main")));
                Assert::AreEqual(false, searchEss(data, _T("^new systems$")));
                Assert::AreEqual(false, searchEss(data, _T("^new^systems$")));
                Assert::AreEqual(false, searchEss(data, _T("^new*systems$*")));
                Assert::AreEqual(false, searchEss(datam, _T("^$")));
                Assert::AreEqual(false, searchEss(datam, _T("$^")));
            }
        }

        TEST_METHOD(filterEndTest7)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // $word
            {
                Assert::AreEqual(false, searchEss(data, _T("$systems")));
                Assert::AreEqual(false, searchEss(data, _T("*$systems")));
                Assert::AreEqual(false, searchEss(data, _T("* $systems")));
                Assert::AreEqual(false, searchEss(data, _T(" $systems")));
                Assert::AreEqual(false, searchEss(data, _T(">$systems")));
                Assert::AreEqual(false, searchEss(data, _T(">$^systems")));
            }
        }

        TEST_METHOD(filterEndTest8)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // word$_
            {
                Assert::AreEqual(false, searchEss(data, _T("systems$ ")));
                Assert::AreEqual(false, searchEss(data, _T("systems$*")));
                Assert::AreEqual(false, searchEss(data, _T("systems$>")));
                Assert::AreEqual(false, searchEss(data, _T("systems$new")));
                Assert::AreEqual(false, searchEss(data, _T("systems$notfound")));
                Assert::AreEqual(false, searchEss(data, _T("systems$*notfound")));
                Assert::AreEqual(false, searchEss(data, _T("systems$*new")));
                Assert::AreEqual(false, searchEss(datam, _T("$ |notfound")));
            }
        }

        TEST_METHOD(filterEndTest9)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // word_$
            {
                Assert::AreEqual(false, searchEss(data, _T("system$s")));
                Assert::AreEqual(false, searchEss(data, _T("systems $")));

                // MS combination
                {
                    Assert::AreEqual(false, searchEss(data, _T("systems$$")));
                    Assert::AreEqual(false, searchEss(data, _T("systems$*")));
                    Assert::AreEqual(false, searchEss(data, _T("systems$*")));
                    Assert::AreEqual(false, searchEss(data, _T("systems$>*")));
                    Assert::AreEqual(false, searchEss(data, _T("notfound*$")));
                    Assert::AreEqual(false, searchEss(data, _T("systems*$")));
                    Assert::AreEqual(false, searchEss(data, _T("systems>$")));
                    Assert::AreEqual(false, searchEss(data, _T("systems>*$")));
                    Assert::AreEqual(false, searchEss(datam, _T(" $|notfound")));

                    // *
                    {
                        Assert::AreEqual(false, searchEss(datam, _T("notfound*$")));
                        {
                            Assert::AreEqual(false, searchEss(data, _T("*systems*$|notfound")));
                            Assert::AreEqual(false, searchEss(data, _T("*systems*$|notfound|systems0*$")));
                        }
                    }
                    // >
                    {
                        Assert::AreEqual(false, searchEss(datam, _T("systems>$")));
                    }

                    //TODO: implement ?,+,# and combination
                    {
                        //// ?
                        //{
                        //    Assert::AreEqual(false, searchEss(data, _T("syste?$")));
                        //}
                        //// +
                        //{
                        //    Assert::AreEqual(false, searchEss(data, _T("systems+$")));
                        //}
                        //// #
                        //{
                        //    Assert::AreEqual(false, searchEss(data, _T("systems#$")));
                        //    Assert::AreEqual(false, searchEss(data, _T("system##$")));
                        //    Assert::AreEqual(false, searchEss(data, _T("systems##$")));
                        //}
                    }
                }
            }
        }

        TEST_METHOD(filterEndTest10)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // split
            {
                Assert::AreEqual(false, searchEss(data, _T("*systems$ |notfound")));
                Assert::AreEqual(false, searchEss(data, _T("systems0$ |notfound")));
                Assert::AreEqual(false, searchEss(data, _T("*systems$  |notfound")));
                Assert::AreEqual(false, searchEss(data, _T("*systems$ zero|notfound")));
                Assert::AreEqual(false, searchEss(data, _T("*systems$*zero|notfound")));
                Assert::AreEqual(false, searchEss(data, _T("*systems$*zero |notfound")));
                Assert::AreEqual(false, searchEss(data, _T("project*systems$ |notfound")));

                Assert::AreEqual(false, searchEss(data, _T("project systems$ |notfound")));
                Assert::AreEqual(false, searchEss(data, _T("project*systems$  |notfound")));
                Assert::AreEqual(false, searchEss(data, _T("project*systems$ zero|notfound")));
                Assert::AreEqual(false, searchEss(data, _T("project*systems$*zero|notfound")));
                Assert::AreEqual(false, searchEss(data, _T("project*systems$*zero |notfound")));

                Assert::AreEqual(false, searchEss(data, _T("new*project systems$ |notfound")));
                Assert::AreEqual(false, searchEss(data, _T("new*project*systems$  |notfound")));
                Assert::AreEqual(false, searchEss(data, _T("new*project*systems$ zero|notfound")));
                Assert::AreEqual(false, searchEss(data, _T("new*project*systems$*zero|notfound")));
                Assert::AreEqual(false, searchEss(data, _T("new*project*systems$*zero |notfound")));

                Assert::AreEqual(false, searchEss(data, _T("systems$ |notfound")));
                Assert::AreEqual(false, searchEss(data, _T("systems$ |notfound|systems$ ")));
                Assert::AreEqual(false, searchEss(data, _T("systems$ |systems$ |notfound")));
                Assert::AreEqual(false, searchEss(data, _T("systems$*|notfound")));
            }
        }

        TEST_METHOD(filterEndTest11)
        {
            // test of filter length
            {
                Assert::AreEqual(false, searchEss(_T("system"), _T("systems$")));
                Assert::AreEqual(false, searchEss(_T("systems"), _T("system$")));
                Assert::AreEqual(true, searchEss(_T("s"), _T("s$")));
                Assert::AreEqual(false, searchEss(_T(""), _T("s$")));

                //Assert::AreEqual(false, searchEss(_T("s"), _T("$")));
                //Assert::AreEqual(false, searchEss(_T(""), _T("$")));
            }
        }

    private:

        EssRxW rxw;

        bool searchEss(const tstring& data, const tstring& filter, bool ignoreCase = true)
        {
            return regXwild::common::searchEss(data, filter, ignoreCase);
        }

    };
}