// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include <cstdint>

BOOL APIENTRY DllMain(HMODULE hModule,
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
	_declspec(dllexport) UINT64 IggyPerfmonCreate(void* pfnMalloc, void* pfnFree, void* ugh)
	{
		char buf[512]{};
		sprintf_s(buf, "%s: malloc address: %p, free address: %p, last param: %p", __FUNCTION__, pfnMalloc, pfnFree, ugh);

		OutputDebugStringA(buf);
		return 1;
	}

	_declspec(dllexport) void IggyPerfmonDestroy()
	{
		OutputDebugStringA(__FUNCTION__);
	}

	_declspec(dllexport) void IggyPerfmonTickAndDraw(void* ptr0, void* ptr1, void* ptr2, int32_t num0)
	{
		char buf[512]{};
		sprintf_s(buf, "%s: %p %p %p %i", __FUNCTION__, ptr0, ptr1, ptr2, num0);

		OutputDebugStringA(buf);
	}
}
