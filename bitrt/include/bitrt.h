#ifndef __bitrt_h__
#define __bitrt_h__

#if defined(_WIN64)||defined(_M_X64)||defined(_M_AMD64)||defined(__x86_64)||defined(__LP64__)
#if defined(_MSC_VER)
#if defined(_WINDLL)
#define BITRTAPI __declspec(dllexport)
#else
#define BITRTAPI __declspec(dllimport)
#endif
#elif defined(__GNUC__)&&defined(__linux__)
#if __GNUC__>=4
#define BITRTAPI __attribute__((visibility("default")))
#else
#define BITRTAPI
#endif
#else
#error "Invalid Platform!"
#endif
#else
#error "Only Support 64b-OS!"
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#include <bitrt_types.h>

typedef struct __bitrtCore *bitrtCore;

bitrtResult BITRTAPI bitrtInit();
bitrtResult BITRTAPI bitrtCreateCore(bitrtCore*);
bitrtSize2  BITRTAPI bitrtGetAccelBuildingSizes(const bitrtSence*);
bitrtResult BITRTAPI bitrtBuildAccel(void*, void*, const bitrtSence*);
int         BITRTAPI bitrtTrace(bitrtHit*, bitrtCore, const void*, const bitrtRay*, int);
bool        BITRTAPI bitrtOccluded(bitrtCore, const void*, const bitrtRay*, int);
bitrtResult BITRTAPI bitrtDestroyCore(bitrtCore);

#ifdef __cplusplus
}
#endif
#endif