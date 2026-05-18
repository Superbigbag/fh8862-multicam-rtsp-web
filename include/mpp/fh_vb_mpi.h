#ifndef __FH_VB_MPI_H__
#define __FH_VB_MPI_H__
/**VB**/
#include "fh_vb_mpipara.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*
*   Name: FH_VB_Init
*            初始化视频缓存池
*
*   Parameters:
*
*            None
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          必须先调用FY_MPI_VB_SetConf配置缓存池属性，否则会失败。
*          可重复初始化。
*/
FH_SINT32 FH_VB_Init(FH_VOID);

/*
*   Name: FH_VB_Exit
*            去初始化视频缓存池
*
*   Parameters:
*
*            None
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          建议在整个系统去初始化后，再去初始化缓存池。
*          必须先去初始化已经创建的模块公共视频缓存池，再去初始化缓存池，否则返回失败。
*          去初始化不会清除先前对缓存池的配置。
*          可以反复去初始化。
*/
FH_SINT32 FH_VB_Exit(FH_VOID);

/*
*   Name: FH_VB_SetConf
*            设置视频缓存池属性
*
*   Parameters:
*
*       [in] const VB_CONF_S *pstVbConf
*            视频缓存池属性指针,静态属性。
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          无。
*/
FH_SINT32 FH_VB_SetConf(const VB_CONF_S *pstVbConf);

/*
*   Name: FH_VB_GetConf
*            获取视频缓存池属性
*
*   Parameters:
*
*       [out] VB_CONF_S *pstVbConf
*            视频缓存池属性指针
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          先FH_VB_SetConf后才能获取得到。
*/
FH_SINT32 FH_VB_GetConf(VB_CONF_S *pstVbConf);

/*
*   Name: FH_VB_CreatePool
*            创建一个视频缓存池。
*
*   Parameters:
*
*       [in] FH_UINT32 u32BlkSize
*            缓存池中每个缓存块的大小
*
*       [in] FH_UINT32 u32BlkCnt
*            缓存池中缓存块的个数
*
*       [in] const FH_CHAR *pcMmzName
*            缓存池所在 DDR 的名字
*
*   Return:
*           非VB_INVALID_POOLID(缓存池号)
*           VB_INVALID_POOLID(失败)
*   Note:
*          该缓存池从空闲VMM中分配，一个缓存池包含若干个大小相同的缓存块。
*          如果该缓存池的大小超过了保留内存中的空闲空间，则创建缓存池会失败。
*          需保证输入的DDR名字已经存在，若DDR名不存在，则分配不到内存。
*          如果 pcMmzName 等于 NULL，则表示在匿名 DDR 中创建缓冲池。
*/
VB_POOL FH_VB_CreatePool(FH_UINT32 u32BlkSize,FH_UINT32 u32BlkCnt,const FH_CHAR *pcMmzName);

/*
*   Name: FH_VB_DestroyPool
*            销毁一个视频缓存池。
*
*   Parameters:
*
*       [in] VB_POOL Pool
*            缓存池 ID 号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          销毁一个不存在的缓存池，则返回 FY_ERR_VB_UNEXIST。
*          在去初始化缓存池时，所有的缓存池都将被销毁，包括用户态的缓存池。
*          销毁缓存池前，要确保该缓存池的所有已经被获取的缓存块已经被释放掉，否则会销毁失败。
*          缓存池ID号范围[0, VB_MAX_POOLS)，包括公共缓存池、模块公共缓存池、模块私有缓存池等的ID号。
*          需确保Pool为FY_MPI_VB_CreatePool所创建的缓存池的ID号，否则会返回失败。
*/
FH_SINT32 FH_VB_DestroyPool(VB_POOL Pool);

/*
*   Name: FH_VB_GetBlock
*            用户态获取一个缓存块。
*
*   Parameters:
*
*       [in] VB_POOL Pool
*            缓存池 ID 号
*
*       [in] FH_UINT32 u32BlkSize
*            缓存池中每个缓存块的大小
*
*       [in] const FH_CHAR *pcMmzName
*            缓存池所在 DDR 的名字
*
*   Return:
*           非VB_INVALID_HANDLE(有效的缓存块句柄)
*            VB_INVALID_HANDLE(获取缓存块失败)
*   Note:
*          用户在创建一个缓存池之后，本接口可从该缓存池中获取一个缓存块，
*          将第1个参数Pool设置为创建的缓存池ID（第2个参数u32BlkSize不用设置），
*          获取的缓存块的大小即为用户创建缓存池时指定的缓存块大小，
*          从指定缓存池获取缓存块时，参数 pcMmzName 无效;
*          如果需从一个公共缓存池中获取一块指定大小的缓存块，
*          则可以将第1个参数Pool设置为VB_INVALID_POOLID，将第2个参数设为需要的缓存块大小，
*          并指定某个DDR，如果指定的DDR上并没有公共缓存池，将获取不到缓存块，
*          如果pcMmzName等于NULL，则表示在匿名DDR上的公共缓存池获取缓存;
*          对公共缓存池的不当操作（如占用过多的缓存块）可会影响系统的正常运行。
*/
VB_BLK FH_VB_GetBlock(VB_POOL Pool, FH_UINT32 u32BlkSize, const FH_CHAR *pcMmzName);

