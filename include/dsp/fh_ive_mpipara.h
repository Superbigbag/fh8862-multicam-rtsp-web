#ifndef __FH_IVE_MPIPARA_H__
#define __FH_IVE_MPIPARA_H__
/**|IVE|**/

#include "types/type_def.h"
#include "fh_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */
#pragma pack(4)

typedef struct {
	FH_UINT64 handle_idx;      // 任务标记 | [ ]
	FH_UINT32 module_idx;      // 硬件模块标记 | [ ]
} IVE_HANDLE;

typedef struct {
	FH_MEM_INFO  data_addr;    // 图像数据地址 | [ ]
	FH_UINT32    data_stride;  // 图像数据跨度 | [ ]
	FH_UINT32    pool_id;      // vb pool id(非VB模式建议配置为-1UL) | []
} IVE_IMAGE;

typedef enum
{
	FH_IVE_COMP_Y   = 0, //Y | [ ]
	FH_IVE_COMP_U   = 1, //U/UV | [ ]
	FH_IVE_COMP_V   = 2, //V | [ ]
}FH_IVE_COMP;

typedef enum
{
	FH_IVE_WIDTH_1BIT    = 0, // 1BIT  | [ ]
	FH_IVE_WIDTH_2BIT    = 1, // 2BIT  | [ ]
	FH_IVE_WIDTH_4BIT    = 2, // 4BIT  | [ ]
	FH_IVE_WIDTH_8BIT    = 3, // 8BIT  | [ ]
	FH_IVE_WIDTH_16BIT   = 4, // 16BIT | [ ]
	FH_IVE_WIDTH_32BIT   = 5, // 32BIT | [ ]
}FH_IVE_PIX_WIDTH;


typedef struct
{
	FH_SIZE          src_size;      // 输入图像幅面 | [ ]
	FH_SIZE          dst_size;      // 输出图像幅面 | [ ]
	IVE_IMAGE        src_addr;      // 输入图像地址 | [ ]
	IVE_IMAGE        dst_addr;      // 输出图像地址 | [ ]
	IVE_IMAGE        src_addr_u;    // 输入图像色度地址 | [ ]
	IVE_IMAGE        dst_addr_u;    // 输出图像色度地址 | [ ]
	FH_UINT8         data_clip_min; // 输出数据最小值限制 | [0-255]
	FH_UINT8         data_clip_max; // 输出数据最大值限制 | [0-255]
	FH_VPU_VO_MODE   in_format;     // 输入数据格式 | [ ]
	FH_SINT32        cropen;        // 扣图使能 | [ ]
	FH_AREA          crop;          // 扣图配置 | [ ]
} IVE_V3_RESIZE_CTRL;

typedef struct
{
	FH_SIZE      image_size;    // 输入图像幅面 | [ ]
	FH_UINT16    gau_coeff0;    // 高斯滤波器系数 | [0-511]
	FH_UINT8     gau_coeff1;    // 高斯滤波器系数 | [0-63]
	FH_UINT8     gau_coeff2;    // 高斯滤波器系数 | [0-63]
	FH_UINT8     gau_coeff3;    // 高斯滤波器系数 | [0-63]
	FH_UINT8     gau_coeff4;    // 高斯滤波器系数 | [0-63]
	FH_UINT8     gau_coeff5;    // 高斯滤波器系数 | [0-63]
	FH_UINT8     data_clip_min; // 输出数据最小值限制 | [0-255]
	FH_UINT8     data_clip_max; // 输出数据最大值限制 | [0-255]
	IVE_IMAGE    src_addr;      // 输入图像地址 | [ ]
	IVE_IMAGE    dst_addr;      // 输出图像地址 | [ ]
} IVE_V3_FILTER_CTRL;

typedef struct
{
	IVE_IMAGE        src_data;      // 输入图像地址 | [ ]
	IVE_IMAGE        dst_data;      // 输出图像地址 | [ ]
	FH_VPU_VO_MODE   srcformat;     // 输入格式 | [ ]
	FH_IVE_COMP      srccomp;       // Y/U/V | [0-2]
	FH_IVE_PIX_WIDTH srcwidth;      // 输入位宽 | [0-5]
	FH_ROTATE_OPS    rotate;        // 旋转角度 | [0-3]
	FH_SIZE          opsize;        // 待处理幅面 | [ ]
	FH_SIZE          srcsize;       // 输入图像幅面 | [ ]
	FH_SIZE          dstsize;       // 输出图像幅面 | [ ]
	FH_POINT         src_start;     // 输入起点坐标 | [ ]
	FH_POINT         dst_start;     // 输出起点坐标 | [ ]
} IVE_V3_ROT_CTRL;

typedef struct
{
	IVE_IMAGE    src_addr;          // 输入图像地址 | [ ]
	IVE_IMAGE    dst_addr;          // 输出图像地址 | [ ]
	FH_SIZE      src_size;          // 输入图像幅面 | [ ]
	FH_SIZE      dst_size;          // 输出图像幅面 | [ ]
	FH_UINT8     data_clip_min;     // 输出数据最小值限制 | [0-255]
	FH_UINT8     data_clip_max;     // 输出数据最大值限制 | [0-255]
	FH_UINT32    type;              // 输入格式 0:Y 1:ARGB 2:NV16 3:NV12| [0-3]
	FH_SINT32    hinitphase;        // 待补充 | [ ]
	FH_SINT32    hinitoffset;       // 待补充 | [ ]
	FH_SINT32    vinitphase;        // 待补充 | [ ]
	FH_UINT32    outwidth;          // 待补充 | [ ]
	FH_UINT32    outheigh;          // 待补充 | [ ]
	FH_SINT32    hinitphase_shear;  // 待补充 | [ ]
	FH_SINT32    vinitphase_shear;  // 待补充 | [ ]
	FH_SINT32    hstep_shear;       // 待补充 | [ ]
	FH_UINT32    hstep;             // 待补充 | [ ]
	FH_UINT32    vstep;             // 待补充 | [ ]
	FH_SINT32    hinitphase1;       // 待补充 | [ ]
	FH_SINT32    hinitoffset1;      // 待补充 | [ ]
	FH_SINT32    vinitphase1;       // 待补充 | [ ]
	FH_SINT32    hinitphase_shear1; // 待补充 | [ ]
	FH_SINT32    vinitphase_shear1; // 待补充 | [ ]
	FH_SINT32    hstep_shear1;      // 待补充 | [ ]
	FH_UINT32    hstep1;            // 待补充 | [ ]
	FH_UINT32    vstep1;            // 待补充 | [ ]
} IVE_V3_SHEAR_CTRL;

#pragma pack()
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

