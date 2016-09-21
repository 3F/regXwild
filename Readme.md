
*from my [sandbox](https://github.com/3F/sandbox)*

Fast and powerful wildcards ! `*,|,?,^,$,+,#,>` to replace slow regexp engine and more...

[![Build status](https://ci.appveyor.com/api/projects/status/92y03ofto5fbb60a/branch/master?svg=true)](https://ci.appveyor.com/project/3Fs/regxwild/branch/master)
[![release-src](https://img.shields.io/github/release/3F/regXwild.svg)](https://github.com/3F/regXwild/releases/latest)
[![License](https://img.shields.io/badge/License-MIT-74A5C2.svg)](https://github.com/3F/regXwild/blob/master/LICENSE)

## C/C++ API

The regXwild library exports the following functions (C-linkage):

```cpp
    /**
    * To search substring in data with filter by the rules of ESS algorithm. 
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @param ignoreCase To check data with no case sensitive rules.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API bool searchEss(const tstring& data, const tstring& filter, bool ignoreCase = true);
    
    /**
    * To search substring in data with filter by the rules of EXT algorithm.
    * @param data Where to search.
    * @param filter The filter of comparison string.
    * @return Returns true value if the data satisfies the condition of the filter.
    */
    REGXWILD_API bool searchExt(const tstring& data, const tstring& filter);
```


## C# & .NET

For .NET users: use [Conari](https://github.com/3F/Conari) engine for work as you like:


TODO:

```csharp

using(var l = new ConariL("regXwild.dll")) {
    // ...    
}
```

## Meta symbols

ESS algorithm:

```cpp
enum MetaSymbols
{
    MS_ANY      = _T('*'), // {0, ~}
    MS_SPLIT    = _T('|'), // str1 or str2 or ...
    MS_ONE      = _T('?'), // {0, 1}, ??? - {0, 3}, ...
    MS_BEGIN    = _T('^'), // [str... or [str1... |[str2...
    MS_END      = _T('$'), // ...str] or ...str1]| ...str2]
    MS_MORE     = _T('+'), // {1, ~}
    MS_SINGLE   = _T('#'), // {1}
    MS_ANYSP    = _T('>'), // as [^/]*  //TODO: >\>/ i.e. '>' + {symbol}
};
```


EXT algorithm:

```cpp
enum MetaSymbols{
    MS_ANY      = _T('*'),
    MS_ANYSP    = _T('>'), //as [^/\\]+
    MS_SPLIT    = _T('|'),
    MS_ONE      = _T('?'),
    MS_START    = _T('^'),
    MS_END      = _T('$'),
};
```

## Features & Unit-Tests

All features of regXwild you can see with Unit-Tests - regXwildTest subproject.

```cpp
searchEss(datam, _T("^main*is ok$"));
searchEss(data, _T("^new*pro?ection"));
searchEss(data, _T("pro*system"));
searchEss(data, _T("sys###s"));
searchEss(data, _T("new+7+system"));
searchEss(data, _T("some project|open*and*star|system"));
...
```

## Speed comparison

*Release/Win32* - *(`algo` subproject as tester of main algorithms)*

**Please note:** **+icase** means that a search engine should ignore case sensitivity when matching the filter(pattern) within the searched string, i.e. `ignoreCase = true`. Without this, all below would be much more faster, and final algorithms EXT & ESS should be **< 1ms** !

Test Data:

* 340 Symbols of Unicode, 10000 iterations ( 340 x 10000 ), Filter: `L"nime**haru*02*Magica"`


                                          | +icase      
------------------------------------------|-------------
Find + Find                               | ~58ms       
Iterator + Find                           | ~57ms       
Getline + Find                            | ~59ms       
Iterator + Substr                         | ~165ms      
Iterator + Iterator                       | ~136ms      
main :: based on Iterator + Find          | ~53ms       
------------------------------------------|-------------
Final algorithm - EXT version:            | ~50ms       
Final algorithm - ESS version:            | ~50ms       
------------------------------------------|-------------
regexp-c++11(regex_search)                | ~64063ms    
regexp-c++11(only as ^match$ like a '==') | ~34ms       
regexp-c++11(regex_match with endings .*) | ~64329ms    


**ESS vs EXT**

Test Data: ( 350 x 10000 )

Operation (+icase)                   | EXT         | ESS
-------------------------------------|-------------|----------
ANY                                  | ~54ms       | ~55ms
ANYSP                                | ~60ms       | ~59ms
ONE                                  | ~56ms       | ~56ms
SPLIT                                | ~92ms       | ~94ms
BEGIN                                | ---         | ~38ms
END                                  | ---         | ~39ms
MORE                                 | ---         | ~44ms
SINGLE                               | ---         | ~43ms


### sandbox


```
[Intel Core2 Duo P8400 @ 2.26GHz]:


                                        |c icase          | без icase
----------------------------------------|-----------------|-----------------------
Iterator + Find                         | ~240ms (~222ms) | ~7ms
Getline + Find                          | ~296ms (~278ms) | ~63ms
Find + Find                             | ~250ms (~232ms) | ~17ms
Iterator + Substr                       | ~370ms (~352ms) | ~137ms
Iterator + Iterator                     | ~320ms (~302ms) | ~87ms
----------------------------------------|-----------------|-----------------------
regexp-c++11(regex_match! только ^str$) | ~970ms          | ~1163ms - среднее действ. выросло
regexp-c++11(regex_search)              | ~85279ms        | ~16426ms
regexp-c++11(regex_match c конечными .*)| ~91715ms        | ~19413ms - ограничение жадности для квантификатора дает сравнимые результаты
----------------------------------------------------------------------------------

Data:
300 символов юникода, 10000 строк, Фильтр L"nime**haru*02*mkv"


[Intel Core i7-3630QM @ 2.40GHz] - EXT vs ESS:

Operation (+icase)                   | EXT             | ESS
-------------------------------------|-----------------|--------------------
ANY                                  | ~119ms          | ~118ms
ANYSP                                | ~124ms          | ~121ms
ONE                                  | ~121ms          | ~120ms
SPLIT                                | ~188ms          | ~188ms
BEGIN                                |      ---        |  TODO
END                                  |      ---        |  TODO
MORE                                 |      ---        |  TODO
SINGLE                               |      ---        |  TODO
----------------------------------------------------------------------------
( 350 x 10000 )
```


## License

The [MIT License (MIT)](https://github.com/3F/regXwild/blob/master/LICENSE)

```
Copyright (c) 2013, 2014, 2016  Denis Kuzmin <entry.reg@gmail.com>
```

##

### How to Get

Available variants:

TODO:


[![Donate](https://www.paypalobjects.com/en_US/i/btn/btn_donate_SM.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_donations&business=entry%2ereg%40gmail%2ecom&lc=US&item_name=3F%2dOpenSource%20%5b%20github%2ecom%2f3F&currency_code=USD&bn=PP%2dDonationsBF%3abtn_donate_SM%2egif%3aNonHosted)
