#ifndef __FH_BGM_MPI_H__
#define __FH_BGM_MPI_H__
/**BGM**/

#include "types/type_def.h"
#include "fh_common.h"
#include "fh_bgm_mpipara.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/*
*   Name: FH_BGM_InitMem
*            背景建模初始化
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*       [in] FH_UINT32 Bgmwidth
*            背景建模支持的最大幅面宽
*
*       [in] FH_UINT32 Bgmheight
*            背景建模支持的最大幅面高
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_InitMem(FH_UINT32 chan,FH_UINT32 Bgmwidth,FH_UINT32 Bgmheight);

/*
*   Name: FH_BGM_FreeMem
*            释放背景建模经过VMM分配的内存，需要在通道停止运行后才可以释放。
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_FreeMem(FH_UINT32 chan);

/*
*   Name: FH_BGM_SetConfig
*            设置背景建模处理幅面。
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*       [in] const FH_SIZE *pstBgmconfig
*            背景建模处理幅面,幅面大小为主码流幅面16对齐后的1/8下采样的大小，不超过初始化最大幅面。
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_SetConfig(FH_UINT32 chan,const FH_SIZE *pstBgmconfig);

/*
*   Name: FH_BGM_GetConfig
*            获取背景建模处理幅面。
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*       [out] FH_SIZE *pstBgmconfig
*            背景建模处理幅面
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_GetConfig(FH_UINT32 chan,FH_SIZE *pstBgmconfig);

/*
*   Name: FH_BGM_Enable
*            开启背景建模使能
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_Enable(FH_UINT32 chan);


/*
*   Name: FH_BGM_Disable
*            关闭背景建模使能
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_Disable(FH_UINT32 chan);

/*
*   Name: FH_BGM_SubmitFrame
*            向背景建模模块提交图像数据
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*       [in] const FH_BGM_FRAME *pstframe
*            背景建模图像数据描述信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_SubmitFrame(FH_UINT32 chan,const FH_BGM_FRAME *pstframe);

/*
*   Name: FH_BGM_GetSWStatus
*            获取背景建模软件处理结果,立即返回
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*       [out] FH_BGM_SW_STATUS *pststatus
*            背景建模软件结果
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_GetSWStatus(FH_UINT32 chan,FH_BGM_SW_STATUS *pststatus);

/*
*   Name: FH_BGM_GetSWStatus_Timeout
*            获取背景建模软件处理结果，带超时
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*       [out] FH_BGM_SW_STATUS *pststatus
*            背景建模软件结果
*
*       [in] FH_UINT32 timeout
*            超时,单位ms
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_GetSWStatus_Timeout(FH_UINT32 chan,FH_BGM_SW_STATUS *pststatus, FH_UINT32 timeout);

/*
*   Name: FH_BGM_BkgReinit
*            重新初始化背景帧。一般情况下无需用户调用。
*            在一些利用BGM信息做智能分析等应用中，在发生场景切换后需要BGM数据生效时间加快时可以使用。
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_BkgReinit(FH_UINT32 chan);

/*
*   Name: FH_BGM_ADV_SetUpdateSigGauCount
*            设置单高斯模型生效时间。需要驱动关闭多高斯时生效。
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*       [in] FH_UINT32 count
*            更新单高斯的更新帧数周期
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_ADV_SetUpdateSigGauCount(FH_UINT32 chan,FH_UINT32 count);

/*
*   Name: FH_BGM_SetCapality
*            设置BGM工作模式。
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*       [in] FH_UINT32 work_mode
*            工作模式(0:BGM_PRO,1:BGM,2:BGM_LITE)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_SetCapality(FH_UINT32 chan,FH_UINT32 work_mode);

/*
*   Name: FH_BGM_SetBlobOutEn
*            设置BGM是否输出联通域目标矩形信息。
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*       [in] FH_UINT32 blob_en
*            是否输出联通域目标矩形信息.需要分配更多内存.
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_SetBlobOutEn(FH_UINT32 chan,FH_UINT32 blob_en);

/*
*   Name: FH_BGM_SetFgOutEn
*            设置BGM是否输出前景信息。
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*       [in] FH_UINT32 fg_en
*            是否输出前景信息.需要分配更多内存.
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_SetFgOutEn(FH_UINT32 chan,FH_UINT32 fg_en);

/*
*   Name: FH_BGM_QueryMem
*            获取BGM通道需要的内存,仅使用外部buf时调用.
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*       [in] FH_UINT32 Bgmwidth
*            处理图像宽度.
*
*       [in] FH_UINT32 Bgmheight
*            处理图像高度.
*
*       [out] FH_UINT32 *needsize
*            内存大小.
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_QueryMem(FH_UINT32 chan,FH_UINT32 Bgmwidth,FH_UINT32 Bgmheight,FH_UINT32 *needsize);

/*
*   Name: FH_BGM_InitMemWithExtBuf
*            创建BGM通道(外部分配buf).
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*       [in] FH_UINT32 Bgmwidth
*            处理图像宽度.
*
*       [in] FH_UINT32 Bgmheight
*            处理图像高度.
*
*       [out] FH_MEM_INFO *mem
*            内存信息.
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_InitMemWithExtBuf(FH_UINT32 chan,FH_UINT32 Bgmwidth,FH_UINT32 Bgmheight,FH_MEM_INFO *mem);

/*
*   Name: FH_BGM_GetSWStatusEx
*            获取BGM处理结果，超时和指定时间戳
*
*   Parameters:
*
*       [in] FH_UINT32 chan
*            背景建模通道号
*
*       [out] FH_BGM_SW_STATUS *pststatus
*            背景建模软件结果.
*
*       [in] FH_UINT32 timeout
*            超时,单位ms.
*
*       [in] FH_UINT32 time_stamp
*            时间戳,如BGM最新结果时间戳大于等于此值立刻返回结果
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_BGM_GetSWStatusEx(FH_UINT32 chan,FH_BGM_SW_STATUS *pststatus,FH_UINT32 timeout,FH_UINT32 time_stamp);

/*智能编码GOP设置接口,会在VENC相关接口中被调用,不建议用户直接调用此接口*/
FH_SINT32 fh_bgm_setgopth(FH_UINT32 chan,const FH_GOP_TH *pgopth);
FH_SINT32 fh_bgm_getgopth(FH_UINT32 chan,FH_GOP_TH *pgopth);

