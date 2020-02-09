
# [regXwild](https://github.com/3F/regXwild) 

Small and super Fast advanced wildcards! `*`,`|`,`?`,`^`,`$`,`+`,`#`,`>` in addition to slow regex engine and more.

Unique algorithms that was implemented on native unmanaged C++ but easily accessible also in .NET through **[Conari](https://github.com/3F/Conari)** (recommended due to caching of 0x29 opcodes and other related optimization).

[![Build status](https://ci.appveyor.com/api/projects/status/8knio1ggle0o8ugh/branch/master?svg=true)](https://ci.appveyor.com/project/3Fs/regxwild-github/branch/master)
[![release](https://img.shields.io/github/release/3F/regXwild.svg)](https://github.com/3F/regXwild/releases/latest)
[![License](https://img.shields.io/badge/License-MIT-74A5C2.svg)](https://github.com/3F/regXwild/blob/master/LICENSE)
[![NuGet package](https://img.shields.io/nuget/v/regXwild.svg)](https://www.nuget.org/packages/regXwild/)
[![Tests](https://img.shields.io/appveyor/tests/3Fs/regxwild-github/master.svg)](https://ci.appveyor.com/project/3Fs/regxwild-github/build/tests)

[![Build history](https://buildstats.info/appveyor/chart/3Fs/regxwild-github?buildCount=20&includeBuildsFromPullRequest=true&showStats=true)](https://ci.appveyor.com/project/3Fs/regxwild-github/history)


```cpp
= searchEssC(L"number = '1271';", L"number = '????';", true);
```
```cpp
= searchEss(data, _T("^main*is ok$"));
= searchEss(data, _T("^new*pro?ection"));
= searchEss(data, _T("pro*system"));
= searchEss(data, _T("sys###s"));
= searchEss(data, _T("new+7+system"));
= searchEss(data, _T("some project$|open*and*star|^system"));
```

## Why regXwild ?

It was designed to be faster than just fast, when using more features that usually go beyond the typical wildcards.

🔍 Easy to start:

Unmanaged native C++ or managed .NET project. It doesn't matter, just use it:

C++
```cpp
#include "regXwildAPI.h"
using namespace net::r_eg::regXwild;
...
if(searchEssC(_T("regXwild"), _T("reg?wild"), true)) {
    // ...
}
```

C# if you're using [ [Conari](https://github.com/3F/Conari) ]
```csharp
using(var l = new ConariL("regXwild.dll")) 
{
    if(l.DLR.searchEssC<bool>("regXwild", "reg?wild", true)) {
        // ...
    }
}
```

🏄 Amazing meta symbols:

ESS version (advanced EXT version)

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
    MS_ANYSP    = _T('>'), // as [^/]*
};
```

EXT version (more simplified than ESS)

```cpp
enum MetaSymbols 
{
    MS_ANY      = _T('*'),
    MS_ANYSP    = _T('>'), //as [^/\\]+
    MS_SPLIT    = _T('|'),
    MS_ONE      = _T('?'),
};
```

Check it with our actual **Unit-Tests**.

🚀 Awesome speed: 

* [~2000 times faster when C++](#speed).
* For .NET (including modern .NET Core), [Conari](https://github.com/3F/Conari) provides optional caching of 0x29 opcodes (Calli) and more to get a similar result as possible.

🍰 Open and Free:

Open Source project; MIT License, Enjoy 🎉

## License

The [MIT License (MIT)](https://github.com/3F/regXwild/blob/master/LICENSE)

```
Copyright (c) 2013-2014, 2016-2017, 2020  Denis Kuzmin < x-3F@outlook.com > GitHub/3F
```

[ [ ☕ Donate ](https://3F.github.com/Donation/) ]

regXwild contributors: https://github.com/3F/regXwild/graphs/contributors

We're waiting for your awesome contributions!

## Speed

Please note:

* **+icase** means ignore case sensitivity when matching the filter(pattern) within the searched string, i.e. `ignoreCase = true`. **Without** this, everything **will be much faster** of course. *That is, icase always adds complexity.*
* Commonly **MultiByte** will be faster than **Unicode** (for the same platform and the same way of module use) but it depends on specific architecture and can be about ~2 times faster when native C++, and about ~4 times faster when .NET + Conari and related.
* The results below can be different on different machines. You need only look at the difference (in milliseconds) between algorithms for a specific target.
* To calculate the data, as in the table below, you need execute `algo.exe`

### Procedure of testing

* Used the `algo` subproject as tester of the main algorithms (***Release*** *cfg - x32 & x64*)
* In general, calculation is simple and uses average as `i = (t2 - t1); (sum(i) / n)` where:
    * **i** - one iteration for searching by filter. Represents the delta of time `t2 - t1`
    * **n** - the number of repeats of the matching to get average.

e.g.:

```cpp
{
    Meter meter;
    int results = 0;

    for(int total = 0; total < average; ++total)
    {
        meter.start();
        for(int i = 0; i < iterations; ++i)
        {
            if((alg.*method)(data, filter)) {
                //...
            }
        }
        results += meter.delta();
    }

    TRACE((results / average) << "ms");
}
```

for regex results it also prepares additional `basic_regex` from filter, but of course, **only one for all iterations**:

```cpp
meter.start();

auto rfilter = tregex(
    filter,
    regex_constants::icase | regex_constants::optimize
);

results += meter.delta();
...
```

### Sample of speed for Unicode

340 Unicode Symbols and 10^4 iterations (340 x 10000); Filter: `L"nime**haru*02*Magica"`


 algorithms (see impl. from `algo`)       | +icase [x32]| +icase [x64]
------------------------------------------|-------------|-------------
Find + Find                               | ~58ms       | ~44ms       
Iterator + Find                           | ~57ms       | ~46ms       
Getline + Find                            | ~59ms       | ~54ms       
Iterator + Substr                         | ~165ms      | ~132ms      
Iterator + Iterator                       | ~136ms      | ~118ms      
main :: based on Iterator + Find          | ~53ms       | ~45ms       
​ ​                                         | ​            | 
**Final algorithm - EXT version:**        | **~50ms**   | **~26ms**   
**Final algorithm - ESS version:**        | **~50ms**   | **~27ms**   
​ ​                                         | ​            | 
regexp-c++11(regex_search)                | ~59309ms    | ~53334ms    
regexp-c++11(only as ^match$ like a '==') | ~12ms       | ~5ms        
regexp-c++11(regex_match with endings .*) | ~59503ms    | ~53817ms    


**ESS vs EXT**

350 Unicode Symbols and 10^4 iterations (350 x 10000);

Operation (+icase)    | EXT  [x32] | ESS  [x32] | EXT  [x64] | ESS  [x64] 
----------------------|------------|------------|------------|------------
ANY                   | ~54ms      | ~55ms      | ~32ms      | ~34ms
ANYSP                 | ~60ms      | ~59ms      | ~37ms      | ~38ms
ONE                   | ~56ms      | ~56ms      | ~33ms      | ~35ms
SPLIT                 | ~92ms      | ~94ms      | ~58ms      | ~63ms
BEGIN                 | ---        | ~38ms      | ---        | ~19ms
END                   | ---        | ~39ms      | ---        | ~21ms
MORE                  | ---        | ~44ms      | ---        | ~23ms
SINGLE                | ---        | ~43ms      | ---        | ~22ms


**For .NET users through [Conari](https://github.com/3F/Conari) engine:** 

*Same test Data & Filter: 10^4 iterations* 

*Release cfg; x32 or x64 regXwild (Unicode)*

**Attention:** For more speed you need upgrading to [Conari **1.3**](https://github.com/3F/Conari/commit/4f14cecbcea75895a510954c2cd402ee0e9e3521) or higher !

 algorithms  (see impl. from `snet`)        | +icase [x32] | +icase [x64] | ​  
--------------------------------------------|--------------|--------------|---
regXwild via Conari v1.2 (Lambda) - ESS     | ~1032ms      | ~1418ms      | x
regXwild via Conari v1.2 (DLR) - ESS        | ~1238ms      | ~1609ms      | x
regXwild via Conari v1.2 (Lambda) - EXT     | ~1117ms      | ~1457ms      | x
regXwild via Conari v1.2 (DLR) - EXT        | ~1246ms      | ~1601ms      | x
​ ​                                           | ​             |  ​            |
regXwild via Conari **v1.3** (Lambda) - ESS | **~58ms**    | **~42ms**    | `<<`
regXwild via Conari **v1.3** (DLR) - ESS    | ~218ms       | ~234ms       |
regXwild via Conari **v1.3** (Lambda) - EXT | **~54ms**    | **~35ms**    | `<<`
regXwild via Conari **v1.3** (DLR) - EXT    | ~214ms       | ~226ms       |
​ ​                                           | ​             |  ​            |
.NET Regex engine [Compiled]                | ~38310ms     | ~37242ms     |
.NET Regex engine [Compiled]{only ^match$}  | < 1ms        | ~3ms         |
.NET Regex engine                           | ~31565ms     | ~30975ms     |
.NET Regex engine {only ^match$}            | < 1ms        | ~1ms         |


### How to get regXwild

regXwild v1.1+ can also be installed through **NuGet** same for both unmanaged and managed projects.

For .NET it will put x32 & x64 regXwild into $(TargetDir). Use it with your .net modules through [Conari](https://github.com/3F/Conari) and so on.

x64 + x32 Unicode + MultiByte modules;

Please note: Modern regXwild packages will no longer be distributed together with [Conari](https://github.com/3F/Conari). Please consider to use it separately, [Conari nuget packages](https://www.nuget.org/packages/Conari/).

* regXwild NuGet: [![NuGet package](https://img.shields.io/nuget/v/regXwild.svg)](https://www.nuget.org/packages/regXwild/)
* [GetNuTool](https://github.com/3F/GetNuTool): `msbuild gnt.core /p:ngpackages="regXwild"` or **[gnt](https://3f.github.io/GetNuTool/releases/latest/gnt/)** /p:ngpackages="regXwild"
* [GitHub Releases](https://github.com/3F/regXwild/releases) [ [latest](https://github.com/3F/regXwild/releases/latest) ]
* 🎲 CI builds: [`CI /artifacts`](https://ci.appveyor.com/project/3Fs/regxwild-github/history) ( [old CI](https://ci.appveyor.com/project/3Fs/regxwild/history) )