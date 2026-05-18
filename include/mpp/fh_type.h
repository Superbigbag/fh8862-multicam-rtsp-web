#ifndef __FY_TYPE_H__
#define __FY_TYPE_H__

#include "types/type_def.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define VB_PHYADDR              FH_UINT64

typedef unsigned char           FY_U8;
typedef unsigned short          FY_U16;
typedef unsigned int            FY_U32;
typedef double                  FY_DOUBLE;
typedef signed char             FY_S8;
typedef short                   FY_S16;
typedef int                     FY_S32;
typedef char                    FY_CHAR;

#ifndef _M_IX86
    typedef unsigned long long  FY_U64;
    typedef long long           FY_S64;
#else
    typedef __int64             FY_U64;
    typedef __int64             FY_S64;
#endif


#define FY_VOID void
#define FY_BOOL FH_BOOL
#define FY_TRUE FH_TRUE
#define FY_FALSE FH_FALSE

#ifndef NULL
    #define NULL    0L
#endif

#define FY_NULL     0L
#define FY_SUCCESS  0
#define FY_FAILURE  (-1)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __FY_TYPE_H__ */

