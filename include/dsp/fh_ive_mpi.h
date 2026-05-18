#ifndef __FH_IVE_MPI_H__
#define __FH_IVE_MPI_H__
/**IVE**/

#include "types/type_def.h"
#include "fh_common.h"
#include "fh_ive_mpipara.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/*
*   Name: FH_IVE_V3_Resize
*            创建图像缩放任务
*
*   Parameters:
*
*       [out] IVE_HANDLE *handle
*            IVE_V3任务句柄
*
*       [in] IVE_V3_RESIZE_CTRL *ctrl
*            缩放任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*          需加载BGM驱动,是否支持见能力集说明．
*/
FH_SINT32 FH_IVE_V3_Resize(IVE_HANDLE *handle,IVE_V3_RESIZE_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_IVE_V3_Filter
*            创建图像滤波任务
*
*   Parameters:
*
*       [out] IVE_HANDLE *handle
*            IVE_V3任务句柄
*
*       [in] IVE_V3_FILTER_CTRL *ctrl
*            滤波任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*          需加载BGM驱动,是否支持见能力集说明．
*/
FH_SINT32 FH_IVE_V3_Filter(IVE_HANDLE *handle,IVE_V3_FILTER_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_IVE_V3_Rot
*            创建旋转任务
*
*   Parameters:
*
*       [out] IVE_HANDLE *handle
*            IVE_V3任务句柄
*
*       [in] IVE_V3_ROT_CTRL *ctrl
*            旋转任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*          需加载BGM驱动,是否支持见能力集说明．
*/
FH_SINT32 FH_IVE_V3_Rot(IVE_HANDLE *handle,IVE_V3_ROT_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_IVE_V3_Shear
*            创建错切任务
*
*   Parameters:
*
*       [out] IVE_HANDLE *handle
*            IVE_V3任务句柄
*
*       [in] IVE_V3_SHEAR_CTRL *ctrl
*            错切任务控制参数
*
*       [in] FH_BOOL instant
*            接口是否立即返回(FH_FALSE:阻塞)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*          需加载BGM驱动,是否支持见能力集说明．
*/
FH_SINT32 FH_IVE_V3_Shear(IVE_HANDLE *handle,IVE_V3_SHEAR_CTRL *ctrl,FH_BOOL instant);

/*
*   Name: FH_IVE_Query
*            查询IVE任务是否完成
*
*   Parameters:
*
*       [in] IVE_HANDLE handle
*            IVE任务句柄
*
*       [out] FH_BOOL *isfinish
*            IVE任务是否完成标志
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
FH_SINT32 FH_IVE_Query(IVE_HANDLE handle,FH_BOOL *isfinish,FH_BOOL isblock);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
