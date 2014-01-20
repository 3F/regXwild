/*
  * Copyright (c) 2013 Developed by reg <entry.reg@gmail.com>
  * 
  * Distributed under the Boost Software License, Version 1.0
  * (see accompanying file LICENSE or a copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "AlgorithmEss.h"

namespace net { namespace r_eg { namespace text { namespace wildcards {

void AlgorithmEssTestCase::assertsAny()
{
    tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

    /* should be found: */
    assert(alg.search(data, _T("protection of various")) == true);      // __ __ __
    assert(alg.search(data, _T("pro*system")) == true);                 // __ * __
    assert(alg.search(data, _T("*pro*system*")) == true);               // * __ * __ *
    assert(alg.search(data, _T("project**various")) == true);           // __ ** __
    assert(alg.search(data, _T("new*7*systems")) == true);              // __ * __ * __
    assert(alg.search(data, _T("")) == true);                           // empty
    
    assert(alg.search(data, _T("*")) == true);
    assert(alg.search(data, _T("***")) == true);
    assert(alg.search(_T("new str"), _T("new str")) == true);

    /* should not be found: */
    assert(alg.search(data, _T("project 12 and")) == false);            // __ _x_ __
    assert(alg.search(data, _T("new*express")) == false);               // __ * _x_
    assert(alg.search(data, _T("tes*ting*project")) == false);          // __ * _x_ * __
    assert(alg.search(data, _T("testing*project*and")) == false);       // _x_ * __ * __
    assert(alg.search(data, _T("now*is*completely")) == false);         // _x_ * _x_ * _x_
    assert(alg.search(data, _T("protection*project*new")) == false);    // backwards __ * __ * __
    assert(alg.search(data, _T("**open**close")) == false);             // ** _x_ ** _x_
}

void AlgorithmEssTestCase::assertsSplit()
{
    tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

    /* should be found: */
    assert(alg.search(data, _T("protection of|new tes")) == true);       // __ __ | __ __
    assert(alg.search(data, _T("some project|of various")) == true);     // _x_ __ | __ __
    assert(alg.search(data, _T("various systems|new 237")) == true);     // __ __ | __ _x_
    assert(alg.search(data, _T("pro*12|new*system")) == true);           // __ * __ | __ *__
    assert(alg.search(data, _T("ject*new|pro*tems")) == true);           // __ * _x_ | __ * __
    assert(alg.search(data, _T("pro*tems|seems*and")) == true);          // __ * __ | _x_ * __
    assert(alg.search(data, _T("project*|new")) == true);                // __ *| __
    assert(alg.search(data, _T("various*|zeep")) == true);               // __ * | _x_
    assert(alg.search(data, _T("goo*|systems")) == true);                // _x_ * | __
    assert(alg.search(data, _T("project||protect")) == true);            // __ || __
    assert(alg.search(data, _T("|new||and|")) == true);                  // | __ || __ |
    assert(alg.search(data, _T("|fail|system")) == true);                // | _x_ | __
    assert(alg.search(data, _T("|12||true||")) == true);                 // | __ || _x_ ||
    assert(alg.search(data, _T("above|new|with")) == true);              // _x_ | __ | _x_
    assert(alg.search(data, _T("project**|new")) == true);               // __ **| __
    assert(alg.search(data, _T("zoom|*pro")) == true);                   // _x_ | * __
    assert(alg.search(data, _T("zoom|*pro**")) == true);                 // _x_ | *__ **
    assert(alg.search(data, _T("||")) == true);                          //empty
    assert(alg.search(data, _T("")) == true);                            //empty
    assert(alg.search(data, _T("||zoom||out||")) == true);               // ||_x_ || _x_ ||
    assert(alg.search(data, _T("|*|")) == true);                         // |*|
    assert(alg.search(data, _T("|long-term")) == true);                  // | _x_
    assert(alg.search(data, _T("long-term|")) == true);                  // _x_ |
    assert(alg.search(data, _T("*|*")) == true);                         // *|*
    assert(alg.search(data, _T("*|")) == true);                          // *|
    assert(alg.search(data, _T("|*")) == true);                          // |*
    assert(alg.search(data, _T("seems|open*and*star|*system")) == true); // _x_ | _x_ * __ * _x_ | * __

    /* should not be found: */
    assert(alg.search(data, _T("above|fails|with")) == false);           // _x_ | _x_ | _x_
    assert(alg.search(data, _T("let*proj|project*deep")) == false);      // _x_ * __ | __ * _x_
    assert(alg.search(data, _T("operator*|*zeep")) == false);            // _x_ *|* _x_
    assert(alg.search(data, _T("some project|let*various")) == false);   // _x_ __ | _x_* __
    assert(alg.search(data, _T("some project|various*zoom")) == false);  // _x_ __ | __ * _x_
    assert(alg.search(data, _T("be|pen*and*star|*my*system")) == false); // _x_ | _x_ * __ * _x_ | * _x_ * __
}

