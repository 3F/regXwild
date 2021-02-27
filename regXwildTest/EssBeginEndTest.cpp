#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\regXwild\regXwild.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace net::r_eg::regXwild;

namespace regXwildTest
{
    namespace regXwild = net::r_eg::regXwild;
    using namespace regXwild::rxwtypes;

    TEST_CLASS(EssBeginEndTest)
    {
    public:

        TEST_METHOD(msBeginTest1)
        {
            tstring data = _T("00123");
            Assert::IsFalse(match(data, _T("^0#2")));
            Assert::IsFalse(match(data, _T("^0##3")));
            Assert::IsFalse(match(data, _T("^01")));
            Assert::IsTrue(match(data, _T("^00#2")));
            Assert::IsFalse(match(data, _T("^012")));
            Assert::IsTrue(match(data, _T("^0012")));
            Assert::IsFalse(match(data, _T("^0021")));

            data = _T("0123");
            Assert::IsFalse(match(data, _T("^0#3")));
            Assert::IsTrue(match(data, _T("^0#2")));
        }

        TEST_METHOD(msBeginTest2)
        {
            tstring data = _T("00123");
            Assert::IsTrue(match(data, _T("^0*2")));
            Assert::IsTrue(match(data, _T("^00*2")));
            Assert::IsTrue(match(data, _T("^001*2")));
            Assert::IsFalse(match(data, _T("^0012*2")));

            Assert::IsTrue(match(data, _T("^0+2")));
            Assert::IsTrue(match(data, _T("^00+2")));
            Assert::IsFalse(match(data, _T("^001+2")));

            Assert::IsFalse(match(data, _T("^0?2")));
            Assert::IsTrue(match(data, _T("^00?2")));
            Assert::IsTrue(match(data, _T("^001?2")));
            Assert::IsFalse(match(data, _T("^0012?2")));
        }

        TEST_METHOD(msBeginTest3)
        {
            tstring data = _T("001234");
            Assert::IsTrue(match(data, _T("^00+?2")));
            Assert::IsTrue(match(data, _T("^00+?3")));
            Assert::IsFalse(match(data, _T("^00+?4")));
            Assert::IsTrue(match(data, _T("^0+?2")));
            Assert::IsFalse(match(data, _T("^0+?3")));

            Assert::IsTrue(match(data, _T("^0#?2")));
            Assert::IsTrue(match(data, _T("^00#?2")));
            Assert::IsFalse(match(data, _T("^001#?2")));
        }

        TEST_METHOD(msBeginTest4)
        {
            tstring data = _T("00123");
            Assert::IsFalse(match(data, _T("^0##3")));
            Assert::IsTrue(match(data, _T("^00##3")));

            Assert::IsTrue(match(data, _T("^0++3")));
            Assert::IsTrue(match(data, _T("^00++3")));
            Assert::IsFalse(match(data, _T("^001++3")));

            Assert::IsTrue(match(data, _T("^0??2")));
            Assert::IsFalse(match(data, _T("^0??3")));

            Assert::IsTrue(match(data, _T("0???2")));
            Assert::IsTrue(match(data, _T("^0???2")));
            Assert::IsTrue(match(data, _T("^0???3")));
        }

        TEST_METHOD(msBeginTest5)
        {
            Assert::IsTrue(rxw.match(_T("00123"), _T("^0>/3"), EssRxW::EngineOptions::F_NONE));
            Assert::IsFalse(rxw.match(_T("00/123"), _T("^0>/3"), EssRxW::EngineOptions::F_NONE));

            Assert::IsFalse(rxw.match(_T("0123"), _T("^1>/3"), EssRxW::EngineOptions::F_NONE));
            Assert::IsFalse(rxw.match(_T("0123"), _T("^0>/0"), EssRxW::EngineOptions::F_NONE));
            Assert::IsTrue(rxw.match(_T("0123"), _T("^0>/1"), EssRxW::EngineOptions::F_NONE));
            Assert::IsFalse(rxw.match(_T("0/123"), _T("^0>/1"), EssRxW::EngineOptions::F_NONE));
        }

        TEST_METHOD(msEndTest1)
        {
            Assert::IsFalse(match(_T("43210"), _T("3#0$")));
            Assert::IsTrue(match(_T("43210"), _T("3#1")));
            Assert::IsFalse(match(_T("43210"), _T("3#1$")));
            Assert::IsTrue(match(_T("43210"), _T("2#0$")));

            tstring data = _T("32100");
            Assert::IsFalse(match(data, _T("2#0$")));
            Assert::IsTrue(match(data, _T("2#00$")));
            Assert::IsTrue(match(data, _T("2##0$")));
            Assert::IsFalse(match(data, _T("10$")));
            Assert::IsFalse(match(data, _T("210$")));
            Assert::IsTrue(match(data, _T("2100$")));
            Assert::IsFalse(match(data, _T("1200$")));
        }

        TEST_METHOD(msEndTest2)
        {
            tstring data = _T("32100");
            Assert::IsFalse(match(data, _T("2*0$")));
            Assert::IsTrue(match(data, _T("2*00$")));
            Assert::IsTrue(match(data, _T("2*100$")));
            Assert::IsFalse(match(data, _T("2*2100$")));

            Assert::IsFalse(match(data, _T("2+0$")));
            Assert::IsTrue(match(data, _T("2+00$")));
            Assert::IsFalse(match(data, _T("2+100$")));

            Assert::IsFalse(match(data, _T("2?0$")));
            Assert::IsTrue(match(data, _T("2?00$")));
            Assert::IsTrue(match(data, _T("2?100$")));
            Assert::IsFalse(match(data, _T("2?2100$")));
        }

        TEST_METHOD(msEndTest3)
        {
            tstring data = _T("32100");
            Assert::IsFalse(match(data, _T("2+?0$"))); // TODO: ? ambiguous; 1-2; 32[10]0->$ and 32[1]->0
            Assert::IsFalse(match(data, _T("2#?0$"))); // TODO: ? ambiguous; 1|2; 32[10]0->$ and 32[1]->0 

            Assert::IsFalse(match(data, _T("3+?0$")));
            Assert::IsTrue(match(data, _T("3+?00$")));
            Assert::IsTrue(match(data, _T("2+?00$")));

            Assert::IsTrue(match(data, _T("2#?00$")));
            Assert::IsFalse(match(data, _T("2#?100$")));
        }

        TEST_METHOD(msEndTest4)
        {
            tstring data = _T("32100");
            
            Assert::IsTrue(match(data, _T("3+++0$")));
            Assert::IsFalse(match(data, _T("3##0$")));
            Assert::IsTrue(match(data, _T("3##00$")));

            Assert::IsFalse(match(data, _T("3++0$"))); // TODO: ? ambiguous; 2+; 3[21]0->$ and 3[210]->0

            Assert::IsTrue(match(data, _T("3++00$")));
            Assert::IsFalse(match(data, _T("3++100$")));

            Assert::IsFalse(match(data, _T("2??0$"))); // TODO: ? ambiguous; 0,1,2; 2[1]0->$ and 2[10]->0
            Assert::IsFalse(match(data, _T("3??0$")));
            Assert::IsFalse(match(data, _T("2???0$"))); // TODO: ? ambiguous; 0,1,2,3; 2[1]0->$ and 2[10]->0
            Assert::IsFalse(match(data, _T("3???0$"))); // TODO: ? ambiguous; 0,1,2,3; 3[21]0->$ and 3[210]->0
        }

        TEST_METHOD(msEndTest5)
        {
            Assert::IsTrue(rxw.match(_T("00123"), _T("0>/3$"), EssRxW::EngineOptions::F_NONE));
            Assert::IsFalse(rxw.match(_T("00/123"), _T("0>/3$"), EssRxW::EngineOptions::F_NONE));

            Assert::IsFalse(rxw.match(_T("0123"), _T("0>/2$"), EssRxW::EngineOptions::F_NONE));
            Assert::IsFalse(rxw.match(_T("0123"), _T("3>/3$"), EssRxW::EngineOptions::F_NONE));
            Assert::IsTrue(rxw.match(_T("0123"), _T("2>/3$"), EssRxW::EngineOptions::F_NONE));
            Assert::IsFalse(rxw.match(_T("012/3"), _T("2>/3$"), EssRxW::EngineOptions::F_NONE));
        }
        
        TEST_METHOD(filterBeginTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            Assert::IsTrue(match(data, _T("^new")));
            Assert::IsTrue(match(data, _T("^new*")));
            Assert::IsTrue(match(data, _T("^new*pro?ection")));
        }

        TEST_METHOD(filterBeginTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // split
            {
                Assert::IsTrue(match(data, _T("notfound|^new*pro?ection")));
                Assert::IsTrue(match(data, _T("notfound|^")));
                Assert::IsTrue(match(data, _T("notfound|^|")));
                Assert::IsTrue(match(data, _T("^|notfound")));
                Assert::IsTrue(match(data, _T("|^|notfound")));

                Assert::IsTrue(match(data, _T(" ^new|notfound|^new")));
                Assert::IsTrue(match(data, _T(" ^new|^new|notfound")));
                Assert::IsTrue(match(data, _T("^new|*^new|notfound")));

                Assert::IsTrue(match(data, _T("^*new*|notfound|^new")));
                Assert::IsTrue(match(data, _T("^*n0ew*|notfound|^new")));
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
                    Assert::IsTrue(match(datam, _T("^*systems")));
                    Assert::IsTrue(match(data, _T("^*new")));
                    Assert::IsTrue(match(data, _T("^**new")));
                }
                // >
                {
                    Assert::IsTrue(match(data, _T("^>new")));
                    Assert::IsTrue(match(data, _T("^>**new")));
                    Assert::IsTrue(match(data, _T("^>>new")));
                    Assert::IsTrue(match(data, _T("^>systems")));
                }

                // ?
                {
                    Assert::IsTrue(match(datam, _T("^?ain")));
                    Assert::IsTrue(match(datam, _T("^?main")));
                }
                // +
                {
                    Assert::IsTrue(match(datam, _T("^+ain")));
                    Assert::IsTrue(match(datam, _T("^+in")));
                }
                // #
                {
                    Assert::IsTrue(match(datam, _T("^#ain")));
                    Assert::IsTrue(match(datam, _T("^##in")));
                }
            }
        }

