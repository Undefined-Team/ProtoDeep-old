#ifndef PD_MEM_H
# define PD_MEM_H

// Lib

// Macro

// Structures
typedef struct          pds_mem16 {
    unsigned long       placeholder1;
    unsigned long       placeholder2;
}                       pd_mem16;

typedef struct          pds_mem32 {
    pd_mem16             placeholder1;
    pd_mem16             placeholder2;
}                       pd_mem32;

typedef struct          pds_mem64 {
    pd_mem32             placeholder1;
    pd_mem32             placeholder2;
}                       pd_mem64;

typedef struct          pds_mem128 {
    pd_mem64             placeholder1;
    pd_mem64             placeholder2;
}                       pd_mem128;

typedef struct          pds_mem256 {
    pd_mem128             placeholder1;
    pd_mem128             placeholder2;
}                       pd_mem256;

typedef struct          pds_mem512 {
    pd_mem256             placeholder1;
    pd_mem256             placeholder2;
}                       pd_mem512;

typedef struct          pds_mem1024 {
    pd_mem512             placeholder1;
    pd_mem512             placeholder2;
}                       pd_mem1024;

typedef struct          pds_mem2048 {
    pd_mem1024             placeholder1;
    pd_mem1024             placeholder2;
}                       pd_mem2048;

typedef struct          pds_mem4096 {
    pd_mem2048             placeholder1;
    pd_mem2048             placeholder2;
}                       pd_mem4096;

typedef struct          pds_mem8192 {
    pd_mem4096             placeholder1;
    pd_mem4096             placeholder2;
}                       pd_mem8192;

typedef struct          pds_mem16384 {
    pd_mem8192             placeholder1;
    pd_mem8192             placeholder2;
}                       pd_mem16384;

typedef struct          pds_mem32768 {
    pd_mem16384             placeholder1;
    pd_mem16384             placeholder2;
}                       pd_mem32768;

typedef struct          pds_mem65536 {
    pd_mem32768             placeholder1;
    pd_mem32768             placeholder2;
}                       pd_mem65536;

typedef struct          pds_mem131072 {
    pd_mem65536             placeholder1;
    pd_mem65536             placeholder2;
}                       pd_mem131072;

typedef struct          pds_mem262144 {
    pd_mem131072             placeholder1;
    pd_mem131072             placeholder2;
}                       pd_mem262144;

typedef struct          pds_mem524288 {
    pd_mem262144             placeholder1;
    pd_mem262144             placeholder2;
}                       pd_mem524288;

typedef struct          pds_mem1048576 {
    pd_mem524288             placeholder1;
    pd_mem524288             placeholder2;
}                       pd_mem1048576;

typedef struct          pds_mem2097152 {
    pd_mem1048576             placeholder1;
    pd_mem1048576             placeholder2;
}                       pd_mem2097152;

typedef struct          pds_mem4194304 {
    pd_mem2097152             placeholder1;
    pd_mem2097152             placeholder2;
}                       pd_mem4194304;

typedef struct          pds_mem8388608 {
    pd_mem4194304             placeholder1;
    pd_mem4194304             placeholder2;
}                       pd_mem8388608;

typedef struct          pds_mem16777216 {
    pd_mem8388608             placeholder1;
    pd_mem8388608             placeholder2;
}                       pd_mem16777216;

typedef struct          pds_mem33554432 {
    pd_mem16777216             placeholder1;
    pd_mem16777216             placeholder2;
}                       pd_mem33554432;

typedef struct          pds_mem67108864 {
    pd_mem33554432             placeholder1;
    pd_mem33554432             placeholder2;
}                       pd_mem67108864;

typedef struct          pds_mem134217728 {
    pd_mem67108864             placeholder1;
    pd_mem67108864             placeholder2;
}                       pd_mem134217728;

typedef struct          pds_mem268435456 {
    pd_mem134217728             placeholder1;
    pd_mem134217728             placeholder2;
}                       pd_mem268435456;

typedef struct          pds_mem536870912 {
    pd_mem268435456             placeholder1;
    pd_mem268435456             placeholder2;
}                       pd_mem536870912;

typedef struct          pds_mem1073741824 {
    pd_mem536870912             placeholder1;
    pd_mem536870912             placeholder2;
}                       pd_mem1073741824;

typedef struct          pds_mem2147483648 {
    pd_mem1073741824             placeholder1;
    pd_mem1073741824             placeholder2;
}                       pd_mem2147483648;

typedef struct          pds_mem4294967296 {
    pd_mem2147483648             placeholder1;
    pd_mem2147483648             placeholder2;
}                       pd_mem4294967296;

// Prototypes
void            pd_mem_cpy(void* dst, void *src, size_t len);
void            pd_mem_set(void *array, int c, size_t len);
void            pd_mem_qcpy(void *dst, void *src, size_t len);

#endif