/*
*   Name: FH_VB_ReleaseBlock
*            用户态释放一个已经获取的缓存块
*
*   Parameters:
*
*       [in] VB_BLK Block
*            缓存块句柄
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          获取的缓存块使用完后，需调用此接口释放缓存块。
*/
FH_SINT32 FH_VB_ReleaseBlock(VB_BLK Block);

/*
*   Name: FH_VB_Handle2PhysAddr
*            用户态获取一个缓存块的物理地址
*
*   Parameters:
*
*       [in] VB_BLK Block
*            缓存块句柄
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          指定的缓存块应是从视频缓存池中获取的有效缓存块
*/
VB_PHYADDR FH_VB_Handle2PhysAddr(VB_BLK Block);

/*
*   Name: FH_VB_Handle2PoolId
*            用户态获取一个帧缓存块所在缓存池的 ID
*
*   Parameters:
*
*       [in] VB_BLK Block
*            缓存块句柄
*
*   Return:
*           正常范围内id号(有效的缓存池 ID 号)
*           正常范围外id号(无效的缓存池 ID 号)
*   Note:
*           指定的缓存块应是从视频缓存池中获取的有效缓存块
*/
VB_POOL FH_VB_Handle2PoolId(VB_BLK Block);

/*
*   Name: FH_VB_InquireUserCnt
*            查询缓存块使用计数信息。
*
*   Parameters:
*
*       [in] VB_BLK Block
*            缓存块句柄
*
*   Return:
*           VB_INVALID_HANDLE(查询失败)
*           非 VB_INVALID_HANDLE(缓存块使用计数值)
*   Note:
*           无
*/
FH_SINT32 FH_VB_InquireUserCnt(VB_BLK Block);

/*
*   Name: FH_VB_MmapPool
*            为一个视频缓存池映射用户态虚拟地址。
*
*   Parameters:
*
*       [in] VB_POOL Pool
*            缓存池 ID 号
*
*   Return:
*           0(成功)
*           非 0(失败，详见错误码)
*   Note:
*           必须输入合法的缓存池 ID。重复映射视为成功。
*           用户创建的vb，默认会自动进行映射。
*/
FH_SINT32 FH_VB_MmapPool(VB_POOL Pool);

/*
*   Name: FH_VB_MunmapPool
*            为一个视频缓存池解除用户态映射。
*
*   Parameters:
*
*       [in] VB_POOL Pool
*            缓存池 ID 号
*
*   Return:
*           0(成功)
*           非 0(失败，详见错误码)
*   Note:
*           必须输入合法的缓存池 ID。
*           视频缓存池必须已经映射过，如果视频缓存池未映射，则直接返回成功。
*           解除映射时，需要确保缓存块没有正在被使用。
*           去初始化时，默认会自动进行解映射。
*/
FH_SINT32 FH_VB_MunmapPool(VB_POOL Pool);

/*
*   Name: FH_VB_GetBlkVirAddr
*            获取一个视频缓存池中的缓存块的用户态虚拟地址。
*
*   Parameters:
*
*       [in] VB_POOL Pool
*            缓存池 ID 号
*
*       [in] VB_PHYADDR u64PhyAddr
*            缓存块的物理地址
*
*       [out] FH_VOID **ppVirAddr
*            用户态虚拟地址
*
*   Return:
*           0(成功)
*           非 0(失败，详见错误码)
*   Note:
*           必须输入合法的缓存池 ID、合法的缓存块物理地址。
*           默认情况创建用户层vb后会自动映射，因此可直接获取。
*/
FH_SINT32 FH_VB_GetBlkVirAddr(VB_POOL Pool, VB_PHYADDR u64PhyAddr, FH_VOID **ppVirAddr);

/*
*   Name: FH_VB_InitModCommPool
*            初始化模块公共视频缓存池
*
*   Parameters:
*
*       [in] VB_UID_E enVbUid
*            使用模块公共视频缓冲池的模块 ID
*
*   Return:
*           0(成功)
*           非 0(失败，详见错误码)
*   Note:
*           当前公共视频缓冲池仅适用于 VDEC 模块。
*           需先调用 FY_MPI_VB_Init 进行公共视频缓冲池初始化。
*           需先调用 FY_MPI_VB_SetModPoolConf 配置缓存池属性，再初始化，否则会失败。
*           可反复初始化，不返回失败
*           VDEC 模块公共池仅在解码帧存分配方式使用模块公共VB池时才需要创建（VDEC的模块参数VBSource为 0），
*           否则不需要创建 VDEC 模块公共 VB 池。
*/
FH_SINT32 FH_VB_InitModCommPool(VB_UID_E enVbUid);

