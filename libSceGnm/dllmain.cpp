// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

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

namespace sce
{
	namespace Gnm
	{
		class Sampler
		{
		public:
			__declspec(dllexport) void init()
			{
				OutputDebugStringA(__FUNCTION__);
			}
		};

		class DataFormat
		{
		public:

			__declspec(dllexport) unsigned int getTexelsPerElement(void) const
			{
				OutputDebugStringA(__FUNCTION__);
				return 0;
			}

			__declspec(dllexport) bool isBlockCompressedFormat(void) const
			{
				OutputDebugStringA(__FUNCTION__);
				return false;
			}

			__declspec(dllexport) unsigned int getTotalBitsPerElement(void) const
			{
				OutputDebugStringA(__FUNCTION__);
				return 0;
			}
		};
	}
}