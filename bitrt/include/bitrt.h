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

#include <bitrt/bitrt_types.h>

typedef struct __bitrtCore  *bitrtCore;
typedef struct __bitrtAccel *bitrtAccel;

typedef enum bitrtResult_t
{
    bitrtSuccess             = 0,
    bitrtErrorInvalidDevice  = 1,
    bitrtErrorInvalidValue   = 2,
    bitrtErrorInvalidAccel   = 3,
    bitrtErrorInvalidCore    = 4,
    bitrtErrorMemAllocFailed = 5
} bitrtResult;

bitrtResult BITRTAPI bitrtInit();
bitrtResult BITRTAPI bitrtCreateCore(bitrtCore*);
bitrtResult BITRTAPI bitrtCreateAccel(bitrtAccel*);
size_t      BITRTAPI bitrtGetAccelLeaderBuildingSize(uint32_t);
size_t      BITRTAPI bitrtGetAccelLeaderSize(uint32_t);
size_t      BITRTAPI bitrtBuildAccelLeader(bitrtAccel, void*, void*, const bitrtSence*);
size_t      BITRTAPI bitrtBuildAccel(bitrtAccel, void*, size_t, const void*, const bitrtSence*);
size_t      BITRTAPI bitrtGetAccelSize(bitrtAccel);
bitrtResult BITRTAPI bitrtTrace(bitrtCore, bitrtAccel, bitrtPayload*);
bool        BITRTAPI bitrtOccluded(bitrtCore, bitrtAccel, const bitrtPayload*, const bitrtFloat4*, int);
bitrtResult BITRTAPI bitrtDestroyAccel(bitrtAccel);
bitrtResult BITRTAPI bitrtDestroyCore(bitrtCore);

#ifdef __cplusplus
}
#endif
#endif