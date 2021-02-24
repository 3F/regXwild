#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\regXwild\regXwild.h"

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
            EssRxW::MatchResult m;

            assertTrueAndEqual(input, _T("= +;"), 7, 14, m);
            assertTrueAndEqual(input, _T("= +;*//TODO"), 7, 21, m);
        }

        TEST_METHOD(uMatchTest2)
        {
            tstring input = _T("number = 8888; //TODO: up");
            EssRxW::MatchResult m;

            assertTrueAndEqual(input, _T("//+:"), 15, 22, m);

            assertFalse(input, _T("= +;*//NOTE"), m);
        }

        TEST_METHOD(uMatchTest3)
        {
            EssRxW::MatchResult m;

            assertTrueAndEqual(_T("0123456789"), _T("456"), 4, 7, m);
            assertTrueAndEqual(_T("01298"), _T("0#2?9"), 0, 4, m);
        }

        TEST_METHOD(uMatchTest4)
        {
            EssRxW::MatchResult m;
            tstring input = _T("0012398");

            assertTrueAndEqual(input, _T("0#2?9"), 1, 6, m);

            assertTrueAndNpos
            (
                rxw.match(input, _T("0#2?9"), EssRxW::EngineOptions::F_NONE, &m),
                m
            );
            
            assertFalse(input, _T("^0#2?9"), m);
            assertFalse(input, _T("0#2?9$"), m);

            assertTrueAndEqual(input, _T("^0#1*8$"), 0, 7, m);
        }

        TEST_METHOD(uMatchTest5)
        {
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

            assertTrueAndEqual(_T("sd-01-d2"), _T("sd-##-#2"), 0, 8, m);
            assertTrueAndEqual(_T("01-dd-02"), _T("#1-dd-0#"), 0, 8, m);
            assertTrueAndEqual(_T("sd-01-d2"), _T("sd-##-d"), 0, 7, m);

            assertTrueAndEqual(_T("01-dd-02"), _T("0#-dd-#2"), 0, 8, m);
            assertTrueAndEqual(_T("01-dd-02"), _T("##-dd-##"), 0, 8, m);
        }

        TEST_METHOD(uMatchTest7)
        {
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

            assertTrueAndEqual(_T("01-sd"), _T("+-sd"), 0, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("+-s"), 0, 4, m);
            assertTrueAndEqual(_T("sd-01"), _T("sd-+"), 0, 5, m);
            assertTrueAndEqual(_T("sd-01"), _T("d-+"), 1, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("0+-sd"), 0, 5, m);
            assertTrueAndEqual(_T("01-sd"), _T("0+-s"), 0, 4, m);
        }

        TEST_METHOD(uMatchTest9)
        {
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

            assertTrueAndEqual(_T("01-dd-02-ff"), _T("0?-d#-0+-*f"), 0, 10, m);
            assertTrueAndEqual(_T("001-dd-02-ff"), _T("0?-d#-0+-*f"), 1, 11, m);

            assertTrueAndEqual(_T("01-dd-02-ff"), _T("0?-d#-0+-f*"), 0, 10, m);
            assertTrueAndEqual(_T("0040012398"), _T("0#5|0#2?9"), 4, 9, m);
        }

        TEST_METHOD(uGreedyBalanceTest1)
        {
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;
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
            EssRxW::MatchResult m;
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
            EssRxW::MatchResult m;
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
            EssRxW::MatchResult m;
            assertTrueAndEqual(_T("0123"), _T("^0>/1"), 0, 2, m);
            assertTrueAndEqual(_T("00123"), _T("^0>/3"), 0, 5, m);

            assertTrueAndNpos(
                rxw.match(_T("0123"), _T("^0>/1"), EssRxW::EngineOptions::F_NONE, &m),
                m
            );
            assertTrueAndNpos(
                rxw.match(_T("00123"), _T("^0>/3"), EssRxW::EngineOptions::F_NONE, &m),
                m
            );

            assertFalse(rxw.match(_T("00/123"), _T("^0>/3"), EssRxW::EngineOptions::F_NONE), m);
            assertFalse(rxw.match(_T("0123"), _T("^1>/3"), EssRxW::EngineOptions::F_NONE), m);
            assertFalse(rxw.match(_T("0123"), _T("^0>/0"), EssRxW::EngineOptions::F_NONE), m);
            assertFalse(rxw.match(_T("0/123"), _T("^0>/1"), EssRxW::EngineOptions::F_NONE), m);
        }

        TEST_METHOD(uMatchEmsTest1)
        {
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;
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
            EssRxW::MatchResult m;
            tstring data = _T("32100");

            assertTrueAndEqual(data, _T("3+?00$"), 0, 5, m);
            assertTrueAndEqual(data, _T("2+?00$"), 1, 5, m);
            assertTrueAndEqual(data, _T("2#?00$"), 1, 5, m);

            assertFalse(data, _T("3+?0$"), m);
            assertFalse(data, _T("2#?100$"), m);
        }

        TEST_METHOD(uMatchEmsTest4)
        {
            EssRxW::MatchResult m;
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
            EssRxW::MatchResult m;
            
            assertTrueAndEqual(_T("00123"), _T("0>/3$"), 0, 5, m);
            assertTrueAndEqual(_T("0123"), _T("2>/3$"), 2, 4, m);

            assertTrueAndNpos(
                rxw.match(_T("00123"), _T("0>/3$"), EssRxW::EngineOptions::F_NONE, &m),
                m
            );
            assertTrueAndNpos(
                rxw.match(_T("0123"), _T("2>/3$"), EssRxW::EngineOptions::F_NONE, &m),
                m
            );

            assertFalse(_T("00/123"), _T("0>/3$"), m);
            assertFalse(_T("0123"), _T("0>/2$"), m);
            assertFalse(_T("0123"), _T("3>/3$"), m);
            assertFalse(_T("012/3"), _T("2>/3$"), m);
        }

        TEST_METHOD(mixTest1)
        {
            EssRxW::MatchResult m;

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
            EssRxW::MatchResult m;

            tstring input = _T("year = 2021; age = 21; future = 'up';");

            assertTrueAndEqual(input, _T(" ##;"), 18, 22, m);
            assertTrueAndEqual(input, _T(" ++??;"), 6, 12, m);
        }

        TEST_METHOD(mixTest3)
        {
            EssRxW::MatchResult m;

            tstring input = _T("year = 2021; pnum = 24617; vd = 1; dd = 17; vt = 55;");

            assertTrueAndEqual(input, _T(" ##;"), 39, 43, m);
            assertTrueAndEqual(input, _T(" ??;"), 31, 34, m);
        }

        TEST_METHOD(uReplaceTest1)
        {
            tstring input       = _T("number = '8888'; //TODO: up");
            tstring expected    = _T("number = '9777'; //TODO: up");

            EssRxW::MatchResult m;
            rxw.match(input, _T("'+'"), EssRxW::EngineOptions::F_MATCH_RESULT, &m);
            input = input.replace(m.start, m.end - m.start, _T("'9777'"));

            Assert::AreEqual(expected, input);
        }

        TEST_METHOD(uReplaceTest2)
        {
            tstring input       = _T("year = 2021; age = 21; future = 'up';");
            tstring expected    = _T("year = 2022; age = 22; future = 'up';");

            Assert::IsTrue(rxw.replace(input, _T(" ##;"), _T(" 22;")));
            Assert::IsTrue(rxw.replace(input, _T(" ++??;"), _T(" 2022;")));
            Assert::AreEqual(expected, input);
        }

        TEST_METHOD(uReplaceTest3)
        {

            tstring input       = _T("year = 2021; pnum = 24617; vd = 1; dd = 17; vt = 55;");
            tstring expected    = _T("year = 2021; pnum = 24617; vd = 7; dd = 00; vt = 55;");

            Assert::IsTrue(rxw.replace(input, _T(" ##;"), _T(" 00;")));
            Assert::IsTrue(rxw.replace(input, _T(" ??;"), _T(" 7;")));
            Assert::AreEqual(expected, input);
        }

        TEST_METHOD(offsetTest1)
        {
            EssRxW::MatchResult m;

            tstring input   = _T("a = 1; b = 2; c = 3; d = 4;");
            tstring pattern = _T(" #;");

            assertTrueAndEqual(input, pattern, 3, 6, m, 0);
            assertTrueAndEqual(input, pattern, 3, 6, m, 1);
            assertTrueAndEqual(input, pattern, 3, 6, m, 2);
            assertTrueAndEqual(input, pattern, 3, 6, m, 3);

            assertTrueAndEqual(input, pattern, 10, 13, m, 4);
            assertTrueAndEqual(input, pattern, 10, 13, m, 5);
            assertTrueAndEqual(input, pattern, 10, 13, m, 6);
            assertTrueAndEqual(input, pattern, 10, 13, m, 7);
            assertTrueAndEqual(input, pattern, 10, 13, m, 8);
            assertTrueAndEqual(input, pattern, 10, 13, m, 9);
            assertTrueAndEqual(input, pattern, 10, 13, m, 10);

            assertTrueAndEqual(input, pattern, 17, 20, m, 11);
            assertTrueAndEqual(input, pattern, 17, 20, m, 12);
            assertTrueAndEqual(input, pattern, 17, 20, m, 13);
            assertTrueAndEqual(input, pattern, 17, 20, m, 14);
            assertTrueAndEqual(input, pattern, 17, 20, m, 15);
            assertTrueAndEqual(input, pattern, 17, 20, m, 16);
            assertTrueAndEqual(input, pattern, 17, 20, m, 17);

            assertTrueAndEqual(input, pattern, 24, 27, m, 18);
            assertTrueAndEqual(input, pattern, 24, 27, m, 19);
            assertTrueAndEqual(input, pattern, 24, 27, m, 20);
            assertTrueAndEqual(input, pattern, 24, 27, m, 21);
            assertTrueAndEqual(input, pattern, 24, 27, m, 22);
            assertTrueAndEqual(input, pattern, 24, 27, m, 23);
            assertTrueAndEqual(input, pattern, 24, 27, m, 24);

            assertFalse(input, pattern, m, 25);
            assertFalse(input, pattern, m, 26);
            assertFalse(input, pattern, m, 27);
        }

        TEST_METHOD(offsetTest2)
        {
            EssRxW::MatchResult m;

            tstring input   = _T("a = 1; b = 2;");
            tstring pattern = _T(" #;");

            assertFalse(input, pattern, m, -1);
            assertFalse(input, pattern, m, -2);
            assertFalse(input, pattern, m, input.length() - 1);
            assertFalse(input, pattern, m, input.length());
            assertFalse(input, pattern, m, input.length() + 1);
        }

        TEST_METHOD(offsetTest3)
        {
            EssRxW::MatchResult m;

            tstring input   = _T("a = 1; b = 2; c = 3; d = 4;");
            tstring pattern = _T(" #;");

            Assert::IsTrue(rxw.replace(input, pattern, _T(" 5;"), 24));
            Assert::AreEqual(static_cast<tstring>(_T("a = 1; b = 2; c = 3; d = 5;")), input);

            Assert::IsTrue(rxw.replace(input, pattern, _T(" 6;"), 17));
            Assert::AreEqual(static_cast<tstring>(_T("a = 1; b = 2; c = 6; d = 5;")), input);

            Assert::IsTrue(rxw.replace(input, pattern, _T(" 7;"), 10));
            Assert::AreEqual(static_cast<tstring>(_T("a = 1; b = 7; c = 6; d = 5;")), input);

            Assert::IsTrue(rxw.replace(input, pattern, _T(" 8;"), 3));
            Assert::AreEqual(static_cast<tstring>(_T("a = 8; b = 7; c = 6; d = 5;")), input);
        }

        TEST_METHOD(offsetTest4)
        {
            EssRxW::MatchResult m;

            tstring input       = _T("a = 1; b = 2;");
            tstring expected    = input;
            tstring pattern     = _T(" #;");
            tstring replacement = _T(" 7;");

            Assert::IsFalse(rxw.replace(input, pattern, replacement, -1));
            Assert::AreEqual(expected, input);

            Assert::IsFalse(rxw.replace(input, pattern, replacement, -2));
            Assert::AreEqual(expected, input);

            Assert::IsFalse(rxw.replace(input, pattern, replacement, input.length() - 1));
            Assert::AreEqual(expected, input);

            Assert::IsFalse(rxw.replace(input, pattern, replacement, input.length()));
            Assert::AreEqual(expected, input);

            Assert::IsFalse(rxw.replace(input, pattern, replacement, input.length() + 1));
            Assert::AreEqual(expected, input);
        }


    private:

        EssRxW rxw;

        void assertTrueAndEqual(tstring input, tstring pattern, udiff_t expectedStart, udiff_t expectedEnd, EssRxW::MatchResult& actual, udiff_t ofs = 0)
        {
            assertTrueAndEqual
            (
                rxw.match(input, pattern, ofs, EssRxW::EngineOptions::F_MATCH_RESULT, &actual),
                expectedStart, expectedEnd, actual
            );
        }

        void assertTrueAndEqual(bool result, rxwtypes::udiff_t expectedStart, rxwtypes::udiff_t expectedEnd, EssRxW::MatchResult& actual)
        {
            Assert::IsTrue(result);
            assertEqual(expectedStart, expectedEnd, actual);
        }

        void assertTrueAndNpos(bool result, EssRxW::MatchResult& actual)
        {
            Assert::IsTrue(result);
            Assert::AreEqual(static_cast<rxwtypes::udiff_t>(EssRxW::MatchResult::npos), actual.start);
        }

        void assertFalse(tstring input, tstring pattern, EssRxW::MatchResult& actual, udiff_t ofs = 0)
        {
            assertFalse
            (
                rxw.match(input, pattern, ofs, EssRxW::EngineOptions::F_MATCH_RESULT, &actual),
                actual
            );
        }

        void assertFalse(bool result, EssRxW::MatchResult& actual)
        {
            Assert::IsFalse(result);
            Assert::AreEqual(static_cast<rxwtypes::udiff_t>(EssRxW::MatchResult::npos), actual.start);
        }

        void assertEqual(rxwtypes::udiff_t expectedStart, rxwtypes::udiff_t expectedEnd, EssRxW::MatchResult& actual)
        {
            Assert::AreEqual(static_cast<rxwtypes::udiff_t>(expectedStart), actual.start);
            Assert::AreEqual(static_cast<rxwtypes::udiff_t>(expectedEnd), actual.end);
        }

#endif

    };
}