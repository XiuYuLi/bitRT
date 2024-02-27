                                            BITRT Brief Introduction
    bitRT is an ultra-high performance ray tracing core library (currently only providing ray traversal acceleration structure and triangle mesh intersection function), 
    based on non BVH technology routes, with a lot of innovation at the algorithm level. The current version has been highly optimized for the AVX2 and AVX512 ISA, 
    and its performance in diffuse ray traversal & intersection is much higher than that the embree. We will also increase support for GPUs in the future. 
    The goal of bitRT is to achieve performance comparable to hardware ray tracing through algorithmic innovation and highly optimized software on general-purpose processors(CPU and the general computing unit of GPU)


bitrtInit():
    Initialize bitrt context and check hardware

bitrtResult bitrtCreateCore(bitrtCore* p_handle):
    Create bitrtCore handle and store result to *p_handle, should create one handle per thread

bitrtSize2 bitrtGetAccelBuildingSizes(const bitrtSence* p_sence):
    Get accel building sizes, the result.x is max size of accel building need and result.y is workspace size

bitrtResult bitrtBuildAccel(void* accel, void* temp, const bitrtSence* p_sence):
    Build accel, accel&temp is allocated with sizes form 'bitrtGetAccelBuildingSizes',
    Note: start address of accel must be aligned to 64 bytes and temp address of temp must be aligned to 16 bytes

size_t bitrtGetAccelInfo(const void* accel, bitrtAccelInfo info):
    Accel is builded by 'bitrtBuildAccel', it return actual size of accelerate struction when info is 'bitrt_accel_info_size'
    and you can use this size to allocate compressed accel space and the use 'bitrtCompressAccel'

bitrtResult bitrtCompressAccel(void* dst, const void* src):
    Compress src to dst, dst size is get through 'bitrtGetAccelInfo' with bitrt_accel_info_size'

int bitrtTrace(bitrtHit* p_hit, bitrtCore core, const bitrtSence* p_sence, const void* accel, const bitrtRay* p_ray, int entry_node_index):
    Traverse&intersect, 'p_hit' store the intersect result; 'entry_node_index' is the start node index of ray traverse(first is 0);
    This func return a 'int' result is the 'hit node index' and can be as the entry node index of next trace or 'bitrtOccluded'

bool bitrtOccluded(bitrtCore core, const bitrtSence* p_sence, const void* accel, const bitrtRay* p_ray, int entry_node_index):
    If return 'true' means is occluded, used to shadow ray test and occlusion test

bitrtResult bitrtDestroyCore(bitrtCore handle):
    Release resource of handle