void AlgorithmEssTestCase::assertsOne()
{
    tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

    /* should be found: */
    assert(alg.search(data, _T("?")) == true);
    assert(alg.search(data, _T("????")) == true);

    assert(alg.search(data, _T("new*pro?ection")) == true);                 // __ * [pro]ject ... [pro]t[ection]
    assert(alg.search(data, _T("????")) == true);
    assert(alg.search(data, _T("project?12")) == true);
    assert(alg.search(data, _T("systems?")) == true);
    assert(alg.search(data, _T("????new")) == true);
    assert(alg.search(data, _T("systems????")) == true);
    assert(alg.search(data, _T("???systems????")) == true);
    assert(alg.search(data, _T("pro????ion")) == true);                     // {0,4}: min: proion, max: protection
    assert(alg.search(data, _T("protection????????????system")) == true);
    assert(alg.search(data, _T("protection?????????????system")) == true);
    assert(alg.search(data, _T("protection??????????????system")) == true);
    assert(alg.search(data, _T("pro??????????ion")) == true);
    assert(alg.search(_T("system-17 fee"), _T("system?17")) == true);

    // EXT changed:
    {
        assert(alg.search(_T("system17"), _T("system?17")) == true);                 // == 0{2}
        assert(alg.search(_T("str1 project-12 str2"), _T("project?12")) == true);    // == 1
        assert(alg.search(_T("str1 project-12 str2"), _T("str?1")) == true);         // == 0
    }

    // MS combination
    {
        assert(alg.search(data, _T("?*??*")) == true);
        assert(alg.search(data, _T("new?*systems")) == true);
        assert(alg.search(data, _T("new*?*systems")) == true);
        assert(alg.search(data, _T("new*??*systems")) == true);
        assert(alg.search(data, _T("new*??*systems?")) == true);
        //assert(alg.search(data, _T("new*?systems")) == true); //TODO: implement combination {MS} + {?}
    }

    /* should not be found: */
    assert(alg.search(data, _T("?pro?12?|seems?7")) == false);
    assert(alg.search(_T("system, installments range from 2 to 17"), _T("system?17")) == false);
    assert(alg.search(_T("system_-17 fee also"), _T("system?17")) == false);
    assert(alg.search(_T("project"), _T("pro?tect")) == false);
    assert(alg.search(_T("project"), _T("fro?ject")) == false);
    {
        assert(alg.search(_T("str1 project--12 str2"), _T("project?12")) == false);  // > 1
    }

    // MS combination
    {
        assert(alg.search(data, _T("*new?systems*")) == false);
        assert(alg.search(data, _T("*?new?sys?*?ms*")) == false);
    }
}

