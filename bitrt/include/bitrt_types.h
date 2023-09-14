#ifndef __bitrt_types_h__
#define __bitrt_types_h__

#include <stdint.h>

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

typedef struct alignas(2) bitrtChar2_t
{
    int8_t x;
    int8_t y;
} bitrtChar2;

typedef struct alignas(2) bitrtByte2_t
{
    uint8_t x;
    uint8_t y;
} bitrtByte2;

typedef struct alignas(4) bitrtChar4_t
{
    int8_t x;
    int8_t y;
    int8_t z;
    int8_t w;
} bitrtChar4;

typedef struct alignas(4) bitrtByte4_t
{
    uint8_t x;
    uint8_t y;
    uint8_t z;
    uint8_t w;
} bitrtByte4;

typedef struct alignas(4) bitrtShort2_t
{
    int16_t x;
    int16_t y;
} bitrtShort2;

typedef struct alignas(4) bitrtUshort2_t
{
    uint16_t x;
    uint16_t y;
} bitrtUshort2;

typedef struct bitrtShort3_t
{
    int16_t x;
    int16_t y;
    int16_t z;
} bitrtShort3;

typedef struct bitrtUshort3_t
{
    uint16_t x;
    uint16_t y;
    uint16_t z;
} bitrtUshort3;

typedef struct alignas(8) bitrtShort4_t
{
    int16_t x;
    int16_t y;
    int16_t z;
    int16_t w;
} bitrtShort4;

typedef struct alignas(8) bitrtUshort4_t
{
    uint16_t x;
    uint16_t y;
    uint16_t z;
    uint16_t w;
} bitrtUshort4;

typedef struct alignas(8) bitrtUint2_t
{
    uint32_t x;
    uint32_t y;
} bitrtUint2;

typedef struct bitrtUint3_t
{
    uint32_t x;
    uint32_t y;
    uint32_t z;
} bitrtUint3;

typedef struct alignas(16) bitrtUint4_t
{
    uint32_t x;
    uint32_t y;
    uint32_t z;
    uint32_t w;
} bitrtUint4;

typedef struct alignas(32) bitrtUint8_t
{
    uint32_t s0;
    uint32_t s1;
    uint32_t s2;
    uint32_t s3;
    uint32_t s4;
    uint32_t s5;
    uint32_t s6;
    uint32_t s7;
} bitrtUint8;

typedef struct alignas(8) bitrtInt2_t
{
    int32_t x;
    int32_t y;
} bitrtInt2;

typedef struct bitrtInt3_t
{
    int x;
    int y;
    int z;
} bitrtInt3;

typedef struct alignas(16) bitrtInt4_t
{
    int x;
    int y;
    int z;
    int w;
} bitrtInt4;

typedef struct alignas(32) bitrtInt8_t
{
    int s0;
    int s1;
    int s2;
    int s3;
    int s4;
    int s5;
    int s6;
    int s7;
} bitrtInt8;

typedef struct alignas(16) bitrtSize2_t
{
    size_t x;
    size_t y;
} bitrtSize2;

typedef struct alignas(8) bitrtSize3_t
{
    size_t x;
    size_t y;
    size_t z;
} bitrtSize3;

typedef struct alignas(8) bitrtFloat2_t
{
    float x;
    float y;
} bitrtFloat2;

typedef struct bitrtFloat3_t
{
    float x;
    float y;
    float z;
} bitrtFloat3;

typedef struct alignas(16) bitrtFloat4_t
{
    float x;
    float y;
    float z;
    float w;
} bitrtFloat4;

typedef struct alignas(32) bitrtFloat8_t
{
    float s0;
    float s1;
    float s2;
    float s3;
    float s4;
    float s5;
    float s6;
    float s7;
} bitrtFloat8;

typedef struct alignas(16) bitrtExternalAccel_t
{
    uint64_t* root;
    uint32_t* leafPrimlistPtr;
    uint32_t* leafPrimlist;
    uint32_t  nodeCnt;
    uint32_t  depth;
} bitrtExternalAccel;

typedef struct alignas(32) bitrtRay_t
{
    union
    {
        struct
        {
            union
            {
                bitrtFloat4 o;
                struct{
                    bitrtFloat3 o3;
                    float tmin;
                };
            };
            union
            {
                bitrtFloat4 d;
                struct{
                    bitrtFloat3 d3;
                    float tmax;
                };
            };
        };
        bitrtFloat8 v;
    };
} bitrtRay;

typedef struct alignas(16) bitrtHit_t
{
    union
    {
        struct
        {
            float    dt;
            uint32_t primID;
            float    bu;
            float    bv;
        };
        bitrtFloat4 v;
    };
} bitrtHit;

typedef struct bitrtPayload_t
{
    bitrtRay ray;
    bitrtHit hit;
    int entry;
} bitrtPayload;

typedef struct alignas(16) bitrtSphere_t
{
    union
    {
        bitrtFloat4 v;
        struct{
            bitrtFloat3 centre;
            float radius;
        };
    };
} bitrtSphere;

typedef struct alignas(16) bitrtSence_t
{
    bitrtFloat4  bmin;
    bitrtFloat4  bmax;
    void       * indexBuffer;
    bitrtFloat3* coordBuffer;
    uint64_t     cullMask;
    uint32_t     vertCnt;
    uint32_t     primCnt;
} bitrtSence;

#endif