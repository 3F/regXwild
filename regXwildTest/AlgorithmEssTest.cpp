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

    TEST_CLASS(AlgorithmEssTest)
    {
    public:
        
        TEST_METHOD(filterAnyTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

            /* should be found: */
            Assert::AreEqual(true, searchEss(data, _T("protection of various")));      // __ __ __
            Assert::AreEqual(true, searchEss(data, _T("pro*system")));                 // __ * __
            Assert::AreEqual(true, searchEss(data, _T("*pro*system*")));               // * __ * __ *
            Assert::AreEqual(true, searchEss(data, _T("project**various")));           // __ ** __
            Assert::AreEqual(true, searchEss(data, _T("new*7*systems")));              // __ * __ * __
            Assert::AreEqual(true, searchEss(data, _T("")));                           // empty

            Assert::AreEqual(true, searchEss(data, _T("*")));
            Assert::AreEqual(true, searchEss(data, _T("***")));
            Assert::AreEqual(true, searchEss(_T("new str"), _T("new str")));
            Assert::AreEqual(true, searchEss(_T(""), _T("")));
        }

        TEST_METHOD(filterAnyTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

            Assert::AreEqual(false, searchEss(data, _T("project 12 and")));            // __ _x_ __
            Assert::AreEqual(false, searchEss(data, _T("new*express")));               // __ * _x_
            Assert::AreEqual(false, searchEss(data, _T("tes*ting*project")));          // __ * _x_ * __
            Assert::AreEqual(false, searchEss(data, _T("testing*project*and")));       // _x_ * __ * __
            Assert::AreEqual(false, searchEss(data, _T("now*is*completely")));         // _x_ * _x_ * _x_
            Assert::AreEqual(false, searchEss(data, _T("protection*project*new")));    // backwards __ * __ * __
            Assert::AreEqual(false, searchEss(data, _T("**open**close")));             // ** _x_ ** _x_
        }

        TEST_METHOD(filterSplitTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

            Assert::AreEqual(true, searchEss(data, _T("protection of|new tes")));       // __ __ | __ __
            Assert::AreEqual(true, searchEss(data, _T("some project|of various")));     // _x_ __ | __ __
            Assert::AreEqual(true, searchEss(data, _T("various systems|new 237")));     // __ __ | __ _x_
            Assert::AreEqual(true, searchEss(data, _T("pro*12|new*system")));           // __ * __ | __ *__
            Assert::AreEqual(true, searchEss(data, _T("ject*new|pro*tems")));           // __ * _x_ | __ * __
            Assert::AreEqual(true, searchEss(data, _T("pro*tems|seems*and")));          // __ * __ | _x_ * __
            Assert::AreEqual(true, searchEss(data, _T("project*|new")));                // __ *| __
            Assert::AreEqual(true, searchEss(data, _T("various*|zeep")));               // __ * | _x_
            Assert::AreEqual(true, searchEss(data, _T("goo*|systems")));                // _x_ * | __
            Assert::AreEqual(true, searchEss(data, _T("project||protect")));            // __ || __
            Assert::AreEqual(true, searchEss(data, _T("|new||and|")));                  // | __ || __ |
            Assert::AreEqual(true, searchEss(data, _T("|fail|system")));                // | _x_ | __
            Assert::AreEqual(true, searchEss(data, _T("|12||true||")));                 // | __ || _x_ ||
            Assert::AreEqual(true, searchEss(data, _T("above|new|with")));              // _x_ | __ | _x_
            Assert::AreEqual(true, searchEss(data, _T("project**|new")));               // __ **| __
            Assert::AreEqual(true, searchEss(data, _T("zoom|*pro")));                   // _x_ | * __
            Assert::AreEqual(true, searchEss(data, _T("zoom|*pro**")));                 // _x_ | *__ **
            Assert::AreEqual(true, searchEss(data, _T("||")));                          //empty
            Assert::AreEqual(true, searchEss(data, _T("")));                            //empty
            Assert::AreEqual(true, searchEss(data, _T("||zoom||out||")));               // ||_x_ || _x_ ||
            Assert::AreEqual(true, searchEss(data, _T("|*|")));                         // |*|
            Assert::AreEqual(true, searchEss(data, _T("|long-term")));                  // | _x_
            Assert::AreEqual(true, searchEss(data, _T("long-term|")));                  // _x_ |
            Assert::AreEqual(true, searchEss(data, _T("*|*")));                         // *|*
            Assert::AreEqual(true, searchEss(data, _T("*|")));                          // *|
            Assert::AreEqual(true, searchEss(data, _T("|*")));                          // |*
            Assert::AreEqual(true, searchEss(data, _T("seems|open*and*star|*system"))); // _x_ | _x_ * __ * _x_ | * __
        }

        TEST_METHOD(filterSplitTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

            Assert::AreEqual(false, searchEss(data, _T("above|fails|with")));           // _x_ | _x_ | _x_
            Assert::AreEqual(false, searchEss(data, _T("let*proj|project*deep")));      // _x_ * __ | __ * _x_
            Assert::AreEqual(false, searchEss(data, _T("operator*|*zeep")));            // _x_ *|* _x_
            Assert::AreEqual(false, searchEss(data, _T("some project|let*various")));   // _x_ __ | _x_* __
            Assert::AreEqual(false, searchEss(data, _T("some project|various*zoom")));  // _x_ __ | __ * _x_
            Assert::AreEqual(false, searchEss(data, _T("be|pen*and*star|*my*system"))); // _x_ | _x_ * __ * _x_ | * _x_ * __
        }

        TEST_METHOD(filterOneTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            /* should be found: */
            Assert::AreEqual(true, searchEss(data, _T("?")));
            Assert::AreEqual(true, searchEss(data, _T("????")));

            Assert::AreEqual(true, searchEss(data, _T("new*pro?ection")));                 // __ * [pro]ject ... [pro]t[ection]
            Assert::AreEqual(true, searchEss(data, _T("????")));
            Assert::AreEqual(true, searchEss(data, _T("project?12")));
            Assert::AreEqual(true, searchEss(data, _T("systems?")));
            Assert::AreEqual(true, searchEss(data, _T("????new")));
            Assert::AreEqual(true, searchEss(data, _T("systems????")));
            Assert::AreEqual(true, searchEss(data, _T("???systems????")));
            Assert::AreEqual(true, searchEss(data, _T("pro????ion")));                     // {0,4}: min: proion, max: protection
            Assert::AreEqual(true, searchEss(data, _T("protection????????????system")));
            Assert::AreEqual(true, searchEss(data, _T("protection?????????????system")));
            Assert::AreEqual(true, searchEss(data, _T("protection??????????????system")));
            Assert::AreEqual(true, searchEss(data, _T("pro??????????ion")));
            Assert::AreEqual(true, searchEss(_T("system-17 fee"), _T("system?17")));
        }

        TEST_METHOD(filterOneTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // EXT changed:

            Assert::AreEqual(true, searchEss(_T("system17"), _T("system?17")));                 // == 0{2}
            Assert::AreEqual(true, searchEss(_T("str1 project-12 str2"), _T("project?12")));    // == 1
            Assert::AreEqual(true, searchEss(_T("str1 project-12 str2"), _T("str?1")));         // == 0
        }

        TEST_METHOD(filterOneTest3)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // MS combination

            Assert::AreEqual(true, searchEss(data, _T("?*??*")));
            Assert::AreEqual(true, searchEss(data, _T("new?*systems")));
            Assert::AreEqual(true, searchEss(data, _T("new*?*systems")));
            Assert::AreEqual(true, searchEss(data, _T("new*??*systems")));
            Assert::AreEqual(true, searchEss(data, _T("new*??*systems?")));
            //Assert::AreEqual(true, searchEss(data, _T("new*?systems"))); //TODO: implement combination {MS} + {?}
        }

        TEST_METHOD(filterOneTest4)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // MS combination

            Assert::AreEqual(true, searchEss(data, _T("?*??*")));
            Assert::AreEqual(true, searchEss(data, _T("new?*systems")));
            Assert::AreEqual(true, searchEss(data, _T("new*?*systems")));
            Assert::AreEqual(true, searchEss(data, _T("new*??*systems")));
            Assert::AreEqual(true, searchEss(data, _T("new*??*systems?")));
            //Assert::AreEqual(true, searchEss(data, _T("new*?systems"))); //TODO: implement combination {MS} + {?}
        }

        TEST_METHOD(filterOneTest5)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            Assert::AreEqual(false, searchEss(data, _T("?pro?12?|seems?7")));
            Assert::AreEqual(false, searchEss(_T("system, installments range from 2 to 17"), _T("system?17")));
            Assert::AreEqual(false, searchEss(_T("system_-17 fee also"), _T("system?17")));
            Assert::AreEqual(false, searchEss(_T("project"), _T("pro?tect")));
            Assert::AreEqual(false, searchEss(_T("project"), _T("fro?ject")));
            {
                Assert::AreEqual(false, searchEss(_T("str1 project--12 str2"), _T("project?12")));  // > 1
            }
        }

        TEST_METHOD(filterOneTest6)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // MS combination
            {
                Assert::AreEqual(false, searchEss(data, _T("*new?systems*")));
                Assert::AreEqual(false, searchEss(data, _T("*?new?sys?*?ms*")));
            }
        }

        TEST_METHOD(filterAnySPTest1)
        {
            Assert::AreEqual(true, searchEss(_T("/new/user_myhid_test.bzip2"), _T("myhid>bzip")));   // __...___
            Assert::AreEqual(true, searchEss(_T("/new/user_myhid_test.bzip2"), _T("myhid>")));       // __...EOL
            Assert::AreEqual(true, searchEss(_T("/new/user_myhid"), _T("myhid>")));                  // __EOL
        }

        TEST_METHOD(filterAnySPTest2)
        {
            /* with other metasymbols: */
            
            Assert::AreEqual(true, searchEss(_T("/new/user_myhid"), _T("myhid>*")));
            Assert::AreEqual(true, searchEss(_T("/new/user_myhid"), _T("myhid>***")));
            Assert::AreEqual(true, searchEss(_T("/new/user_myhid"), _T("myhid>?")));
            Assert::AreEqual(true, searchEss(_T("/new/user_myhid"), _T("myhid>?*")));
        }

        TEST_METHOD(filterAnySPTest3)
        {
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid_t/est.bzip2"), _T("myhid>bzip")));     // __.../...__
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid/_test.bzip2"), _T("myhid>bzip")));     // __/...__
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid_test./bzip2"), _T("myhid>bzip")));     // __.../__
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid_te/st.bzip2"), _T("myhid>")));         // __.../...EOL
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid_te/"), _T("myhid>")));                 // __.../EOL
        }

        TEST_METHOD(filterAnySPTest4)
        {
            /* with other metasymbols: */

            Assert::AreEqual(false, searchEss(_T("/new/user_myhid_s/df.txt"), _T("myhid>*")));
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid_s/df.txt"), _T("myhid>***")));
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid_s/df.txt"), _T("myhid>?")));
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid_s/df.txt"), _T("myhid>?*")));
            //-
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid_s/df.txt"), _T("myhid>*txt")));
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid_s/df.txt"), _T("myhid>***txt")));
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid_s/df.txt"), _T("myhid>?txt")));
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid_s/df.txt"), _T("myhid>?*??txt")));
            //-
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid"), _T("myhid>*txt")));
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid"), _T("myhid>***txt")));
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid"), _T("myhid>?txt")));
            Assert::AreEqual(false, searchEss(_T("/new/user_myhid"), _T("myhid>?*??txt")));
        }

        TEST_METHOD(filterSingleTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            Assert::AreEqual(true, searchEss(data, _T("#")));
            Assert::AreEqual(true, searchEss(data, _T("####")));

            Assert::AreEqual(true, searchEss(data, _T("pro####ion")));
            Assert::AreEqual(true, searchEss(data, _T("project##2")));
            Assert::AreEqual(true, searchEss(data, _T("project#12")));
            Assert::AreEqual(true, searchEss(data, _T("#systems")));
            Assert::AreEqual(true, searchEss(data, _T("75#protection")));
            Assert::AreEqual(true, searchEss(data, _T("sys###s")));
            Assert::AreEqual(true, searchEss(data, _T("new#tes#ted")));
            Assert::AreEqual(true, searchEss(data, _T("project###, and #####ote##ion")));
            Assert::AreEqual(true, searchEss(data, _T("projec####, and #####ote##ion")));
            Assert::AreEqual(true, searchEss(data, _T("new tes;ted project-##, and ##_protection of various systems")));
            Assert::AreEqual(true, searchEss(_T("system_-17 fee also"), _T("system##17")));
            Assert::AreEqual(true, searchEss(_T("pro-ject"), _T("pro#ject")));
        }

        TEST_METHOD(filterSingleTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // ext cmp-one:
            {
                Assert::AreEqual(true, searchEss(_T("str1 project-12 str2"), _T("project#12"))); // == 1
            }

            // split
            {
                Assert::AreEqual(true, searchEss(data, _T("notfound|project##2")));
                Assert::AreEqual(true, searchEss(data, _T("notfound|notfound2|project##2")));
            }
        }

        TEST_METHOD(filterSingleTest3)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // MS combination
            {
                //TODO: implement *,?,+,> and combination
                {
                    //Assert::AreEqual(true, searchEss(data, _T("*#")));
                    //Assert::AreEqual(true, searchEss(data, _T("*#*")));
                    //Assert::AreEqual(true, searchEss(data, _T("#*")));
                    //Assert::AreEqual(true, searchEss(data, _T("*#systems")));
                    //Assert::AreEqual(true, searchEss(data, _T("new*#*systems")));
                    //Assert::AreEqual(true, searchEss(data, _T("*new#*systems*")));
                    //Assert::AreEqual(true, searchEss(data, _T("new#*systems")));
                    //Assert::AreEqual(true, searchEss(data, _T("75*#protection")));
                    //Assert::AreEqual(true, searchEss(data, _T("75*#*protection")));
                    //Assert::AreEqual(true, searchEss(data, _T("new*#systems")));
                    //Assert::AreEqual(true, searchEss(data, _T("*new#*#systems*")));
                }
            }
        }

        TEST_METHOD(filterSingleTest4)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            Assert::AreEqual(false, searchEss(_T("pro-ject"), _T("pro#tect")));
            Assert::AreEqual(false, searchEss(_T("pro-ject"), _T("fro#ject")));
            Assert::AreEqual(false, searchEss(_T("project"), _T("pro#ject")));
            Assert::AreEqual(false, searchEss(data, _T("project#2")));
            Assert::AreEqual(false, searchEss(data, _T("systems#")));
            Assert::AreEqual(false, searchEss(data, _T("systems #")));
            Assert::AreEqual(false, searchEss(data, _T("systems# ")));
            Assert::AreEqual(false, searchEss(data, _T("#new")));
            Assert::AreEqual(false, searchEss(data, _T("###new")));
            Assert::AreEqual(false, searchEss(data, _T("##new")));
            Assert::AreEqual(false, searchEss(data, _T("new#systems")));
            Assert::AreEqual(false, searchEss(data, _T("new##systems")));
            Assert::AreEqual(false, searchEss(data, _T("new tes;ted project-##, and ##_protection of various systems ")));
            Assert::AreEqual(false, searchEss(_T("system, installments range from 2 to 17"), _T("system#17")));
            Assert::AreEqual(false, searchEss(_T("system_-17 fee also"), _T("system#17")));
            Assert::AreEqual(false, searchEss(_T("system17 fee also"), _T("system#17")));
        }

        TEST_METHOD(filterSingleTest5)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // ext cmp-one:
            {
                Assert::AreEqual(false, searchEss(_T("str1 project-12 str2"), _T("str#1")));        // == 0
                Assert::AreEqual(false, searchEss(_T("str1 project--12 str2"), _T("project#12")));  // > 1
            }

            // split
            {
                Assert::AreEqual(false, searchEss(data, _T("notfound|project##systems")));
                Assert::AreEqual(false, searchEss(data, _T("notfound|notfound2|project##systems")));
            }
        }

        TEST_METHOD(filterSingleTest6)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // MS combination
            {
                //TODO: implement *,?,+,> and combination
                {
                    //Assert::AreEqual(false, searchEss(data, _T("*new#systems*")));
                    //Assert::AreEqual(false, searchEss(data, _T("*new##systems*")));
                    //Assert::AreEqual(false, searchEss(data, _T("systems*#")));
                    //Assert::AreEqual(false, searchEss(data, _T("pro#*ject")));
                    //Assert::AreEqual(false, searchEss(data, _T("systems#*")));
                }
            }
        }

        TEST_METHOD(filterMoreTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            Assert::AreEqual(true, searchEss(data, _T("+")));
            Assert::AreEqual(true, searchEss(data, _T("+++++")));

            Assert::AreEqual(true, searchEss(data, _T("new+systems")));
            Assert::AreEqual(true, searchEss(data, _T("new++systems")));
            Assert::AreEqual(true, searchEss(data, _T("+systems")));
            Assert::AreEqual(true, searchEss(data, _T("project+12")));
            Assert::AreEqual(false, searchEss(data, _T("project++12")));
            Assert::AreEqual(true, searchEss(data, _T("75+*systems")));
            Assert::AreEqual(true, searchEss(data, _T("75*+*systems")));
            Assert::AreEqual(true, searchEss(data, _T("new+7+system")));
        }

        TEST_METHOD(filterMoreTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // split
            {
                Assert::AreEqual(true, searchEss(data, _T("notfound|project+systems")));
                Assert::AreEqual(true, searchEss(data, _T("notfound|notfound2|project+systems")));
            }
        }

        TEST_METHOD(filterMoreTest3)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // MS combination
            {
                Assert::AreEqual(true, searchEss(data, _T("*+")));
                Assert::AreEqual(true, searchEss(data, _T("*+*")));
                Assert::AreEqual(true, searchEss(data, _T("+*")));
                Assert::AreEqual(true, searchEss(data, _T("+*new")));
            }
        }

        TEST_METHOD(filterMoreTest4)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            Assert::AreEqual(false, searchEss(data, _T("+new")));
            Assert::AreEqual(false, searchEss(data, _T("+new+")));

            Assert::AreEqual(false, searchEss(data, _T("systems+")));
            Assert::AreEqual(false, searchEss(data, _T("systems++")));
            Assert::AreEqual(false, searchEss(data, _T("+systems+")));

            Assert::AreEqual(false, searchEss(data, _T("+new+systems")));
            Assert::AreEqual(false, searchEss(data, _T("new+notfound")));
            Assert::AreEqual(false, searchEss(data, _T("tes+ting+project")));
            Assert::AreEqual(false, searchEss(data, _T("project+new")));
            Assert::AreEqual(false, searchEss(data, _T("++open++close")));
            Assert::AreEqual(false, searchEss(data, _T("now+is+completely")));
            Assert::AreEqual(false, searchEss(data, _T("testing+project+and")));
        }

        TEST_METHOD(filterMoreTest5)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // split
            {
                Assert::AreEqual(false, searchEss(data, _T("notfound|project+new")));
                Assert::AreEqual(false, searchEss(data, _T("notfound|notfound2|project+new")));
            }
        }

        TEST_METHOD(filterMoreTest6)
        {
            tstring data = _T("new project20+ 10-pro data");

            Assert::AreEqual(true, searchEss(data, _T("++")));
            Assert::AreEqual(true, searchEss(data, _T("+++")));
            Assert::AreEqual(true, searchEss(data, _T("++++")));
            Assert::AreEqual(true, searchEss(data, _T("++++proj")));

            Assert::AreEqual(false, searchEss(data, _T("+++++proj")));

            Assert::AreEqual(false, searchEss(data, _T("project+20")));
            Assert::AreEqual(true, searchEss(data, _T("project+10")));
            Assert::AreEqual(true, searchEss(data, _T("project++10")));
            Assert::AreEqual(true, searchEss(data, _T("project+++10")));
            Assert::AreEqual(true, searchEss(data, _T("project++++10")));
            Assert::AreEqual(false, searchEss(data, _T("project+++++10")));
            Assert::AreEqual(false, searchEss(data, _T("project++++++10")));
        }

        /* behaviour by default for non implemented combinations - END */
        TEST_METHOD(stubENDCombinationTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
            tstring datam = _T("main systems 1272/is ok");

            // MS combination
            {
                //TODO: implement *,>,?,+,# and combination
                {
                    /* true: */

                    // *
                    {
                        Assert::AreEqual(false, searchEss(data, _T("systems*$")));
                        Assert::AreEqual(false, searchEss(data, _T("systems**$")));
                        Assert::AreEqual(false, searchEss(datam, _T("main*$")));
                        Assert::AreEqual(false, searchEss(datam, _T("main**$")));
                        Assert::AreEqual(false, searchEss(data, _T("systems*$")));
                        Assert::AreEqual(false, searchEss(data, _T("project*$")));
                        Assert::AreEqual(false, searchEss(datam, _T("^main*$")));
                        {
                            Assert::AreEqual(false, searchEss(data, _T("^*new*$")));
                            Assert::AreEqual(false, searchEss(data, _T("^*$")));
                            Assert::AreEqual(false, searchEss(data, _T("^*$")));
                            Assert::AreEqual(false, searchEss(datam, _T("^*1272*$")));
                        }
                    }

                    // >
                    {
                        Assert::AreEqual(false, searchEss(data, _T("systems>$")));
                        Assert::AreEqual(false, searchEss(data, _T("systems>*$")));
                        Assert::AreEqual(false, searchEss(data, _T("various>$")));
                        Assert::AreEqual(false, searchEss(data, _T("various>*$")));
                        Assert::AreEqual(false, searchEss(data, _T("various>>$")));
                    }

                    // ?
                    {
                        Assert::AreEqual(false, searchEss(data, _T("system?$")));
                        Assert::AreEqual(false, searchEss(data, _T("systems?$")));
                    }

                    // +
                    {
                        Assert::AreEqual(false, searchEss(data, _T("system+$")));
                        Assert::AreEqual(false, searchEss(data, _T("syste+$")));
                    }

                    // #
                    {
                        Assert::AreEqual(false, searchEss(data, _T("system#$")));
                        Assert::AreEqual(false, searchEss(data, _T("syste##$")));
                    }

                    /* false: */

                    // ?
                    {
                        Assert::AreEqual(false, searchEss(data, _T("syste?$")));
                    }

                    // +
                    {
                        Assert::AreEqual(false, searchEss(data, _T("systems+$")));
                    }

                    // #
                    {
                        Assert::AreEqual(false, searchEss(data, _T("systems#$")));
                        Assert::AreEqual(false, searchEss(data, _T("system##$")));
                        Assert::AreEqual(false, searchEss(data, _T("systems##$")));
                    }
                }
            }
        }

        TEST_METHOD(caseSensitiveTest1)
        {
            Assert::AreEqual(false, searchEss(_T("system"), _T("syStem"), false));
            Assert::AreEqual(true, searchEss(_T("system"), _T("system"), false));
            Assert::AreEqual(false, searchEss(_T("syStem"), _T("system"), false));
            Assert::AreEqual(true, searchEss(_T("SYSTEM"), _T("SYSTEM"), false));

            Assert::AreEqual(false, searchEss(_T("system"), _T("sy*Stem"), false));
            Assert::AreEqual(false, searchEss(_T("system"), _T("syS*tem"), false));
            Assert::AreEqual(true, searchEss(_T("system"), _T("sy*stem"), false));
        }

        TEST_METHOD(underscoreTest1)
        {
            tstring data = _T("TV_[11_of_24]");

            Assert::IsTrue(searchEss(data, _T("1#_of")));
            Assert::IsTrue(searchEss(data, _T("#1_of")));
            Assert::IsTrue(searchEss(data, _T("1_of")));
            Assert::IsTrue(searchEss(data, _T("[1#_o*24")));
            Assert::IsFalse(searchEss(data, _T("[1##_o*24")));
            Assert::IsFalse(searchEss(data, _T("[1###_o*24")));
            Assert::IsFalse(searchEss(data, _T("[1###_o")));
            Assert::IsFalse(searchEss(data, _T("[1###_of")));
            Assert::IsTrue(searchEss(data, _T("[1#_of")));
            Assert::IsFalse(searchEss(data, _T("[1__of")));
            Assert::IsTrue(searchEss(data, _T("1_of")));
            Assert::IsTrue(searchEss(data, _T("[1??_of")));
            Assert::IsTrue(searchEss(data, _T("[1???_of")));
            Assert::IsTrue(searchEss(data, _T("[1+_of")));
            Assert::IsFalse(searchEss(data, _T("[1++_of")));
            Assert::IsFalse(searchEss(data, _T("[1+++_of")));
        }

        TEST_METHOD(underscoreTest2)
        {
            tstring data = _T("TV_[11_of_24]");

            Assert::IsFalse(searchEss(data, _T("1####4")));
            Assert::IsTrue(searchEss(data, _T("1#####4")));
            Assert::IsTrue(searchEss(data, _T("1######4")));
            Assert::IsFalse(searchEss(data, _T("f####4")));
            Assert::IsFalse(searchEss(data, _T("f###4")));
            Assert::IsTrue(searchEss(data, _T("f##4")));
            Assert::IsFalse(searchEss(data, _T("1#######_of")));
            Assert::IsFalse(searchEss(data, _T("1###############_of")));
            Assert::IsFalse(searchEss(data, _T("1###############f")));
            Assert::IsFalse(searchEss(data, _T("1###############_f")));
            Assert::IsFalse(searchEss(data, _T("1###############_o")));
            Assert::IsFalse(searchEss(data, _T("[1####_of")));
            Assert::IsFalse(searchEss(data, _T("[1####of")));
            Assert::IsFalse(searchEss(data, _T("[1###of")));
            Assert::IsTrue(searchEss(data, _T("[1##of")));
        }


    private:

        bool searchEss(const tstring& data, const tstring& filter, bool ignoreCase = true)
        {
            return regXwild::common::searchEss(data, filter, ignoreCase);
        }

    };
}