void AlgorithmEssTestCase::assertsAnySP()
{
    /* should be found: */
    assert(alg.search(_T("/new/user_myhid_test.bzip2"), _T("myhid>bzip")) == true);   // __...___
    assert(alg.search(_T("/new/user_myhid_test.bzip2"), _T("myhid>")) == true);       // __...EOL
    assert(alg.search(_T("/new/user_myhid"), _T("myhid>")) == true);                  // __EOL
        
    /* with other metasymbols: */
    {
        assert(alg.search(_T("/new/user_myhid"), _T("myhid>*")) == true);
        assert(alg.search(_T("/new/user_myhid"), _T("myhid>***")) == true);
        assert(alg.search(_T("/new/user_myhid"), _T("myhid>?")) == true);
        assert(alg.search(_T("/new/user_myhid"), _T("myhid>?*")) == true);
    }

    /* should not be found: */
    assert(alg.search(_T("/new/user_myhid_t/est.bzip2"), _T("myhid>bzip")) == false);     // __.../...__
    assert(alg.search(_T("/new/user_myhid/_test.bzip2"), _T("myhid>bzip")) == false);     // __/...__
    assert(alg.search(_T("/new/user_myhid_test./bzip2"), _T("myhid>bzip")) == false);     // __.../__
    assert(alg.search(_T("/new/user_myhid_te/st.bzip2"), _T("myhid>")) == false);         // __.../...EOL
    assert(alg.search(_T("/new/user_myhid_te/"), _T("myhid>")) == false);                 // __.../EOL
        
    /* with other metasymbols: */
    {
        assert(alg.search(_T("/new/user_myhid_s/df.txt"), _T("myhid>*")) == false);
        assert(alg.search(_T("/new/user_myhid_s/df.txt"), _T("myhid>***")) == false);
        assert(alg.search(_T("/new/user_myhid_s/df.txt"), _T("myhid>?")) == false);
        assert(alg.search(_T("/new/user_myhid_s/df.txt"), _T("myhid>?*")) == false);
        //-
        assert(alg.search(_T("/new/user_myhid_s/df.txt"), _T("myhid>*txt")) == false);
        assert(alg.search(_T("/new/user_myhid_s/df.txt"), _T("myhid>***txt")) == false);
        assert(alg.search(_T("/new/user_myhid_s/df.txt"), _T("myhid>?txt")) == false);
        assert(alg.search(_T("/new/user_myhid_s/df.txt"), _T("myhid>?*??txt")) == false);
        //-
        assert(alg.search(_T("/new/user_myhid"), _T("myhid>*txt")) == false);
        assert(alg.search(_T("/new/user_myhid"), _T("myhid>***txt")) == false);
        assert(alg.search(_T("/new/user_myhid"), _T("myhid>?txt")) == false);
        assert(alg.search(_T("/new/user_myhid"), _T("myhid>?*??txt")) == false);
    }
}

void AlgorithmEssTestCase::assertsSingle()
{
    tstring data = _T("new tes;ted project-12, and 75_protection of various systems");
    _stubSINGLECombination();

    /* should be found: */
    assert(alg.search(data, _T("#")) == true);
    assert(alg.search(data, _T("####")) == true);

    assert(alg.search(data, _T("pro####ion")) == true);
    assert(alg.search(data, _T("project##2")) == true);
    assert(alg.search(data, _T("project#12")) == true);
    assert(alg.search(data, _T("#systems")) == true);
    assert(alg.search(data, _T("75#protection")) == true);
    assert(alg.search(data, _T("sys###s")) == true);
    assert(alg.search(data, _T("new#tes#ted")) == true);
    assert(alg.search(data, _T("project###, and #####ote##ion")) == true);
    assert(alg.search(data, _T("projec####, and #####ote##ion")) == true);
    assert(alg.search(data, _T("new tes;ted project-##, and ##_protection of various systems")) == true);
    assert(alg.search(_T("system_-17 fee also"), _T("system##17")) == true);
    assert(alg.search(_T("pro-ject"), _T("pro#ject")) == true);

    // ext cmp-one:
    {
        assert(alg.search(_T("str1 project-12 str2"), _T("project#12")) == true); // == 1
    }

    // split
    {
        assert(alg.search(data, _T("notfound|project##2")) == true);
        assert(alg.search(data, _T("notfound|notfound2|project##2")) == true);
    }

    // MS combination
    {
        //TODO: implement *,?,+,> and combination
        {
            //assert(alg.search(data, _T("*#")) == true);
            //assert(alg.search(data, _T("*#*")) == true);
            //assert(alg.search(data, _T("#*")) == true);
            //assert(alg.search(data, _T("*#systems")) == true);
            //assert(alg.search(data, _T("new*#*systems")) == true);
            //assert(alg.search(data, _T("*new#*systems*")) == true);
            //assert(alg.search(data, _T("new#*systems")) == true);
            //assert(alg.search(data, _T("75*#protection")) == true);
            //assert(alg.search(data, _T("75*#*protection")) == true);
            //assert(alg.search(data, _T("new*#systems")) == true);
            //assert(alg.search(data, _T("*new#*#systems*")) == true);
        }
    }


    /* should not be found: */
    assert(alg.search(_T("pro-ject"), _T("pro#tect")) == false);
    assert(alg.search(_T("pro-ject"), _T("fro#ject")) == false);
    assert(alg.search(_T("project"), _T("pro#ject")) == false);
    assert(alg.search(data, _T("project#2")) == false);
    assert(alg.search(data, _T("systems#")) == false);
    assert(alg.search(data, _T("systems #")) == false);
    assert(alg.search(data, _T("systems# ")) == false);
    assert(alg.search(data, _T("#new")) == false);
    assert(alg.search(data, _T("###new")) == false);
    assert(alg.search(data, _T("##new")) == false);
    assert(alg.search(data, _T("new#systems")) == false);
    assert(alg.search(data, _T("new##systems")) == false);
    assert(alg.search(data, _T("new tes;ted project-##, and ##_protection of various systems ")) == false);
    assert(alg.search(_T("system, installments range from 2 to 17"), _T("system#17")) == false);
    assert(alg.search(_T("system_-17 fee also"), _T("system#17")) == false);
    assert(alg.search(_T("system17 fee also"), _T("system#17")) == false);

    // ext cmp-one:
    {
        assert(alg.search(_T("str1 project-12 str2"), _T("str#1")) == false);        // == 0
        assert(alg.search(_T("str1 project--12 str2"), _T("project#12")) == false);  // > 1
    }

    // split
    {
        assert(alg.search(data, _T("notfound|project##systems")) == false);
        assert(alg.search(data, _T("notfound|notfound2|project##systems")) == false);
    }

    // MS combination
    {
        //TODO: implement *,?,+,> and combination
        {
            //assert(alg.search(data, _T("*new#systems*")) == false);
            //assert(alg.search(data, _T("*new##systems*")) == false);
            //assert(alg.search(data, _T("systems*#")) == false);
            //assert(alg.search(data, _T("pro#*ject")) == false);
            //assert(alg.search(data, _T("systems#*")) == false);
        }
    }
}

