#ifndef __FH_VGS_MPI_H__
#define __FH_VGS_MPI_H__
/**VGS**/

#include "types/type_def.h"
#include "fh_common.h"
#include "fh_vgs_mpipara.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/*
*   Name: FH_VGS_V2_PM
*            创建图像马赛克遮挡任务
*
*   Parameters:
*
*       [out] VGS_HANDLE *handle
*            VGS任务句柄
*
*       [in] VGS_V2_PM_CTRL *ctrl
*            遮挡任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VGS_V2_PM(VGS_HANDLE *handle,VGS_V2_PM_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_VGS_V2_CVT
*            创建YUV格式转换任务
*
*   Parameters:
*
*       [out] VGS_HANDLE *handle
*            VGS任务句柄
*
*       [in] VGS_V2_CVT_CTRL *ctrl
*            转换任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VGS_V2_CVT(VGS_HANDLE *handle,VGS_V2_CVT_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_VGS_V2_ROT
*            创建旋转任务
*
*   Parameters:
*
*       [out] VGS_HANDLE *handle
*            VGS任务句柄
*
*       [in] VGS_V2_ROT_CTRL *ctrl
*            旋转任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VGS_V2_ROT(VGS_HANDLE *handle,VGS_V2_ROT_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_VGS_V2_JNT
*            创建图像拼接任务
*
*   Parameters:
*
*       [out] VGS_HANDLE *handle
*            VGS任务句柄
*
*       [in] VGS_V2_JNT_CTRL *ctrl
*            拼接任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VGS_V2_JNT(VGS_HANDLE *handle,VGS_V2_JNT_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_VGS_V2_SCL
*            创建缩放任务
*
*   Parameters:
*
*       [out] VGS_HANDLE *handle
*            VGS任务句柄
*
*       [in] VGS_V2_SCL_CTRL *ctrl
*            缩放任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VGS_V2_SCL(VGS_HANDLE *handle,VGS_V2_SCL_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_VGS_V2_CNE
*            创建腐蚀膨胀任务
*
*   Parameters:
*
*       [out] VGS_HANDLE *handle
*            VGS任务句柄
*
*       [in] VGS_V2_CNE_CTRL *ctrl
*            腐蚀膨胀任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VGS_V2_CNE(VGS_HANDLE *handle,VGS_V2_CNE_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_VGS_V2_INTG
*            创建积分图任务
*
*   Parameters:
*
*       [out] VGS_HANDLE *handle
*            VGS任务句柄
*
*       [in] VGS_V2_INTG_CTRL *ctrl
*            积分图任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VGS_V2_INTG(VGS_HANDLE *handle,VGS_V2_INTG_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_VGS_V2_ADD
*            创建加减运算任务
*
*   Parameters:
*
*       [out] VGS_HANDLE *handle
*            VGS任务句柄
*
*       [in] VGS_V2_ADD_CTRL *ctrl
*            加减运算任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VGS_V2_ADD(VGS_HANDLE *handle,VGS_V2_ADD_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_VGS_V2_MRG
*            创建图像融合任务
*
*   Parameters:
*
*       [out] VGS_HANDLE *handle
*            VGS任务句柄
*
*       [in] VGS_V2_MRG_CTRL *ctrl
*            融合任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VGS_V2_MRG(VGS_HANDLE *handle,VGS_V2_MRG_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_VGS_V2_OSD_CVT
*            创建OSD格式转换任务
*
*   Parameters:
*
*       [out] VGS_HANDLE *handle
*            VGS任务句柄
*
*       [in] VGS_V2_OSD_CVT_CTRL *ctrl
*            转换任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VGS_V2_OSD_CVT(VGS_HANDLE *handle,VGS_V2_OSD_CVT_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_VGS_V2_OSD_OL
*            创建OSD叠加任务
*
*   Parameters:
*
*       [out] VGS_HANDLE *handle
*            VGS任务句柄
*
*       [in] VGS_V2_OSD_OL_CTRL *ctrl
*            OSD叠加任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VGS_V2_OSD_OL(VGS_HANDLE *handle,VGS_V2_OSD_OL_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_VGS_Query
*            查询VGS任务是否完成
*
*   Parameters:
*
*       [in] VGS_HANDLE handle
*            VGS任务句柄
*
*       [out] FH_BOOL *isfinish
*            VGS任务是否完成标志
*
*       [in] FH_BOOL isblock
*            查询接口是否阻塞标志(FH_TRUE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*          当句柄中硬件模块标记相同时，如果任务标记大的任务已完成，代表比其小的任务也都已经完成。
*          硬件模块标记不同时，两个任务标记相互独立，不能推导出另外不同模块标记之间任务是否完成。
*/
FH_SINT32 FH_VGS_Query(VGS_HANDLE handle,FH_BOOL *isfinish,FH_BOOL isblock);

/*
*   Name: FH_VGS_MEM_INIT
*            初始化VGS
*
*   Parameters:
*
*            None
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*/
FH_SINT32 FH_VGS_MEM_INIT(FH_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /*__MPI_VO_H__ */
