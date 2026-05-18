#ifndef __FH_VOU_MPIPARA_H__
#define __FH_VOU_MPIPARA_H__
/**|VOU|**/

#include "types/type_def.h"
#include "types/bufCtrl.h"
#include "fh_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */
#pragma pack(4)

typedef struct
{
	FH_PHYADDR YADDR;     // 亮度物理地址 | [ ]
	FH_PHYADDR CADDR;     // 色度物理地址 | [ ]
	FH_UINT64 time_stamp; // 时间戳  | [ ]
	FH_UINT32 width;      // 宽度，用于和vou的配置进行对比，确认图像幅面与配置相符合 | []
	FH_UINT32 height;     // 高度，用于和vou的配置进行对比，确认图像幅面与配置相符合 | []
	FH_UINT32 pool_id;    // vb pool id(非VB模式建议配置为-1UL) | []
} FH_VOU_FRAME;

typedef struct
{
	FH_UINT32 input_width;  //  | [ ]
	FH_UINT32 input_height; //  | [ ]

	FH_VPU_VO_MODE src_format; // 输入图像格式 | [ ]

	FH_UINT32 output_width; //  | [ ]
	FH_UINT32 output_height;//  | [ ]
	FH_UINT32 crop_start_x; //  | [ ]
	FH_UINT32 crop_start_y; //  | [ ]
	FH_UINT8 crop_en;       //  | [ ]
	FH_UINT32 fps;			// 定点小数，8.24 | [ ]
} FH_VOU_DATA_INFO;


typedef struct
{
	FH_VOU_DATA_INFO pic_info;  // 输入输出信息  | [ ]
	MEM_DESC  ave_string;  // ave的配置串指针 | [ ]
	FH_UINT32 test_mode;  // vou的测试模式使能 | [ ]
	FH_UINT32 uv_mode;  // 设置uv输出顺序，0:u在低位，1:v在低位 | [ ]
	FH_UINT32 ave_out_mode;  // 设置ave的输出类型，CVBS = 0, TVI = 1, AHD = 2, CVI = 3, DIGIT = 0x10 | [ ]
} FH_VOU_INIT_PARAM;
#pragma pack()
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
