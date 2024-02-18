#ifndef __meshReader_h__
#define __meshReader_h__

#include <cstdio>
#include <cstdlib>
#include <cstdint>

#pragma warning(disable:4996)

__forceinline float as_f32(uint32_t u32)
{
    return *reinterpret_cast<float*>(&u32);
}
__forceinline uint32_t as_u32(float f32)
{
    return *reinterpret_cast<uint32_t*>(&f32);
}
static size_t get_meshfile_size(const char* filename)
{
    FILE* fp=fopen(filename, "rb");
    if(fp==nullptr) return 0;
    fseek(fp, 0, SEEK_END);
    size_t size=ftell(fp);
    fclose(fp);
    return size;
}
static bitrtUint2 load_mesh(char* buf, size_t size, const char* filename)
{
    FILE* fp=fopen(filename, "rb");
    if(fp==nullptr) return {0, 0};
    uint32_t n_verts=0, n_prims=0;
    fread(buf, 1, size, fp);
    char c=buf[0];
    for(size_t i=1; i<size; ++i)
    {
        char next=buf[i];
        n_verts+=((c=='v')&&(next==' '));
        n_prims+=((c=='f')&&(next==' '));
        c=next;
    }
    fclose(fp);
    return {n_verts, n_prims};
}
static void parse_mesh(bitrtFloat3* coords, bitrtUint3* prims, const char* buf, size_t buf_size)
{
    static const int k_digit_map[]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    static const double k_scale_radix[]={1.0, 0.1, 0.01, 0.001, 0.0001, 0.00001, 0.000001, 0.0000001};
    auto is_digit=[](char c){ return ((c>='0')&&(c<='9')); };
    auto no_split=[](char c, int axis){
        return (axis<2?(c!=' '):((c!='\n')&&(c!='\0')));
    };

    int digits[16];
    uint32_t vid=0, pid=0;
    for(size_t i=0; i<buf_size; ++i)
    {
        char c=buf[i];
        if(c=='#'){
            while(buf[++i]!='\n');
            continue;
        }
        char next=buf[++i];
        if((c=='v')&&(next==' '))
        {
            for(int axis=0; axis<3; ++axis)
            {
                int n_digits=0, spos=0, sign=0;
                for(c=buf[++i]; c!='\n'; c=buf[++i])
                {
                    if(is_digit(c)){
                        digits[n_digits++]=k_digit_map[c-'0'];
                    } else
                    if(c=='-'){
                        sign=0x80000000;
                    } else
                    if(c=='.'){
                        spos=n_digits;
                    } else
                    if((n_digits>0)&&(c==' ')){
                        break;
                    }
                }
                int64_t coord=0;
                for(int64_t s=n_digits-1, scale=1; s>=0; --s, scale*=10){
                    coord+=static_cast<int64_t>(digits[s])*scale;
                }
                (&coords[vid].x)[axis]=as_f32(as_u32(static_cast<float>(coord*k_scale_radix[n_digits-spos]))|sign);
            }
            ++vid;
        } else
        if((c=='f')&&(next==' '))
        {
            for(int axis=0; axis<3; ++axis)
            {
                int n_digits=0;
                for(c=buf[++i];; c=buf[++i])
                {
                    if(is_digit(c)){
                        digits[n_digits++]=k_digit_map[c-'0'];
                        continue;
                    }
                    if(n_digits>0) break;
                }
                while(no_split(c, axis)){ c=buf[++i]; }
                uint32_t n=0;
                for(int s=n_digits-1, scale=1; s>=0; --s, scale*=10){
                    n+=digits[s]*scale;
                }
                (&prims[pid].x)[axis]=n-1;
            }
            ++pid;
        }
    }
}
#endif