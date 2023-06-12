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

#include <bitrt_types.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct __bitrtCore *bitrtCore;

typedef enum bitrtResult_t
{
    bitrtSuccess             = 0,
    bitrtErrorInvalidDevice  = 1,
    bitrtErrorInvalidValue   = 2,
    bitrtErrorInvalidAccel   = 3,
    bitrtErrorInvalidCore    = 4,
    bitrtErrorMemAllocFailed = 5,
    bitrtErrorOutOfMaxSize   = 6
} bitrtResult;

bitrtResult BITRTAPI bitrtInit();
bitrtResult BITRTAPI bitrtCreateCore(bitrtCore*);
bitrtSize2  BITRTAPI bitrtGetAccelLeaderSizes(const bitrtSence*);
bitrtSize2  BITRTAPI bitrtGetAccelSizes(const void*);
bitrtResult BITRTAPI bitrtBuildAccelLeader(void*, void*, const bitrtSence*);
bitrtResult BITRTAPI bitrtBuildAccel(void*, void*, const void*, const bitrtSence*);
size_t      BITRTAPI bitrtGetAccelActualSize(const void*);
bitrtResult BITRTAPI bitrtTrace(bitrtCore, const void*, bitrtPayload*);
bool        BITRTAPI bitrtOccluded(bitrtCore, const void*, const bitrtPayload*, const bitrtFloat4*, int);
bitrtResult BITRTAPI bitrtDestroyCore(bitrtCore);

#ifdef __cplusplus
}
#endif
#endif