        TEST_METHOD(filterBeginTest4)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // _^word
            {
                Assert::IsFalse(match(data, _T("systems^")));
                Assert::IsFalse(match(data, _T("*systems^")));
                Assert::IsFalse(match(data, _T("*systems*^")));
                Assert::IsFalse(match(data, _T("*systems* ^")));
                Assert::IsFalse(match(data, _T("*systems* ^ ")));
                Assert::IsFalse(match(data, _T("*systems*^*")));
                Assert::IsFalse(match(data, _T("new^pro?ection")));
                Assert::IsFalse(match(data, _T("pro^ection")));
                Assert::IsFalse(match(data, _T("*^new*pro?ection")));
                Assert::IsFalse(match(data, _T(" *^new*pro?ection")));
                Assert::IsFalse(match(data, _T("* ^new*pro?ection")));
                Assert::IsFalse(match(data, _T(" * ^new*pro?ection")));
                Assert::IsFalse(match(data, _T(" ^new*pro?ection")));
            }
        }

        TEST_METHOD(filterBeginTest5)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // ^_word
            {
                Assert::IsFalse(match(data, _T("^ new*pro?ection")));
                Assert::IsFalse(match(data, _T(" ^ new*pro?ection")));
                Assert::IsFalse(match(data, _T("some^new*pro?ection")));
                Assert::IsFalse(match(data, _T("some ^new*pro?ection")));
                Assert::IsFalse(match(data, _T("some*^new*pro?ection")));
                Assert::IsFalse(match(data, _T("sys*^new*pro?ection")));
            }
        }

        TEST_METHOD(filterBeginTest6)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // split
            {
                Assert::IsFalse(match(data, _T("notfound|^ new")));
                Assert::IsFalse(match(data, _T("notfound| ^new*pro?ection")));
                Assert::IsFalse(match(data, _T("notfound| ^new")));
                Assert::IsFalse(match(data, _T("notfound| ^")));
                Assert::IsFalse(match(data, _T(" ^ |notfound")));
                Assert::IsFalse(match(data, _T("^ |notfound")));
                Assert::IsFalse(match(data, _T(" ^ * |notfound")));
                Assert::IsFalse(match(data, _T(" ^notfound* |notfound|not^*found")));
                Assert::IsFalse(match(data, _T("*systems*^|notfound|systems^")));
                Assert::IsFalse(match(data, _T("*systems*^|notfound")));
                Assert::IsFalse(match(data, _T("*systems*^|notfound|systems0*^")));
            }
        }

        TEST_METHOD(filterBeginTest7)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            Assert::IsFalse(match(data, _T("^^new")));
            Assert::IsFalse(match(data, _T("systems>^")));
            Assert::IsFalse(match(data, _T(">^new")));
            Assert::IsFalse(match(data, _T("sys*^*^new*pro?ection")));
            Assert::IsFalse(match(data, _T("*^*^new*pro?ection")));
            Assert::IsFalse(match(data, _T("*^new")));
            Assert::IsFalse(match(data, _T("+^new")));
            Assert::IsFalse(match(data, _T("#^new")));
            Assert::IsFalse(match(data, _T(" ^new")));
            Assert::IsFalse(match(data, _T("systems>^*")));

            // *
            {
                Assert::IsFalse(match(datam, _T("^*notfound")));
            }
            // >
            {
                Assert::IsFalse(match(datam, _T("^>is")));
            }
        }

        TEST_METHOD(filterBeginTest8)
        {
            tstring data = _T("main systems 1272/is ok");

            // ?
            {
                Assert::IsFalse(match(data, _T("^?in")));
            }
            // *
            {
                Assert::IsTrue(match(data, _T("^*main")));
            }
            // +
            {
                Assert::IsFalse(match(data, _T("^+main")));
            }
            // #
            {
                Assert::IsFalse(match(data, _T("^#main")));
                Assert::IsTrue(match(data, _T("^#ain")));
                Assert::IsFalse(match(data, _T("^##ain")));
                Assert::IsFalse(match(data, _T("^##main")));
            }
        }
        
        TEST_METHOD(filterEndTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // word$
            {
                Assert::IsTrue(match(data, _T("systems$")));
                Assert::IsTrue(match(data, _T("*systems$")));
                Assert::IsTrue(match(data, _T(" * systems$")));
                Assert::IsTrue(match(data, _T("*tems$")));
                Assert::IsTrue(match(data, _T("new*pro?ection*systems$")));
            }
        }

        TEST_METHOD(filterEndTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // ^word$
            {
                Assert::IsTrue(match(data, _T("^new*systems$")));
                Assert::IsTrue(match(datam, _T("^main systems 1272/is ok$")));
                Assert::IsTrue(match(datam, _T("^main*is ok$")));
            }
        }

        TEST_METHOD(filterEndTest3)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // split
            {
                Assert::IsTrue(match(data, _T("dwarf|*tems$")));
                Assert::IsTrue(match(data, _T("dwarf|getting|tems$")));
                Assert::IsTrue(match(datam, _T("^old*is ok$|^main*ok$")));
                Assert::IsTrue(match(datam, _T("^main|*ok$")));
                Assert::IsTrue(match(datam, _T("*ok$|^main")));
                Assert::IsTrue(match(datam, _T("^old*is ok|main*ok$")));
                Assert::IsTrue(match(data, _T("*systems$|notfound")));
                Assert::IsTrue(match(data, _T("systems$|notfound")));
                Assert::IsTrue(match(data, _T("project*systems$|notfound")));
                Assert::IsTrue(match(data, _T("project*systems$|notfound")));
                Assert::IsTrue(match(data, _T("new*project*systems$|notfound")));
                Assert::IsTrue(match(data, _T("systems$ |notfound|systems$")));
                Assert::IsTrue(match(data, _T("systems$ |systems$|notfound")));
                Assert::IsTrue(match(data, _T("systems$|systems$*|notfound")));
                Assert::IsTrue(match(data, _T("*systems*$|notfound|systems$")));
            }
        }

        TEST_METHOD(filterEndTest4)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // MS combination
            {
                // *
                {
                    Assert::IsTrue(match(data, _T("systems*$")));
                    Assert::IsTrue(match(data, _T("systems**$")));
                    Assert::IsTrue(match(datam, _T("main*$")));
                    Assert::IsTrue(match(datam, _T("main**$")));
                    Assert::IsTrue(match(data, _T("systems*$")));
                    Assert::IsTrue(match(data, _T("project*$")));
                    Assert::IsTrue(match(datam, _T("^main*$")));
                    {
                        Assert::IsTrue(match(data, _T("^*new*$")));
                        Assert::IsTrue(match(data, _T("^*$")));
                        Assert::IsTrue(match(data, _T("^*$")));
                        Assert::IsTrue(match(datam, _T("^*1272*$")));
                    }
                }
                // >
                {
                    Assert::IsTrue(match(data, _T("systems>$")));
                    Assert::IsTrue(match(data, _T("systems>*$")));
                    Assert::IsTrue(match(data, _T("various>$")));
                    Assert::IsTrue(match(data, _T("various>*$")));
                    Assert::IsTrue(match(data, _T("various>>$")));
                }

                // ?
                {
                    Assert::IsTrue(match(data, _T("system?$")));
                    Assert::IsTrue(match(data, _T("systems?$")));
                }
                // +
                {
                    Assert::IsTrue(match(data, _T("system+$")));
                    Assert::IsTrue(match(data, _T("syste+$")));
                }
                // #
                {
                    Assert::IsTrue(match(data, _T("system#$")));
                    Assert::IsTrue(match(data, _T("syste##$")));
                }
            }
        }

        TEST_METHOD(filterEndTest5)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            Assert::IsFalse(match(datam, _T("m^a$in")));
            Assert::IsFalse(match(data, _T("notfound$systems")));
            Assert::IsFalse(match(data, _T("systems*new$")));
            Assert::IsFalse(match(data, _T("$*new")));
            Assert::IsFalse(match(data, _T("$new")));
        }

        TEST_METHOD(filterEndTest6)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // ^,$
            {
                Assert::IsFalse(match(datam, _T("^main$")));
                Assert::IsFalse(match(datam, _T("^1272$")));
                Assert::IsFalse(match(data, _T("^ $")));
                Assert::IsFalse(match(datam, _T("$main systems 1272/is ok^")));
                Assert::IsTrue(match(datam, _T("^main systems 1272/is ok$")));
                Assert::IsFalse(match(datam, _T("^$main systems 1272/is ok^$")));
                Assert::IsFalse(match(datam, _T("^$main")));
                Assert::IsFalse(match(datam, _T("^*$$main")));
                Assert::IsFalse(match(data, _T("^new systems$")));
                Assert::IsFalse(match(data, _T("^new^systems$")));
                Assert::IsFalse(match(data, _T("^new*systems$*")));
                Assert::IsFalse(match(datam, _T("^$")));
                Assert::IsFalse(match(datam, _T("$^")));
            }
        }

        TEST_METHOD(filterEndTest7)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // $word
            {
                Assert::IsFalse(match(data, _T("$systems")));
                Assert::IsFalse(match(data, _T("*$systems")));
                Assert::IsFalse(match(data, _T("* $systems")));
                Assert::IsFalse(match(data, _T(" $systems")));
                Assert::IsFalse(match(data, _T(">$systems")));
                Assert::IsFalse(match(data, _T(">$^systems")));
            }
        }

        TEST_METHOD(filterEndTest8)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // word$_
            {
                Assert::IsFalse(match(data, _T("systems$ ")));
                Assert::IsFalse(match(data, _T("systems$*")));
                Assert::IsFalse(match(data, _T("systems$>")));
                Assert::IsFalse(match(data, _T("systems$new")));
                Assert::IsFalse(match(data, _T("systems$notfound")));
                Assert::IsFalse(match(data, _T("systems$*notfound")));
                Assert::IsFalse(match(data, _T("systems$*new")));
                Assert::IsFalse(match(datam, _T("$ |notfound")));
            }
        }

        TEST_METHOD(filterEndTest9)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // word_$
            {
                Assert::IsFalse(match(data, _T("system$s")));
                Assert::IsFalse(match(data, _T("systems $")));

                // MS combination
                {
                    Assert::IsFalse(match(data, _T("systems$$")));
                    Assert::IsFalse(match(data, _T("systems$*")));
                    Assert::IsFalse(match(data, _T("systems$*")));
                    Assert::IsFalse(match(data, _T("systems$>*")));
                    Assert::IsFalse(match(data, _T("notfound*$")));
                    Assert::IsTrue(match(data, _T("systems*$")));
                    Assert::IsTrue(match(data, _T("systems>$")));
                    Assert::IsTrue(match(data, _T("systems>*$")));
                    Assert::IsFalse(match(datam, _T(" $|notfound")));

                    // *
                    {
                        Assert::IsFalse(match(datam, _T("notfound*$")));
                        {
                            Assert::IsFalse(match(data, _T("*systems*$|notfound")));
                            Assert::IsFalse(match(data, _T("*systems*$|notfound|systems0*$")));
                        }
                    }
                    // >
                    {
                        Assert::IsFalse(match(datam, _T("systems>$")));
                        Assert::IsTrue(match(datam, _T("is>$")));
                    }
                }
            }
        }

        TEST_METHOD(filterEndTest10)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // split
            {
                Assert::IsFalse(match(data, _T("*systems$ |notfound")));
                Assert::IsFalse(match(data, _T("systems0$ |notfound")));
                Assert::IsFalse(match(data, _T("*systems$  |notfound")));
                Assert::IsFalse(match(data, _T("*systems$ zero|notfound")));
                Assert::IsFalse(match(data, _T("*systems$*zero|notfound")));
                Assert::IsFalse(match(data, _T("*systems$*zero |notfound")));
                Assert::IsFalse(match(data, _T("project*systems$ |notfound")));

                Assert::IsFalse(match(data, _T("project systems$ |notfound")));
                Assert::IsFalse(match(data, _T("project*systems$  |notfound")));
                Assert::IsFalse(match(data, _T("project*systems$ zero|notfound")));
                Assert::IsFalse(match(data, _T("project*systems$*zero|notfound")));
                Assert::IsFalse(match(data, _T("project*systems$*zero |notfound")));

                Assert::IsFalse(match(data, _T("new*project systems$ |notfound")));
                Assert::IsFalse(match(data, _T("new*project*systems$  |notfound")));
                Assert::IsFalse(match(data, _T("new*project*systems$ zero|notfound")));
                Assert::IsFalse(match(data, _T("new*project*systems$*zero|notfound")));
                Assert::IsFalse(match(data, _T("new*project*systems$*zero |notfound")));

                Assert::IsFalse(match(data, _T("systems$ |notfound")));
                Assert::IsFalse(match(data, _T("systems$ |notfound|systems$ ")));
                Assert::IsFalse(match(data, _T("systems$ |systems$ |notfound")));
                Assert::IsFalse(match(data, _T("systems$*|notfound")));
            }
        }

        TEST_METHOD(filterLengthTest1)
        {
            Assert::IsTrue(match(_T(""), _T("$")));
            Assert::IsTrue(match(_T("s"), _T("$")));
            Assert::IsTrue(match(_T(""), _T("^")));
            Assert::IsTrue(match(_T("s"), _T("^")));
        }

        TEST_METHOD(filterLengthTest2)
        {
            Assert::IsFalse(match(_T("system"), _T("systems$")));
            Assert::IsFalse(match(_T("systems"), _T("system$")));
            Assert::IsTrue(match(_T("s"), _T("s$")));
            Assert::IsFalse(match(_T(""), _T("s$")));
        }

    private:

        EssRxW rxw;

        bool match(const tstring& data, const tstring& filter, bool ignoreCase = true)
        {
            return rxw.match(data, filter, (ignoreCase ? EssRxW::EngineOptions::F_ICASE : EssRxW::EngineOptions::F_NONE) | EssRxW::EngineOptions::F_LEGACY_ANYSP);
        }

    };
}