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
		enum GpuMode {};
		enum TileMode {};
		enum ArrayMode {};
		class DataFormat {};
	}

	namespace GpuAddress
	{
		class TilingParameters {};
		class SurfaceInfo {};
		struct SurfaceRegion {};
		enum SurfaceType {};

		__declspec(dllexport) int computeSurfaceInfo(SurfaceInfo* info, TilingParameters const* params)
		{
			OutputDebugStringA(__FUNCTION__);
			return 0;
		}

		__declspec(dllexport) int tileSurfaceRegion(void* ptr0, void const* ptr1, TilingParameters const* params, SurfaceRegion const* surf, unsigned int, unsigned int)
		{
			OutputDebugStringA(__FUNCTION__);
			return 0;
		}

		__declspec(dllexport) int computeTiledSurfaceSize(unsigned __int64* ptr0, unsigned int* ptr1, TilingParameters const* params)
		{
			OutputDebugStringA(__FUNCTION__);
			return 0;
		}

		__declspec(dllexport) int adjustTileMode(Gnm::GpuMode, Gnm::TileMode*, Gnm::TileMode, Gnm::ArrayMode)
		{
			OutputDebugStringA(__FUNCTION__);
			return 0;
		}

		__declspec(dllexport) int computeSurfaceTileMode(Gnm::GpuMode, Gnm::TileMode* __ptr64, SurfaceType, Gnm::DataFormat, unsigned int)
		{
			OutputDebugStringA(__FUNCTION__);
			return 0;
		}
	}
}