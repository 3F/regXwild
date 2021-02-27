#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\regXwild\regXwild.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace net::r_eg::regXwild;

namespace regXwildTest
{
    namespace regXwild = net::r_eg::regXwild;
    using namespace regXwild::rxwtypes;

    TEST_CLASS(EssMixedTest)
    {
    public:

        TEST_METHOD(caseSensitiveTest1)
        {
            EssRxW::EngineOptions opt = EssRxW::EngineOptions::F_NONE;

            Assert::IsFalse(rxw.match(_T("system"), _T("syStem"), opt));
            Assert::IsTrue(rxw.match(_T("system"), _T("system"), opt));
            Assert::IsFalse(rxw.match(_T("syStem"), _T("system"), opt));
            Assert::IsTrue(rxw.match(_T("SYSTEM"), _T("SYSTEM"), opt));

            Assert::IsFalse(rxw.match(_T("system"), _T("sy*Stem"), opt));
            Assert::IsFalse(rxw.match(_T("system"), _T("syS*tem"), opt));
            Assert::IsTrue(rxw.match(_T("system"), _T("sy*stem"), opt));
        }

        TEST_METHOD(underscoreTest1)
        {
            tstring data = _T("TV_[11_of_24]");

            Assert::IsTrue(match(data, _T("1#_of")));
            Assert::IsTrue(match(data, _T("#1_of")));
            Assert::IsTrue(match(data, _T("1_of")));
            Assert::IsTrue(match(data, _T("[1#_o*24")));
            Assert::IsFalse(match(data, _T("[1##_o*24")));
            Assert::IsFalse(match(data, _T("[1###_o*24")));
            Assert::IsFalse(match(data, _T("[1###_o")));
            Assert::IsFalse(match(data, _T("[1###_of")));
            Assert::IsTrue(match(data, _T("[1#_of")));
            Assert::IsFalse(match(data, _T("[1__of")));
            Assert::IsTrue(match(data, _T("1_of")));
            Assert::IsTrue(match(data, _T("[1??_of")));
            Assert::IsTrue(match(data, _T("[1???_of")));
            Assert::IsTrue(match(data, _T("[1+_of")));
            Assert::IsFalse(match(data, _T("[1++_of")));
            Assert::IsFalse(match(data, _T("[1+++_of")));
        }

        TEST_METHOD(underscoreTest2)
        {
            tstring data = _T("TV_[11_of_24]");

            Assert::IsFalse(match(data, _T("1####4")));
            Assert::IsTrue(match(data, _T("1#####4")));
            Assert::IsTrue(match(data, _T("1######4")));
            Assert::IsFalse(match(data, _T("f####4")));
            Assert::IsFalse(match(data, _T("f###4")));
            Assert::IsTrue(match(data, _T("f##4")));
            Assert::IsFalse(match(data, _T("1#######_of")));
            Assert::IsFalse(match(data, _T("1###############_of")));
            Assert::IsFalse(match(data, _T("1###############f")));
            Assert::IsFalse(match(data, _T("1###############_f")));
            Assert::IsFalse(match(data, _T("1###############_o")));
            Assert::IsFalse(match(data, _T("[1####_of")));
            Assert::IsFalse(match(data, _T("[1####of")));
            Assert::IsFalse(match(data, _T("[1###of")));
            Assert::IsTrue(match(data, _T("[1##of")));
        }
        
        TEST_METHOD(filterAnyTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

            Assert::IsTrue(match(data, _T("protection of various")));      // __ __ __
            Assert::IsTrue(match(data, _T("pro*system")));                 // __ * __
            Assert::IsTrue(match(data, _T("*pro*system*")));               // * __ * __ *
            Assert::IsTrue(match(data, _T("project**various")));           // __ ** __
            Assert::IsTrue(match(data, _T("new*7*systems")));              // __ * __ * __
            Assert::IsTrue(match(data, _T("")));                           // empty

            Assert::IsTrue(match(data, _T("*")));
            Assert::IsTrue(match(data, _T("***")));
            Assert::IsTrue(match(_T("new str"), _T("new str")));
            Assert::IsTrue(match(_T(""), _T("")));
        }

        TEST_METHOD(filterAnyTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

            Assert::IsFalse(match(data, _T("project 12 and")));            // __ _x_ __
            Assert::IsFalse(match(data, _T("new*express")));               // __ * _x_
            Assert::IsFalse(match(data, _T("tes*ting*project")));          // __ * _x_ * __
            Assert::IsFalse(match(data, _T("testing*project*and")));       // _x_ * __ * __
            Assert::IsFalse(match(data, _T("now*is*completely")));         // _x_ * _x_ * _x_
            Assert::IsFalse(match(data, _T("protection*project*new")));    // backwards __ * __ * __
            Assert::IsFalse(match(data, _T("**open**close")));             // ** _x_ ** _x_
        }

        TEST_METHOD(filterSplitTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

            Assert::IsTrue(match(data, _T("protection of|new tes")));       // __ __ | __ __
            Assert::IsTrue(match(data, _T("some project|of various")));     // _x_ __ | __ __
            Assert::IsTrue(match(data, _T("various systems|new 237")));     // __ __ | __ _x_
            Assert::IsTrue(match(data, _T("pro*12|new*system")));           // __ * __ | __ *__
            Assert::IsTrue(match(data, _T("ject*new|pro*tems")));           // __ * _x_ | __ * __
            Assert::IsTrue(match(data, _T("pro*tems|seems*and")));          // __ * __ | _x_ * __
            Assert::IsTrue(match(data, _T("project*|new")));                // __ *| __
            Assert::IsTrue(match(data, _T("various*|zeep")));               // __ * | _x_
            Assert::IsTrue(match(data, _T("goo*|systems")));                // _x_ * | __
            Assert::IsTrue(match(data, _T("project||protect")));            // __ || __
            Assert::IsTrue(match(data, _T("|new||and|")));                  // | __ || __ |
            Assert::IsTrue(match(data, _T("|fail|system")));                // | _x_ | __
            Assert::IsTrue(match(data, _T("|12||true||")));                 // | __ || _x_ ||
            Assert::IsTrue(match(data, _T("above|new|with")));              // _x_ | __ | _x_
            Assert::IsTrue(match(data, _T("project**|new")));               // __ **| __
            Assert::IsTrue(match(data, _T("zoom|*pro")));                   // _x_ | * __
            Assert::IsTrue(match(data, _T("zoom|*pro**")));                 // _x_ | *__ **
            Assert::IsTrue(match(data, _T("||")));                          //empty
            Assert::IsTrue(match(data, _T("")));                            //empty
            Assert::IsTrue(match(data, _T("||zoom||out||")));               // ||_x_ || _x_ ||
            Assert::IsTrue(match(data, _T("|*|")));                         // |*|
            Assert::IsTrue(match(data, _T("|long-term")));                  // | _x_
            Assert::IsTrue(match(data, _T("long-term|")));                  // _x_ |
            Assert::IsTrue(match(data, _T("*|*")));                         // *|*
            Assert::IsTrue(match(data, _T("*|")));                          // *|
            Assert::IsTrue(match(data, _T("|*")));                          // |*
            Assert::IsTrue(match(data, _T("seems|open*and*star|*system"))); // _x_ | _x_ * __ * _x_ | * __
        }

        TEST_METHOD(filterSplitTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

            Assert::IsFalse(match(data, _T("above|fails|with")));           // _x_ | _x_ | _x_
            Assert::IsFalse(match(data, _T("let*proj|project*deep")));      // _x_ * __ | __ * _x_
            Assert::IsFalse(match(data, _T("operator*|*zeep")));            // _x_ *|* _x_
            Assert::IsFalse(match(data, _T("some project|let*various")));   // _x_ __ | _x_* __
            Assert::IsFalse(match(data, _T("some project|various*zoom")));  // _x_ __ | __ * _x_
            Assert::IsFalse(match(data, _T("be|pen*and*star|*my*system"))); // _x_ | _x_ * __ * _x_ | * _x_ * __
        }

        TEST_METHOD(filterOneTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            Assert::IsTrue(match(data, _T("?")));
            Assert::IsTrue(match(data, _T("????")));

            Assert::IsTrue(match(data, _T("new*pro?ection")));                 // __ * [pro]ject ... [pro]t[ection]
            Assert::IsTrue(match(data, _T("????")));
            Assert::IsTrue(match(data, _T("project?12")));
            Assert::IsTrue(match(data, _T("systems?")));
            Assert::IsTrue(match(data, _T("????new")));
            Assert::IsTrue(match(data, _T("systems????")));
            Assert::IsTrue(match(data, _T("???systems????")));
            Assert::IsTrue(match(data, _T("pro????ion")));                     // {0,4}: min: proion, max: protection
            Assert::IsTrue(match(data, _T("protection????????????system")));
            Assert::IsTrue(match(data, _T("protection?????????????system")));
            Assert::IsTrue(match(data, _T("protection??????????????system")));
            Assert::IsTrue(match(data, _T("pro??????????ion")));
            Assert::IsTrue(match(_T("system-17 fee"), _T("system?17")));
        }

        TEST_METHOD(filterOneTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            Assert::IsTrue(match(_T("system17"), _T("system?17")));                 // == 0{2}
            Assert::IsTrue(match(_T("str1 project-12 str2"), _T("project?12")));    // == 1
            Assert::IsTrue(match(_T("str1 project-12 str2"), _T("str?1")));         // == 0
        }

        TEST_METHOD(filterOneTest3)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // MS combination

            Assert::IsTrue(match(data, _T("?*??*")));
            Assert::IsTrue(match(data, _T("new?*systems")));
            Assert::IsTrue(match(data, _T("new*?*systems")));
            Assert::IsTrue(match(data, _T("new*??*systems")));
            Assert::IsTrue(match(data, _T("new*??*systems?")));
        }

