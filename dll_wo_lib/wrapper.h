#ifndef _H_W_
#define _H_W_

#ifdef _EXPORT_
#define DLL_PREFIX dllexport
#else
#define DLL_PREFIX dllimport
#endif

#include <stdio.h>

extern "C" __declspec(DLL_PREFIX) void extern_func();

#endif