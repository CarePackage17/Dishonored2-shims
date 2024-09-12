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
	namespace Shader
	{
		namespace Wave
		{
			namespace Psslc 
			{
				struct Output {};
				struct Options {};

				__declspec(dllexport) unsigned int destroyOutput(Output const * ptr)
				{
					OutputDebugStringA(__FUNCTION__);
					return 0;
				}

				__declspec(dllexport) unsigned int initializeOptions(Options* ptr, unsigned int unknown)
				{
					OutputDebugStringA(__FUNCTION__);
					return 0;
				}
			}
		}
	}
}
