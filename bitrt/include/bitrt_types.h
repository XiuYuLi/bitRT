#ifndef __bitrt_types_h__
#define __bitrt_types_h__

#include <stdint.h>

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
    int z;
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
                    bitrtFloat3 oxyz;
                    float tmin;
                };
            };
            union
            {
                bitrtFloat4 d;
                struct{
                    bitrtFloat3 dxyz;
                    float tmax;
                };
            };
        };
        bitrtFloat8 v;
    };
} bitrtRay;

typedef struct alignas(16) bitrtHit_t
{
    uint32_t primID;
    float dt;
    float bu;
    float bv;
} bitrtHit;

typedef struct bitrtPayload_t
{
    bitrtRay ray;
    bitrtHit hit;
    int instanceID;
    int localPrimID;
    int entry;
    int depth;
} bitrtPayload;


typedef struct alignas(16) bitrtTriangleMesh_t
{
    uint64_t indexBufOffs;
    uint32_t vertCnt;
    uint32_t primCnt;
} bitrtTriangleMesh;

typedef struct bitrtMeshInstance_t
{
    uint64_t coordBufOffs;
    uint32_t indexOffs;
    uint32_t primOffs;
    bitrtBox aabb;
    uint32_t meshID;
} bitrtMeshInstance;

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
    bitrtUint3       * indexBuffer;
    bitrtFloat3      * coordBuffer;
    bitrtTriangleMesh* meshs;
    bitrtMeshInstance* instances;
    bitrtSphere_t    * spheres;
    bitrtBox aabb;
    uint32_t meshCnt;
    uint32_t instanceCnt;
    uint32_t sphereCnt;
    uint32_t faceFlags;
} bitrtSence;

typedef void (*bitrtShaderFunc)(bitrtPayload*);

#endif