void AlgorithmEssTestCase::assertsMore()
{
    tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

    /* should be found: */
    assert(alg.search(data, _T("+")) == true);
    assert(alg.search(data, _T("+++++")) == true);

    assert(alg.search(data, _T("new+systems")) == true);
    assert(alg.search(data, _T("new++systems")) == true);
    assert(alg.search(data, _T("+systems")) == true);
    assert(alg.search(data, _T("project+12")) == true);
    assert(alg.search(data, _T("project++12")) == true);
    assert(alg.search(data, _T("75+*systems")) == true);
    assert(alg.search(data, _T("75*+*systems")) == true);
    assert(alg.search(data, _T("new+7+system")) == true);

    // split
    {
        assert(alg.search(data, _T("notfound|project+systems")) == true);
        assert(alg.search(data, _T("notfound|notfound2|project+systems")) == true);
    }

    // MS combination
    {
        assert(alg.search(data, _T("*+")) == true);
        assert(alg.search(data, _T("*+*")) == true);
        assert(alg.search(data, _T("+*")) == true);
        assert(alg.search(data, _T("+*new")) == true);
    }

    /* should not be found: */
    assert(alg.search(data, _T("+new")) == false);
    assert(alg.search(data, _T("+new+")) == false);
        
    assert(alg.search(data, _T("systems+")) == false);
    assert(alg.search(data, _T("systems++")) == false);
    assert(alg.search(data, _T("+systems+")) == false);

    assert(alg.search(data, _T("+new+systems")) == false);
    assert(alg.search(data, _T("new+notfound")) == false);
    assert(alg.search(data, _T("tes+ting+project")) == false);
    assert(alg.search(data, _T("project+new")) == false);
    assert(alg.search(data, _T("++open++close")) == false);
    assert(alg.search(data, _T("now+is+completely")) == false);
    assert(alg.search(data, _T("testing+project+and")) == false);

    // split
    {
        assert(alg.search(data, _T("notfound|project+new")) == false);
        assert(alg.search(data, _T("notfound|notfound2|project+new")) == false);
    }
}

