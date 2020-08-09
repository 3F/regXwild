/*
* The MIT License (MIT)
*
* Copyright (c) 2013-2014, 2016-2017, 2020  Denis Kuzmin < x-3F@outlook.com > GitHub/3F
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include "stdafx.h"
#include "AlgorithmEss.h"

namespace net { namespace r_eg { namespace regXwild { namespace core { namespace ESS {

/**
 * entry for match cases
 * TODO: 
 *  - implement: ONE, MORE, SINGLE for BEGIN & any MS comb. for END [current return value is FALSE]
 *  - MS combination: (item.delta == 0) -> unsigned short int bitmask & pre-comb. variations
 */
bool AlgorithmEss::search(const tstring& text, const tstring& filter, bool ignoreCase)
{
    if(filter.empty()) {
        return true;
    }

    if(ignoreCase) {
        //TODO: [perfomance] by single char for iterator
        _text   = _lowercase(text);
        _filter = _lowercase(filter); //: ~18ms
    }
    else {
        _text   = text;
        _filter = filter;
    }

    item.reset();
    words.reset();

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
            case MS_BEGIN:{
                item.mask.curr = BEGIN;
                break;
            }
            case MS_END:{
                item.mask.curr = END;
                break;
            }
            case MS_MORE:{
                item.mask.curr = MORE;
                break;
            }
            case MS_SINGLE:{
                item.mask.curr = SINGLE;
                break;
            }
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
        
        /* When previous symbol is a meta-symbol - delta equal 0 */

        if((item.delta = item.left - 1 - item.pos) == 0)
        {
            if(item.mask.curr & (SPLIT | EOL)){
                return true;
            }
            
            if(item.mask.curr & BEGIN && (item.mask.prev & (BOL | SPLIT)) == 0) // is not: BOL^__ or SPLIT^__
            {
                if(rewindToNextBlock(it)){ continue; } return false;
            }
            else if(item.mask.curr & END) // combination found, e.g.: *$, ??$, etc. TODO: stub - _stubENDCombination()
            {
                if(rewindToNextBlock(it)){ continue; } return false;
            }

            // ++?? and ##??
            if(item.mask.prev & (MORE | SINGLE) && item.mask.curr & ONE) 
            {
                item.mixpos = item.overlay + 1;
                item.mixms  = item.mask.prev;
            }

            // Sequential combinations of #, ?, +
            if((item.mask.curr & SINGLE && item.mask.prev & SINGLE) 
                || (item.mask.curr & ONE && item.mask.prev & ONE)
                || (item.mask.curr & MORE && item.mask.prev & MORE))
            {
                ++item.overlay;
            }
            else{ item.overlay = 0; }

            ++item.pos;

            // TODO: implement non-sequential MS combinations ~ unsigned short int ..
            if((item.mask.prev & ANYSP) == 0){
                item.mask.prev = item.mask.curr;
            }
            continue;
        }

        /* Otherwise work with a part of word ... */

        if(item.mask.curr & BEGIN){ // __^xxx
            if(rewindToNextBlock(it)){ continue; } return false;
        }

        // getting of current word
        item.curr = _filter.substr(item.pos, item.delta);

        if(item.mask.curr & END)
        {
            if(item.delta <= _text.length() 
                && _text.substr(_text.length() - item.delta).compare(item.curr) == 0)
            {
                if(it + 1 == itEnd){ return true; /*EOL*/ }

                switch(*(it + 1)){
                    case MS_SPLIT:{
                        return true;
                    }
                }
            }
            // __$x
            if(rewindToNextBlock(it)){ continue; } return false;
        }

        if(item.mask.prev & BEGIN)
        {
            if(_text.substr(0, item.delta).compare(item.curr) == 0){
                if(item.mask.curr & (SPLIT | EOL)){
                    return true;
                }
                words.found = 0;
            }
            else{
                if(item.mask.curr & EOL){
                    return false;
                }
                if(item.mask.curr & SPLIT){
                    continue;
                }
                if(rewindToNextBlock(it)){ continue; } return false;
            }
        }
        else{
            // find a part
            if(item.mask.prev & MORE){
                ++words.left;
            }
            words.found = _text.find(item.curr, words.left);
        }

        // working with an interval
        if(words.found != tstring::npos){
            words.found = interval();
        }
        item.overlay = 0; //flush sequence

        /* SPLIT control */

        if(words.found == tstring::npos)
        {
            if(item.mask.curr & EOL){ //TODO: [optimize]: ...or last split-block
                return false;
            }

            item.pos = item.left;
            if(item.mask.curr & SPLIT)
            {
                words.left = 0;
                item.mixpos = 0;
                item.mask.prev = BOL;
                continue; //to next block
            }
            if(rewindToNextBlock(it, false)){ continue; } return false;
        }

        /* Success: */

        if(item.mask.curr & (SPLIT | EOL)){
            return true;
        }

        item.pos        = item.left;
        words.left      = words.found + item.delta;
        item.mask.prev  = item.mask.curr;
        item.prev       = item.curr;
    }

    /* after ending iteration: */

    if(item.mask.prev & MORE && words.left > 0){ // e.g: {word}EOL + {1,~}
        return false;
    }

    if(item.mask.prev & SINGLE){
        if(words.left == _text.length()){ // e.g: {word}EOL + {1}
            return false;
        }
    }

    if(item.mask.prev & ANYSP){ // {word}>***??* etc.
        if(_text.substr(words.left).find(ANYSP_CMP_DEFAULT) != tstring::npos){
            return false;
        }
    }
    return true;
}

