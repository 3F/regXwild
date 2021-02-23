#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\regXwild\regXwild.common.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace net::r_eg::regXwild;


namespace regXwildTest
{
    namespace regXwild = net::r_eg::regXwild;
    using namespace regXwild::rxwtypes;

    TEST_CLASS(EssMatchTest)
    {
    public:

#if _RXW_FEATURE_MATCH_RESULT
        TEST_METHOD(uMatchTest1)
        {
            tstring input = _T("number = 8888; //TODO: up");
            EssRxW::Match m;

            assertTrueAndEqual(input, _T("= +;"), 7, 14, m);
            assertTrueAndEqual(input, _T("= +;*//TODO"), 7, 21, m);
        }

        TEST_METHOD(uMatchTest2)
        {
            tstring input = _T("number = 8888; //TODO: up");
            EssRxW::Match m;

            assertTrueAndEqual(input, _T("//+:"), 15, 22, m);

            assertFalse(input, _T("= +;*//NOTE"), m);
        }

        TEST_METHOD(uMatchTest3)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("0123456789"), _T("456"), 4, 7, m);
            assertTrueAndEqual(_T("01298"), _T("0#2?9"), 0, 4, m);
        }

        TEST_METHOD(uMatchTest4)
        {
            EssRxW::Match m;
            tstring input = _T("0012398");

            assertTrueAndEqual(input, _T("0#2?9"), 1, 6, m);

            assertTrueAndNpos
            (
                rxw.match(input, _T("0#2?9"), EssRxW::FlagsRxW::F_NONE, &m),
                m
            );
            
            assertFalse(input, _T("^0#2?9"), m);
            assertFalse(input, _T("0#2?9$"), m);

            assertTrueAndEqual(input, _T("^0#1*8$"), 0, 7, m);
        }

        TEST_METHOD(uMatchTest5)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("001-sd"), _T("#-sd"), 2, 6, m);
            assertTrueAndEqual(_T("sd-01"), _T("d-##"), 1, 5, m);
            assertTrueAndEqual(_T("sd-01"), _T("sd-##"), 0, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("##-sd"), 0, 5, m);
            assertTrueAndEqual(_T("sd-01"), _T("sd-#"), 0, 4, m);
            
            assertTrueAndEqual(_T("sd-01"), _T("d-#"), 1, 4, m);
            assertTrueAndEqual(_T("01-sd"), _T("##-s"), 0, 4, m);
        }

        TEST_METHOD(uMatchTest6)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("sd-01-d2"), _T("sd-##-#2"), 0, 8, m);
            assertTrueAndEqual(_T("01-dd-02"), _T("#1-dd-0#"), 0, 8, m);
            assertTrueAndEqual(_T("sd-01-d2"), _T("sd-##-d"), 0, 7, m);

            assertTrueAndEqual(_T("01-dd-02"), _T("0#-dd-#2"), 0, 8, m);
            assertTrueAndEqual(_T("01-dd-02"), _T("##-dd-##"), 0, 8, m);
        }

        TEST_METHOD(uMatchTest7)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("sd-01"), _T("sd-*"), 0, 3, m); //TODO: option for -> lazy (3) ; -> greedy (5)
            assertTrueAndEqual(_T("sd-01"), _T("d-*"), 1, 3, m); //TODO: option for -> lazy (3) ; -> greedy (5)
            assertTrueAndEqual(_T("01-sd"), _T("*-sd"), 2, 5, m); //TODO: option for lazy (2) -> ; greedy (0) ->
            assertTrueAndEqual(_T("01-sd"), _T("*-s"), 2, 4, m); //TODO: option for lazy (2) -> ; greedy (0) ->
            assertTrueAndEqual(_T("01-sd"), _T("0*-sd"), 0, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("0*-s"), 0, 4, m);
            assertTrueAndEqual(_T("012-sd"), _T("1*-s"), 1, 5, m);

            assertTrueAndEqual(_T("sd-01-d2"), _T("sd-*d"), 0, 7, m);
            assertTrueAndEqual(_T("sd-01-d2"), _T("sd-*d2"), 0, 8, m);
            assertTrueAndEqual(_T("sd-01-d2"), _T("d-*d"), 1, 7, m);
            assertTrueAndEqual(_T("sd-01-d2"), _T("d-*2"), 1, 8, m);
        }

        TEST_METHOD(uMatchTest8)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("01-sd"), _T("+-sd"), 0, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("+-s"), 0, 4, m);
            assertTrueAndEqual(_T("sd-01"), _T("sd-+"), 0, 5, m);
            assertTrueAndEqual(_T("sd-01"), _T("d-+"), 1, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("0+-sd"), 0, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("0+-s"), 0, 4, m);
        }

        TEST_METHOD(uMatchTest9)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("01-dd-02"), _T("+1-dd-0+"), 0, 8, m);

            assertTrueAndEqual(_T("sd-01-d2"), _T("sd-++-+2"), 0, 8, m);
            assertTrueAndEqual(_T("sd-01-d2"), _T("sd-++-d"), 0, 7, m);

            assertTrueAndEqual(_T("sd-01-d2"), _T("sd-+-+2"), 0, 8, m);
            assertTrueAndEqual(_T("sd-01-d2"), _T("sd-+-d"), 0, 7, m);

            assertTrueAndEqual(_T("01-dd-02"), _T("0+-dd-+2"), 0, 8, m);
            assertTrueAndEqual(_T("01-dd-02"), _T("++-dd-++"), 0, 8, m);
            assertTrueAndEqual(_T("01-dd-02"), _T("+-dd-+"), 0, 8, m);
        }

        TEST_METHOD(uMatchTest10)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("sd-01"), _T("sd-?"), 0, 3, m); //TODO: option for -> lazy (3) ; -> greedy (4)
            assertTrueAndEqual(_T("sd-01"), _T("d-?"), 1, 3, m); //TODO: option for -> lazy (3) ; -> greedy (4)
            assertTrueAndEqual(_T("sd-01"), _T("sd-??"), 0, 3, m); //TODO: option for -> lazy (3) ; -> greedy (5)
            assertTrueAndEqual(_T("sd-01"), _T("d-??"), 1, 3, m); //TODO: option for -> lazy (3) ; -> greedy (5)

            assertTrueAndEqual(_T("01-sd"), _T("?-sd"), 2, 5, m); //TODO: option for lazy (2) -> ; greedy (1) ->
            assertTrueAndEqual(_T("01-sd"), _T("??-sd"), 2, 5, m); //TODO: option for lazy (2) -> ; greedy (0) ->
            assertTrueAndEqual(_T("01-sd"), _T("??-s"), 2, 4, m); //TODO: option for lazy (2) -> ; greedy (0) ->
            assertTrueAndEqual(_T("01-sd"), _T("?-s"), 2, 4, m); //TODO: option for lazy (2) -> ; greedy (1) ->

            assertTrueAndEqual(_T("01-sd"), _T("0??-sd"), 0, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("0??-s"), 0, 4, m);

            assertTrueAndEqual(_T("00-sd"), _T("0?-s"), 1, 4, m); //TODO: ? option for lazy/greedy
            assertTrueAndEqual(_T("00-sd"), _T("0??-s"), 1, 4, m); //TODO: ? option for lazy/greedy
            assertTrueAndEqual(_T("00-sd"), _T("?0-s"), 1, 4, m);  //TODO: option for lazy (1) -> ; greedy (0) ->
            assertTrueAndEqual(_T("00-sd"), _T("??0-s"), 1, 4, m); //TODO: option for lazy (1) -> ; greedy (0) ->
        }

        TEST_METHOD(uMatchTest11)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("sd-01"), _T("sd-#"), 0, 4, m);
            assertTrueAndEqual(_T("sd-01"), _T("d-#"), 1, 4, m);
            assertTrueAndEqual(_T("sd-01"), _T("sd-##"), 0, 5, m);
            assertTrueAndEqual(_T("sd-01"), _T("d-##"), 1, 5, m);
            
            assertTrueAndEqual(_T("01-sd"), _T("#-sd"), 1, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("##-sd"), 0, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("##-s"), 0, 4, m);
            assertTrueAndEqual(_T("01-sd"), _T("#-s"), 1, 4, m);

            assertTrueAndEqual(_T("01-sd"), _T("0#-sd"), 0, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("0#-s"), 0, 4, m);

            assertFalse(_T("01-sd"), _T("0##-s"), m);
            assertFalse(_T("00-sd"), _T("0##-s"), m);

            assertTrueAndEqual(_T("00-sd"), _T("0#-s"), 0, 4, m);
            assertTrueAndEqual(_T("00-sd"), _T("#0-s"), 0, 4, m);
        }

        TEST_METHOD(uMatchTest12)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("sd-01"), _T("sd-+"), 0, 5, m);
            assertTrueAndEqual(_T("sd-01"), _T("d-+"), 1, 5, m);
            assertTrueAndEqual(_T("sd-01"), _T("sd-++"), 0, 5, m);
            assertTrueAndEqual(_T("sd-01"), _T("d-++"), 1, 5, m);
            
            assertTrueAndEqual(_T("01-sd"), _T("+-sd"), 0, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("++-sd"), 0, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("++-s"), 0, 4, m);
            assertTrueAndEqual(_T("01-sd"), _T("+-s"), 0, 4, m);

            assertTrueAndEqual(_T("01-sd"), _T("0++d"), 0, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("0++s"), 0, 4, m);
            assertFalse(_T("01-sd"), _T("0++-d"), m);

            assertFalse(_T("01-sd"), _T("0++-s"), m);
            assertFalse(_T("00-sd"), _T("0++-s"), m);

            assertTrueAndEqual(_T("00-sd"), _T("0+-s"), 0, 4, m);
            assertFalse(_T("00-sd"), _T("0++-d"), m);
            assertFalse(_T("00-sd"), _T("0++-s"), m);
            assertTrueAndEqual(_T("00-sd"), _T("0+-s"), 0, 4, m);
            assertTrueAndEqual(_T("00-sd"), _T("0++s"), 0, 4, m);
            assertTrueAndEqual(_T("00-sd"), _T("+0-s"), 0, 4, m);
            assertFalse(_T("00-sd"), _T("++0-s"), m);
        }

        TEST_METHOD(uMatchTest13)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("sd-01"), _T("sd-*"), 0, 3, m);
            assertTrueAndEqual(_T("sd-01"), _T("d-*"), 1, 3, m);
            assertTrueAndEqual(_T("sd-01"), _T("sd-**"), 0, 3, m);
            assertTrueAndEqual(_T("sd-01"), _T("d-**"), 1, 3, m);
            
            assertTrueAndEqual(_T("01-sd"), _T("*-sd"), 2, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("**-sd"), 2, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("**-s"), 2, 4, m);
            assertTrueAndEqual(_T("01-sd"), _T("*-s"), 2, 4, m);

            assertTrueAndEqual(_T("01-sd"), _T("s*d"), 3, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("0*-sd"), 0, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("0*-s"), 0, 4, m);

            assertTrueAndEqual(_T("00-sd"), _T("0*-s"), 1, 4, m);
            assertTrueAndEqual(_T("00-sd"), _T("0*-s"), 1, 4, m);
            assertTrueAndEqual(_T("00-sd"), _T("*0-s"), 1, 4, m);
            assertTrueAndEqual(_T("00-sd"), _T("**0-s"), 1, 4, m);
        }

        TEST_METHOD(uMatchTest14)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("sd-01-d2"), _T("sd-??-d?"), 0, 7, m); //TODO: option for -> lazy (7) ; -> greedy (8)
            assertTrueAndEqual(_T("sd-01-d2"), _T("sd-??-?2"), 0, 8, m);

            assertTrueAndEqual(_T("sd-01-d2"), _T("d-?1-?2"), 1, 8, m);
            assertTrueAndEqual(_T("sd-01-d2"), _T("d-?1-d?"), 1, 7, m); //TODO: option for -> lazy (7) ; -> greedy (8)

            assertTrueAndEqual(_T("01-dd-02"), _T("?1-dd-0?"), 1, 7, m); //TODO: option for lazy (1<->7) ; greedy (0<->8)
            assertTrueAndEqual(_T("01-dd-02"), _T("0?-dd-0?"), 0, 7, m); //TODO: option for -> lazy (7) ; -> greedy (8)

            assertTrueAndEqual(_T("sd-01-d2"), _T("sd-??-?2"), 0, 8, m);
            assertTrueAndEqual(_T("sd-01-d2"), _T("sd-??-d"), 0, 7, m);

            assertTrueAndEqual(_T("01-dd-02"), _T("0?-dd-?2"), 0, 8, m);
            assertTrueAndEqual(_T("01-dd-02"), _T("??-dd-??"), 2, 6, m); //TODO: option for lazy (2<->6) ; greedy (0<->8)
        }

        TEST_METHOD(uMatchTest15)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T(" 123"), _T(" "), 0, 1, m);
            assertFalse(_T("123"), _T(" "), m);

            assertTrueAndEqual(_T("t123"), _T(""), 0, 4, m);
            assertTrueAndEqual(_T(""), _T(""), 0, 0, m);

            assertTrueAndEqual(_T(""), _T("?"), 0, 0, m);
            assertTrueAndEqual(_T(""), _T("??"), 0, 0, m);

            assertTrueAndEqual(_T(""), _T("*"), 0, 0, m);
            assertTrueAndEqual(_T(""), _T("**"), 0, 0, m);

            assertFalse(_T(""), _T("#"), m);
            assertFalse(_T(""), _T("##"), m);

            assertFalse(_T(""), _T("+"), m);
            assertFalse(_T(""), _T("++"), m);
        }

        TEST_METHOD(uMatchTest16)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("sd-m4"), _T("s*4"), 0, 5, m);
            assertTrueAndEqual(_T("sd-m4"), _T("d*4"), 1, 5, m);
            assertTrueAndEqual(_T("sd-m4"), _T("s*m"), 0, 4, m);
            assertTrueAndEqual(_T("sd-m4"), _T("d*m"), 1, 4, m);

            assertTrueAndEqual(_T("sd-m4"), _T("sd?m4"), 0, 5, m);
            assertTrueAndEqual(_T("sd-m4"), _T("sd+m4"), 0, 5, m);
            assertTrueAndEqual(_T("sd-m4"), _T("sd#m4"), 0, 5, m);

            assertTrueAndEqual(_T("sd"), _T("????"), 0, 0, m); //TODO: option for -> lazy (0) ; -> greedy (2)
            assertTrueAndEqual(_T("sd"), _T("???"), 0, 0, m); //TODO: option for -> lazy (0) ; -> greedy (2)
            assertTrueAndEqual(_T("sd"), _T("??"), 0, 0, m); //TODO: option for -> lazy (0) ; -> greedy (2)
            assertTrueAndEqual(_T("sd"), _T("?"), 0, 0, m);
            assertTrueAndEqual(_T("sd"), _T("s?"), 0, 1, m); //TODO: option for -> lazy (1) ; -> greedy (2)
            assertTrueAndEqual(_T("sd"), _T("s??"), 0, 1, m); //TODO: option for -> lazy (1) ; -> greedy (2)
        }

        TEST_METHOD(uMatchTest17)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("sd"), _T("#"), 0, 1, m);
            assertTrueAndEqual(_T("sd"), _T("##"), 0, 2, m);
            assertTrueAndEqual(_T("s"), _T("#"), 0, 1, m);

            assertTrueAndEqual(_T("sd"), _T("*"), 0, 0, m); //TODO: option for -> lazy (0) ; -> greedy (2)
            assertTrueAndEqual(_T("sd1"), _T("**"), 0, 0, m); //TODO: option for -> lazy (0) ; -> greedy (3)
            assertTrueAndEqual(_T("s"), _T("*"), 0, 0, m); //TODO: option for -> lazy (0) ; -> greedy (1)

            assertTrueAndEqual(_T("sd"), _T("s*"), 0, 1, m); //TODO: option for -> lazy (1) ; -> greedy (2)
            assertTrueAndEqual(_T("sd"), _T("s#"), 0, 2, m);
            assertTrueAndEqual(_T("sd"), _T("s+"), 0, 2, m);
            assertTrueAndEqual(_T("sd"), _T("+"), 0, 2, m);
            assertTrueAndEqual(_T("sd"), _T("++"), 0, 2, m);
        }

        TEST_METHOD(uMatchTest18)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("012"), _T("0?1"), 0, 2, m);
            assertTrueAndEqual(_T("0123"), _T("0?2"), 0, 3, m);
            assertTrueAndEqual(_T("00123"), _T("0?2"), 1, 4, m);
            assertTrueAndEqual(_T("00123"), _T("0?1"), 1, 3, m);

            assertTrueAndEqual(_T("012"), _T("0*1"), 0, 2, m);
            assertTrueAndEqual(_T("00123"), _T("0*1"), 1, 3, m); //TODO: option for lazy (1) -> ; greedy (0) ->

            assertTrueAndEqual(_T("0012345"), _T("0?2#4"), 1, 6, m);
            assertTrueAndEqual(_T("012345"), _T("0?2#4"), 0, 5, m);

            assertTrueAndEqual(_T("00123"), _T("0#2"), 1, 4, m);
            assertTrueAndEqual(_T("012345"), _T("0#2#4"), 0, 5, m);
            assertTrueAndEqual(_T("0012345"), _T("0#2#4"), 1, 6, m);

            assertTrueAndEqual(_T("00123"), _T("0+2"), 0, 4, m);
            assertTrueAndEqual(_T("012345"), _T("0+2#4"), 0, 5, m);
            assertTrueAndEqual(_T("0012345"), _T("0+2#4"), 0, 6, m);

            assertTrueAndEqual(_T("00123"), _T("0*2"), 0, 4, m);
            assertTrueAndEqual(_T("012345"), _T("0*2#4"), 0, 5, m);
            assertTrueAndEqual(_T("0012345"), _T("0*2#4"), 0, 6, m);

            assertTrueAndEqual(_T("001-dd-"), _T("0?-d#-"), 1, 7, m);
            assertTrueAndEqual(_T("001-dd-"), _T("0#-d#-"), 1, 7, m);

            assertTrueAndEqual(_T("001-dd-"), _T("0+-d#-"), 0, 7, m);
            assertTrueAndEqual(_T("001-dd-"), _T("0*-d#-"), 0, 7, m);
        }

        TEST_METHOD(uMatchTest19)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("00123"), _T("0##?2"), 0, 4, m);
            assertTrueAndEqual(_T("00123"), _T("0#?2"), 0, 4, m); //TODO: option for lazy (1) -> ; greedy (0) ->
            assertTrueAndEqual(_T("012345"), _T("0#?2#?4"), 0, 5, m);
            assertTrueAndEqual(_T("0012345"), _T("0#?2#?4"), 0, 6, m); //TODO: option for lazy (1) -> ; greedy (0) ->

            assertTrueAndEqual(_T("00123"), _T("0++?2"), 0, 4, m);
            assertTrueAndEqual(_T("00123"), _T("0+?2"), 0, 4, m); //TODO: option for lazy (1) -> ; greedy (0) ->
            assertTrueAndEqual(_T("012345"), _T("0+?2+?4"), 0, 5, m);
            assertTrueAndEqual(_T("0012345"), _T("0+?2+?4"), 0, 6, m); //TODO: option for lazy (1) -> ; greedy (0) ->
        }

        TEST_METHOD(uMatchTest20)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("012345"), _T("0+2>/4"), 0, 5, m);
            assertTrueAndEqual(_T("0012345"), _T("0+2>/4"), 0, 6, m);

            assertFalse(_T("00/12345"), _T("0>/2>/4"), m);
            assertFalse(_T("0012-345"), _T("0>/2>-4"), m);

            assertTrueAndEqual(_T("00123"), _T("0>/2"), 0, 4, m);
            assertTrueAndEqual(_T("012345"), _T("0>/2+4"), 0, 5, m);
            assertTrueAndEqual(_T("0012345"), _T("0>/2+4"), 0, 6, m);

            assertFalse(_T("00/123"), _T("0>/2"), m);
            assertFalse(_T("0/0123"), _T("0>/2"), m);
            assertFalse(_T("012/345"), _T("0>/2>/4"), m);
        }

        TEST_METHOD(uMatchTest21)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("01-dd-02-ff"), _T("0?-d#-0+-*f"), 0, 10, m);
            assertTrueAndEqual(_T("001-dd-02-ff"), _T("0?-d#-0+-*f"), 1, 11, m);

            assertTrueAndEqual(_T("01-dd-02-ff"), _T("0?-d#-0+-f*"), 0, 10, m);
            assertTrueAndEqual(_T("0040012398"), _T("0#5|0#2?9"), 4, 9, m);
        }

        TEST_METHOD(uGreedyBalanceTest1)
        {
            EssRxW::Match m;

            // Greedy: + # 
            // Lazy:   * ?

            assertTrueAndEqual(_T("00000-d-00000"), _T("??0-d-0??"), 4, 9, m);
            assertTrueAndEqual(_T("000-d-000"), _T("?0-d-0?"), 2, 7, m);

            assertTrueAndEqual(_T("000-d-000"), _T("+0-d-0+"), 0, 9, m);
            assertTrueAndEqual(_T("000-d-000"), _T("#0-d-0#"), 1, 8, m);
            assertTrueAndEqual(_T("000-d-000"), _T("*0-d-0*"), 2, 7, m);

            assertTrueAndEqual(_T("00000-d-00000"), _T("++0-d-0++"), 0, 13, m);
            assertTrueAndEqual(_T("00000-d-00000"), _T("##0-d-0##"), 2, 11, m);
            assertTrueAndEqual(_T("00000-d-00000"), _T("*0-d-0*"), 4, 9, m);
        }

        TEST_METHOD(uMatchBmsTest1)
        {
            EssRxW::Match m;

            tstring data = _T("00123");
            assertTrueAndEqual(data, _T("^0012"), 0, 4, m);
            assertTrueAndEqual(data, _T("^00#2"), 0, 4, m);

            assertFalse(data, _T("^0#2"), m);
            assertFalse(data, _T("^0##3"), m);
            assertFalse(data, _T("^01"), m);

            data = _T("0123");
            assertFalse(data, _T("^0#3"), m);
            assertTrueAndEqual(data, _T("^0#2"), 0, 3, m);
        }

        TEST_METHOD(uMatchBmsTest2)
        {
            EssRxW::Match m;
            tstring data = _T("00123");

            assertTrueAndEqual(data, _T("^0+2"), 0, 4, m);
            assertTrueAndEqual(data, _T("^0*2"), 0, 4, m);
            assertTrueAndEqual(data, _T("^00*2"), 0, 4, m);
            
            assertTrueAndEqual(data, _T("^00+2"), 0, 4, m);
            assertTrueAndEqual(data, _T("^00?2"), 0, 4, m);
            assertTrueAndEqual(data, _T("^001?2"), 0, 4, m);

            assertFalse(data, _T("^0012*2"), m);
            assertFalse(data, _T("^001+2"), m);
            assertFalse(data, _T("^0?2"), m);
        }

        TEST_METHOD(uMatchBmsTest3)
        {
            EssRxW::Match m;
            tstring data = _T("001234");

            assertTrueAndEqual(data, _T("^00+?2"), 0, 4, m);
            assertTrueAndEqual(data, _T("^00+?3"), 0, 5, m);
            assertTrueAndEqual(data, _T("^0#?2"), 0, 4, m);

            assertFalse(data, _T("^00+?4"), m);
            assertFalse(data, _T("^0+?3"), m);
            assertFalse(data, _T("^001#?2"), m);
        }

        TEST_METHOD(uMatchBmsTest4)
        {
            EssRxW::Match m;
            tstring data = _T("00123");

            assertTrueAndEqual(data, _T("^00##3"), 0, 5, m);
            assertTrueAndEqual(data, _T("^0++3"), 0, 5, m);
            assertTrueAndEqual(data, _T("^00++3"), 0, 5, m);
            assertTrueAndEqual(data, _T("^0??2"), 0, 4, m);
            assertTrueAndEqual(data, _T("0???2"), 0, 4, m);
            assertTrueAndEqual(data, _T("^0???2"), 0, 4, m);
            assertTrueAndEqual(data, _T("^0???3"), 0, 5, m);

            assertFalse(data, _T("^0##3"), m);
            assertFalse(data, _T("^001++3"), m);
            assertFalse(data, _T("^0??3"), m);
        }

        TEST_METHOD(uMatchBmsTest5)
        {
            EssRxW::Match m;
            assertTrueAndEqual(_T("0123"), _T("^0>/1"), 0, 2, m);
            assertTrueAndEqual(_T("00123"), _T("^0>/3"), 0, 5, m);

            assertTrueAndNpos(
                rxw.match(_T("0123"), _T("^0>/1"), EssRxW::FlagsRxW::F_NONE, &m),
                m
            );
            assertTrueAndNpos(
                rxw.match(_T("00123"), _T("^0>/3"), EssRxW::FlagsRxW::F_NONE, &m),
                m
            );

            assertFalse(rxw.match(_T("00/123"), _T("^0>/3"), EssRxW::FlagsRxW::F_NONE), m);
            assertFalse(rxw.match(_T("0123"), _T("^1>/3"), EssRxW::FlagsRxW::F_NONE), m);
            assertFalse(rxw.match(_T("0123"), _T("^0>/0"), EssRxW::FlagsRxW::F_NONE), m);
            assertFalse(rxw.match(_T("0/123"), _T("^0>/1"), EssRxW::FlagsRxW::F_NONE), m);
        }

        TEST_METHOD(uMatchEmsTest1)
        {
            EssRxW::Match m;

            assertTrueAndEqual(_T("43210"), _T("3#1"), 1, 4, m);
            assertTrueAndEqual(_T("43210"), _T("2#0$"), 2, 5, m);

            assertFalse(_T("43210"), _T("3#0$"), m);
            assertFalse(_T("43210"), _T("3#1$"), m);

            tstring data = _T("32100");
            assertTrueAndEqual(data, _T("2##0$"), 1, 5, m);
            assertTrueAndEqual(data, _T("2#00$"), 1, 5, m);
            assertTrueAndEqual(data, _T("2100$"), 1, 5, m);

            assertFalse(data, _T("2#0$"), m);
            assertFalse(data, _T("10$"), m);
            assertFalse(data, _T("210$"), m);
            assertFalse(data, _T("1200$"), m);
        }

        TEST_METHOD(uMatchEmsTest2)
        {
            EssRxW::Match m;
            tstring data = _T("32100");

            assertTrueAndEqual(data, _T("2*00$"), 1, 5, m);
            assertTrueAndEqual(data, _T("2*100$"), 1, 5, m);
            assertTrueAndEqual(data, _T("2+00$"), 1, 5, m);
            assertTrueAndEqual(data, _T("2?00$"), 1, 5, m);
            assertTrueAndEqual(data, _T("2?100$"), 1, 5, m);

            assertFalse(data, _T("2*0$"), m);
            assertFalse(data, _T("2*2100$"), m);
            assertFalse(data, _T("2+0$"), m);
            assertFalse(data, _T("2+100$"), m);
            assertFalse(data, _T("2?0$"), m);
            assertFalse(data, _T("2?2100$"), m);
        }

        TEST_METHOD(uMatchEmsTest3)
        {
            EssRxW::Match m;
            tstring data = _T("32100");

            assertTrueAndEqual(data, _T("3+?00$"), 0, 5, m);
            assertTrueAndEqual(data, _T("2+?00$"), 1, 5, m);
            assertTrueAndEqual(data, _T("2#?00$"), 1, 5, m);

            assertFalse(data, _T("3+?0$"), m);
            assertFalse(data, _T("2#?100$"), m);
        }

        TEST_METHOD(uMatchEmsTest4)
        {
            EssRxW::Match m;
            tstring data = _T("32100");
            
            assertTrueAndEqual(data, _T("3+++0$"), 0, 5, m);
            assertTrueAndEqual(data, _T("3##00$"), 0, 5, m);
            assertTrueAndEqual(data, _T("3++00$"), 0, 5, m);

            assertFalse(data, _T("3##0$"), m);
            assertFalse(data, _T("3++100$"), m);
            assertFalse(data, _T("3??0$"), m);
        }

        TEST_METHOD(uMatchEmsTest5)
        {
            EssRxW::Match m;
            
            assertTrueAndEqual(_T("00123"), _T("0>/3$"), 0, 5, m);
            assertTrueAndEqual(_T("0123"), _T("2>/3$"), 2, 4, m);

            assertTrueAndNpos(
                rxw.match(_T("00123"), _T("0>/3$"), EssRxW::FlagsRxW::F_NONE, &m),
                m
            );
            assertTrueAndNpos(
                rxw.match(_T("0123"), _T("2>/3$"), EssRxW::FlagsRxW::F_NONE, &m),
                m
            );

            assertFalse(_T("00/123"), _T("0>/3$"), m);
            assertFalse(_T("0123"), _T("0>/2$"), m);
            assertFalse(_T("0123"), _T("3>/3$"), m);
            assertFalse(_T("012/3"), _T("2>/3$"), m);
        }

        TEST_METHOD(mixTest1)
        {
            EssRxW::Match m;

            tstring input = _T("year = 2021;");

            assertTrueAndEqual(input, _T(" ##??;"), 6, 12, m);
            assertTrueAndEqual(input, _T(" ++??;"), 6, 12, m);

            assertTrueAndEqual(input, _T(" +???;"), 6, 12, m);
            assertTrueAndEqual(input, _T(" +++?;"), 6, 12, m);
            assertTrueAndEqual(input, _T(" ++??????;"), 4, 12, m);
            assertTrueAndEqual(input, _T(" ++????????;"), 4, 12, m);

            assertFalse(input, _T(" ++++?;"), m);

            assertTrueAndEqual(input, _T(" ###?;"), 6, 12, m);
            assertTrueAndEqual(input, _T(" #####?;"), 4, 12, m);
            assertTrueAndEqual(input, _T(" ####??;"), 4, 12, m);
            assertFalse(input, _T(" ####???;"), m);
        }

        TEST_METHOD(mixTest2)
        {
            EssRxW::Match m;

            tstring input = _T("year = 2021; age = 21; future = 'up';");

            assertTrueAndEqual(input, _T(" ##;"), 18, 22, m);
            assertTrueAndEqual(input, _T(" ++??;"), 6, 12, m);
        }

    private:

        EssRxW rxw;

        void assertTrueAndEqual(tstring input, tstring pattern, udiff_t expectedStart, udiff_t expectedEnd, EssRxW::Match& actual)
        {
            assertTrueAndEqual
            (
                rxw.match(input, pattern, EssRxW::FlagsRxW::F_MATCH_RESULT, &actual),
                expectedStart, expectedEnd, actual
            );
        }

        void assertTrueAndEqual(bool result, rxwtypes::udiff_t expectedStart, rxwtypes::udiff_t expectedEnd, EssRxW::Match& actual)
        {
            Assert::IsTrue(result);
            assertEqual(expectedStart, expectedEnd, actual);
        }

        void assertTrueAndNpos(bool result, EssRxW::Match& actual)
        {
            Assert::IsTrue(result);
            Assert::AreEqual(static_cast<rxwtypes::udiff_t>(EssRxW::Match::npos), actual.start);
        }

        void assertFalse(tstring input, tstring pattern, EssRxW::Match& actual)
        {
            assertFalse
            (
                rxw.match(input, pattern, EssRxW::FlagsRxW::F_MATCH_RESULT, &actual),
                actual
            );
        }

        void assertFalse(bool result, EssRxW::Match& actual)
        {
            Assert::IsFalse(result);
            Assert::AreEqual(static_cast<rxwtypes::udiff_t>(EssRxW::Match::npos), actual.start);
        }

        void assertEqual(rxwtypes::udiff_t expectedStart, rxwtypes::udiff_t expectedEnd, EssRxW::Match& actual)
        {
            Assert::AreEqual(static_cast<rxwtypes::udiff_t>(expectedStart), actual.start);
            Assert::AreEqual(static_cast<rxwtypes::udiff_t>(expectedEnd), actual.end);
        }

        bool searchEss(const tstring& data, const tstring& filter, bool ignoreCase = false)
        {
            return regXwild::common::searchEss(data, filter, ignoreCase);
        }

#endif

    };
}