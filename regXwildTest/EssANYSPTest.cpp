#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\regXwild\regXwild.common.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace net::r_eg::regXwild;


namespace regXwildTest
{
    namespace regXwild = net::r_eg::regXwild;
    using namespace regXwild::rxwtypes;

    TEST_CLASS(EssANYSPTest)
    {
    public:

        TEST_METHOD(uMatchTest1)
        {
            EssRxW::FlagsRxW cfg = EssRxW::FlagsRxW::F_LEGACY_ANYSP;

            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>/.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir_test.zip"), _T("dir>/.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>_.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir_test.zip"), _T("dir>_.zip"), cfg));

            cfg = EssRxW::FlagsRxW::F_NONE;

            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>/.zip"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir_test.zip"), _T("dir>/.zip"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("dir>_.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir_test.zip"), _T("dir>_.zip"), cfg));
        }

        TEST_METHOD(uMatchTest2)
        {
            EssRxW::FlagsRxW cfg = EssRxW::FlagsRxW::F_LEGACY_ANYSP;
            
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>.zip"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir_test.zip"), _T("dir>.zip"), cfg));

            Assert::AreEqual(true, rxw.match(_T("/dir_test/.zip"), _T("dir>/.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test_.zip"), _T("dir>_.zip"), cfg));

            cfg = EssRxW::FlagsRxW::F_NONE;
            
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir_test.zip"), _T("dir>.zip"), cfg));

            Assert::AreEqual(false, rxw.match(_T("/dir_test/.zip"), _T("dir>/.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test_.zip"), _T("dir>_.zip"), cfg));
        }

        TEST_METHOD(uMatchTest3)
        {
            EssRxW::FlagsRxW cfg = EssRxW::FlagsRxW::F_NONE;

            Assert::AreEqual(false, rxw.match(_T("/dir test.zip"), _T("dir> "), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>/"), cfg));

            Assert::AreEqual(false, rxw.match(_T("/dir test.zip"), _T("dir> st"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>/st"), cfg));
        }

        TEST_METHOD(uMatchTest4)
        {
            EssRxW::FlagsRxW cfg = EssRxW::FlagsRxW::F_NONE;

            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("dir>"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("dir> "), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir /test.zip"), _T("dir> zip"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/ dir/test.zip"), _T("dir> zip"), cfg));

            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("test>"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("test>/"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("zip>"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("zip>/"), cfg));
        }

        TEST_METHOD(uMatchTest5)
        {
            EssRxW::FlagsRxW cfg = EssRxW::FlagsRxW::F_LEGACY_ANYSP;

            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir /test.zip"), _T("dir>"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("dir>/"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("test>"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("test>/"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("zip>"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("zip>/"), cfg));
        }

        void uMatchTest6(EssRxW::FlagsRxW cfg)
        {
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>/zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>/ "), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip "), _T("dir>/ "), cfg));
        }
        TEST_METHOD(uMatchTest6)
        {
            uMatchTest6(EssRxW::FlagsRxW::F_NONE);
            uMatchTest6(EssRxW::FlagsRxW::F_LEGACY_ANYSP);

            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("dir>/*"), EssRxW::FlagsRxW::F_LEGACY_ANYSP));
            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("dir>*"), EssRxW::FlagsRxW::F_NONE));

            // due to disbaled MS combinations in legacy mode
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>*"), EssRxW::FlagsRxW::F_LEGACY_ANYSP));
        }

        TEST_METHOD(uMatchTest7)
        {
            EssRxW::FlagsRxW cfg = EssRxW::FlagsRxW::F_NONE;

            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>/*ip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>/st*ip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>/st*"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("dir>/*"), cfg));

            Assert::AreEqual(true, rxw.match(_T("/dir test.zip"), _T("dir>/*ip"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir test.zip"), _T("dir>/st*ip"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir test.zip"), _T("dir>/st*"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir test.zip"), _T("dir>/*"), cfg));
        }

        TEST_METHOD(uMatchTest8)
        {
            EssRxW::FlagsRxW cfg = EssRxW::FlagsRxW::F_NONE;

            Assert::AreEqual(true, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir>\\st>/b1.zip"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir\\test/sub1.zip"), _T("dir>/st>\\b1.zip"), cfg));

            Assert::AreEqual(false, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir>/st>\\b1.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir\\test/sub1.zip"), _T("dir>\\st>/b1.zip"), cfg));

            cfg = EssRxW::FlagsRxW::F_LEGACY_ANYSP;

            Assert::AreEqual(false, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir>\\st>/b1.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir\\test/sub1.zip"), _T("dir>/st>\\b1.zip"), cfg));

            Assert::AreEqual(false, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir>/st>\\b1.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir\\test/sub1.zip"), _T("dir>\\st>/b1.zip"), cfg));
        }

        TEST_METHOD(uMatchTest9)
        {
            EssRxW::FlagsRxW cfg = EssRxW::FlagsRxW::F_NONE;

            Assert::AreEqual(true, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir>\\s>/b1.zip"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir\\test/sub1.zip"), _T("dir>/s>\\b1.zip"), cfg));

            Assert::AreEqual(false, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir>/s>\\b1.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir\\test/sub1.zip"), _T("dir>\\s>/b1.zip"), cfg));

            Assert::AreEqual(true, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir>\\test>/sub1.zip"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir\\test/sub1.zip"), _T("dir>/test>\\sub1.zip"), cfg));

            Assert::AreEqual(false, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir>/test>\\sub1.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir\\test/sub1.zip"), _T("dir>\\test>/sub1.zip"), cfg));
        }

        TEST_METHOD(uMatchTest10)
        {
            EssRxW::FlagsRxW cfg = EssRxW::FlagsRxW::F_NONE;

            // >a >b >c  - `a` will dominate; ie. `b`, `c`, `...` symbols will not be applied if sequential

            Assert::AreEqual(true, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir/>/>\\b1.zip"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir test\\sub1.zip"), _T("dir>/>\\b1.zip"), cfg));

            Assert::AreEqual(true, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir> >/>\\b1.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test sub1.zip"), _T("dir> >/>\\b1.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir test\\sub1.zip"), _T("dir> >/>\\b1.zip"), cfg));

            Assert::AreEqual(false, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir>\\>/b1.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir\\test/sub1.zip"), _T("dir>/>\\b1.zip"), cfg));

            Assert::AreEqual(false, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir>/>\\b1.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir\\test/sub1.zip"), _T("dir>\\>/b1.zip"), cfg));

            Assert::AreEqual(false, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir/>\\>/b1.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir test\\sub1.zip"), _T("dir>\\>/b1.zip"), cfg));

            Assert::AreEqual(true, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir>\\>/\\sub1.zip"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir/>/>\\\\sub1.zip"), cfg));

            Assert::AreEqual(true, rxw.match(_T("/dir test\\sub1.zip"), _T("dir>/> b1.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir test\\sub1.zip"), _T("dir> >/b1.zip"), cfg));
        }

        TEST_METHOD(uMatchTest11)
        {
            EssRxW::FlagsRxW cfg = EssRxW::FlagsRxW::F_NONE;

            Assert::AreEqual(false, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir>/st*b1.zip"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir> st*b1.zip"), cfg));

            Assert::AreEqual(true, rxw.match(_T("/dir test\\sub1.zip"), _T("dir>/st*b1.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir test\\sub1.zip"), _T("dir> st*b1.zip"), cfg));
        }

        TEST_METHOD(uMatchTest12)
        {
            EssRxW::FlagsRxW cfg = EssRxW::FlagsRxW::F_NONE;

            Assert::AreEqual(false, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir>/st*sub#.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir test\\sub1.zip"), _T("dir> st*sub#.zip"), cfg));

            Assert::AreEqual(true, rxw.match(_T("/dir/test\\sub1.zip"), _T("dir> st*sub#.zip"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir test\\sub1.zip"), _T("dir>/st*sub#.zip"), cfg));

            Assert::AreEqual(false, rxw.match(_T("/dir/test\\sub.zip"), _T("dir> st*sub#.zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir test\\sub.zip"), _T("dir>/st*sub#.zip"), cfg));
        }

        TEST_METHOD(uMatchTest13)
        {
            EssRxW::FlagsRxW cfg = EssRxW::FlagsRxW::F_NONE;

            Assert::AreEqual(false, rxw.match(_T("/new/user_myhid_t/est.bzip2"), _T("myhid>/bzip"), cfg));  // __.../...__
            Assert::AreEqual(false, rxw.match(_T("/new/user_myhid/_test.bzip2"), _T("myhid>/bzip"), cfg));  // __/...__
            Assert::AreEqual(false, rxw.match(_T("/new/user_myhid_test./bzip2"), _T("myhid>/bzip"), cfg));  // __.../__
            Assert::AreEqual(false, rxw.match(_T("/new/user_myhid_te/st.bzip2"), _T("myhid>/"), cfg));      // __.../...EOL
            Assert::AreEqual(false, rxw.match(_T("/new/user_myhid_te/"), _T("myhid>/"), cfg));              // __.../EOL
        }

        TEST_METHOD(uMatchTest14)
        {
            EssRxW::FlagsRxW cfg = EssRxW::FlagsRxW::F_NONE;

            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T(">"), cfg)); // > + \0
            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("> "), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T(">/zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T(">/>/zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T(" >/zip"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T(" >/"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T(">/"), cfg));
            Assert::AreEqual(false, rxw.match(_T("/dir/test.zip"), _T("r>/"), cfg));

            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("dir>//test.zip"), cfg));
            Assert::AreEqual(true, rxw.match(_T("/dir/test.zip"), _T("dir/>/test.zip"), cfg));
        }

    private:

        EssRxW rxw;

    };
}