// This code was generated by a vsSolutionBuildEvent.
// Changes to this file may cause incorrect behavior and will be lost if the code is regenerated.

#pragma once
#ifndef _RXW_VERSION_
#define _RXW_VERSION_

#include "stdafx.h"

namespace net { namespace r_eg { namespace regXwild
{
    struct RXWVersion
    {
        struct TNum
        {
            const int major;
            const int minor;
            const int patch;
            const int build;

            TNum() : major(1), minor(3), patch(0), build(0) { }

        } number;

        const rxwtypes::TCHAR* bSha1;
        const rxwtypes::TCHAR* config;
        const rxwtypes::TCHAR* product;

        RXWVersion() : bSha1(_T("")), config(_T("")), product(_T("1.3.0")) { }
    };
}}}

#endif // _RXW_VERSION_
