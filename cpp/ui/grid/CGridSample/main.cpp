#include "stdafx.h"
#include "resource.h"

#include "Sample.h"

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR /*lpstrCmdLine*/, int /*nCmdShow*/)
{
    CAppModule _Module;
    HRESULT hRes = ::CoInitialize(NULL);
    ATLASSERT(SUCCEEDED(hRes));

    AtlInitCommonControls(ICC_WIN95_CLASSES);

    hRes = _Module.Init(NULL, hInstance);
    ATLASSERT(SUCCEEDED(hRes));

    Sample sample;
    int nRet = sample.DoModal();

    _Module.Term();
    ::CoUninitialize();

    return nRet;
}