#ifndef __FH_VOU_MPI_H__
#define __FH_VOU_MPI_H__
/**VOU**/

#include "types/type_def.h"
#include "fh_vou_mpipara.h"
#include "types/bufCtrl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/*
*   Name: FH_VOU_SubmitFrame
*            向驱动提交一帧图像数据
*
*   Parameters:
*
*       [in] FH_VOU_FRAME *frame
*            图像数据描述信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*      无
*/
FH_SINT32 FH_VOU_SubmitFrame(FH_VOU_FRAME *frame);

/*
*   Name: FH_VOU_Start
*            启动vou的硬件
*
*   Parameters:
*
*       [] FH_VOID
*            
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*      无
*/
FH_SINT32 FH_VOU_Start(FH_VOID);
/*
*   Name: FH_VOU_Stop
*            停止vou的硬件
*
*   Parameters:
*
*       [] FH_VOID
*            
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*      无
*/
FH_SINT32 FH_VOU_Stop(FH_VOID);
/*
*   Name: FH_VOU_Reset
*            复位vou硬件
*
*   Parameters:
*
*       [] FH_VOID
*            
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*      无
*/
FH_SINT32 FH_VOU_Reset(FH_VOID);
/*
*   Name: FH_VOU_SetParam
*            设置vou初始化所需参数
*
*   Parameters:
*
*       [in] FH_VOU_INIT_PARAM *init_param
*            初始化参数的结构体指针
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*      无
*/
FH_SINT32 FH_VOU_SetParam(FH_VOU_INIT_PARAM *init_param);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
