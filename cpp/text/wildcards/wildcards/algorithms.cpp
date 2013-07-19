// sandbox - cpp/text/wildcards
// b0da341, 0100295,  - bitbucket.org/3F/flightsdc/commits/b0da3416478c55f184d65fde1eec8e06c3689d68

#include "algorithms.hpp"
#include <assert.h>

int Algorithms::_started;

/**
 *
 */ 
bool Algorithms::main(const tstring& text, const tstring& filter)
{
    if(filter.empty()){
        return true;
    }

    tstring _text   = uppercase(text);
    tstring _filter = uppercase(filter); //if optimize(to outward): ~18ms

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
            std::size_t lPos        = found - itemPrevLen - 1;
            if(lPos == tstring::npos || _text.substr(lPos, itemPrevLen).compare(itemPrev) != 0){
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
    return std::regex_match(text, std::wregex(filter, std::tr1::regex_constants::icase));
}

bool Algorithms::findRegexpCpp11s(const tstring& text, const tstring& filter)
{
    return std::regex_search(text, std::wregex(filter, std::tr1::regex_constants::icase));
}

bool Algorithms::findGetlineFind(const tstring& text, const tstring& filter)
{
    tstring _text   = uppercase(text);
    tstring _filter = uppercase(filter);
    TCHAR symbol    = _T('*');

    std::wstringstream ss(_filter);
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
    tstring _text   = uppercase(text);
    tstring _filter = uppercase(filter);
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
    tstring _text   = uppercase(text);
    tstring _filter = uppercase(filter);
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
    tstring _text   = uppercase(text);
    tstring _filter = uppercase(filter);
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
    tstring _text       = uppercase(text);
    tstring _filter     = uppercase(filter);
    tstring symbol      = _T("*");

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


/** asserts */

void Algorithms::mainAsserts()
{
    tstring data = _T("new tes;ted project-12, and 75_protection of various systems.");

    // default mode:
     // "*"
        // should be found:
        assert(main(data, _T("protection of various")) == true);      // __ __ __
        assert(main(data, _T("pro*system")) == true);                 // __ * __
        assert(main(data, _T("*pro*system*")) == true);               // * __ * __ *
        assert(main(data, _T("project**various")) == true);           // __ ** __
        assert(main(data, _T("new*7*systems")) == true);              // __ * __ * __
        assert(main(data, _T("")) == true);                           // empty

        // should not be found:
        assert(main(data, _T("project 12 and")) == false);            // __ _x_ __
        assert(main(data, _T("new*express")) == false);               // __ * _x_
        assert(main(data, _T("tes*ting*project")) == false);          // __ * _x_ * __
        assert(main(data, _T("testing*project*and")) == false);       // _x_ * __ * __
        assert(main(data, _T("now*is*completely")) == false);         // _x_ * _x_ * _x_
        assert(main(data, _T("protection*project*new")) == false);    // backwards __ * __ * __
        assert(main(data, _T("**open**close")) == false);             // ** _x_ ** _x_
    
    //split mode:
        // should be found:
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

        // should not be found:        
        assert(main(data, _T("above|fails|with")) == false);           // _x_ | _x_ | _x_
        assert(main(data, _T("let*proj|project*deep")) == false);      // _x_ * __ | __ * _x_
        assert(main(data, _T("operator*|*zeep")) == false);            // _x_ *|* _x_
        assert(main(data, _T("some project|let*various")) == false);   // _x_ __ | _x_* __
        assert(main(data, _T("some project|various*zoom")) == false);  // _x_ __ | __ * _x_
        assert(main(data, _T("be|pen*and*star|*my*system")) == false); // _x_ | _x_ * __ * _x_ | * _x_ * __

    // test of "?"
        // should be found:
        assert(main(data, _T("new*pro?ection")) == true);              // __ * [pro]ject ... [pro]t[ection]
        assert(main(data, _T("????")) == true);
        assert(main(data, _T("project?12")) == true);
        assert(main(_T("system-17 fee also offers protection"), _T("system?17")) == true);

        // should not be found:
        assert(main(data, _T("?pro?12?|seems?7")) == false);
        assert(main(_T("system, installments range from 2 to 17"), _T("system?17")) == false);
        assert(main(_T("system17 fee also"), _T("system?17")) == false);
        assert(main(_T("my system17 fee also"), _T("system?17")) == false);
        assert(main(_T("system_-17 fee also"), _T("system?17")) == false);
}