/*
*   Name: FH_VB_ExitModCommPool
*            去初始化模块公共视频缓存池
*
*   Parameters:
*
*       [in] VB_UID_E enVbUid
*            使用模块公共视频缓冲池的模块 ID
*
*   Return:
*           0(成功)
*           非 0(失败，详见错误码)
*   Note:
*           需在 FY_MPI_VB_Exit 之前调用该接口，否则返回失败。
*           可以反复退出，不返回失败。
*           退出后会清除先前对模块公共视频缓存池的配置。
*/
FH_SINT32 FH_VB_ExitModCommPool(VB_UID_E enVbUid);

/*
*   Name: FH_VB_SetModPoolConf
*            设置模块公共视频缓存池属性
*
*   Parameters:
*
*       [in] VB_UID_E enVbUid
*            使用模块公共视频缓冲池的模块 ID
*
*       [in] const VB_CONF_S *pstVbConf
*            模块公共视频缓存池属性指针，静态属性
*
*   Return:
*           0(成功)
*           非 0(失败，详见错误码)
*   Note:
*           模块公共视频缓冲区的配置根据实际需要配置，否则会造成内存浪费。
*/
FH_SINT32 FH_VB_SetModPoolConf(VB_UID_E enVbUid, const VB_CONF_S *pstVbConf);

/*
*   Name: FH_VB_GetModPoolConf
*            获取模块公共视频缓存池属性
*
*   Parameters:
*
*       [in] VB_UID_E enVbUid
*            使用模块公共视频缓冲池的模块 ID
*
*       [out] VB_CONF_S *pstVbConf
*            模块公共视频缓存池属性指针
*
*   Return:
*           0(成功)
*           非 0(失败，详见错误码)
*   Note:
*           需先设置模块公共视频缓存池属性后，再获取属性。
*/
FH_SINT32 FH_VB_GetModPoolConf(VB_UID_E enVbUid, VB_CONF_S *pstVbConf);

/*
*   Name: FH_VB_CreateVirtualVbPool
*            仅创建虚拟缓存池，池里没有物理缓存块。
*
*   Parameters:
*
*       [in] FH_UINT32 u32BlkCnt
*            缓存池中缓存块的个数
*
*       [in] const FH_CHAR *pcMmzName
*            缓存池所在DDR的名字
*
*   Return:
*           非VB_INVALID_POOLID(成功，有效的缓存池ID号)
*           VB_INVALID_POOLID(创建缓存池失败)
*   Note:
*           pcMmzName未支持，在匿名DDR上处理。
*/
VB_POOL FH_VB_CreateVirtualVbPool(FH_UINT32 u32BlkCnt, const FH_CHAR *pcMmzName);

/*
*   Name: FH_VB_AddBlock
*            往虚拟VB池里增加缓存块
*
*   Parameters:
*
*       [in] VB_POOL Pool
*            缓存池 ID 号
*
*       [in] VB_PHYADDR u64PhyAddr
*            缓存块的物理地址
*
*       [in] FH_UINT32 u32Size
*            缓存块大小
*
*   Return:
*           非VB_INVALID_POOLID(成功，有效的缓存池ID号)
*           VB_INVALID_POOLID(创建缓存池失败)
*   Note:
*           此换存块由用户自己分配，不在公共VB池内，此接口只是负责把缓存块加入 VB 池。
*           不能再调用 FY_MPI_VB_GetBlock 获取此缓存块。
*           用户需保证传递的物理地址不冲突并在VMM地址范围内，且内存大小需256字节对齐。
*           Virtualpool里的vb的物理地址没有做虚拟地址映射,如果用户需要使用虚拟地址，可自行map映射。
*           内存的申请释放都由用户控制，接口里只检查队列里面是否会存在地址冲突。
*           用户可以调用 FY_MPI_VB_ReleaseBlock 从缓存池里释放缓存块。释放后缓存块就不再在缓存池里，
*           用户如果需要再使用，需要再次调用 FY_MPI_VB_AddBlock 接口把缓存块增加到缓存池。
*           用户可以调用 FY_MPI_VB_InquireUserCnt 查询此缓存块是否被占用。
*/
VB_BLK FH_VB_AddBlock(VB_POOL Pool , VB_PHYADDR u64PhyAddr, FH_UINT32 u32Size);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*__FH_VB_MPI_H__ */

