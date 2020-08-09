#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\regXwild\regXwildAPI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace net::r_eg::regXwild;


namespace regXwildTest
{
    namespace regXwild = net::r_eg::regXwild;

    TEST_CLASS(EssSamplesTest)
    {
    public:

        TEST_METHOD(sReadmeTest1)
        {
            Assert::IsTrue(searchEss(_T("number = '1271';"), _T("number = '????';")));
            Assert::IsTrue(searchEss(_T("year = '2020';"), _T("'##'|'####'")));
            Assert::IsTrue(searchEss(_T("year = '20';"), _T("= '##??'")));
            Assert::IsTrue(searchEss(_T("number = 888;"), _T("number = +??;")));

            // opposite data

            Assert::IsFalse(searchEss(_T("number = '12710';"), _T("number = '????';")));
            Assert::IsFalse(searchEss(_T("year = '2020y';"), _T("'##'|'####'")));
            Assert::IsFalse(searchEss(_T("year = '20y';"), _T("= '##??'")));
            Assert::IsFalse(searchEss(_T("number = 8888;"), _T("number = +??;")));
        }

        TEST_METHOD(sReadmeTest2)
        {
            Assert::IsTrue(searchEss(_T("everything is ok"), _T("^everything*ok$")));
            Assert::IsTrue(searchEss(_T("systems"), _T("system?")));
            Assert::IsTrue(searchEss(_T("systems"), _T("sys###s")));
            Assert::IsTrue(searchEss(_T("A new 'X1' project"), _T("^A*'+' pro?ect")));
            Assert::IsTrue(searchEss(_T("professional system"), _T("pro*system")));
            Assert::IsTrue(searchEss(_T("regXwild in action"), _T("pro?ect$|open*source+act|^regXwild")));

            // opposite data

            Assert::IsFalse(searchEss(_T("everything is okay"), _T("^everything*ok$")));
            Assert::IsTrue(searchEss(_T("system"), _T("system?")));
            Assert::IsFalse(searchEss(_T("sys-tems"), _T("sys###s")));
            Assert::IsTrue(searchEss(_T("An amazing 'Y2' protect"), _T("^A*'+' pro?ect")));
            Assert::IsTrue(searchEss(_T("protecting system"), _T("pro*system")));
            Assert::IsTrue(searchEss(_T("opensource project regXwild in action"), _T("pro?ect$|open*source+act|^regXwild")));
        }


    private:

        bool searchEss(const tstring& data, const tstring& filter)
        {
            return regXwild::searchEss(data, filter, false);
        }

    };
}