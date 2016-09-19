#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\regXwild\regXwildAPI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace net::r_eg::regXwild;


namespace regXwildTest
{
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
            Assert::AreEqual(true, searchEss(data, _T("project++12")));
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
            tstring datam = _T("main systems 1272/is ok");

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

        /* behaviour by default for non implemented combinations - SINGLE */
        TEST_METHOD(stubSINGLECombinationTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

            // MS combination
            {
                //TODO: implement *,>,?,+,# and combination
                {
                    /* true: */

                    // *
                    {
                        Assert::AreEqual(false, searchEss(data, _T("*#")));
                        Assert::AreEqual(false, searchEss(data, _T("*#*")));
                        Assert::AreEqual(false, searchEss(data, _T("#*")));
                        Assert::AreEqual(false, searchEss(data, _T("*#systems")));
                        Assert::AreEqual(false, searchEss(data, _T("new*#*systems")));
                        Assert::AreEqual(false, searchEss(data, _T("*new#*systems*")));
                        Assert::AreEqual(false, searchEss(data, _T("new#*systems")));
                        Assert::AreEqual(false, searchEss(data, _T("75*#protection")));
                        Assert::AreEqual(false, searchEss(data, _T("75*#*protection")));
                        Assert::AreEqual(false, searchEss(data, _T("new*#systems")));
                        Assert::AreEqual(false, searchEss(data, _T("*new#*#systems*")));
                    }

                    /* false */
                    {
                        Assert::AreEqual(false, searchEss(data, _T("*new#systems*")));
                        Assert::AreEqual(false, searchEss(data, _T("*new##systems*")));
                        Assert::AreEqual(false, searchEss(data, _T("systems*#")));
                        Assert::AreEqual(false, searchEss(data, _T("pro#*ject")));
                        Assert::AreEqual(false, searchEss(data, _T("systems#*")));
                    }
                }
            }
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

    };
}