/**
 * 软件驱动能力集定义,供应用参考和简化多平台兼容逻辑.
 * API接口不会使用到此头文件,无强制依赖要求.
 */
#ifndef __FH_MEDIA_H__
#define __FH_MEDIA_H__

/** VPU 驱动能力集**/
// VPU 最大分时复用组数量
#define FHVPU_MAX_GRP_NUM    (8)
// VPU 最大物理通道数量
#define FHVPU_MAX_PHYCHN_NUM (5)
// VPU 最大扩展通道数量
#define FHVPU_MAX_EXTCHN_NUM (4)
// VPU RGB输出通道号
#define FHVPU_AI_CHN_ID      (3)
// VPU 辅助通道号
#define FHVPU_BRANCH_CHN_ID  (4)

/** VENC 驱动能力集**/
// VENC 最大通道数(注意默认开启数量非最大,参考开发手册maxencnum命令)
#define FHVENC_MAX_CHN_NUM   (32)

/** BGM 驱动能力集**/
// BGM 最大通道数
#define FHBGM_MAX_CHN_NUM    (4)

/** NNA 驱动能力集**/
// NNA 最大通道数
#define FHNNA_MAX_CHN_NUM    (8)

#endif
