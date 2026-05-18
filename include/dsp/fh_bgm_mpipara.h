#ifndef __FH_BGM_MPIPARA_H__
#define __FH_BGM_MPIPARA_H__
/**|BGM|**/

#include "types/type_def.h"
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
	FH_SIZE         size;       // 图像幅面  | [ ]
	FH_PHYADDR      YADDR;      // 亮度物理地址 | [ ]
	FH_PHYADDR      CADDR;      // 色度物理地址,参数无效 | [ ]
	FH_UINT64       time_stamp; // 时间戳  | [ ]
	FH_UINT64       frame_id;   // 帧号  | [ ]
	FH_UINT32       pool_id;    // vb pool id(非VB模式建议配置为-1UL) | []
}FH_BGM_FRAME;

typedef struct
{
	FH_SIZE         size;                   //幅面大小 | [ ]
	FH_ADDR_INFO    confidence_level;       //置信度信息 | [ ]
	FH_ADDR_INFO    blob_list;              //联通域目标数据,需开启blob_en否则无效 | []
	FH_ADDR_INFO    fg_data;                //前景数据,需开启fg_en否则无效 | []
	FH_UINT32       background_change_flag; //场景切换标识 | [ ]
	FH_UINT32       static_frm_flag;        //背景更新标识 | [ ]
	FH_UINT32       foreground_point_num;   //前景点数 | [ ]
	FH_UINT32       total_pixel_num;        //总像素数 | [ ]
	FH_UINT64       time_stamp;             //时间戳 | [ ]
	FH_UINT64       frame_id;               //帧号 | [ ]
}FH_BGM_SW_STATUS;

#define MAX_TH_NUM 5
typedef struct
{
	FH_UINT32 GOP_TH_NUM;            // GOP门限数量 | [0-5]
	FH_UINT32 TH_VAL[MAX_TH_NUM];    // 门限值,单位百分比,从小到大,代表从安静到运动 | [0-100]
	FH_UINT32 MIN_GOP[MAX_TH_NUM+1]; // 小于对应门限时最小的GOP长度  | [ ]
}FH_GOP_TH;

/*高级参数配置,不建议用户自行配置此参数*/

typedef struct
{
	FH_UINT32       foreground_point_num;
	FH_UINT32       frm_diffa_point_num;
	FH_UINT32       frm_diffb_point_num;
	FH_UINT32       frm_diffc_point_num;
	FH_ADDR_INFO    fg_a_point_addr;
	FH_ADDR_INFO    fg_b_point_addr;
	FH_ADDR_INFO    frm_diff_a_addr;
	FH_ADDR_INFO    frm_diff_b_addr;
	FH_ADDR_INFO    run_num_addr;
	FH_ADDR_INFO    run0_pos_addr;
	FH_UINT64       time_stamp;
	FH_UINT64       frame_id;
}FH_BGM_HW_STATUS;

typedef struct
{
	FH_UINT16 refresh_rate;
	FH_UINT8  precision;
	FH_UINT8  variance_gain;
	FH_UINT8  variance_min;
	FH_UINT8  variance_max;
}FH_SINGLE_GAU_CFG;

typedef struct
{
	FH_UINT16 refresh_rate;
	FH_UINT16 refresh_weight_rate;
	FH_UINT8  precision;
	FH_UINT8  variance_gain;
	FH_UINT8  variance_init;
	FH_UINT8  variance_min;
	FH_UINT8  variance_max;
	FH_UINT8  bg_weight_th;
	FH_UINT8  bg_time_th;
	FH_UINT8  sel_mode;
	FH_UINT8  time_update_en;
}FH_MULTI_GAU_CFG;

typedef enum
{
	FH_MULTI_GAU_FG_A     = 0,
	FH_MULTI_GAU_FG_B     = 1,
	FH_FRM_DIFF_PRE       = 2,
	FH_LONG_TERM_FG_A     = 3,
	FH_LONG_TERM_FG_B     = 4,
	FH_CON_EXPA_IDX_DUMMY = 0xffffffff,
}FH_CON_EXPA_IDX;

typedef struct
{
	FH_UINT32 win_mask;
	FH_UINT8  expa_th;
	FH_UINT8  center_en;
}FH_CON_EXPA_CFG;

typedef struct
{
	FH_UINT8 diff_th0;
	FH_UINT8 diff_th1;
	FH_UINT8 longTermFgTh0;
	FH_UINT8 longTermFgTh1;
}FH_FRM_DIFF_CFG;

#pragma pack()
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