void AlgorithmEssTestCase::assertsBegin()
{
    tstring data  = _T("new tes;ted project-12, and 75_protection of various systems");
    tstring datam = _T("main systems 1272/is ok");

    /* should be found: ^word */
    {
        assert(alg.search(data, _T("^new")) == true);
        assert(alg.search(data, _T("^new*")) == true);
        assert(alg.search(data, _T("^new*pro?ection")) == true);

        // split
        {
            assert(alg.search(data, _T("notfound|^new*pro?ection")) == true);
            assert(alg.search(data, _T("notfound|^")) == true);
            assert(alg.search(data, _T("notfound|^|")) == true);
            assert(alg.search(data, _T("^|notfound")) == true);
            assert(alg.search(data, _T("|^|notfound")) == true);

            assert(alg.search(data, _T(" ^new|notfound|^new")) == true);
            assert(alg.search(data, _T(" ^new|^new|notfound")) == true);
            assert(alg.search(data, _T("^new|*^new|notfound")) == true);

            assert(alg.search(data, _T("^*new*|notfound|^new")) == true);
            assert(alg.search(data, _T("^*n0ew*|notfound|^new")) == true);
        }

        // MS combination
        {
            // *
            {
                assert(alg.search(datam, _T("^*systems")) == true);
                assert(alg.search(data, _T("^*new")) == true);
                assert(alg.search(data, _T("^**new")) == true);
            }
            // >
            {
                assert(alg.search(data, _T("^>new")) == true);
                assert(alg.search(data, _T("^>**new")) == true);
                assert(alg.search(data, _T("^>>new")) == true);
                assert(alg.search(data, _T("^>systems")) == true);
            }

            //TODO: implement ?,+,# and combination
            {
                //// ?
                //{
                //    assert(alg.search(datam, _T("^?ain")) == true);
                //    assert(alg.search(datam, _T("^?main")) == true);
                //}
                //// +
                //{
                //    assert(alg.search(datam, _T("^+ain")) == true);
                //    assert(alg.search(datam, _T("^+in")) == true);
                //}
                //// #
                //{
                //    assert(alg.search(datam, _T("^#ain")) == true);
                //    assert(alg.search(datam, _T("^##in")) == true);
                //}
            }
        }
    }

    /* should not be found: */
    {

        // _^word
        {
            assert(alg.search(data, _T("systems^")) == false);
            assert(alg.search(data, _T("*systems^")) == false);
            assert(alg.search(data, _T("*systems*^")) == false);
            assert(alg.search(data, _T("*systems* ^")) == false);
            assert(alg.search(data, _T("*systems* ^ ")) == false);
            assert(alg.search(data, _T("*systems*^*")) == false);
            assert(alg.search(data, _T("new^pro?ection")) == false);
            assert(alg.search(data, _T("pro^ection")) == false);
            assert(alg.search(data, _T("*^new*pro?ection")) == false);
            assert(alg.search(data, _T(" *^new*pro?ection")) == false);
            assert(alg.search(data, _T("* ^new*pro?ection")) == false);
            assert(alg.search(data, _T(" * ^new*pro?ection")) == false);
            assert(alg.search(data, _T(" ^new*pro?ection")) == false);
        }

        // ^_word
        {
            assert(alg.search(data, _T("^ new*pro?ection")) == false);
            assert(alg.search(data, _T(" ^ new*pro?ection")) == false);
            assert(alg.search(data, _T("some^new*pro?ection")) == false);
            assert(alg.search(data, _T("some ^new*pro?ection")) == false);
            assert(alg.search(data, _T("some*^new*pro?ection")) == false);
            assert(alg.search(data, _T("sys*^new*pro?ection")) == false);
        }

        // split
        {
            assert(alg.search(data, _T("notfound|^ new")) == false);
            assert(alg.search(data, _T("notfound| ^new*pro?ection")) == false);
            assert(alg.search(data, _T("notfound| ^new")) == false);
            assert(alg.search(data, _T("notfound| ^")) == false);
            assert(alg.search(data, _T(" ^ |notfound")) == false);
            assert(alg.search(data, _T("^ |notfound")) == false);
            assert(alg.search(data, _T(" ^ * |notfound")) == false);
            assert(alg.search(data, _T(" ^notfound* |notfound|not^*found")) == false);
            assert(alg.search(data, _T("*systems*^|notfound|systems^")) == false);
            assert(alg.search(data, _T("*systems*^|notfound")) == false);
            assert(alg.search(data, _T("*systems*^|notfound|systems0*^")) == false);
        }


        // MS combination
        {
            assert(alg.search(data, _T("^^new")) == false);
            assert(alg.search(data, _T("systems>^")) == false);
            assert(alg.search(data, _T(">^new")) == false);
            assert(alg.search(data, _T("sys*^*^new*pro?ection")) == false);
            assert(alg.search(data, _T("*^*^new*pro?ection")) == false);
            assert(alg.search(data, _T("*^new")) == false);
            assert(alg.search(data, _T("systems>^*")) == false);

            // *
            {
                assert(alg.search(datam, _T("^*notfound")) == false);
            }
            // >
            {
                assert(alg.search(datam, _T("^>is")) == false);
            }

            //TODO: implement ?,+,# and combination
            {
                //// ?
                //{
                //    assert(alg.search(datam, _T("^?in")) == false);
                //}
                //// +
                //{
                //    assert(alg.search(datam, _T("^+main")) == false);
                //}
                //// #
                //{
                //    assert(alg.search(datam, _T("^#main")) == false);
                //    assert(alg.search(datam, _T("^##ain")) == false);
                //    assert(alg.search(datam, _T("^##main")) == false);
                //}
            }
        }
    }
}

