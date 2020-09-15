#pragma once

#ifdef UNICODE
#define CONVERT(value) std::to_wstring(value)
#else
#define CONVERT(value) std::to_string(value)
#endif

#ifdef _DEBUG 
#include <Windows.h>
#define ErrorMsg(handle, msg) if (FAILED(handle)) \
	{ \
		MessageBox( \
		nullptr, \
		TEXT(msg), \
		TEXT("Error"), \
		MB_OK | MB_ICONERROR \
		); \
		return false; \
	}
#else // _DEBUG
#define ErrorMsg(handle, msg)
#endif // _DEBUG

// COM - Component Object Model
template<typename T> ULONG safeRelease(T* &obj)
{
	ULONG refCount = 0;
	if (obj != nullptr)
	{
		refCount = obj->Release();
		obj = nullptr;
	}
	return refCount;
}

template<typename T> void safeDeInit(T* &obj)
{
	if (obj != nullptr)
	{
		obj->deInit();
		delete obj;
		obj = nullptr;
	}
}