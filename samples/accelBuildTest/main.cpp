#include "bitrt.h"
#include "meshReader.h"
#pragma comment(lib, "bitrt.lib")

static void get_global_bbox(bitrtSence* sence)
{
    bitrtUint3 v=sence->indexBuffer[0];
    bitrtFloat3 p0=sence->coordBuffer[v.x];
    bitrtFloat3 p1=sence->coordBuffer[v.y];
    bitrtFloat3 p2=sence->coordBuffer[v.z];
    bitrtFloat4& bmin=sence->meshBounds[0];
    bitrtFloat4& bmax=sence->meshBounds[1];
    bmin.x=fminf(fminf(p0.x, p1.x), p2.x);
    bmin.y=fminf(fminf(p0.y, p1.y), p2.y);
    bmin.z=fminf(fminf(p0.z, p1.z), p2.z);
    bmax.x=fmaxf(fmaxf(p0.x, p1.x), p2.x);
    bmax.y=fmaxf(fmaxf(p0.y, p1.y), p2.y);
    bmax.z=fmaxf(fmaxf(p0.z, p1.z), p2.z);
    for(uint32_t i=1; i<sence->primCnt; ++i)
    {
        v=sence->indexBuffer[i];
        p0=sence->coordBuffer[v.x];
        p1=sence->coordBuffer[v.y];
        p2=sence->coordBuffer[v.z];
        bmin.x=fminf(fminf(fminf(p0.x, p1.x), p2.x), bmin.x);
        bmin.y=fminf(fminf(fminf(p0.y, p1.y), p2.y), bmin.y);
        bmin.z=fminf(fminf(fminf(p0.z, p1.z), p2.z), bmin.z);
        bmax.x=fmaxf(fmaxf(fmaxf(p0.x, p1.x), p2.x), bmax.x);
        bmax.y=fmaxf(fmaxf(fmaxf(p0.y, p1.y), p2.y), bmax.y);
        bmax.z=fmaxf(fmaxf(fmaxf(p0.z, p1.z), p2.z), bmax.z);
    }
}

int main(int argc, char** argv)
{
    const char* model_name="dog.ob";
    size_t size=get_meshfile_size(model_name);
    printf("MeshFile size = %llu\n", size);
    char* buf=new char[size+1];
    if(buf==nullptr){
        printf("File buffer alloc failed!\n");
        return 0;
    }
    buf[size]='\0';
    const bitrtUint2 counter=load_mesh(buf, size, model_name);
    const uint32_t& n_verts=counter.x;
    const uint32_t& n_prims=counter.y;
    printf("vertCnt = %u\nprimCnt = %u\n", n_verts, n_prims);

    bitrtSence sence;
    sence.vertCnt=n_verts;
    sence.primCnt=n_prims;
    sence.meshCnt=1;
    sence.coordBuffer=new bitrtFloat3[n_verts];
    sence.indexBuffer=new bitrtUint3[n_prims];
    sence.meshBounds=new bitrtFloat4[2];
    parse_mesh(sence.coordBuffer, sence.indexBuffer, buf, size);
    delete[] buf;
    get_global_bbox(&sence);

    if(bitrtInit()!=bitrtSuccess){
        printf("Error : initializing failed!\n");
        goto __free_pt0;
    }

    {
        bitrtSize2 sizes=bitrtGetAccelBuildingSizes(&sence);
        printf("Accel Size = %llu\nBuilding Space Size = %llu\n", sizes.x, sizes.y);
        char* accel_buf=(char*)_aligned_malloc(sizes.x, 64);
        char* build_buf=(char*)_aligned_malloc(sizes.y, 16);
        if(bitrtBuildAccel(accel_buf, build_buf, &sence)!=bitrtSuccess){
            printf("Error : build failed!\n");
            goto __free_pt1;
        }
        {
            size_t accel_size=bitrtGetAccelInfo(accel_buf, bitrt_accel_info_size);
            uint32_t node_cnt=(uint32_t)bitrtGetAccelInfo(accel_buf, bitrt_accel_info_node_count);
            uint32_t depth=(uint32_t)bitrtGetAccelInfo(accel_buf, bitrt_accel_info_depth);
            printf("  Accel Size = %f(M)\n", ((double)accel_size)/(1024*1024));
            printf("  Node Count = %u\n", node_cnt);
            printf("  Accel Depth = %u\n", depth);
        }
    __free_pt1:
        _aligned_free(accel_buf);
        _aligned_free(build_buf);
    }
__free_pt0:
    delete[] sence.coordBuffer;
    delete[] sence.indexBuffer;
    delete[] sence.meshBounds;
    return 0;  
}