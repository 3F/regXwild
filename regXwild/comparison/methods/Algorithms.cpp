/*
* The MIT License (MIT)
*
* Copyright (c) 2013, 2014, 2016  Denis Kuzmin <entry.reg@gmail.com>
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

#include "Algorithms.h"
#include "../../common/Util.h"

namespace net { namespace r_eg { namespace regXwild {

bool Algorithms::main(const tstring& text, const tstring& filter)
{
    if(filter.empty()){
        return true;
    }

    tstring _text   = Util::uppercase(text);
    tstring _filter = Util::uppercase(filter); //if optimize(to outward): ~18ms

    enum MetaOperation{
        FLUSH   = 0,
        ANY     = 1,
        SPLIT   = 2,
        ONE     = 4,
        START   = 8,
        END     = 16,
        EOL     = 32,
    } mask, prevMask = FLUSH;

    enum MetaSymbols{
        MS_ANY      = _T('*'),
        MS_SPLIT    = _T('|'),
        MS_ONE      = _T('?'),
        MS_START    = _T('^'),
        MS_END      = _T('$'),
    };

    //split-mode: at least one "|"
    bool split = _filter.find(MS_SPLIT) != tstring::npos; //if optimize(to outward): < 1ms

    // to wildcards
    tstring     item;
    tstring     itemPrev;
    std::size_t itemPos     = 0;
    std::size_t itemLeft    = 0;
    std::size_t itemDelta   = 0;

    // to words
    std::size_t found;
    std::size_t left        = 0;
    for(tstring::const_iterator it = _filter.begin(); it != _filter.end(); ++it){
        ++itemLeft;

        switch(*it){
            case MS_ANY:{
                mask = ANY;
                break;
            }
            case MS_SPLIT:{
                mask = SPLIT;
                break;
            }
            case MS_ONE:{
                mask = ONE;
                break;
            }
            //case MS_START:{
            //    mask = START;
            //    break;
            //}
            //case MS_END:{
            //    mask = END;
            //    break;
            //}
            default:{
                if(it + 1 == _filter.end()){
                    mask = EOL;
                    ++itemLeft;
                }
                else{
                    continue;
                }
            }
        }
        
        if((itemDelta = itemLeft - 1 - itemPos) == 0){
            if(mask & SPLIT || mask & EOL){
                return true;
            }
            ++itemPos;
            continue;
        }

        item = _filter.substr(itemPos, itemDelta);

        //find a part
        found = _text.find(item, left);

        //compare delta -> w?ord
        // TODO: [optimize perfomance]: pre-combination - "item?item"
        if(prevMask & ONE && found != tstring::npos && (found - left) != 1){
            std::size_t itemPrevLen = itemPrev.length();
            short int lPos          = found - itemPrevLen - 1;
            if(lPos < 0 || _text.substr(lPos, itemPrevLen).compare(itemPrev) != 0){
                found = tstring::npos;
            }
        }

        if(found == tstring::npos){
            if(!split || mask & EOL){ //TODO: [optimize perfomance]: ...or last block
                return false;
            }

            itemPos = itemLeft;
            if(mask & SPLIT){
                continue; //to next block
            }

            // rewind to next block |
            itemLeft = _filter.find(MS_SPLIT, itemLeft);
            if(itemLeft == tstring::npos){
                return false; //EOL
            }
            left    = 0;
            it     += ++itemLeft - itemPos; //or overload =
            itemPos = itemLeft;
            continue;
        }

        if(found != tstring::npos){
            if(mask & SPLIT || mask & EOL){
                return true;
            }

            itemPos     = itemLeft;
            left        = found + itemDelta;
            prevMask    = mask;
            itemPrev    = item;
        }
    }
    return true;
}

bool Algorithms::findRegexpCpp11m(const tstring& text, const tstring& filter)
{
    return std::regex_match(text, tregex(filter, std::tr1::regex_constants::icase));
}

bool Algorithms::findRegexpCpp11s(const tstring& text, const tstring& filter)
{
    return std::regex_search(text, tregex(filter, std::tr1::regex_constants::icase));
}

bool Algorithms::findGetlineFind(const tstring& text, const tstring& filter)
{
    tstring _text   = Util::uppercase(text);
    tstring _filter = Util::uppercase(filter);
    TCHAR symbol    = _T('*');

    tstringStream ss(_filter);
    tstring item;
    size_t found;
 
    size_t prevFound   = 0;
    size_t prevLen     = 0;
    while(std::getline(ss, item, symbol)){        
        found = _text.find(item, (prevFound + prevLen));
 
        if(found == std::string::npos){
            return false;
        }
 
        prevLen     = item.length();
        prevFound   = found;
    }
    return true;
}

bool Algorithms::findFindFind(const tstring& text, const tstring& filter)
{
    tstring _text   = Util::uppercase(text);
    tstring _filter = Util::uppercase(filter);
    TCHAR symbol    = _T('*');

    size_t nextDelim;
    size_t pos = 0;
    tstring item;
 
    size_t found;
    size_t prevFound   = 0;
    size_t prevLen     = 0;
    while((nextDelim = _filter.find(symbol, pos)) != std::string::npos){
        item = _filter.substr(pos, nextDelim - pos);
        if(!item.empty()){
            found = _text.find(item, (prevFound + prevLen));
 
            if(found == std::string::npos){
                return false;
            }
 
            prevLen     = item.length();
            prevFound   = found;
        }
        pos = nextDelim + 1;
    }
    return true;
}

bool Algorithms::findIteratorSubstr(const tstring& text, const tstring& filter)
{
    tstring _text   = Util::uppercase(text);
    tstring _filter = Util::uppercase(filter);
    TCHAR symbol    = _T('*');

    tstring item;
    size_t posFilter = 0;
    size_t posFilter2 = 0;
    //---
    tstring item2;
    size_t itemLen;
    size_t posPrev = 0;
    //--- 
 
    for(tstring::const_iterator it = _filter.begin(); it != _filter.end(); ++it){
        item = *it;
        posFilter2++;
        if(*it == symbol){
            item = _filter.substr(posFilter, posFilter2 - 1 - posFilter);
 
            if(item.empty()){
                posFilter = posFilter2;
                continue;
            }
 
            itemLen = item.length();
            bool flag = false;
            for(int idx = posPrev, n = text.length(); idx < n; ++idx){
                item2 = _text.substr(idx, itemLen);
                if(item.compare(item2) == 0){
                    posPrev = idx + itemLen;
                    flag = true;
                    break;
                }
            }
            if(!flag){
                return false;
            } 
            posFilter = posFilter2;
        }
    } 
    return true;
}

bool Algorithms::findIteratorFind(const tstring& text, const tstring& filter)
{
    tstring _text   = Util::uppercase(text);
    tstring _filter = Util::uppercase(filter);
    tstring symbol  = _T("*");

    // to wildcards
    tstring     item;
    std::size_t itemPos     = 0;
    std::size_t itemLeft    = 0;
    std::size_t itemDelta   = 0;

    // to words
    std::size_t found;
    std::size_t left        = 0;
    for(tstring::const_iterator it = _filter.begin(); it != _filter.end(); ++it){
        item = *it;
        ++itemLeft;
        if(item.compare(symbol) == 0 || it + 1 == _filter.end() && ++itemLeft ){
            if((itemDelta = itemLeft - 1 - itemPos) == 0){
                ++itemPos;
                continue;
            }
            item = _filter.substr(itemPos, itemDelta);

            //find a part
            found = _text.find(item, left);
            if(found == std::string::npos){
                return false;
            }
            left = found + item.length();

            itemPos = itemLeft;
        }
    }
    return true;
}

bool Algorithms::findIteratorIterator(const tstring& text, const tstring& filter)
{
    tstring _text   = Util::uppercase(text);
    tstring _filter = Util::uppercase(filter);
    tstring symbol  = _T("*");

    tstring item;
    std::size_t posFilter   = 0;
    std::size_t posFilter2  = 0;
    //---
    tstring item2;
    std::size_t itemLen;
    std::size_t posPrev = 0;
    std::size_t idx;
    tstring::const_iterator iterLast = _text.begin();
    //---

    for(tstring::const_iterator it = _filter.begin(); it != _filter.end(); ++it){
        item = *it;
        posFilter2++;
        if(item.compare(symbol) == 0){
            item = _filter.substr(posFilter, posFilter2 - 1 - posFilter);
 
            if(item.empty()){
                posFilter = posFilter2;
                continue;
            }
 
            itemLen     = item.length();
            bool flag   = false;
            item2       = _T("");
            idx         = 0;
            for(tstring::const_iterator it2 = iterLast; it2 != _text.end(); ++it2){
                item2 += *it2;
                if(++idx < itemLen){
                    continue;
                }
                if(item.compare(item2) == 0){
                    iterLast = it2 + 1;
                    flag = true;
                    break;
                }
                item2.erase(0, 1);
                idx = itemLen - 1;
            }
            if(!flag){
                return false;
            } 
            posFilter = posFilter2;
        }
    } 
    return true;
}

}}}