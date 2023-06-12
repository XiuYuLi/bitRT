#ifndef __bitrt_types_h__
#define __bitrt_types_h__

#include <stdint.h>

typedef struct alignas(2) bitrtSbyte2_t
{
    int8_t x;
    int8_t y;
} bitrtSbyte2;

typedef struct alignas(2) bitrtByte2_t
{
    uint8_t x;
    uint8_t y;
} bitrtByte2;

typedef struct alignas(4) bitrtSbyte4_t
{
    int8_t x;
    int8_t y;
    int8_t z;
    int8_t w;
} bitrtSbyte4;

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
    int x;
    int y;
} bitrtInt2;

typedef struct rtInt3_t
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
    int32_t s0;
    int32_t s1;
    int32_t s2;
    int32_t s3;
    int32_t s4;
    int32_t s5;
    int32_t s6;
    int32_t s7;
} bitrtInt8;

typedef struct alignas(16) bitrtSize2_t
{
    size_t x;
    size_t y;
} bitrtSize2;

typedef struct alignas(8) bitrtBox_t
{
    bitrtFloat3 bmin;
    bitrtFloat3 bmax;
} bitrtBox;

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
    int32_t  geoID;
    int32_t  localPrimID;
    int32_t  entry;
    int32_t  depth;
} bitrtPayload;

typedef struct alignas(8) bitrtMesh_t
{
    size_t   coordBufOffs;
    size_t   indexBufOffs;
    uint32_t vertCnt;
    uint32_t primCnt;
    bitrtBox aabb;
} bitrtMesh;

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

typedef struct bitrtSence_t
{
    bitrtMesh   *meshs;
    void        *indexBuffer;
    bitrtFloat3 *coordBuffer;
    bitrtBox aabb;
    uint32_t meshCnt;
    uint32_t vertCnt;
    uint32_t primCnt;
    uint32_t faceFlags;
} bitrtSence;

#endif