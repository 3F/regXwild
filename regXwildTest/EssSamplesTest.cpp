#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\regXwild\regXwild.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace net::r_eg::regXwild;

namespace regXwildTest
{
    TEST_CLASS(EssSamplesTest)
    {
    public:

        TEST_METHOD(sReadmeTest1)
        {
            Assert::IsTrue(rxw.match(_T("number = '1271';"), _T("number = '????';")));
            Assert::IsTrue(rxw.match(_T("year = '2020';"), _T("'##'|'####'")));
            Assert::IsTrue(rxw.match(_T("year = '20';"), _T("= '##??'")));
            Assert::IsTrue(rxw.match(_T("number = 888;"), _T("number = +??;")));

            // opposite data

            Assert::IsFalse(rxw.match(_T("number = '12710';"), _T("number = '????';")));
            Assert::IsFalse(rxw.match(_T("year = '2020y';"), _T("'##'|'####'")));
            Assert::IsFalse(rxw.match(_T("year = '20y';"), _T("= '##??'")));
            Assert::IsFalse(rxw.match(_T("number = 8888;"), _T("number = +??;")));
        }

        TEST_METHOD(sReadmeTest2)
        {
            Assert::IsTrue(rxw.match(_T("everything is ok"), _T("^everything*ok$")));
            Assert::IsTrue(rxw.match(_T("systems"), _T("system?")));
            Assert::IsTrue(rxw.match(_T("systems"), _T("sys###s")));
            Assert::IsTrue(rxw.match(_T("A new 'X1' project"), _T("^A*'+' pro?ect")));
            Assert::IsTrue(rxw.match(_T("professional system"), _T("pro*system")));
            Assert::IsTrue(rxw.match(_T("regXwild in action"), _T("pro?ect$|open*source+act|^regXwild")));

            // opposite data

            Assert::IsFalse(rxw.match(_T("everything is okay"), _T("^everything*ok$")));
            Assert::IsTrue(rxw.match(_T("system"), _T("system?")));
            Assert::IsFalse(rxw.match(_T("sys-tems"), _T("sys###s")));
            Assert::IsTrue(rxw.match(_T("An amazing 'Y2' protect"), _T("^A*'+' pro?ect")));
            Assert::IsTrue(rxw.match(_T("protecting system"), _T("pro*system")));
            Assert::IsTrue(rxw.match(_T("opensource project regXwild in action"), _T("pro?ect$|open*source+act|^regXwild")));
        }


    private:

        EssRxW rxw;

    };
}