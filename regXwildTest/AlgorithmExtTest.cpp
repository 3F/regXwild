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

    TEST_CLASS(AlgorithmExtTest)
    {
    public:
        
        TEST_METHOD(filterAnyTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

            Assert::AreEqual(true, searchExt(data, _T("protection of various")));      // __ __ __
            Assert::AreEqual(true, searchExt(data, _T("pro*system")));                 // __ * __
            Assert::AreEqual(true, searchExt(data, _T("*pro*system*")));               // * __ * __ *
            Assert::AreEqual(true, searchExt(data, _T("project**various")));           // __ ** __
            Assert::AreEqual(true, searchExt(data, _T("new*7*systems")));              // __ * __ * __
            Assert::AreEqual(true, searchExt(data, _T("")));                           // empty
        }

        TEST_METHOD(filterAnyTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

            Assert::AreEqual(false, searchExt(data, _T("project 12 and")));            // __ _x_ __
            Assert::AreEqual(false, searchExt(data, _T("new*express")));               // __ * _x_
            Assert::AreEqual(false, searchExt(data, _T("tes*ting*project")));          // __ * _x_ * __
            Assert::AreEqual(false, searchExt(data, _T("testing*project*and")));       // _x_ * __ * __
            Assert::AreEqual(false, searchExt(data, _T("now*is*completely")));         // _x_ * _x_ * _x_
            Assert::AreEqual(false, searchExt(data, _T("protection*project*new")));    // backwards __ * __ * __
            Assert::AreEqual(false, searchExt(data, _T("**open**close")));             // ** _x_ ** _x_
        }

        TEST_METHOD(filterSplitTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

            Assert::AreEqual(true, searchExt(data, _T("protection of|new tes")));       // __ __ | __ __
            Assert::AreEqual(true, searchExt(data, _T("some project|of various")));     // _x_ __ | __ __
            Assert::AreEqual(true, searchExt(data, _T("various systems|new 237")));     // __ __ | __ _x_
            Assert::AreEqual(true, searchExt(data, _T("pro*12|new*system")));           // __ * __ | __ *__
            Assert::AreEqual(true, searchExt(data, _T("ject*new|pro*tems")));           // __ * _x_ | __ * __
            Assert::AreEqual(true, searchExt(data, _T("pro*tems|seems*and")));          // __ * __ | _x_ * __
            Assert::AreEqual(true, searchExt(data, _T("project*|new")));                // __ *| __
            Assert::AreEqual(true, searchExt(data, _T("various*|zeep")));               // __ * | _x_
            Assert::AreEqual(true, searchExt(data, _T("goo*|systems")));                // _x_ * | __
            Assert::AreEqual(true, searchExt(data, _T("project||protect")));            // __ || __
            Assert::AreEqual(true, searchExt(data, _T("|new||and|")));                  // | __ || __ |
            Assert::AreEqual(true, searchExt(data, _T("|fail|system")));                // | _x_ | __
            Assert::AreEqual(true, searchExt(data, _T("|12||true||")));                 // | __ || _x_ ||
            Assert::AreEqual(true, searchExt(data, _T("above|new|with")));              // _x_ | __ | _x_
            Assert::AreEqual(true, searchExt(data, _T("project**|new")));               // __ **| __
            Assert::AreEqual(true, searchExt(data, _T("zoom|*pro")));                   // _x_ | * __
            Assert::AreEqual(true, searchExt(data, _T("zoom|*pro**")));                 // _x_ | *__ **
            Assert::AreEqual(true, searchExt(data, _T("||")));                          //empty
            Assert::AreEqual(true, searchExt(data, _T("")));                            //empty
            Assert::AreEqual(true, searchExt(data, _T("||zoom||out||")));               // ||_x_ || _x_ ||
            Assert::AreEqual(true, searchExt(data, _T("|*|")));                         // |*|
            Assert::AreEqual(true, searchExt(data, _T("|long-term")));                  // | _x_
            Assert::AreEqual(true, searchExt(data, _T("long-term|")));                  // _x_ |
            Assert::AreEqual(true, searchExt(data, _T("*|*")));                         // *|*
            Assert::AreEqual(true, searchExt(data, _T("*|")));                          // *|
            Assert::AreEqual(true, searchExt(data, _T("|*")));                          // |*
            Assert::AreEqual(true, searchExt(data, _T("seems|open*and*star|*system"))); // _x_ | _x_ * __ * _x_ | * __
        }

        TEST_METHOD(filterSplitTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

            Assert::AreEqual(false, searchExt(data, _T("above|fails|with")));           // _x_ | _x_ | _x_
            Assert::AreEqual(false, searchExt(data, _T("let*proj|project*deep")));      // _x_ * __ | __ * _x_
            Assert::AreEqual(false, searchExt(data, _T("operator*|*zeep")));            // _x_ *|* _x_
            Assert::AreEqual(false, searchExt(data, _T("some project|let*various")));   // _x_ __ | _x_* __
            Assert::AreEqual(false, searchExt(data, _T("some project|various*zoom")));  // _x_ __ | __ * _x_
            Assert::AreEqual(false, searchExt(data, _T("be|pen*and*star|*my*system"))); // _x_ | _x_ * __ * _x_ | * _x_ * __
        }

        TEST_METHOD(filterOneTest1)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

            Assert::AreEqual(true, searchExt(data, _T("new*pro?ection")));              // __ * [pro]ject ... [pro]t[ection]
            Assert::AreEqual(true, searchExt(data, _T("????")));
            Assert::AreEqual(true, searchExt(data, _T("project?12")));
            Assert::AreEqual(true, searchExt(_T("system-17 fee also offers protection"), _T("system?17")));
        }

        TEST_METHOD(filterOneTest2)
        {
            tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

            Assert::AreEqual(false, searchExt(data, _T("?pro?12?|seems?7")));
            Assert::AreEqual(false, searchExt(_T("system, installments range from 2 to 17"), _T("system?17")));
            Assert::AreEqual(false, searchExt(_T("system17 fee also"), _T("system?17")));
            Assert::AreEqual(false, searchExt(_T("my system17 fee also"), _T("system?17")));
            Assert::AreEqual(false, searchExt(_T("system_-17 fee also"), _T("system?17")));
        }

        TEST_METHOD(filterOneTest3)
        {
            tstring data = _T("number = '1234';");

            Assert::IsTrue, searchExt(data, _T("'????'"));
            Assert::IsTrue, searchExt(data, _T("'?????'"));
            Assert::IsTrue, searchExt(data, _T("'??????'"));
            Assert::IsFalse, searchExt(data, _T("'???'"));
            Assert::IsFalse, searchExt(data, _T("'??'"));
            Assert::IsFalse, searchExt(data, _T("'?'"));
            Assert::IsFalse, searchExt(data, _T("''"));
        }

        TEST_METHOD(filterAnySPTest1)
        {
            Assert::AreEqual(true, searchExt(_T("/new/user_myhid_test.bzip2"), _T("myhid>bzip")));   // __...___
            Assert::AreEqual(true, searchExt(_T("/new/user_myhid_test.bzip2"), _T("myhid>")));       // __...EOL
            Assert::AreEqual(true, searchExt(_T("/new/user_myhid"), _T("myhid>")));                  // __EOL
        }

        TEST_METHOD(filterAnySPTest2)
        {
            /* with other metasymbols: */
            {
                Assert::AreEqual(true, searchExt(_T("/new/user_myhid"), _T("myhid>*")));
                Assert::AreEqual(true, searchExt(_T("/new/user_myhid"), _T("myhid>***")));
                Assert::AreEqual(true, searchExt(_T("/new/user_myhid"), _T("myhid>?")));
                Assert::AreEqual(true, searchExt(_T("/new/user_myhid"), _T("myhid>?*")));
            }
        }

        TEST_METHOD(filterAnySPTest3)
        {
            Assert::AreEqual(false, searchExt(_T("/new/user_myhid_t/est.bzip2"), _T("myhid>bzip")));     // __.../...__
            Assert::AreEqual(false, searchExt(_T("/new/user_myhid/_test.bzip2"), _T("myhid>bzip")));     // __/...__
            Assert::AreEqual(false, searchExt(_T("/new/user_myhid_test./bzip2"), _T("myhid>bzip")));     // __.../__
            Assert::AreEqual(false, searchExt(_T("/new/user_myhid_te/st.bzip2"), _T("myhid>")));         // __.../...EOL
            Assert::AreEqual(false, searchExt(_T("/new/user_myhid_te/"), _T("myhid>")));                 // __.../EOL
            Assert::AreEqual(false, searchExt(_T("/new/user_myhid_t\\est.bzip2"), _T("myhid>bzip")));    //  "\" & "//"
        }

        TEST_METHOD(filterAnySPTest4)
        {
            /* with other metasymbols: */
            {
                Assert::AreEqual(false, searchExt(_T("/new/user_myhid_s/df.txt"), _T("myhid>*")));
                Assert::AreEqual(false, searchExt(_T("/new/user_myhid_s/df.txt"), _T("myhid>***")));
                Assert::AreEqual(false, searchExt(_T("/new/user_myhid_s/df.txt"), _T("myhid>?")));
                Assert::AreEqual(false, searchExt(_T("/new/user_myhid_s/df.txt"), _T("myhid>?*")));
                //-
                Assert::AreEqual(false, searchExt(_T("/new/user_myhid_s/df.txt"), _T("myhid>*txt")));
                Assert::AreEqual(false, searchExt(_T("/new/user_myhid_s/df.txt"), _T("myhid>***txt")));
                Assert::AreEqual(false, searchExt(_T("/new/user_myhid_s/df.txt"), _T("myhid>?txt")));
                Assert::AreEqual(false, searchExt(_T("/new/user_myhid_s/df.txt"), _T("myhid>?*??txt")));
                //-
                Assert::AreEqual(false, searchExt(_T("/new/user_myhid"), _T("myhid>*txt")));
                Assert::AreEqual(false, searchExt(_T("/new/user_myhid"), _T("myhid>***txt")));
                Assert::AreEqual(false, searchExt(_T("/new/user_myhid"), _T("myhid>?txt")));
                Assert::AreEqual(false, searchExt(_T("/new/user_myhid"), _T("myhid>?*??txt")));
            }
        }

        TEST_METHOD(caseSensitiveTest1)
        {
            Assert::AreEqual(false, searchExt(_T("system"), _T("syStem"), false));
            Assert::AreEqual(true, searchExt(_T("system"), _T("system"), false));
            Assert::AreEqual(false, searchExt(_T("syStem"), _T("system"), false));
            Assert::AreEqual(true, searchExt(_T("SYSTEM"), _T("SYSTEM"), false));

            Assert::AreEqual(false, searchExt(_T("system"), _T("sy*Stem"), false));
            Assert::AreEqual(false, searchExt(_T("system"), _T("syS*tem"), false));
            Assert::AreEqual(true, searchExt(_T("system"), _T("sy*stem"), false));
        }

    private:

        bool searchExt(const tstring& data, const tstring& filter, bool ignoreCase = true)
        {
            return regXwild::common::searchExt(data, filter, ignoreCase);
        }

    };

}