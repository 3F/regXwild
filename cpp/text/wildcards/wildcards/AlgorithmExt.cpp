// sandbox - cpp/text/wildcards
// b0da341, 0100295,  - bitbucket.org/3F/flightsdc/commits/b0da3416478c55f184d65fde1eec8e06c3689d68
// based on {Iterator + Find}

/*
  * Copyright (c) 2013 Developed by reg <entry.reg@gmail.com>
  * 
  * Distributed under the Boost Software License, Version 1.0
  * (see accompanying file LICENSE or a copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "AlgorithmExt.hpp"
#include "Util.hpp"
#include <assert.h>

namespace reg { namespace sandbox { namespace cpp { namespace text { namespace wildcards {

    #define WILDCARDS_SYMB_SLASHS _T("\\/") //both

    bool AlgorithmExt::main(const tstring& text, const tstring& filter)
    {
        if(filter.empty()){
            return true;
        }

        tstring _text   = Util::uppercase(text);
        tstring _filter = Util::uppercase(filter); //if optimize(to outward): ~18ms

        //split-mode: at least one "|"
        bool split = _filter.find(MS_SPLIT) != tstring::npos; //if optimize(to outward): < 1ms

        Item item;
        Words words;

        for(tstring::const_iterator it = _filter.begin(); it != _filter.end(); ++it){
            ++item.left;

            switch(*it){
                case MS_ANY:{
                    item.mask.curr = ANY;
                    break;
                }
                case MS_ANYSP:{
                    item.mask.curr = ANYSP;
                    break;
                }
                case MS_SPLIT:{
                    item.mask.curr = SPLIT;
                    break;
                }
                case MS_ONE:{
                    item.mask.curr = ONE;
                    break;
                }
                //case MS_START:{
                //    item.mask.curr = START;
                //    break;
                //}
                //case MS_END:{
                //    item.mask.curr = END;
                //    break;
                //}
                default:{
                    if(it + 1 == _filter.end()){
                        item.mask.curr = EOL;
                        ++item.left;
                    }
                    else{
                        continue;
                    }
                }
            }
        
            if((item.delta = item.left - 1 - item.pos) == 0){
                if(item.mask.curr & SPLIT || item.mask.curr & EOL){
                    return true;
                }
                ++item.pos;
                continue;
            }

            //getting item
            item.curr = _filter.substr(item.pos, item.delta);

            //find a part
            words.found = _text.find(item.curr, words.left);

            //working with an interval
            //   inner placed ~= outer placed  ~= outer placed + recommendation to compiler with inner placing (inline)
            //       ~211ms   ~=     ~200ms    ~=    ~208ms    :: -_- (average on 110 x (10000 x 300))
            words.found = _handlerInterval(item, words, _text);

            if(words.found == tstring::npos){
                if(!split || item.mask.curr & EOL){ //TODO: [optimize perfomance]: ...or last block
                    return false;
                }

                item.pos = item.left;
                if(item.mask.curr & SPLIT){
                    continue; //to next block
                }

                 // rewind to next block |
                item.left = _filter.find(MS_SPLIT, item.left);
                if(item.left == tstring::npos){
                    return false; //EOL
                }
                words.left  = 0;
                it         += ++item.left - item.pos; //or overload =
                item.pos    = item.left;
                continue;
            }

            if(words.found != tstring::npos){
                if(item.mask.curr & SPLIT || item.mask.curr & EOL){
                    return true;
                }

                item.pos        = item.left;
                words.left      = words.found + item.delta;
                item.mask.prev  = item.mask.curr;
                item.prev       = item.curr;
            }
        }

        //after ending iteration
        if(item.mask.prev & ANYSP){ // {word}>***??* etc.
            if(_text.substr(words.left).find_first_of(WILDCARDS_SYMB_SLASHS) != tstring::npos){
                return false;
            }
        }
        return true;
    }

    size_t AlgorithmExt::_handlerInterval(Item& item, Words& words, const tstring& text)
    {
        if(words.found == tstring::npos){
            return tstring::npos;
        }

        // "?"
        // TODO: [optimize perfomance]: pre-combination - "item?item"
        if(item.mask.prev & ONE && (words.found - words.left) != 1){ // :: delta -> w?ord
            size_t len  = item.prev.length();
            size_t lPos = words.found - len - 1;
            if(lPos == tstring::npos || text.substr(lPos, len).compare(item.prev) != 0){
                return tstring::npos;
            }
            return words.found;
        }

        // ">"
        if(item.mask.prev & ANYSP){
            tstring inside = text.substr(words.left, words.found - words.left);
            if(inside.find_first_of(WILDCARDS_SYMB_SLASHS) != tstring::npos){ // < ~1ms; comparison with: '\\' -> '/' + find() ~= 3-4ms
                return tstring::npos;
            }
            return words.found;
        }

        //....
        return words.found;
    }

    void AlgorithmExt::_assertsAny()
    {
        tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

        /* should be found: */
        assert(main(data, _T("protection of various")) == true);      // __ __ __
        assert(main(data, _T("pro*system")) == true);                 // __ * __
        assert(main(data, _T("*pro*system*")) == true);               // * __ * __ *
        assert(main(data, _T("project**various")) == true);           // __ ** __
        assert(main(data, _T("new*7*systems")) == true);              // __ * __ * __
        assert(main(data, _T("")) == true);                           // empty

        /* should not be found: */
        assert(main(data, _T("project 12 and")) == false);            // __ _x_ __
        assert(main(data, _T("new*express")) == false);               // __ * _x_
        assert(main(data, _T("tes*ting*project")) == false);          // __ * _x_ * __
        assert(main(data, _T("testing*project*and")) == false);       // _x_ * __ * __
        assert(main(data, _T("now*is*completely")) == false);         // _x_ * _x_ * _x_
        assert(main(data, _T("protection*project*new")) == false);    // backwards __ * __ * __
        assert(main(data, _T("**open**close")) == false);             // ** _x_ ** _x_
    }

    void AlgorithmExt::_assertsSplit()
    {
        tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

        /* should be found: */
        assert(main(data, _T("protection of|new tes")) == true);       // __ __ | __ __
        assert(main(data, _T("some project|of various")) == true);     // _x_ __ | __ __
        assert(main(data, _T("various systems|new 237")) == true);     // __ __ | __ _x_
        assert(main(data, _T("pro*12|new*system")) == true);           // __ * __ | __ *__
        assert(main(data, _T("ject*new|pro*tems")) == true);           // __ * _x_ | __ * __
        assert(main(data, _T("pro*tems|seems*and")) == true);          // __ * __ | _x_ * __
        assert(main(data, _T("project*|new")) == true);                // __ *| __
        assert(main(data, _T("various*|zeep")) == true);               // __ * | _x_
        assert(main(data, _T("goo*|systems")) == true);                // _x_ * | __
        assert(main(data, _T("project||protect")) == true);            // __ || __
        assert(main(data, _T("|new||and|")) == true);                  // | __ || __ |
        assert(main(data, _T("|fail|system")) == true);                // | _x_ | __
        assert(main(data, _T("|12||true||")) == true);                 // | __ || _x_ ||
        assert(main(data, _T("above|new|with")) == true);              // _x_ | __ | _x_
        assert(main(data, _T("project**|new")) == true);               // __ **| __
        assert(main(data, _T("zoom|*pro")) == true);                   // _x_ | * __
        assert(main(data, _T("zoom|*pro**")) == true);                 // _x_ | *__ **
        assert(main(data, _T("||")) == true);                          //empty
        assert(main(data, _T("")) == true);                            //empty
        assert(main(data, _T("||zoom||out||")) == true);               // ||_x_ || _x_ ||
        assert(main(data, _T("|*|")) == true);                         // |*|
        assert(main(data, _T("|long-term")) == true);                  // | _x_
        assert(main(data, _T("long-term|")) == true);                  // _x_ |
        assert(main(data, _T("*|*")) == true);                         // *|*
        assert(main(data, _T("*|")) == true);                          // *|
        assert(main(data, _T("|*")) == true);                          // |*
        assert(main(data, _T("seems|open*and*star|*system")) == true); // _x_ | _x_ * __ * _x_ | * __

        /* should not be found: */
        assert(main(data, _T("above|fails|with")) == false);           // _x_ | _x_ | _x_
        assert(main(data, _T("let*proj|project*deep")) == false);      // _x_ * __ | __ * _x_
        assert(main(data, _T("operator*|*zeep")) == false);            // _x_ *|* _x_
        assert(main(data, _T("some project|let*various")) == false);   // _x_ __ | _x_* __
        assert(main(data, _T("some project|various*zoom")) == false);  // _x_ __ | __ * _x_
        assert(main(data, _T("be|pen*and*star|*my*system")) == false); // _x_ | _x_ * __ * _x_ | * _x_ * __
    }

    void AlgorithmExt::_assertsOne()
    {
        tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

        /* should be found: */
        assert(main(data, _T("new*pro?ection")) == true);              // __ * [pro]ject ... [pro]t[ection]
        assert(main(data, _T("????")) == true);
        assert(main(data, _T("project?12")) == true);
        assert(main(_T("system-17 fee also offers protection"), _T("system?17")) == true);

        /* should not be found: */
        assert(main(data, _T("?pro?12?|seems?7")) == false);
        assert(main(_T("system, installments range from 2 to 17"), _T("system?17")) == false);
        assert(main(_T("system17 fee also"), _T("system?17")) == false);
        assert(main(_T("my system17 fee also"), _T("system?17")) == false);
        assert(main(_T("system_-17 fee also"), _T("system?17")) == false);
    }

    void AlgorithmExt::_assertsAnySP()
    {
        /* should be found: */
        assert(main(_T("/new/user_myhid_test.bzip2"), _T("myhid>bzip")) == true);   // __...___
        assert(main(_T("/new/user_myhid_test.bzip2"), _T("myhid>")) == true);       // __...EOL
        assert(main(_T("/new/user_myhid"), _T("myhid>")) == true);                  // __EOL
        
        /* with other metasymbols: */
        {
            assert(main(_T("/new/user_myhid"), _T("myhid>*")) == true);
            assert(main(_T("/new/user_myhid"), _T("myhid>***")) == true);
            assert(main(_T("/new/user_myhid"), _T("myhid>?")) == true);
            assert(main(_T("/new/user_myhid"), _T("myhid>?*")) == true);
        }

        /* should not be found: */
        assert(main(_T("/new/user_myhid_t/est.bzip2"), _T("myhid>bzip")) == false);     // __.../...__
        assert(main(_T("/new/user_myhid/_test.bzip2"), _T("myhid>bzip")) == false);     // __/...__
        assert(main(_T("/new/user_myhid_test./bzip2"), _T("myhid>bzip")) == false);     // __.../__
        assert(main(_T("/new/user_myhid_te/st.bzip2"), _T("myhid>")) == false);         // __.../...EOL
        assert(main(_T("/new/user_myhid_te/"), _T("myhid>")) == false);                 // __.../EOL
        assert(main(_T("/new/user_myhid_t\\est.bzip2"), _T("myhid>bzip")) == false);    //  "\" & "//"
        
        /* with other metasymbols: */
        {
            assert(main(_T("/new/user_myhid_s/df.txt"), _T("myhid>*")) == false);
            assert(main(_T("/new/user_myhid_s/df.txt"), _T("myhid>***")) == false);
            assert(main(_T("/new/user_myhid_s/df.txt"), _T("myhid>?")) == false);
            assert(main(_T("/new/user_myhid_s/df.txt"), _T("myhid>?*")) == false);
            //-
            assert(main(_T("/new/user_myhid_s/df.txt"), _T("myhid>*txt")) == false);
            assert(main(_T("/new/user_myhid_s/df.txt"), _T("myhid>***txt")) == false);
            assert(main(_T("/new/user_myhid_s/df.txt"), _T("myhid>?txt")) == false);
            assert(main(_T("/new/user_myhid_s/df.txt"), _T("myhid>?*??txt")) == false);
            //-
            assert(main(_T("/new/user_myhid"), _T("myhid>*txt")) == false);
            assert(main(_T("/new/user_myhid"), _T("myhid>***txt")) == false);
            assert(main(_T("/new/user_myhid"), _T("myhid>?txt")) == false);
            assert(main(_T("/new/user_myhid"), _T("myhid>?*??txt")) == false);
        }
    }

    void AlgorithmExt::_asserts()
    {
        _assertsAny();
        _assertsSplit();
        _assertsOne();
        _assertsAnySP();
    }

}}}}};
