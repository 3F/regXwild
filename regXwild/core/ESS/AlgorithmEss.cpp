/*
* The MIT License (MIT)
*
* Copyright (c) 2013-2021  Denis Kuzmin <x-3F@outlook.com> github/3F
* Copyright (c) regXwild contributors https://github.com/3F/regXwild
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

using namespace def;

/// <summary>
/// Basic search for occurrence using filter.
/// </summary>
/// <returns>True if found.</returns>
bool AlgorithmEss::search(const tstring& text, const tstring& filter, bool ignoreCase)
{
    return match(text, filter, (ignoreCase ? FlagsRxW::F_ICASE : FlagsRxW::F_NONE) | FlagsRxW::F_LEGACY_ANYSP);
}

/// <summary>
/// Searches an input string for a substring that matches a pattern.
/// </summary>
/// <param name="input">The string to search for a match.</param>
/// <param name="pattern">Compatible pattern to match.</param>
/// <param name="options">A bitwise combination of the enumeration values that provide options for matching.</param>
/// <param name="result">Information about the match.</param>
/// <returns>True if the match was successful.</returns>
bool AlgorithmEss::match(const tstring& input, const tstring& pattern, const FlagsRxW& options, Match* result)
{
    if(pattern.empty()) return set(result, options, 0, input.length());
    reset(result);

    tstring text, filter;

    if(options & FlagsRxW::F_ICASE) {
        //TODO: [perfomance] char by char along with the pattern chunks as we move to the right
        text    = _lowercase(input);
        filter  = _lowercase(pattern);
    }
    else {
        text    = input;
        filter  = pattern;
    }

    Item item;

    item.mres  = result;
    item.flags = &options;

    FWord word;
    word.len = text.length();

    tstring::const_iterator it = filter.begin();
    item.it = &it;

    for(tstring::const_iterator itEnd = filter.end(); it != itEnd; item.it = &++it)
    {
        ++item.left;

        switch(*it)
        {
            case MS_ANY:    { item.mask.curr = ANY; break;      }
            case MS_ANYSP:  { item.mask.curr = ANYSP; break;    }
            case MS_SPLIT:  { item.mask.curr = SPLIT; break;    }
            case MS_ONE:    { item.mask.curr = ONE; break;      }
            case MS_BEGIN:  { item.mask.curr = BEGIN; break;    }
            case MS_END:    { item.mask.curr = END; break;      }
            case MS_MORE:   { item.mask.curr = MORE; break;     }
            case MS_SINGLE: { item.mask.curr = SINGLE; break;   }
            default:
            {
                if(it + 1 == itEnd) {
                    item.mask.curr = EOL;
                    ++item.left;
                }
                else continue;
            }
        }
        
        // When previous symbol is a meta-symbol
        if((item.delta = item.left - 1 - item.pos) == 0)
        {
            if(item.mask.curr & (SPLIT | EOL)) return setEnd(item, word);
            
            if(item.mask.curr & BEGIN && (item.mask.prev & (BOL | SPLIT)) == 0) // is not BOL^__ or SPLIT^__
            {
                if(jumpRight(item, word, filter, it)) { continue; } return unsetMatch(item);
            }
            else if(item.mask.curr & END) // combination, e.g.: *$, ??$, etc. TODO: stub - _stubENDCombination()
            {
                if(jumpRight(item, word, filter, it)) { continue; } return unsetMatch(item);
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

            if((options & FlagsRxW::F_LEGACY_ANYSP) == 0 && item.mask.curr & ANYSP)
            {
                ++item.pos;
                if(item.left > 1) continue;
            }
            else
            {
                if((item.mask.prev & ANYSP) == 0) item.mask.prev = item.mask.curr;
                continue;
            }
        }

        /* Otherwise, work with part of the word ... */

        if(item.mask.curr & BEGIN) { // __^xxx
            if(jumpRight(item, word, filter, it)) { continue; } return unsetMatch(item);
        }

        // Actual word part between meta-symbols
        item.curr = (item.pos < filter.length()) ? filter.substr(item.pos, item.delta) : _T("\0");

        if(item.mask.prev & BEGIN)
        {
            if(text.substr(0, item.delta).compare(item.curr) == 0)
            {
                if(item.mask.curr & (SPLIT | EOL)) {
                    return setEnd(item, word);
                }
                if(item.mask.curr & (SINGLE | ONE | MORE)) {
                    item.bems = BEGIN;
                }
                word.found = 0;
            }
            else
            {
                if(item.mask.curr & EOL) return unsetMatch(item);
                if(item.mask.curr & SPLIT) continue;
                if(jumpRight(item, word, filter, it)) { continue; } return unsetMatch(item);
            }
        }
        else
        {
            udiff_t roff = (item.mask.prev & (MORE | SINGLE)) ? ++word.left + item.overlay 
                                                              : word.left;

            word.found = text.find(item.curr, roff);
        }

        if(isOnResult(result, options) && result->start == Match::npos)
        {
            result->start = (item.mask.prev & (SINGLE | MORE)) ? word.found - item.overlay - 1 
                                                               : word.found;
        }

        if(word.found != tstring::npos) {
            word.found = parseInterval(item, word, options, text, filter);
        }
        item.overlay = 0; //flush sequence

        /* End of block control */

        if(word.found == tstring::npos)
        {
            if(item.mask.curr & (EOL | END)) { //TODO: [optimize]: ...or last split-block
                return unsetMatch(item);
            }

            item.pos = item.left;
            if(item.mask.curr & SPLIT)
            {
                word.left = 0;
                item.mixpos = 0;
                item.mask.prev = BOL;
                continue; //to next block
            }

            if(jumpRight(item, word, filter, it, false)) { continue; } return unsetMatch(item);
        }
        else
        {
            if(item.mask.curr & END)
            {
                if(text.substr(word.found).compare(item.curr) == 0)
                {
                    const tstring::const_iterator itUp = it + 1;

                    if(itUp == itEnd) return setEnd(item, word); /*EOL*/

                    switch(*(itUp)) {
                        case MS_SPLIT: return setEnd(item, word);
                    }
                }
                // __$x
                if(jumpRight(item, word, filter, it)) { continue; } return unsetMatch(item);
            }
        }

        /* Success */

        if(item.mask.curr & (SPLIT | EOL)) return setEnd(item, word);

        item.pos        = item.left;
        word.left       = word.found + item.delta;
        item.mask.prev  = item.mask.curr;
        item.prev       = item.curr;
    }
    item.mask.curr = EOL; // it + 1 == itEnd

    /* After the end of iterations */

    if(item.mask.prev & (MORE | SINGLE) && word.left >= text.length()) {
        return unsetMatch(item); // {word}EOL + {1,~}
    }

    if(item.mask.prev & ANYSP) { // disables MS combination if legacy mode ({word} >*) and completes >{char}{EOL} as [^{char}]*$
        if(text.substr(word.left).find(getSPSymbol(item, options)) != tstring::npos) {
            return unsetMatch(item);
        }
    }
    return setEnd(item, word);
}

