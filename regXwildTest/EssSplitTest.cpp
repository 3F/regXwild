#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\regXwild\regXwildAPI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace net::r_eg::regXwild;


namespace regXwildTest
{
    namespace regXwild = net::r_eg::regXwild;
    using namespace regXwild::rxwtypes;

    TEST_CLASS(EssSplitTest)
    {
    public:

        TEST_METHOD(splitTest1)
        {
            tstring filter = _T("'##'|'####'");

            Assert::IsTrue(searchEss(_T("year = '2020';"), filter));
            Assert::IsTrue(searchEss(_T("year = '20';"), filter));
            Assert::IsFalse(searchEss(_T("year = '20y';"), filter));
            Assert::IsFalse(searchEss(_T("year = '2020y';"), filter));
            Assert::IsFalse(searchEss(_T("year = 2020;"), filter));
        }

        TEST_METHOD(splitTest2)
        {
            tstring filter = _T("year = '####'|year = '##'");

            Assert::IsTrue(searchEss(_T("year = '2020';"), filter));
            Assert::IsTrue(searchEss(_T("year = '20';"), filter));
            Assert::IsFalse(searchEss(_T("year = '2020y';"), filter));
            Assert::IsFalse(searchEss(_T("year = 2020;"), filter));
        }

        TEST_METHOD(splitTest3)
        {
            tstring filter = _T("str = '+++?'|str = '????'");

            Assert::IsFalse(searchEss(_T("str = '12345'"), filter));
            Assert::IsTrue(searchEss(_T("str = '1234'"), filter));
            Assert::IsTrue(searchEss(_T("str = '123'"), filter));
            Assert::IsTrue(searchEss(_T("str = '12'"), filter));
            Assert::IsTrue(searchEss(_T("str = '1'"), filter));
            Assert::IsTrue(searchEss(_T("str = ''"), filter));
        }


    private:

        bool searchEss(const tstring& data, const tstring& filter)
        {
            return regXwild::searchEss(data, filter, true);
        }

    };
}