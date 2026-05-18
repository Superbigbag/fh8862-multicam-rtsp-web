#ifndef __FH_SYSTEM_MPI_H__
#define __FH_SYSTEM_MPI_H__
/**System Control**/

#include "types/type_def.h"
#include "fh_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/*
*   Name: FH_SYS_Init
*            初始化MPP系统。打开各个设备驱动。
*
*   Parameters:
*
*            None
*
*   Return:
*              0(成功)
*            非0(失败,详见错误码)
*   Note:
*            对于各模块相关内存和功能裁剪需要在此函数之前调用。
*/
FH_SINT32  FH_SYS_Init(FH_VOID);

/*
*   Name: FH_SYS_Init_Pre
*            初始化MPP系统。打开部分设备驱动。
*            适用于快速启动相关应用场景
*
*   Parameters:
*
*            None
*
*   Return:
*              0(成功)
*            非0(失败,详见错误码)
*   Note:
*            对于在此接口中打开的模块相关内存和功能裁剪需要在此函数之前调用。
*/
FH_SINT32 FH_SYS_Init_Pre(FH_VOID);
/*
*   Name: FH_SYS_Init_Post
*            初始化MPP系统。打开FH_SYS_Init_Pre未被初始化的设备驱动。
*            适用于快速启动相关应用场景
*
*   Parameters:
*
*            None
*
*   Return:
*              0(成功)
*            非0(失败,详见错误码)
*   Note:
*            对于在此接口中打开的模块相关内存和功能裁剪需要在此函数之前调用。
*/
FH_SINT32 FH_SYS_Init_Post(FH_VOID);

/*
*   Name: FH_SYS_Exit
*            退出MPP系统。关闭各个设备驱动。释放内存资源。
*
*   Parameters:
*
*            None
*
*   Return:
*              0(成功)
*            非0(失败,详见错误码)
*/
FH_SINT32  FH_SYS_Exit(FH_VOID);

/*
*   Name: FH_SYS_Bind
*            数据源到数据接收者的绑定接口
*
*   Parameters:
*
*       [in] FH_BIND_INFO src
*            数据源信息
*
*       [in] FH_BIND_INFO dst
*            数据接收者信息
*
*   Return:
*              0(成功)
*            非0(失败,详见错误码)
*
*   Note:
*            支持的绑定关系和相关注意实现请参见系统控制章节相关说明
*/
FH_SINT32 FH_SYS_Bind(FH_BIND_INFO src,FH_BIND_INFO dst);

/*
*   Name: FH_SYS_UnBindbySrc
*            解除数据源的所有绑定关系(存在多个接收者时也会全部解除)
*
*   Parameters:
*
*       [in] FH_BIND_INFO src
*            数据源信息
*
*   Return:
*              0(成功)
*            非0(失败,详见错误码)
*/
FH_SINT32  FH_SYS_UnBindbySrc(FH_BIND_INFO src);

/*
*   Name: FH_SYS_UnBindbyDst
*            解除数据接收者的所有绑定关系
*
*   Parameters:
*
*       [in] FH_BIND_INFO dst
*            数据接收者信息
*
*   Return:
*              0(成功)
*            非0(失败,详见错误码)
*/
FH_SINT32 FH_SYS_UnBindbyDst(FH_BIND_INFO dst);

/*
*   Name: FH_SYS_GetBindbyDest
*            根据接收者获取数据源的信息
*
*   Parameters:
*
*       [out] FH_BIND_INFO *src
*            数据源信息
*
*       [in] FH_BIND_INFO dst
*            数据接收者信息
*
*   Return:
*              0(成功)
*            非0(失败,详见错误码)
*/
FH_SINT32 FH_SYS_GetBindbyDest(FH_BIND_INFO *src,FH_BIND_INFO dst);

/*
*   Name: FH_SYS_GetVersion
*            获取系统版本信息
*
*   Parameters:
*
*       [out] FH_VERSION_INFO *pstSystemversion
*            版本号等信息
*
*   Return:
*              0(成功)
*            非0(失败,详见错误码)
*/
FH_SINT32  FH_SYS_GetVersion(FH_VERSION_INFO *pstSystemversion);

/*
*   Name: *FH_DSP_Version
*            获取DSP版本信息字符串
*
*   Parameters:
*
*       [in] FH_UINT32 print_enable
*            是否自动打印相关版本信息
*
*   Return:
*              0(成功)
*            非0(失败,详见错误码)
*/
FH_CHAR *FH_DSP_Version(FH_UINT32 print_enable);

/*
*   Name: FH_SYS_GetChipID
*            获取芯片标识,芯片标识定义见fh_common.h
*
*   Parameters:
*
*            None
*
*   Return:
*            芯片标识
*
*/
FH_UINT32 FH_SYS_GetChipID(FH_VOID);

/*
*   Name: FH_SYS_SetReg
*            设置寄存器/内存地址
*
*   Parameters:
*
*       [in] FH_PHYADDR addr
*            物理地址
*
*       [out]  FH_UINT32 value
*            设置值
*
*   Return:
*              0(成功)
*            非0(失败,详见错误码)
*/
FH_SINT32 FH_SYS_SetReg(FH_PHYADDR addr, FH_UINT32 value);

/*
*   Name: FH_SYS_GetReg
*            获取寄存器/内存地址
*
*   Parameters:
*
*       [in] FH_PHYADDR u32Addr
*            物理地址
*
*       [out]  FH_UINT32 *pu32Value
*            实际值
*
*   Return:
*              0(成功)
*            非0(失败,详见错误码)
*/
FH_SINT32 FH_SYS_GetReg(FH_PHYADDR u32Addr, FH_UINT32 *pu32Value);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /*__MPI_VO_H__ */

