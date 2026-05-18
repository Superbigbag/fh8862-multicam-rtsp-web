#ifndef __FHADV_SMARTIR_MPI_H_
#define __FHADV_SMARTIR_MPI_H_

#include "FH_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef enum
{
	SMARTIR_STATUS_DAY   = 0, /* day */
	SMARTIR_STATUS_NIGHT = 1, /* night */
}FHADV_SMARTIR_STATUS_e;

typedef enum
{
    SMARTIR_DEBUG_OFF     = 0x0, /* close debug print */
    SMARTIR_DEBUG_THRE    = 0x1, /* print basic threshold */
    SMARTIR_DEBUG_ADVTHRE = 0x2, /* print advance threshold */
    SMARTIR_DEBUG_ALL     = 0xf, /* print all */
}FHADV_SMARTIR_DEBUG_e;

typedef struct
{
    FH_UINT16 d2n_thre; /* day to night threshold */
    FH_UINT16 n2d_gain; /* night to day gain threshold */
    FH_UINT16 n2d_value; /* night to day value threshold */

    FH_UINT16 adv_rr; /* advanced rr threshold */
    FH_UINT16 adv_br; /* advanced br threshold */
    FH_UINT16 adv_sr; /* advanced sr threshold */

    FH_UINT16 adv_delay; /* advanced delay */
}FHADV_SMARTIR_CFG_t;

typedef struct
{
    float luma_step;        /* min adjust step */
    unsigned int tar_luma;  /* adjust target luma */
    unsigned int dim_zone0; /* adjust stop level */
    unsigned int dim_zone1; /* adjust start level */
}FHADV_SMARTDIM_CFG_t;

/**
 *  @brief      smartir初始化
 *
 * @param[in]   grpidx 组id
 * @return      成功：0 失败：详见错误码
 */
FH_SINT32 FHAdv_SmartIR_Init(FH_SINT32 grpidx);

/**
 *  @brief      smartir去初始化
 *
 * @param[in]   grpidx 组id
 * @return      成功：0 失败：详见错误码
 */
FH_SINT32 FHAdv_SmartIR_UnInit(FH_SINT32 grpidx);

/**
* @brief 设置日夜切换阀值
* @param [in] grpidx, [in]psmartir_cfg
* @return 0: 成功 非0：失败
*/
FH_SINT32 FHAdv_SmartIR_SetCfg(FH_SINT32 grpidx, const FHADV_SMARTIR_CFG_t *psmartir_cfg);

/**
*@brief 获取日夜切换增益阀值
*@param [in] grpidx, [out] psmartir_cfg
*@return 0: 成功 非0：失败
*/
FH_SINT32 FHAdv_SmartIR_GetCfg(FH_SINT32 grpidx, FHADV_SMARTIR_CFG_t *psmartir_cfg);

/**
*@brief 获取当前白天晚上状态
*@param [in] grpidx, [in] irCurr  当前ir状态，初始必须为白天
*@return 0:白天 1：晚上
*/
FH_SINT32 FHAdv_SmartIR_GetDayNightStatus(FH_SINT32 grpidx, FHADV_SMARTIR_STATUS_e irCurr);

/**
*@brief 打印库版本信息
*@param [in] print_enable
*@return 0: OK
*/
FH_CHAR* FH_ADV_SMARTIR_Version(FH_UINT32 print_enable);

/**
*@ 配置debug等级
*@param [in] grpidx
*@return 0: OK
*/
FH_SINT32 FHAdv_SmartIR_SetDebugLevel(FH_SINT32 grpidx, FHADV_SMARTIR_DEBUG_e level);

/**
*@ 调光初始化
*@param [in] grpidx
*@return 0: OK
*/
FH_SINT32 FHAdv_SmartDim_Init(FH_SINT32 grpidx);

/**
*@ 调光去初始化
*@param [in] grpidx
*@return 0: OK
*/
FH_SINT32 FHAdv_SmartDim_UnInit(FH_SINT32 grpidx);

/**
*@ 获取调光配置
*@param [in] grpidx, [in] dim_cfg
*@return 0: OK
*/
FH_SINT32 FHAdv_SmartDim_GetConfig(FH_SINT32 grpidx, FHADV_SMARTDIM_CFG_t *dim_cfg);

/**
*@ 设置调光配置
*@param [in] grpidx, [in] dim_cfg
*@return 0: OK
*/
FH_SINT32 FHAdv_SmartDim_SetConfig(FH_SINT32 grpidx, const FHADV_SMARTDIM_CFG_t *dim_cfg);

/**
*@ 开启调光策略
*@param [in] grpidx, [in] pre_duty  当前占空比
*@return 下一帧占空比
*/
float FHAdv_SmartDim_Run(FH_SINT32 grpidx, float pre_duty);

/**
*@ 开启debug调试
*@param [in] grpidx, [in] enable
*@return 0: OK
*/
FH_SINT32 FHAdv_SmartDim_Debug(FH_SINT32 grpidx, FH_SINT32 enable);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _FHADV_SMART_IR_H_ */


