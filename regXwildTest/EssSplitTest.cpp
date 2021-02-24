#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\regXwild\regXwild.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace net::r_eg::regXwild;
using namespace net::r_eg::regXwild::rxwtypes;

namespace regXwildTest
{
    TEST_CLASS(EssSplitTest)
    {
    public:

        TEST_METHOD(splitTest1)
        {
            tstring filter = _T("'##'|'####'");

            Assert::IsTrue(rxw.match(_T("year = '2020';"), filter));
            Assert::IsTrue(rxw.match(_T("year = '20';"), filter));
            Assert::IsFalse(rxw.match(_T("year = '20y';"), filter));
            Assert::IsFalse(rxw.match(_T("year = '2020y';"), filter));
            Assert::IsFalse(rxw.match(_T("year = 2020;"), filter));
        }

        TEST_METHOD(splitTest2)
        {
            tstring filter = _T("year = '####'|year = '##'");

            Assert::IsTrue(rxw.match(_T("year = '2020';"), filter));
            Assert::IsTrue(rxw.match(_T("year = '20';"), filter));
            Assert::IsFalse(rxw.match(_T("year = '2020y';"), filter));
            Assert::IsFalse(rxw.match(_T("year = 2020;"), filter));
        }

        TEST_METHOD(splitTest3)
        {
            tstring filter = _T("str = '+++?'|str = '????'");

            Assert::IsFalse(rxw.match(_T("str = '12345'"), filter));
            Assert::IsTrue(rxw.match(_T("str = '1234'"), filter));
            Assert::IsTrue(rxw.match(_T("str = '123'"), filter));
            Assert::IsTrue(rxw.match(_T("str = '12'"), filter));
            Assert::IsTrue(rxw.match(_T("str = '1'"), filter));
            Assert::IsTrue(rxw.match(_T("str = ''"), filter));
        }


    private:

        EssRxW rxw;

    };
}