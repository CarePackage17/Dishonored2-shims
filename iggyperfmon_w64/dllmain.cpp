// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
//#include <stdio.h>
#include <cstdint>
//#include <cstdlib>

BOOL APIENTRY _DllMainCRTStartup(HMODULE hModule,
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

//the 2 args are wacky, maybe it's because they're class members? idk, but the call itself doesn't
//require a value to work, so passing null is fine here.
typedef void* (__cdecl* pFnMallocD2)(void* unused, uint32_t bytes);
typedef void (__cdecl* pFnFreeD2)(void* unused, void* mem);

extern "C"
{
	_declspec(dllexport) void* IggyPerfmonCreate(pFnMallocD2 mallocFn, pFnFreeD2 freeFn, size_t bytes)
	{
		//char buf[512]{};
		void* mallocResult = mallocFn(nullptr, 65536);
		void* block2 = mallocFn(nullptr, 16);
		void* block3 = mallocFn(nullptr, 32768);

		//TODO:
		//alright, it's not just the allocs. This function very likely returns a struct with a bunch of function
		//pointers, one of them is later called where we currently crash. Unfrotunately, static analysis is bit
		//hard here, so we'll need to debug a bunch (which rn seems marginally easier).

		/*sprintf_s(buf, "%s: malloc address: %p, free address: %p, bytes: %zu, mallocResult: %p\n", 
			__FUNCTION__, malloc, free, bytes, mallocResult);*/
		//OutputDebugStringA(buf);
		//free(nullptr, mallocResult);

		OutputDebugStringA(__FUNCTION__);

		return mallocResult;
	}

	_declspec(dllexport) void IggyPerfmonDestroy(int64_t num0, int64_t num1)
	{
		OutputDebugStringA(__FUNCTION__);

		//this will probably need to call free I guess, but we're not even getting that far rn
	}

	_declspec(dllexport) void IggyPerfmonTickAndDraw(void* ptr0, void* ptr1, void* ptr2, int32_t num0, int num1, int num2, int num3)
	{
		//char buf[512]{};
		//sprintf_s(buf, "%s: %p %p %p %i %i %i %i", __FUNCTION__, ptr0, ptr1, ptr2, num0, num1, num2, num3);

		//OutputDebugStringA(buf);
		OutputDebugStringA(__FUNCTION__);
	}
}
