// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

extern "C"
{
    _declspec(dllexport) void XGCreateTexture2DComputer()
    {
        OutputDebugStringA(__FUNCTION__);
    }

    _declspec(dllexport) void XGComputeOptimalTileMode()
    {
        OutputDebugStringA(__FUNCTION__);
    }

    _declspec(dllexport) void XGCreateTexture1DComputer()
    {
        OutputDebugStringA(__FUNCTION__);
    }

    _declspec(dllexport) void XGCreateTexture3DComputer()
    {
        OutputDebugStringA(__FUNCTION__);
    }
}