void AlgorithmEssTestCase::assertsEnd()
{
    _stubENDCombination();

    tstring data  = _T("new tes;ted project-12, and 75_protection of various systems");
    tstring datam = _T("main systems 1272/is ok");

    /* should be found: */
    {
        // word$
        {
            assert(alg.search(data, _T("systems$")) == true);
            assert(alg.search(data, _T("*systems$")) == true);
            assert(alg.search(data, _T(" * systems$")) == true);
            assert(alg.search(data, _T("*tems$")) == true);
            assert(alg.search(data, _T("new*pro?ection*systems$")) == true);
        }

        // ^word$
        {
            assert(alg.search(data, _T("^new*systems$")) == true);
            assert(alg.search(datam, _T("^main systems 1272/is ok$")) == true);
            assert(alg.search(datam, _T("^main*is ok$")) == true);
            
        }

        // split
        {
            assert(alg.search(data, _T("dwarf|*tems$")) == true);
            assert(alg.search(data, _T("dwarf|getting|tems$")) == true);
            assert(alg.search(datam, _T("^old*is ok$|^main*ok$")) == true);
            assert(alg.search(datam, _T("^main|*ok$")) == true);
            assert(alg.search(datam, _T("*ok$|^main")) == true);
            assert(alg.search(datam, _T("^old*is ok|main*ok$")) == true);
            assert(alg.search(data, _T("*systems$|notfound")) == true);
            assert(alg.search(data, _T("systems$|notfound")) == true);
            assert(alg.search(data, _T("project*systems$|notfound")) == true);
            assert(alg.search(data, _T("project*systems$|notfound")) == true);
            assert(alg.search(data, _T("new*project*systems$|notfound")) == true);            
            assert(alg.search(data, _T("systems$ |notfound|systems$")) == true);
            assert(alg.search(data, _T("systems$ |systems$|notfound")) == true);
            assert(alg.search(data, _T("systems$|systems$*|notfound")) == true);
            assert(alg.search(data, _T("*systems*$|notfound|systems$")) == true);
        }

        // MS combination
        {
            //TODO: implement *,>,?,+,# and combination
            {
                //// *
                //{
                //    assert(alg.search(data, _T("systems*$")) == true);
                //    assert(alg.search(data, _T("systems**$")) == true);
                //    assert(alg.search(datam, _T("main*$")) == true);
                //    assert(alg.search(datam, _T("main**$")) == true);
                //    assert(alg.search(data, _T("systems*$")) == true);
                //    assert(alg.search(data, _T("project*$")) == true);
                //    assert(alg.search(datam, _T("^main*$")) == true);
                //    {
                //        assert(alg.search(data, _T("^*new*$")) == true);
                //        assert(alg.search(data, _T("^*$")) == true);
                //        assert(alg.search(data, _T("^*$")) == true);
                //        assert(alg.search(datam, _T("^*1272*$")) == true);
                //    }
                //}
                //// >
                //{
                //    assert(alg.search(data, _T("systems>$")) == true);
                //    assert(alg.search(data, _T("systems>*$")) == true);
                //    assert(alg.search(data, _T("various>$")) == true);
                //    assert(alg.search(data, _T("various>*$")) == true);
                //    assert(alg.search(data, _T("various>>$")) == true);
                //}

                //// ?
                //{
                //    assert(alg.search(data, _T("system?$")) == true);
                //    assert(alg.search(data, _T("systems?$")) == true);
                //}
                //// +
                //{
                //    assert(alg.search(data, _T("system+$")) == true);
                //    assert(alg.search(data, _T("syste+$")) == true);
                //}
                //// #
                //{
                //    assert(alg.search(data, _T("system#$")) == true);
                //    assert(alg.search(data, _T("syste##$")) == true);
                //}
            }
        }
    }

    /* should not be found: */
    {
        assert(alg.search(datam, _T("m^a$in")) == false);
        assert(alg.search(data, _T("notfound$systems")) == false);
        assert(alg.search(data, _T("systems*new$")) == false);
        assert(alg.search(data, _T("$*new")) == false);
        assert(alg.search(data, _T("$new")) == false);

        // ^,$
        {
            assert(alg.search(datam, _T("^main$")) == false);
            assert(alg.search(datam, _T("^1272$")) == false);
            assert(alg.search(data, _T("^ $")) == false);
            assert(alg.search(datam, _T("$main systems 1272/is ok^")) == false);
            assert(alg.search(datam, _T("^main systems 1272/is ok$")) == true);
            assert(alg.search(datam, _T("^$main systems 1272/is ok^$")) == false);
            assert(alg.search(datam, _T("^$main")) == false);
            assert(alg.search(datam, _T("^*$$main")) == false);
            assert(alg.search(data, _T("^new systems$")) == false);
            assert(alg.search(data, _T("^new^systems$")) == false);
            assert(alg.search(data, _T("^new*systems$*")) == false);
            assert(alg.search(datam, _T("^$")) == false);
            assert(alg.search(datam, _T("$^")) == false);
        }

        // $word
        {
            assert(alg.search(data, _T("$systems")) == false);
            assert(alg.search(data, _T("*$systems")) == false);
            assert(alg.search(data, _T("* $systems")) == false);
            assert(alg.search(data, _T(" $systems")) == false);
            assert(alg.search(data, _T(">$systems")) == false);
            assert(alg.search(data, _T(">$^systems")) == false);
        }

        // word$_
        {
            assert(alg.search(data, _T("systems$ ")) == false);
            assert(alg.search(data, _T("systems$*")) == false);
            assert(alg.search(data, _T("systems$>")) == false);
            assert(alg.search(data, _T("systems$new")) == false);
            assert(alg.search(data, _T("systems$notfound")) == false);
            assert(alg.search(data, _T("systems$*notfound")) == false);
            assert(alg.search(data, _T("systems$*new")) == false);
            assert(alg.search(datam, _T("$ |notfound")) == false);
        }

        // word_$
        {
            assert(alg.search(data, _T("system$s")) == false);
            assert(alg.search(data, _T("systems $")) == false);

            // MS combination
            {
                assert(alg.search(data, _T("systems$$")) == false);
                assert(alg.search(data, _T("systems$*")) == false);
                assert(alg.search(data, _T("systems$*")) == false);
                assert(alg.search(data, _T("systems$>*")) == false);
                assert(alg.search(data, _T("notfound*$")) == false);
                assert(alg.search(data, _T("systems*$")) == false);
                assert(alg.search(data, _T("systems>$")) == false);
                assert(alg.search(data, _T("systems>*$")) == false);
                assert(alg.search(datam, _T(" $|notfound")) == false);

                // *
                {
                    assert(alg.search(datam, _T("notfound*$")) == false);
                    {
                        assert(alg.search(data, _T("*systems*$|notfound")) == false);
                        assert(alg.search(data, _T("*systems*$|notfound|systems0*$")) == false);
                    }
                }
                // >
                {
                    assert(alg.search(datam, _T("systems>$")) == false);
                }

                //TODO: implement ?,+,# and combination
                {
                    //// ?
                    //{
                    //    assert(alg.search(data, _T("syste?$")) == false);
                    //}
                    //// +
                    //{
                    //    assert(alg.search(data, _T("systems+$")) == false);
                    //}
                    //// #
                    //{
                    //    assert(alg.search(data, _T("systems#$")) == false);
                    //    assert(alg.search(data, _T("system##$")) == false);
                    //    assert(alg.search(data, _T("systems##$")) == false);
                    //}
                }
            }
        }

        // split
        {
            assert(alg.search(data, _T("*systems$ |notfound")) == false);
            assert(alg.search(data, _T("systems0$ |notfound")) == false);
            assert(alg.search(data, _T("*systems$  |notfound")) == false);
            assert(alg.search(data, _T("*systems$ zero|notfound")) == false);
            assert(alg.search(data, _T("*systems$*zero|notfound")) == false);
            assert(alg.search(data, _T("*systems$*zero |notfound")) == false);
            assert(alg.search(data, _T("project*systems$ |notfound")) == false);
            
            assert(alg.search(data, _T("project systems$ |notfound")) == false);
            assert(alg.search(data, _T("project*systems$  |notfound")) == false);
            assert(alg.search(data, _T("project*systems$ zero|notfound")) == false);
            assert(alg.search(data, _T("project*systems$*zero|notfound")) == false);
            assert(alg.search(data, _T("project*systems$*zero |notfound")) == false);

            assert(alg.search(data, _T("new*project systems$ |notfound")) == false);
            assert(alg.search(data, _T("new*project*systems$  |notfound")) == false);
            assert(alg.search(data, _T("new*project*systems$ zero|notfound")) == false);
            assert(alg.search(data, _T("new*project*systems$*zero|notfound")) == false);
            assert(alg.search(data, _T("new*project*systems$*zero |notfound")) == false);

            assert(alg.search(data, _T("systems$ |notfound")) == false);
            assert(alg.search(data, _T("systems$ |notfound|systems$ ")) == false);
            assert(alg.search(data, _T("systems$ |systems$ |notfound")) == false);
            assert(alg.search(data, _T("systems$*|notfound")) == false);
        }
    }
}

