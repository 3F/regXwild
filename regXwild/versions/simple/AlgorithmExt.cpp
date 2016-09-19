// sandbox - cpp/text/wildcards
// b0da341, 0100295,  - bitbucket.org/3F/flightsdc/commits/b0da3416478c55f184d65fde1eec8e06c3689d68
// based on {Iterator + Find}

/*
  * Copyright (c) 2013 Developed by reg <entry.reg@gmail.com>
  * 
  * Distributed under the Boost Software License, Version 1.0
  * (see accompanying file LICENSE or a copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include "AlgorithmExt.h"

namespace net { namespace r_eg { namespace regXwild {

#define WILDCARDS_SYMB_SLASHS _T("\\/") //both

bool AlgorithmExt::main(const tstring& text, const tstring& filter)
{
    if(filter.empty()){
        return true;
    }

    tstring _text   = _lowercase(text);
    tstring _filter = _lowercase(filter); //if optimize(to outward): ~18ms

    //split-mode: at least one "|"
    bool split = _filter.find(MS_SPLIT) != tstring::npos; //if optimize(to outward): < 1ms

    Item item;
    Words words;

    for(tstring::const_iterator it = _filter.begin(), itEnd = _filter.end(); it != itEnd; ++it)
    {
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
                if(it + 1 == itEnd){
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

        // working with an interval
        if(words.found != tstring::npos){
            //   inner placed ~= outer placed  ~= outer placed + recommendation to compiler with inner placing (inline)
            //       ~211ms   ~=     ~200ms    ~=    ~208ms    :: -_- (average on 110 x (10000 x 300)), see asm instructions
            words.found = _handlerInterval(item, words, _text);
        }

        // SPLIT control
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

        // Success:

        if(item.mask.curr & SPLIT || item.mask.curr & EOL){
            return true;
        }

        item.pos        = item.left;
        words.left      = words.found + item.delta;
        item.mask.prev  = item.mask.curr;
        item.prev       = item.curr;
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
    // "?"
    // TODO: [optimize perfomance]: pre-combination - "item?item"
    if(item.mask.prev & ONE && (words.found - words.left) != 1){ // :: delta -> w?ord
        size_t len      = item.prev.length();
        short int lPos  = words.found - len - 1;
        if(lPos < 0 || text.substr(lPos, len).compare(item.prev) != 0){
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

}}}