udiff_t AlgorithmEss::parseInterval(Item& item, FWord& word, const FlagsRxW& options, const tstring& text, const tstring& filter)
{
    // ">"
    if(item.mask.prev & ANYSP)
    {
        if(text.substr(word.left, word.found - word.left).find(getSPSymbol(item, options)) != tstring::npos) {
            return tstring::npos;
        }

        // We don't need to process anything else just to get out here ASAP
        if(options & FlagsRxW::F_LEGACY_ANYSP || (item.mask.curr & ANYSP) == 0) return word.found;
    }
    // ^v
    if(item.mask.curr & ANYSP && (options & FlagsRxW::F_LEGACY_ANYSP) == 0)
    {
        if(item.left < filter.length())
        {
            // ">" + {symbol}
            item.anysp = filter[item.left++];
            ++*item.it;
        }
        return word.found;
    }

    // ++?? or ##??
    if(item.mask.prev & ONE && item.mixpos > 0)
    {
        size_t len      = item.prev.length();
        diff_t delta    = word.found - word.left;

        diff_t min = item.mixpos;
        diff_t max = min + item.overlay + 1;

        if(item.mixms & SINGLE && delta != min && delta != max || /*& MORE*/delta > max) // " = 12" -> "= 123"
        {
            diff_t lPos = word.found - len - max;

            if(lPos < 0 || (item.bems & BEGIN && lPos != 0) || text.substr(lPos, len).compare(item.prev) != 0) {
                return tstring::npos;
            }

            if(isOnResult(item.mres, options) && isEqPrev(text, item, len)) shiftStart(lPos, item);
            return word.found;
        }
        if(/*& MORE*/delta < min) return tstring::npos;

        if(text.substr(word.found - len - delta, len).compare(item.prev) == 0) {
            return word.found;
        }

        return tstring::npos;
    }

    // "#"
    if(item.mask.prev & SINGLE)
    {
        udiff_t len = item.prev.length();
        diff_t lPos = word.found - len - item.overlay - 1;

        if(item.bems & BEGIN && lPos != 0) return tstring::npos;

        // [pro]ject ... [pro]t[ection] -> [pro]<-#-ection
        if(lPos < 0 || text.substr(lPos, len).compare(item.prev) != 0) {
            return tstring::npos;
        }

        // shifts the position to the current, ie. ^0->0#2
        if(isOnResult(item.mres, options) && isEqPrev(text, item, len)) shiftStart(lPos, item);
        return word.found;
    }

    // "+"
    if(item.mask.prev & MORE)
    {
        udiff_t len     = item.prev.length();
        diff_t lPosMax  = word.found - len;
        diff_t plim     = word.found - word.left;
        diff_t lPos     = lPosMax - plim - 1;

        if(item.overlay > plim) return tstring::npos; // When filter ++++ (4 or more) is more than origin data.

        if(text.substr(lPos, len).compare(item.prev) != 0) return tstring::npos;

        if(isOnResult(item.mres, options) && isEqPrev(text, item, len)) shiftStart(lPos, item);
        return word.found;
    }

    // "?"
    if(item.mask.prev & ONE && (word.found - word.left) > 1)
    {
        udiff_t len     = item.prev.length();
        diff_t lPosMax  = word.found - len;
        diff_t lPos     = lPosMax - item.overlay - 1;

        if(lPos < 0) { // When filter ???? (0-4) is more than origin data.
            lPos = 0;  //TOOD: currently no info about mixed ms like ??#?
        }

        if(item.bems & BEGIN && lPos != 0) return tstring::npos;

        do // ????? - min<->max:
        {
            if(text.substr(lPos, len).compare(item.prev) == 0)
            {
                if(isOnResult(item.mres, options) && isEqPrev(text, item, len))
                    shiftStart(len < 1 ? /*lazy*/word.found : /*greedy*/lPos, item);

                return word.found;
            }
        } while(++lPos < lPosMax);

        return tstring::npos;
    }
    // ^v calculates "?" for mres->start position
    if(isOnResult(item.mres, options) && item.mask.prev & (ONE | ANY) && (word.found - word.left) == 1)
    {
        udiff_t len = item.prev.length();
        diff_t lPos = word.found - len;

        if(text.substr(lPos, len).compare(item.prev) == 0 && isEqPrev(text, item, len)) shiftStart(lPos, item);
    }

    return word.found;
}