void AlgorithmEssTestCase::_stubSINGLECombination()
{
    tstring data = _T("new tes;ted project-12, and 75_protection of various systems");

    // MS combination
    {
        //TODO: implement *,>,?,+,# and combination
        {
            /* true: */
            // *
            {
                assert(alg.search(data, _T("*#")) == false);
                assert(alg.search(data, _T("*#*")) == false);
                assert(alg.search(data, _T("#*")) == false);
                assert(alg.search(data, _T("*#systems")) == false);
                assert(alg.search(data, _T("new*#*systems")) == false);
                assert(alg.search(data, _T("*new#*systems*")) == false);
                assert(alg.search(data, _T("new#*systems")) == false);
                assert(alg.search(data, _T("75*#protection")) == false);
                assert(alg.search(data, _T("75*#*protection")) == false);
                assert(alg.search(data, _T("new*#systems")) == false);
                assert(alg.search(data, _T("*new#*#systems*")) == false);
            }

            /* false */
            {
                assert(alg.search(data, _T("*new#systems*")) == false);
                assert(alg.search(data, _T("*new##systems*")) == false);
                assert(alg.search(data, _T("systems*#")) == false);
                assert(alg.search(data, _T("pro#*ject")) == false);
                assert(alg.search(data, _T("systems#*")) == false);
            }
        }

    }

}

