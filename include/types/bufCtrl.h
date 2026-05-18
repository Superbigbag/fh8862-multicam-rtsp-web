#ifndef _BUFCTRL_H_
#define _BUFCTRL_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

typedef struct mem_desc {
	unsigned int base;
	void        *vbase;
	unsigned int size;
	unsigned int align;
} MEM_DESC;

typedef struct mem_desc64 {
	unsigned long long base;
	void        *vbase;
	unsigned int size;
	unsigned int align;
} MEM_DESC64;

int buffer_malloc(MEM_DESC *mem, int size, int align);
int buffer_malloc_withname_cached(MEM_DESC *mem, int size, int align,const char* name);
int buffer_malloc_withname(MEM_DESC *mem, int size, int align, const char* name);
int buffer_malloc_withname_sram(MEM_DESC *mem, int size, int align, const char* name);

int buffer_malloc64(MEM_DESC64 *mem, int size, int align);
int buffer_malloc_withname_cached64(MEM_DESC64 *mem, int size, int align,const char* name);
int buffer_malloc_withname64(MEM_DESC64 *mem, int size, int align, const char* name);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
