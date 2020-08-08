#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\regXwild\regXwildAPI.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace net::r_eg::regXwild;


namespace regXwildTest
{
    namespace regXwild = net::r_eg::regXwild;

    TEST_CLASS(EssRangesTest)
    {
    public:

        TEST_METHOD(rangeAtOneTest1)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("number = '???';")));
            Assert::IsFalse(searchEss(data, _T("number = '??';")));
            Assert::IsFalse(searchEss(data, _T("number = '?';")));
            Assert::IsFalse(searchEss(data, _T("number = '';")));
            Assert::IsTrue(searchEss(data, _T("number = '????';")));
            Assert::IsTrue(searchEss(data, _T("number = '?????';")));
        }

        TEST_METHOD(rangeAtOneTest2)
        {
            tstring filter = _T("number = '???';");

            // ??? means 0 - 3
            Assert::IsTrue(searchEss(_T("number = '';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1';"), filter));
            Assert::IsTrue(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(rangeAtOneTest3)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("ber = '???';")));
            Assert::IsFalse(searchEss(data, _T("ber = '??';")));
            Assert::IsFalse(searchEss(data, _T("ber = '?';")));
            Assert::IsFalse(searchEss(data, _T("ber = '';")));
            Assert::IsTrue(searchEss(data, _T("ber = '????';")));
            Assert::IsTrue(searchEss(data, _T("ber = '?????';")));
        }

        TEST_METHOD(rangeAtOneTest4)
        {
            tstring filter = _T("ber = '???';");

            // ??? means 0 - 3
            Assert::IsTrue(searchEss(_T("number = '';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1';"), filter));
            Assert::IsTrue(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(rangeAtSingleTest1)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("number = '###';")));
            Assert::IsFalse(searchEss(data, _T("number = '##';")));
            Assert::IsFalse(searchEss(data, _T("number = '#';")));
            Assert::IsFalse(searchEss(data, _T("number = '####';")));
            Assert::IsFalse(searchEss(data, _T("number = '#####';")));
        }

        TEST_METHOD(rangeAtSingleTest2)
        {
            tstring filter = _T("number = '###';");

            // ### means only 3

            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12345';"), filter));
        }

        TEST_METHOD(rangeAtSingleTest3)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("ber = '###';")));
            Assert::IsFalse(searchEss(data, _T("ber = '##';")));
            Assert::IsFalse(searchEss(data, _T("ber = '#';")));
            Assert::IsFalse(searchEss(data, _T("ber = '####';")));
            Assert::IsFalse(searchEss(data, _T("ber = '#####';")));
        }

        TEST_METHOD(rangeAtSingleTest4)
        {
            tstring filter = _T("ber = '###';");

            // ### means only 3

            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12345';"), filter));
        }

        TEST_METHOD(rangeAtMoreTest1)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("number = '+++';")));
            Assert::IsTrue(searchEss(data, _T("number = '++';")));
            Assert::IsTrue(searchEss(data, _T("number = '+';")));
            Assert::IsFalse(searchEss(data, _T("number = '++++';")));
            Assert::IsFalse(searchEss(data, _T("number = '+++++';")));
        }

        TEST_METHOD(rangeAtMoreTest2)
        {
            tstring filter = _T("number = '+++';");

            // +++ means 3 or more
            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(rangeAtMoreTest3)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("ber = '+++';")));
            Assert::IsTrue(searchEss(data, _T("ber = '++';")));
            Assert::IsTrue(searchEss(data, _T("ber = '+';")));
            Assert::IsFalse(searchEss(data, _T("ber = '++++';")));
            Assert::IsFalse(searchEss(data, _T("ber = '+++++';")));
        }

        TEST_METHOD(rangeAtMoreTest4)
        {
            tstring filter = _T("ber = '+++';");

            // +++ means 3 or more
            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(rangeAtAnyTest1)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("number = '***';")));
            Assert::IsTrue(searchEss(data, _T("number = '**';")));
            Assert::IsTrue(searchEss(data, _T("number = '*';")));
            Assert::IsTrue(searchEss(data, _T("number = '****';")));
            Assert::IsTrue(searchEss(data, _T("number = '*****';")));
        }

        TEST_METHOD(rangeAtAnyTest2)
        {
            tstring filter = _T("number = '***';");

            // *** still means 0 or more ie. * == ***
            Assert::IsTrue(searchEss(_T("number = '';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1';"), filter));
            Assert::IsTrue(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(rangeAtAnyTest3)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("ber = '***';")));
            Assert::IsTrue(searchEss(data, _T("ber = '**';")));
            Assert::IsTrue(searchEss(data, _T("ber = '*';")));
            Assert::IsTrue(searchEss(data, _T("ber = '****';")));
            Assert::IsTrue(searchEss(data, _T("ber = '*****';")));
        }

        TEST_METHOD(rangeAtAnyTest4)
        {
            tstring filter = _T("ber = '***';");

            // *** still means 0 or more ie. * == ***
            Assert::IsTrue(searchEss(_T("number = '';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1';"), filter));
            Assert::IsTrue(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1234';"), filter));
        }

        /* '..'; >> '.'{space} */

        TEST_METHOD(wrongRangeAtOneTest1)
        {
            tstring data = _T("number = '123';");

            Assert::IsFalse(searchEss(data, _T("number = '???' ")));
            Assert::IsFalse(searchEss(data, _T("number = '??' ")));
            Assert::IsFalse(searchEss(data, _T("number = '?' ")));
            Assert::IsFalse(searchEss(data, _T("number = '' ")));
            Assert::IsFalse(searchEss(data, _T("number = '????' ")));
            Assert::IsFalse(searchEss(data, _T("number = '?????' ")));
        }

        TEST_METHOD(wrongRangeAtOneTest2)
        {
            tstring filter = _T("number = '???' ");

            // ??? means 0 - 3
            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsFalse(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(wrongRangeAtOneTest3)
        {
            tstring data = _T("number = '123';");

            Assert::IsFalse(searchEss(data, _T("ber = '???' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '??' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '?' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '????' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '?????' ")));
        }

        TEST_METHOD(wrongRangeAtOneTest4)
        {
            tstring filter = _T("ber = '???' ");

            // ??? means 0 - 3
            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsFalse(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(wrongRangeAtSingleTest1)
        {
            tstring data = _T("number = '123';");

            Assert::IsFalse(searchEss(data, _T("number = '###' ")));
            Assert::IsFalse(searchEss(data, _T("number = '##' ")));
            Assert::IsFalse(searchEss(data, _T("number = '#' ")));
            Assert::IsFalse(searchEss(data, _T("number = '####' ")));
            Assert::IsFalse(searchEss(data, _T("number = '#####' ")));
        }

        TEST_METHOD(wrongRangeAtSingleTest2)
        {
            tstring filter = _T("number = '###' ");

            // ### means only 3

            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsFalse(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12345';"), filter));
        }

        TEST_METHOD(wrongRangeAtSingleTest3)
        {
            tstring data = _T("number = '123';");

            Assert::IsFalse(searchEss(data, _T("ber = '###' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '##' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '#' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '####' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '#####' ")));
        }

        TEST_METHOD(wrongRangeAtSingleTest4)
        {
            tstring filter = _T("ber = '###' ");

            // ### means only 3

            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsFalse(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12345';"), filter));
        }

        TEST_METHOD(wrongRangeAtMoreTest1)
        {
            tstring data = _T("number = '123';");

            Assert::IsFalse(searchEss(data, _T("number = '+++' ")));
            Assert::IsFalse(searchEss(data, _T("number = '++' ")));
            Assert::IsFalse(searchEss(data, _T("number = '+' ")));
            Assert::IsFalse(searchEss(data, _T("number = '++++' ")));
            Assert::IsFalse(searchEss(data, _T("number = '+++++' ")));
        }

        TEST_METHOD(wrongRangeAtMoreTest2)
        {
            tstring filter = _T("number = '+++' ");

            // +++ means 3 or more
            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsFalse(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(wrongRangeAtMoreTest3)
        {
            tstring data = _T("number = '123';");

            Assert::IsFalse(searchEss(data, _T("ber = '+++' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '++' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '+' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '++++' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '+++++' ")));
        }

        TEST_METHOD(wrongRangeAtMoreTest4)
        {
            tstring filter = _T("ber = '+++' ");

            // +++ means 3 or more
            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsFalse(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(wrongRangeAtAnyTest1)
        {
            tstring data = _T("number = '123';");

            Assert::IsFalse(searchEss(data, _T("number = '***' ")));
            Assert::IsFalse(searchEss(data, _T("number = '**' ")));
            Assert::IsFalse(searchEss(data, _T("number = '*' ")));
            Assert::IsFalse(searchEss(data, _T("number = '****' ")));
            Assert::IsFalse(searchEss(data, _T("number = '*****' ")));
        }

        TEST_METHOD(wrongRangeAtAnyTest2)
        {
            tstring filter = _T("number = '***' ");

            // *** still means 0 or more ie. * == ***
            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsFalse(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(wrongRangeAtAnyTest3)
        {
            tstring data = _T("number = '123';");

            Assert::IsFalse(searchEss(data, _T("ber = '***' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '**' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '*' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '****' ")));
            Assert::IsFalse(searchEss(data, _T("ber = '*****' ")));
        }

        TEST_METHOD(wrongRangeAtAnyTest4)
        {
            tstring filter = _T("ber = '***' ");

            // *** still means 0 or more ie. * == ***
            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsFalse(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
        }

        /* '..'; >> '..' */

        TEST_METHOD(limRangeAtOneTest1)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("number = '???'")));
            Assert::IsFalse(searchEss(data, _T("number = '??'")));
            Assert::IsFalse(searchEss(data, _T("number = '?'")));
            Assert::IsFalse(searchEss(data, _T("number = ''")));
            Assert::IsTrue(searchEss(data, _T("number = '????'")));
            Assert::IsTrue(searchEss(data, _T("number = '?????'")));
        }

        TEST_METHOD(limRangeAtOneTest2)
        {
            tstring filter = _T("number = '???'");

            // ??? means 0 - 3
            Assert::IsTrue(searchEss(_T("number = '';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1';"), filter));
            Assert::IsTrue(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(limRangeAtOneTest3)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("ber = '???'")));
            Assert::IsFalse(searchEss(data, _T("ber = '??'")));
            Assert::IsFalse(searchEss(data, _T("ber = '?'")));
            Assert::IsFalse(searchEss(data, _T("ber = ''")));
            Assert::IsTrue(searchEss(data, _T("ber = '????'")));
            Assert::IsTrue(searchEss(data, _T("ber = '?????'")));
        }

        TEST_METHOD(limRangeAtOneTest4)
        {
            tstring filter = _T("ber = '???'");

            // ??? means 0 - 3
            Assert::IsTrue(searchEss(_T("number = '';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1';"), filter));
            Assert::IsTrue(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(limRangeAtSingleTest1)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("number = '###'")));
            Assert::IsFalse(searchEss(data, _T("number = '##'")));
            Assert::IsFalse(searchEss(data, _T("number = '#'")));
            Assert::IsFalse(searchEss(data, _T("number = '####'")));
            Assert::IsFalse(searchEss(data, _T("number = '#####'")));
        }

        TEST_METHOD(limRangeAtSingleTest2)
        {
            tstring filter = _T("number = '###'");

            // ### means only 3

            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12345';"), filter));
        }

        TEST_METHOD(limRangeAtSingleTest3)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("ber = '###'")));
            Assert::IsFalse(searchEss(data, _T("ber = '##'")));
            Assert::IsFalse(searchEss(data, _T("ber = '#'")));
            Assert::IsFalse(searchEss(data, _T("ber = '####'")));
            Assert::IsFalse(searchEss(data, _T("ber = '#####'")));
        }

        TEST_METHOD(limRangeAtSingleTest4)
        {
            tstring filter = _T("ber = '###'");

            // ### means only 3

            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1234';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12345';"), filter));
        }

        TEST_METHOD(limRangeAtMoreTest1)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("number = '+++'")));
            Assert::IsTrue(searchEss(data, _T("number = '++'")));
            Assert::IsTrue(searchEss(data, _T("number = '+'")));
            Assert::IsFalse(searchEss(data, _T("number = '++++'")));
            Assert::IsFalse(searchEss(data, _T("number = '+++++'")));
        }

        TEST_METHOD(limRangeAtMoreTest2)
        {
            tstring filter = _T("number = '+++'");

            // +++ means 3 or more
            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(limRangeAtMoreTest3)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("ber = '+++'")));
            Assert::IsTrue(searchEss(data, _T("ber = '++'")));
            Assert::IsTrue(searchEss(data, _T("ber = '+'")));
            Assert::IsFalse(searchEss(data, _T("ber = '++++'")));
            Assert::IsFalse(searchEss(data, _T("ber = '+++++'")));
        }

        TEST_METHOD(limRangeAtMoreTest4)
        {
            tstring filter = _T("ber = '+++'");

            // +++ means 3 or more
            Assert::IsFalse(searchEss(_T("number = '';"), filter));
            Assert::IsFalse(searchEss(_T("number = '1';"), filter));
            Assert::IsFalse(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(limRangeAtAnyTest1)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("number = '***'")));
            Assert::IsTrue(searchEss(data, _T("number = '**'")));
            Assert::IsTrue(searchEss(data, _T("number = '*'")));
            Assert::IsTrue(searchEss(data, _T("number = '****'")));
            Assert::IsTrue(searchEss(data, _T("number = '*****'")));
        }

        TEST_METHOD(limRangeAtAnyTest2)
        {
            tstring filter = _T("number = '***'");

            // *** still means 0 or more ie. * == ***
            Assert::IsTrue(searchEss(_T("number = '';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1';"), filter));
            Assert::IsTrue(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(limRangeAtAnyTest3)
        {
            tstring data = _T("number = '123';");

            Assert::IsTrue(searchEss(data, _T("ber = '***'")));
            Assert::IsTrue(searchEss(data, _T("ber = '**'")));
            Assert::IsTrue(searchEss(data, _T("ber = '*'")));
            Assert::IsTrue(searchEss(data, _T("ber = '****'")));
            Assert::IsTrue(searchEss(data, _T("ber = '*****'")));
        }

        TEST_METHOD(limRangeAtAnyTest4)
        {
            tstring filter = _T("ber = '***'");

            // *** still means 0 or more ie. * == ***
            Assert::IsTrue(searchEss(_T("number = '';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1';"), filter));
            Assert::IsTrue(searchEss(_T("number = '12';"), filter));
            Assert::IsTrue(searchEss(_T("number = '123';"), filter));
            Assert::IsTrue(searchEss(_T("number = '1234';"), filter));
        }

        TEST_METHOD(mixTest1)
        {
            Assert::IsTrue(searchEss(_T("number = '123';"), _T("number = '??3';")));

            Assert::IsTrue(searchEss(_T("12345"), _T("1##45")));
            Assert::IsFalse(searchEss(_T("12345"), _T("1##5")));

            Assert::IsFalse(searchEss(_T("test = 12345"), _T("test 1##5")));
            Assert::IsFalse(searchEss(_T("test = 12345"), _T("test = 1##5")));
            Assert::IsTrue(searchEss(_T("test = 12345"), _T("test = 1##")));

            Assert::IsFalse(searchEss(_T("test = 12345;"), _T("test = 1##;")));
            Assert::IsTrue(searchEss(_T("test = 12345;"), _T("test = 1####;")));
            Assert::IsTrue(searchEss(_T("test = 12345;"), _T("test = 1##")));
            Assert::IsTrue(searchEss(_T("test = 12345;"), _T("test = 1##4#;")));
        }


    private:

        bool searchEss(const tstring& data, const tstring& filter)
        {
            return regXwild::searchEss(data, filter, true);
        }

    };
}