void AlgorithmEssTestCase::_stubENDCombination()
{
    tstring data  = _T("new tes;ted project-12, and 75_protection of various systems");
    tstring datam = _T("main systems 1272/is ok");

    // MS combination
    {
        //TODO: implement *,>,?,+,# and combination
        {
            /* true: */
            // *
            {
                assert(alg.search(data, _T("systems*$")) == false);
                assert(alg.search(data, _T("systems**$")) == false);
                assert(alg.search(datam, _T("main*$")) == false);
                assert(alg.search(datam, _T("main**$")) == false);
                assert(alg.search(data, _T("systems*$")) == false);
                assert(alg.search(data, _T("project*$")) == false);
                assert(alg.search(datam, _T("^main*$")) == false);
                {
                    assert(alg.search(data, _T("^*new*$")) == false);
                    assert(alg.search(data, _T("^*$")) == false);
                    assert(alg.search(data, _T("^*$")) == false);
                    assert(alg.search(datam, _T("^*1272*$")) == false);
                }
            }
            // >
            {
                assert(alg.search(data, _T("systems>$")) == false);
                assert(alg.search(data, _T("systems>*$")) == false);
                assert(alg.search(data, _T("various>$")) == false);
                assert(alg.search(data, _T("various>*$")) == false);
                assert(alg.search(data, _T("various>>$")) == false);
            }

            // ?
            {
                assert(alg.search(data, _T("system?$")) == false);
                assert(alg.search(data, _T("systems?$")) == false);
            }
            // +
            {
                assert(alg.search(data, _T("system+$")) == false);
                assert(alg.search(data, _T("syste+$")) == false);
            }
            // #
            {
                assert(alg.search(data, _T("system#$")) == false);
                assert(alg.search(data, _T("syste##$")) == false);
            }

            /* false: */

            // ?
            {
                assert(alg.search(data, _T("syste?$")) == false);
            }
            // +
            {
                assert(alg.search(data, _T("systems+$")) == false);
            }
            // #
            {
                assert(alg.search(data, _T("systems#$")) == false);
                assert(alg.search(data, _T("system##$")) == false);
                assert(alg.search(data, _T("systems##$")) == false);
            }
        }
    }
}

void AlgorithmEssTestCase::asserts()
{
    assertsAny();
    assertsSplit();
    assertsOne();
    assertsAnySP();
    assertsBegin();
    assertsEnd();
    assertsMore();
    assertsSingle();
}

}}}}
