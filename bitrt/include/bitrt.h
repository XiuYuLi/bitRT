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

#include "bitrt_types.h"

typedef struct __bitrtCore *bitrtCore;

bitrtResult BITRTAPI bitrtInit();
bitrtResult BITRTAPI bitrtCreateCore(bitrtCore*);
bitrtResult BITRTAPI bitrtCheckExternalAccel(const bitrtExternalAccel*);
bitrtSize3  BITRTAPI bitrtGetExternalAccelBuildingSizes(const bitrtExternalAccel*, const bitrtSence*);
bitrtResult BITRTAPI bitrtBuildExternalAccel(void*, void*, size_t, const bitrtExternalAccel*, const bitrtSence*);
bitrtResult BITRTAPI bitrtBuildAccel(void*, void*, size_t, const bitrtSence*);
bitrtResult BITRTAPI bitrtTrace(bitrtCore, const void*, bitrtPayload*, float);
bool        BITRTAPI bitrtOccluded(bitrtCore, const void*, const bitrtPayload*, const bitrtFloat4*, int, float);
bitrtResult BITRTAPI bitrtDestroyCore(bitrtCore);

#ifdef __cplusplus
}
#endif
#endif