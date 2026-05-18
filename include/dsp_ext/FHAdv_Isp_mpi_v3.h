/**
 * @file     FHAdv_Isp_mpi_v3.h
 * @brief    FHAdv ISP moduel interface
 * @version  V1.0.0
 * @date     11-8-2020
 * @author   Software Team
 *
 * @note
 * Copyright (C) 2016 Shanghai Fullhan Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * @par
 * Fullhan is supplying this software which provides customers with programming
 * information regarding the products. Fullhan has no responsibility or
 * liability for the use of the software. Fullhan not guarantee the correctness
 * of this software. Fullhan reserves the right to make changes in the software
 * without notification.
 *
 */

#ifndef _FHADV_ISP_MPI_H
#define _FHADV_ISP_MPI_H

#include "FH_typedef.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/** @addtogroup Video_ISP 图像效果调整接口
 *  @{
 */

// 曝光时间的单位是微秒(us)
enum FH_SINT32t
{
    FH_SINT32t_1_3      = 333333,
    FH_SINT32t_1_6      = 166666,
    FH_SINT32t_1_12     = 83333,
    FH_SINT32t_1_25     = 40000,
    FH_SINT32t_1_50     = 20000,
    FH_SINT32t_1_100    = 10000,
    FH_SINT32t_1_150    = 6666,
    FH_SINT32t_1_200    = 5000,
    FH_SINT32t_1_250    = 4000,
    FH_SINT32t_1_500    = 2000,
    FH_SINT32t_1_750    = 1333,
    FH_SINT32t_1_1000   = 1000,
    FH_SINT32t_1_2000   = 500,
    FH_SINT32t_1_4000   = 250,
    FH_SINT32t_1_10000  = 100,
    FH_SINT32t_1_100000 = 10,
};
typedef enum FH_SINT32t FHADV_ISP_AE_TIME_LEVEL;
/**
 *  @brief      sensor初始化
 *
 * @param[in]   sns_if, 传入sensor结构体指针
 *
 * @return      0 或 -1
 */
FH_SINT32 FHAdv_Isp_SensorInit(FH_UINT32 u32DevId, struct isp_sensor_if* sns_if);
/**
 *  @brief      ISP参数初始化
 *
 *              为了能正确读取初始参数，请务必在程序初始化时调用FHAdv_Isp_Init接口,调用位置必须在配置完成sensor幅面和加载完成效果参数之后。
 *
 * @param[in]   无
 * @return      0
 */
FH_SINT32 FHAdv_Isp_Init(FH_UINT32 u32DevId);

/**
 *  @brief      设置自动白平衡增益
 *
 * @param[in]   mode    设置模式：
 *                      mode 0:自动白平衡
 *                      mode 1:锁定白平衡
 *                      mode 2:白炽灯
 *                      mode 3:暖光灯
 *                      mode 4:自然光
 *                      mode 5:日光灯
 *              模式2/3/4/5必须sensor库实现get_user_awb_gain函数
 * @return      0 或 -1
 */
FH_SINT32 FHAdv_Isp_SetAwbGain(FH_UINT32 u32DevId,FH_UINT32 mode);

/**
 *  @brief      获取自动白平衡增益
 *
 *              使用方法参考：
 *                 FH_UINT32 awbgain[3];
 *                 FHAdv_Isp_GetAwbGain(FH_UINT32 u32DevId,awbgain);
 *              结果保存在awbgain数组中,分别对应rgain,ggain,bgain
 *
 * @param[out]  AwbGain    数组首地址
 * @return      0
 */
FH_SINT32 FHAdv_Isp_GetAwbGain(FH_UINT32 u32DevId,FH_UINT32 *AwbGain);

/**
 *  @brief      设置自动曝光模式
 *
 * @param[in]   mode               设置模式:
 *                                 mode 0:自动, intt和gain的最大值由intt_us和gain_level决定
 *                                 mode 1:曝光时间手动, 手动曝光由intt_us决定,gain最大值由gain_level决定
 *                                 mode 2:曝光增益手动, 手动增益由gain_level决定,intt最大值由intt_us决定
 *                                 mode 3:均手动, 手动曝光由intt_us决定,手动增益由gain_level决定
 * @param[in]   ae_time_us         可以选择FHADV_ISP_AE_TIME_LEVEL枚举类型中的一个, 也可以直接输入参数, 单位是微秒(us)
 * @param[in]   gain_level         增益等级，0 ~ 100, 0代表增益1倍, 100代表增益最大值
 * @return      0
 */
FH_SINT32 FHAdv_Isp_SetAEMode(FH_UINT32 u32DevId, FH_UINT32 mode, FH_UINT32 intt_us, FH_UINT32 gain_level);

/**
 *  @brief      获取自动曝光模式
 *
 *              使用方法参考：
 *                 FH_SINT32 intt_us, gain_value;
 *                 FHAdv_Isp_GetAEMode(FH_UINT32 u32DevId, &intt_us, &gain_value);
 *
 * @param[out]  intt_us    实际曝光时间,单位为微秒(us)
 * @param[out]  gain_level  曝光增益等级(0~100),值越大增益越大,由于量化误差,获取值与输入值之间可能会有差异
 * @return      0
 */
FH_SINT32 FHAdv_Isp_GetAEMode(FH_UINT32 u32DevId, FH_UINT32 *intt_us, FH_UINT32 *gain_level);

/**
 *  @brief      设置宽动态参数
 *
 * @param[in]   mode    0:关闭, 1:开启
 * @param[in]   level   0~10 值越大，动态范围越大, 必须sensor库实现get_user_ltm_curve函数
 * @return      0 或 -1
 */
FH_SINT32 FHAdv_Isp_SetLtmCfg(FH_UINT32 u32DevId, FH_UINT32 mode, FH_UINT32 level);

/**
 *  @brief      设置宽动态参数
 *
 *              使用参考：
 *                 FH_SINT32 mode,level;
 *                 FHAdv_Isp_GetLtmCfg(FH_UINT32 u32DevId, &mode,&level);
 *
 * @param[out]  mode
 * @param[out]  level
 * @return      0 或 -1
 */
FH_SINT32 FHAdv_Isp_GetLtmCfg(FH_UINT32 u32DevId, FH_UINT32 *mode, FH_UINT32 *level);

/**
 *  @brief      设置亮度等级
 *
 * @param[in]   value    范围0-255, 128表示采用默认值,即FHAdv_Isp_Init获取得到的值
 * @return      0 或 -1
 */
FH_SINT32 FHAdv_Isp_SetBrightness(FH_UINT32 u32DevId, FH_UINT32 value);

/**
 *  @brief      获取当前亮度等级
 *
 * @param[out]  pValue    范围0-255, 由于量化误差,获取值与输入值之间可能会有差异
 * @return      0 或 -1
 */
FH_SINT32 FHAdv_Isp_GetBrightness(FH_UINT32 u32DevId, FH_UINT32 *pValue);

/**
 *  @brief      设置对比度等级
 *
 * @param[in]   mode    0:手动模式，1:gainmapping模式，根据mapping选择并可以手动做整体mapping调整
 * @param[in]   value   范围0-255, 128表示采用默认值,即FHAdv_Isp_Init获取得到的值
 * @return      0 或 小于0的错误值
 */
FH_SINT32 FHAdv_Isp_SetContrast(FH_UINT32 u32DevId, FH_UINT32 mode, FH_UINT32 value);

/**
 *  @brief      获取当前对比度等级
 *
 * @param[out]  mode
 * @param[out]  pValue  范围0-255, 由于量化误差,获取值与输入值之间可能会有差异
 * @return      0 或 小于0的错误值
 */
FH_SINT32 FHAdv_Isp_GetContrast(FH_UINT32 u32DevId, FH_UINT32 *mode, FH_UINT32 *pValue);

/**
 *  @brief      设置饱和度等级
 *
 * @param[in]   mode    0:手动模式，1:gainmapping模式，根据mapping选择并可以手动做整体mapping调整
 * @param[in]   value   范围0-255 128表示采用默认值,即FHAdv_Isp_Init获取得到的值
 * @return      0 或 小于0的错误值
 */
FH_SINT32 FHAdv_Isp_SetSaturation(FH_UINT32 u32DevId, FH_UINT32 mode, FH_UINT32 value);

/**
 *  @brief      获取当前饱和度等级
 *
 * @param[out]  mode
 * @param[out]  pValue  范围0-255, 由于量化误差,获取值与输入值之间可能会有差异
 * @return      0 或 小于0的错误值
 */
FH_SINT32 FHAdv_Isp_GetSaturation(FH_UINT32 u32DevId, FH_UINT32 *mode, FH_UINT32 *pValue);

/**
 *  @brief      设置锐度
 *
 * @param[in]   mode    0:手动模式，1:gainmapping模式，根据mapping选择并可以手动做整体mapping调整
 * @param[in]   value   范围0~255 128表示采用默认值,即FHAdv_Isp_Init获取得到的值
 * @return      0 或 小于0的错误值
 */
FH_SINT32 FHAdv_Isp_SetSharpeness(FH_UINT32 u32DevId, FH_UINT32 mode, FH_UINT32 value);

/**
 *  @brief      获取当前锐度
 *
 * @param[out]  mode
 * @param[out]  pValue  范围0-255, 由于量化误差,获取值与输入值之间可能会有差异
 * @return      0 或 小于0的错误值
 */
FH_SINT32 FHAdv_Isp_GetSharpeness(FH_UINT32 u32DevId, FH_UINT32 *mode, FH_UINT32 *pValue);

/**
 *  @brief      设置色度
 *
 *              暂未实现
 *
 * @param[in]   value
 * @return      0
 */
FH_SINT32 FHAdv_Isp_SetChroma(FH_UINT32 u32DevId, FH_UINT32 value);

/**
 *  @brief      获取色度
 *
 *              暂未实现
 *
 * @param[out]  pValue
 * @return      0
 */
FH_SINT32 FHAdv_Isp_GetChroma(FH_UINT32 u32DevId, FH_UINT32 *pValue);

/**
 *  @brief      设置镜像和翻转
 *
 * @param[in]   mirror    0:恢复镜像，1:使能镜像
 * @param[in]   flip      0:恢复翻转，1:使能翻转
 * @return      0
 */
FH_SINT32 FHAdv_Isp_SetMirrorAndflip(FH_UINT32 u32DevId, FH_UINT32 grpidx, FH_UINT32 mirror, FH_UINT32 flip);

/**
 *  @brief      获取镜像和翻转的状态
 *
 * @param[out]  pMirror
 * @param[out]  pFlip
 * @return      0
 */
FH_SINT32 FHAdv_Isp_GetMirrorAndflip(FH_UINT32 u32DevId, FH_UINT32 *pMirror, FH_UINT32 *pFlip);

/**
 *  @brief      设置颜色模式
 *
 * @param[in]   mode    0:饱和度为0，1:使用默认饱和度
 * @return      0 或 -1
 */
FH_SINT32 FHAdv_Isp_SetColorMode(FH_UINT32 u32DevId, FH_UINT32 mode);

/**
 *  @brief      获取颜色模式
 *
 * @param[out]  pMode  0:黑白模式, 1:彩色模式
 * @return      0 或 -1
 */
FH_SINT32 FHAdv_Isp_GetColorMode(FH_UINT32 u32DevId, FH_UINT32 *pMode);

/********
 * 获取打印库版本信息
 ********/
FH_CHAR* FH_ADV_ISP_Version(FH_UINT32 print_enable);

/*@} end of group Video_ISP */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif