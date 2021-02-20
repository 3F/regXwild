#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\regXwild\regXwild.common.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace net::r_eg::regXwild;


namespace regXwildTest
{
    namespace regXwild = net::r_eg::regXwild;
    using namespace regXwild::rxwtypes;

    TEST_CLASS(EssFlagICASETest)
    {
    public:

        void uMatchTest1Set(const EssRxW::FlagsRxW& cfg)
        {
            Assert::AreEqual(false, rxw.match(_T("system"), _T("syStem"), cfg));
            Assert::AreEqual(true, rxw.match(_T("system"), _T("system"), cfg));
            Assert::AreEqual(false, rxw.match(_T("syStem"), _T("system"), cfg));
            Assert::AreEqual(true, rxw.match(_T("SYSTEM"), _T("SYSTEM"), cfg));

            Assert::AreEqual(false, rxw.match(_T("system"), _T("sy*Stem"), cfg));
            Assert::AreEqual(false, rxw.match(_T("system"), _T("syS*tem"), cfg));
            Assert::AreEqual(true, rxw.match(_T("system"), _T("sy*stem"), cfg));
        }

        TEST_METHOD(uMatchTest1)
        {
            uMatchTest1Set(EssRxW::FlagsRxW::F_NONE);
            uMatchTest1Set(EssRxW::FlagsRxW::F_LEGACY_ANYSP | EssRxW::FlagsRxW::F_MATCH_RESULT);
        }

        void uMatchTest2Set(const EssRxW::FlagsRxW& cfg)
        {
            Assert::AreEqual(true, rxw.match(_T("system"), _T("syStem"), cfg));
            Assert::AreEqual(true, rxw.match(_T("system"), _T("system"), cfg));
            Assert::AreEqual(true, rxw.match(_T("syStem"), _T("system"), cfg));
            Assert::AreEqual(true, rxw.match(_T("SYSTEM"), _T("SYSTEM"), cfg));

            Assert::AreEqual(true, rxw.match(_T("system"), _T("sy*Stem"), cfg));
            Assert::AreEqual(true, rxw.match(_T("system"), _T("syS*tem"), cfg));
            Assert::AreEqual(true, rxw.match(_T("system"), _T("sy*stem"), cfg));
        }

        TEST_METHOD(uMatchTest2)
        {
            uMatchTest2Set(EssRxW::FlagsRxW::F_ICASE);
            uMatchTest2Set(EssRxW::FlagsRxW::F_ICASE | EssRxW::FlagsRxW::F_MATCH_RESULT);
        }

        TEST_METHOD(uMatchTest3)
        {
            Assert::IsFalse(rxw.match(_T("number = '1271';"), _T("NUMBER = '????';")));
            Assert::IsFalse(rxw.match(_T("number = 888;"), _T("NUMBER = +??;")));

            Assert::IsFalse(rxw.match(_T("everything is ok"), _T("^everything*OK$")));
            Assert::IsFalse(rxw.match(_T("systems"), _T("systeM?")));
            Assert::IsFalse(rxw.match(_T("systems"), _T("sys###S")));
            Assert::IsFalse(rxw.match(_T("A new 'X1' project"), _T("^a*'+' pro?ect")));
            Assert::IsFalse(rxw.match(_T("professional system"), _T("pro*System")));
            Assert::IsFalse(rxw.match(_T("regXwild in action"), _T("pro?ect$|open*source+act|^regxwild")));
        }


    private:

        EssRxW rxw;

    };
}