        TEST_METHOD(filterOneTest4)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // MS combination

            Assert::IsTrue(match(data, _T("?*??*")));
            Assert::IsTrue(match(data, _T("new?*systems")));
            Assert::IsTrue(match(data, _T("new*?*systems")));
            Assert::IsTrue(match(data, _T("new*??*systems")));
            Assert::IsTrue(match(data, _T("new*??*systems?")));
        }

        TEST_METHOD(filterOneTest5)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            Assert::IsFalse(match(data, _T("?pro?12?|seems?7")));
            Assert::IsFalse(match(_T("system, installments range from 2 to 17"), _T("system?17")));
            Assert::IsFalse(match(_T("system_-17 fee also"), _T("system?17")));
            Assert::IsFalse(match(_T("project"), _T("pro?tect")));
            Assert::IsFalse(match(_T("project"), _T("fro?ject")));
            {
                Assert::IsFalse(match(_T("str1 project--12 str2"), _T("project?12")));  // > 1
            }
        }

        TEST_METHOD(filterOneTest6)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // MS combination
            {
                Assert::IsFalse(match(data, _T("*new?systems*")));
                Assert::IsFalse(match(data, _T("*?new?sys?*?ms*")));
            }
        }

        TEST_METHOD(filterAnySPTest1)
        {
            Assert::IsTrue(match(_T("/new/user_myhid_test.bzip2"), _T("myhid>bzip")));   // __...___
            Assert::IsTrue(match(_T("/new/user_myhid_test.bzip2"), _T("myhid>")));       // __...EOL
            Assert::IsTrue(match(_T("/new/user_myhid"), _T("myhid>")));                  // __EOL
        }

        TEST_METHOD(filterAnySPTest2)
        {
            Assert::IsTrue(match(_T("/new/user_myhid"), _T("myhid>*")));
            Assert::IsTrue(match(_T("/new/user_myhid"), _T("myhid>***")));
            Assert::IsTrue(match(_T("/new/user_myhid"), _T("myhid>?")));
            Assert::IsTrue(match(_T("/new/user_myhid"), _T("myhid>?*")));
        }

        TEST_METHOD(filterAnySPTest3)
        {
            Assert::IsFalse(match(_T("/new/user_myhid_t/est.bzip2"), _T("myhid>bzip")));     // __.../...__
            Assert::IsFalse(match(_T("/new/user_myhid/_test.bzip2"), _T("myhid>bzip")));     // __/...__
            Assert::IsFalse(match(_T("/new/user_myhid_test./bzip2"), _T("myhid>bzip")));     // __.../__
            Assert::IsFalse(match(_T("/new/user_myhid_te/st.bzip2"), _T("myhid>")));         // __.../...EOL
            Assert::IsFalse(match(_T("/new/user_myhid_te/"), _T("myhid>")));                 // __.../EOL
        }

        TEST_METHOD(filterAnySPTest4)
        {
            Assert::IsFalse(match(_T("/new/user_myhid_s/df.txt"), _T("myhid>*")));
            Assert::IsFalse(match(_T("/new/user_myhid_s/df.txt"), _T("myhid>***")));
            Assert::IsFalse(match(_T("/new/user_myhid_s/df.txt"), _T("myhid>?")));
            Assert::IsFalse(match(_T("/new/user_myhid_s/df.txt"), _T("myhid>?*")));
            //-
            Assert::IsFalse(match(_T("/new/user_myhid_s/df.txt"), _T("myhid>*txt")));
            Assert::IsFalse(match(_T("/new/user_myhid_s/df.txt"), _T("myhid>***txt")));
            Assert::IsFalse(match(_T("/new/user_myhid_s/df.txt"), _T("myhid>?txt")));
            Assert::IsFalse(match(_T("/new/user_myhid_s/df.txt"), _T("myhid>?*??txt")));
            //-
            Assert::IsFalse(match(_T("/new/user_myhid"), _T("myhid>*txt")));
            Assert::IsFalse(match(_T("/new/user_myhid"), _T("myhid>***txt")));
            Assert::IsFalse(match(_T("/new/user_myhid"), _T("myhid>?txt")));
            Assert::IsFalse(match(_T("/new/user_myhid"), _T("myhid>?*??txt")));
        }

        TEST_METHOD(filterSingleTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            Assert::IsTrue(match(data, _T("#")));
            Assert::IsTrue(match(data, _T("####")));

            Assert::IsTrue(match(data, _T("pro####ion")));
            Assert::IsTrue(match(data, _T("project##2")));
            Assert::IsTrue(match(data, _T("project#12")));
            Assert::IsTrue(match(data, _T("#systems")));
            Assert::IsTrue(match(data, _T("75#protection")));
            Assert::IsTrue(match(data, _T("sys###s")));
            Assert::IsTrue(match(data, _T("new#tes#ted")));
            Assert::IsTrue(match(data, _T("project###, and #####ote##ion")));
            Assert::IsTrue(match(data, _T("projec####, and #####ote##ion")));
            Assert::IsTrue(match(data, _T("new tes;ted project-##, and ##_protection of various systems")));
            Assert::IsTrue(match(_T("system_-17 fee also"), _T("system##17")));
            Assert::IsTrue(match(_T("pro-ject"), _T("pro#ject")));
        }

        TEST_METHOD(filterSingleTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // ext cmp-one:
            {
                Assert::IsTrue(match(_T("str1 project-12 str2"), _T("project#12"))); // == 1
            }

            // split
            {
                Assert::IsTrue(match(data, _T("notfound|project##2")));
                Assert::IsTrue(match(data, _T("notfound|notfound2|project##2")));
            }
        }

        TEST_METHOD(filterSingleTest3)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            Assert::IsFalse(match(_T("pro-ject"), _T("pro#tect")));
            Assert::IsFalse(match(_T("pro-ject"), _T("fro#ject")));
            Assert::IsFalse(match(_T("project"), _T("pro#ject")));
            Assert::IsFalse(match(data, _T("project#2")));
            Assert::IsFalse(match(data, _T("systems#")));
            Assert::IsFalse(match(data, _T("systems #")));
            Assert::IsFalse(match(data, _T("systems# ")));
            Assert::IsFalse(match(data, _T("#new")));
            Assert::IsFalse(match(data, _T("###new")));
            Assert::IsFalse(match(data, _T("##new")));
            Assert::IsFalse(match(data, _T("new#systems")));
            Assert::IsFalse(match(data, _T("new##systems")));
            Assert::IsFalse(match(data, _T("new tes;ted project-##, and ##_protection of various systems ")));
            Assert::IsFalse(match(_T("system, installments range from 2 to 17"), _T("system#17")));
            Assert::IsFalse(match(_T("system_-17 fee also"), _T("system#17")));
            Assert::IsFalse(match(_T("system17 fee also"), _T("system#17")));
        }

        TEST_METHOD(filterSingleTest4)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // ext cmp-one:
            {
                Assert::IsFalse(match(_T("str1 project-12 str2"), _T("str#1")));        // == 0
                Assert::IsFalse(match(_T("str1 project--12 str2"), _T("project#12")));  // > 1
            }

            // split
            {
                Assert::IsFalse(match(data, _T("notfound|project##systems")));
                Assert::IsFalse(match(data, _T("notfound|notfound2|project##systems")));
            }
        }

        TEST_METHOD(filterMoreTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            Assert::IsTrue(match(data, _T("+")));
            Assert::IsTrue(match(data, _T("+++++")));

            Assert::IsTrue(match(data, _T("new+systems")));
            Assert::IsTrue(match(data, _T("new++systems")));
            Assert::IsTrue(match(data, _T("+systems")));
            Assert::IsTrue(match(data, _T("project+12")));
            Assert::IsFalse(match(data, _T("project++12")));
            Assert::IsTrue(match(data, _T("75+*systems")));
            Assert::IsTrue(match(data, _T("75*+*systems")));
            Assert::IsTrue(match(data, _T("new+7+system")));
        }

        TEST_METHOD(filterMoreTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // split
            {
                Assert::IsTrue(match(data, _T("notfound|project+systems")));
                Assert::IsTrue(match(data, _T("notfound|notfound2|project+systems")));
            }
        }

        TEST_METHOD(filterMoreTest3)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // MS combination
            {
                Assert::IsTrue(match(data, _T("*+")));
                Assert::IsTrue(match(data, _T("*+*")));
                Assert::IsTrue(match(data, _T("+*")));
                Assert::IsTrue(match(data, _T("+*new")));
            }
        }

        TEST_METHOD(filterMoreTest4)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            Assert::IsFalse(match(data, _T("+new")));
            Assert::IsFalse(match(data, _T("+new+")));

            Assert::IsTrue(match(data, _T("system+")));
            Assert::IsFalse(match(data, _T("systems+")));
            Assert::IsFalse(match(data, _T("systems++")));
            Assert::IsFalse(match(data, _T("+systems+")));

            Assert::IsFalse(match(data, _T("+new+systems")));
            Assert::IsFalse(match(data, _T("new+notfound")));
            Assert::IsFalse(match(data, _T("tes+ting+project")));
            Assert::IsFalse(match(data, _T("project+new")));
            Assert::IsFalse(match(data, _T("++open++close")));
            Assert::IsFalse(match(data, _T("now+is+completely")));
            Assert::IsFalse(match(data, _T("testing+project+and")));
        }

        TEST_METHOD(filterMoreTest5)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // split
            {
                Assert::IsFalse(match(data, _T("notfound|project+new")));
                Assert::IsFalse(match(data, _T("notfound|notfound2|project+new")));
            }
        }

        TEST_METHOD(filterMoreTest6)
        {
            tstring data = _T("new project20+ 10-pro data");

            Assert::IsTrue(match(data, _T("++")));
            Assert::IsTrue(match(data, _T("+++")));
            Assert::IsTrue(match(data, _T("++++")));
            Assert::IsTrue(match(data, _T("++++proj")));

            Assert::IsFalse(match(data, _T("+++++proj")));

            Assert::IsFalse(match(data, _T("project+20")));
            Assert::IsTrue(match(data, _T("project+10")));
            Assert::IsTrue(match(data, _T("project++10")));
            Assert::IsTrue(match(data, _T("project+++10")));
            Assert::IsTrue(match(data, _T("project++++10")));
            Assert::IsFalse(match(data, _T("project+++++10")));
            Assert::IsFalse(match(data, _T("project++++++10")));
        }

        TEST_METHOD(combENDTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // *
            {
                Assert::IsTrue(match(data, _T("systems*$")));
                Assert::IsTrue(match(datam, _T("main*$")));
                Assert::IsTrue(match(datam, _T("main**$")));
                Assert::IsTrue(match(data, _T("systems*$")));
                Assert::IsTrue(match(data, _T("project*$")));
                Assert::IsTrue(match(datam, _T("^main*$")));
                {
                    Assert::IsTrue(match(data, _T("^*new*$")));
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

        TEST_METHOD(combENDTest2)
        {
            tstring data = _T("various systems");

            Assert::IsFalse(match(data, _T("syste?$")));
            Assert::IsTrue(match(data, _T("system?$")));
            Assert::IsTrue(match(data, _T("system??$")));
            Assert::IsTrue(match(data, _T("systems??$")));

            Assert::IsTrue(match(data, _T("syste*$")));
            Assert::IsTrue(match(data, _T("syste+$")));

            Assert::IsFalse(match(data, _T("systems+$")));

            Assert::IsFalse(match(data, _T("systems#$")));
            Assert::IsFalse(match(data, _T("systems##$")));
            Assert::IsFalse(match(data, _T("system##$")));
        }

        TEST_METHOD(combBEGINTest1)
        {
            tstring data = _T("main system");

            Assert::IsFalse(match(data, _T("^?in")));
            Assert::IsTrue(match(data, _T("^??in")));
            Assert::IsTrue(match(data, _T("^+in")));
            Assert::IsTrue(match(data, _T("^*in")));
            Assert::IsFalse(match(data, _T("^#in")));
            Assert::IsTrue(match(data, _T("^##in")));
        }

        TEST_METHOD(combBEGINTest2)
        {
            tstring data = _T("mixed data");

            Assert::IsFalse(match(data, _T("^?in")));
            Assert::IsFalse(match(data, _T("^??in")));
            Assert::IsFalse(match(data, _T("^+in")));
            Assert::IsFalse(match(data, _T("^*in")));
            Assert::IsFalse(match(data, _T("^#in")));
            Assert::IsFalse(match(data, _T("^##in")));
        }

    private:

        EssRxW rxw;

        bool match(const tstring& data, const tstring& filter, bool ignoreCase = true)
        {
            return rxw.match(data, filter, (ignoreCase ? EssRxW::EngineOptions::F_ICASE : EssRxW::EngineOptions::F_NONE) | EssRxW::EngineOptions::F_LEGACY_ANYSP);
        }

    };
}