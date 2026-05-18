#ifndef __FH_VB_MPIPARA_H__
#define __FH_VB_MPIPARA_H__
/**|VB|**/
#include "fh_type.h"
#include "fh_errno.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define MAX_VMM_NAME_LEN 32
#define MMAX_MMB_NAME_LEN 16

#define VB_MAX_POOLS 256
#define VB_MAX_COMM_POOLS 16
#define VB_MAX_MOD_COMM_POOLS 16

#define VB_MAX_USER   VB_UID_BUTT

#define VB_INVALID_POOLID (-1UL)
#define VB_INVALID_HANDLE (-1UL)

#define POOL_OWNER_COMMON   -1		/* Common pool use this owner id, module common pool use VB_UID as owner id */
#define POOL_OWNER_PRIVATE  -2		/* Private pool use this owner id */

#define VB_SUPPLEMENT_JPEG_MASK 0x1

typedef FH_UINT32 VB_POOL;
typedef FH_UINT32 VB_BLK;


typedef enum
{
    VB_UID_VIU          = 0,		//VIU标识 | [ ]
    VB_UID_VOU          = 1,		//VOU标识 | [ ]
    VB_UID_VGS          = 2,		//VGS标识 | [ ]
    VB_UID_VENC         = 3,		//VENC标识 | [ ]
    VB_UID_VDEC         = 4,		//VDEC标识 | [ ]
    VB_UID_VDA          = 5,		//VDA标识 | [ ]
    VB_UID_H264E        = 6,		//H264标识 | [ ]
    VB_UID_JPEGED       = 7,		//JPEGD标识 | [ ]
    VB_UID_MPEG4E       = 8,		//MPEG4E标识 | [ ]
    VB_UID_H264D        = 9,		//H264D标识 | [ ]
    VB_UID_JPEGD        = 10,		//JPEGE标识 | [ ]
    VB_UID_MPEG4D       = 11,		//MPEG4D标识 | [ ]
    VB_UID_VPSS         = 12,		//VPSS标识 | [ ]
    VB_UID_GRP          = 13,		//GRP标识 | [ ]
    VB_UID_MPI          = 14,		//MPI标识 | [ ]
    VB_UID_PCIV         = 15,		//PCIV标识 | [ ]
    VB_UID_AI           = 16,		//AI标识 | [ ]
    VB_UID_AENC         = 17,		//AENC标识 | [ ]
    VB_UID_RC           = 18,		//RC标识 | [ ]
    VB_UID_VFMW         = 19,		//VFMW标识 | [ ]
    VB_UID_USER         = 20,		//USER标识 | [ ]
    VB_UID_H265E        = 21,		//h265E标识 | [ ]
    VB_UID_BGM          = 22,		//BGM标识 | [ ]
    VB_UID_BGMX         = 23,		//BGMX标识 | [ ]
    VB_UID_BGMSW        = 24,		//BGMSW标识 | [ ]
    VB_UID_TDE          = 25,		//TDE标识 | [ ]
    VB_UID_IVE          = 26,		//IVE标识 | [ ]
    VB_UID_NNA          = 27,		//NNA标识 | [ ]
    VB_UID_ISP          = 28,		//ISP标识 | [ ]
    VB_UID_BUTT
} VB_UID_E;

typedef enum
{
    POOL_TYPE_COMMON            = 0,		//公共缓存池类型 | [ ]
    POOL_TYPE_PRIVATE           = 1,		//私有缓存池类型 | [ ]
    POOL_TYPE_MODULE_COMMON     = 2,		//模块公共缓存池类型（目前只有VDEC可能用到） | [ ]
    POOL_TYPE_BUTT
} POOL_TYPE_E;

typedef struct
{
    FH_UINT32 u32MaxPoolCnt;					//系统中可容纳的缓存池数(目前固定) | [VB_MAX_POOLS]
    struct
    {
        FH_UINT32 u32BlkSize;					//缓存块的大小 | []
        FH_UINT32 u32BlkCnt;					//缓存块个数 | []
        FH_CHAR acMmzName[MAX_VMM_NAME_LEN];	//缓存池所在的VMM名 | []
    }astCommPool[VB_MAX_COMM_POOLS];
} VB_CONF_S;


#define FY_ERR_VB_NULL_PTR          FY_DEF_ERR(FY_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_NULL_PTR)
#define FY_ERR_VB_NOMEM             FY_DEF_ERR(FY_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_NOMEM)
#define FY_ERR_VB_NOBUF             FY_DEF_ERR(FY_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_NOBUF)
#define FY_ERR_VB_UNEXIST           FY_DEF_ERR(FY_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_UNEXIST)
#define FY_ERR_VB_ILLEGAL_PARAM     FY_DEF_ERR(FY_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_ILLEGAL_PARAM)
#define FY_ERR_VB_NOTREADY          FY_DEF_ERR(FY_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_SYS_NOTREADY)
#define FY_ERR_VB_BUSY              FY_DEF_ERR(FY_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_BUSY)
#define FY_ERR_VB_NOT_PERM          FY_DEF_ERR(FY_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_NOT_PERM)
#define FY_ERR_VB_2MPOOLS           FY_DEF_ERR(FY_ID_VB, EN_ERR_LEVEL_ERROR, EN_ERR_BUTT + 1)

#define FY_TRACE_VB(level,fmt...)   FY_TRACE(level, FY_ID_VB,##fmt)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /* __FH_VB_MPIPARA_H__ */