inline bool AlgorithmEss::jumpRight(Item& item, FWord& word, const tstring& filter, tstring::const_iterator& it, bool delta)
{
    item.left = filter.find(MS_SPLIT, item.left);
    if(item.left == tstring::npos) return false; //EOL
    
    if(delta) {
        it += ++item.left - (item.pos + item.delta) - 1; //or overload =
    }
    else{
        it += ++item.left - item.pos;
    }

    item.pos        = item.left;
    word.left       = 0;
    item.mask.prev  = SPLIT;
    return true;
}

inline bool AlgorithmEss::set(Match* result, const FlagsRxW& options, udiff_t start, udiff_t end)
{
#if _RXW_FEATURE_MATCH_RESULT

    if(result != nullptr)
    {
        if(options & FlagsRxW::F_MATCH_RESULT)
        {
            result->start = start;
            result->end = end;
        }
        else result->start = Match::npos;
    }

#endif
    return true;
}

inline void AlgorithmEss::reset(Match* result)
{
#if _RXW_FEATURE_MATCH_RESULT
    if(result != nullptr) result->start = Match::npos;
#endif
}

inline bool AlgorithmEss::unsetMatch(Item& item)
{
#if _RXW_FEATURE_MATCH_RESULT
    setStart(item, Match::npos);
#endif
    return false;
}

inline void AlgorithmEss::setStart(Item& item, udiff_t start)
{
#if _RXW_FEATURE_MATCH_RESULT
    if(isOnResult(item.mres, *item.flags)) item.mres->start = start;
#endif
}

inline void AlgorithmEss::shiftStart(udiff_t start, Item& item)
{
#if _RXW_FEATURE_MATCH_RESULT

    if(!item.shiftms)
    {
        item.shiftms = true;
        setStart(item, start);
    }

#endif
}

bool AlgorithmEss::setEnd(Item& item, const FWord& word)
{
#ifndef _RXW_FEATURE_MATCH_RESULT
    return true;
#endif

    if(isOnResult(item.mres, *item.flags))
    {
        udiff_t _found = (word.found == tstring::npos) ? 0 : word.found;

        udiff_t _end = _found;
        if(item.mres->start == Match::npos) item.mres->start = _end;

        if(item.mask.curr & EOL && item.mask.prev & MORE && item.pos == item.left 
            || word.len == 0)
        {
            item.mres->end = word.len;
            return true;
        }

        if(item.delta > 0)
        {
            _end += item.delta;
            if(_end == 0) ++_end;
            if(item.mask.curr & SINGLE || (item.mask.curr & EOL && item.mask.prev & SINGLE && item.pos == item.left)) ++_end;
            item.mres->end = _end + item.overlay;
        }
        else
        {
            _end = word.left < _found ? _found : word.left;
            if(item.mask.curr & SINGLE) _end += item.overlay == 0 ? 1 : static_cast<udiff_t>(item.overlay) + 1;
            if(item.mask.curr & EOL && item.mask.prev & SINGLE) _end += static_cast<udiff_t>(item.overlay) + 1;
            if(item.mask.curr & END) ++_end;
            item.mres->end = _end;
        }
    }
    return true;
}

inline bool AlgorithmEss::isOnResult(const Match* result, const FlagsRxW& options)
{
#if _RXW_FEATURE_MATCH_RESULT
    return result != nullptr && options & FlagsRxW::F_MATCH_RESULT;
#else
    return false;
#endif
}

inline bool AlgorithmEss::isEqPrev(const tstring& input, const Item& item, udiff_t len)
{
#if _RXW_FEATURE_MATCH_RESULT
    return item.mres->start != Match::npos && input.substr(item.mres->start, len).compare(item.prev) == 0;
#else
    return false;
#endif
}

inline TCHAR AlgorithmEss::getSPSymbol(const Item& item, const FlagsRxW& options)
{
    return options & FlagsRxW::F_LEGACY_ANYSP ? ANYSP_CMP_DEFAULT : item.anysp;
}

}}}}}