/*高级参数配置接口,不建议用户自行调用此接口,以免影响背景建模效果*/
FH_SINT32 FH_BGM_ADV_SetSigGauAttr(FH_UINT32 chan,const FH_SINGLE_GAU_CFG *psiggaucfg);
FH_SINT32 FH_BGM_ADV_GetSigGauAttr(FH_UINT32 chan,FH_SINGLE_GAU_CFG *psiggaucfg);
FH_SINT32 FH_BGM_ADV_SetMulGauAttr(FH_UINT32 chan,const FH_MULTI_GAU_CFG *pmulgaucfg);
FH_SINT32 FH_BGM_ADV_GetMulGauAttr(FH_UINT32 chan,FH_MULTI_GAU_CFG *pmulgaucfg);
FH_SINT32 FH_BGM_ADV_SetConExpaAttr(FH_UINT32 chan,FH_CON_EXPA_IDX conidx,const FH_CON_EXPA_CFG *pconexpacfg);
FH_SINT32 FH_BGM_ADV_GetConExpaAttr(FH_UINT32 chan,FH_CON_EXPA_IDX conidx,FH_CON_EXPA_CFG *pconexpacfg);
FH_SINT32 FH_BGM_ADV_SetFrmDiffAttr(FH_UINT32 chan,const FH_FRM_DIFF_CFG *pfrmdiffcfg);
FH_SINT32 FH_BGM_ADV_GetFrmDiffAttr(FH_UINT32 chan,FH_FRM_DIFF_CFG *pfrmdiffcfg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /*__MPI_VO_H__ */