udiff_t AlgorithmEss::interval()
{
    // ++?? or ##??
    if(item.mask.prev & ONE && item.mixpos > 0)
    {
        size_t len      = item.prev.length();
        diff_t delta    = words.found - words.left;

        diff_t min = item.mixpos;
        diff_t max = min + item.overlay + 1;

        if(item.mixms & SINGLE && delta != min && delta != max) {
            return tstring::npos;
        }

        if(delta < min || delta > max) {
            return tstring::npos;
        }

        if(_text.substr(words.found - len - delta, len).compare(item.prev) == 0) {
            return words.found;
        }

        return tstring::npos;

    }

    // "#"
    if(item.mask.prev & SINGLE)
    {
        udiff_t len = item.prev.length();
        diff_t lPos = words.found - len - item.overlay - 1;

        // [pro]ject ... [pro]t[ection] -> [pro]<-#-ection
        if(lPos < 0 || _text.substr(lPos, len).compare(item.prev) != 0){
            return tstring::npos;
        }
        return words.found;
    }

    // "+"
    if(item.mask.prev & MORE)
    {
        udiff_t len     = item.prev.length();
        diff_t lPosMax  = words.found - len;
        diff_t plim     = words.found - words.left;
        diff_t lPos     = lPosMax - plim - 1;

        if(item.overlay > plim) { // When filter ++++ (4 or more) is more than origin data.
            return tstring::npos;
        }

        if(_text.substr(lPos, len).compare(item.prev) == 0) {
            return words.found;
        }

        return tstring::npos;
    }

    // "?"
    if(item.mask.prev & ONE && (words.found - words.left) > 1)
    {
        udiff_t len     = item.prev.length();
        diff_t lPosMax  = words.found - len;
        diff_t lPos     = lPosMax - item.overlay - 1;

        if(lPos < 0) { // When filter ???? (0-4) is more than origin data.
            lPos = 0;  //TOOD: currently no info about mixed ms like ??#?
        }

        do // ????? - min<->max:
        {
            if(_text.substr(lPos, len).compare(item.prev) == 0){
                return words.found;
            }
        } while(++lPos < lPosMax);

        return tstring::npos;
    }

    // ">"
    if(item.mask.prev & ANYSP)
    {
        tstring inside = _text.substr(words.left, words.found - words.left);
        if(inside.find(ANYSP_CMP_DEFAULT) != tstring::npos){
            return tstring::npos;
        }
        return words.found;
    }

    //....
    return words.found;
}

inline bool AlgorithmEss::rewindToNextBlock(tstring::const_iterator& it, bool delta)
{
    item.left = _filter.find(MS_SPLIT, item.left);
    if(item.left == tstring::npos){
        return false; //EOL
    }
    
    if(delta){
        it += ++item.left - (item.pos + item.delta) - 1; //or overload =
    }
    else{
        it += ++item.left - item.pos;
    }

    item.pos        = item.left;
    words.left      = 0;
    item.mask.prev  = SPLIT;
    return true;
}

}}}}}
