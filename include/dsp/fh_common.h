#ifndef __FH_COMMON_H__
#define __FH_COMMON_H__
#include "types/type_def.h"
/**|System Control|**/

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */
#pragma pack(4)

// #define API_PRT
#ifdef API_PRT
#define API_DEBUG(...) do{\
	fh_printf( "%s %d: ", __func__,  __LINE__);\
	fh_printf(__VA_ARGS__);\
	}while(0)
#define API_NOTICE(...) do{\
	fh_printf( "%s %d: ", __func__,  __LINE__);\
	fh_printf(__VA_ARGS__);\
	}while(0)
#else
#define API_DEBUG(...)
#define API_NOTICE(...) do{\
	fh_printf( "%s %d: ", __func__,  __LINE__);\
	fh_printf(__VA_ARGS__);\
	}while(0)
#endif

#define RETURN_NULL                          (0)
#define RETURN_OK                            (0)
#define DEFALT_ALIGN                         (16)
#define MALLOCED_MEM_BASE_DSP                (1)
#define MALLOCED_MEM_VPUPKG                  (0)

/*芯片名称,0代表未知芯片*/
#define FH8632                               (0x863200A1)
#define FH8632v2                             (0x863200A2)
#define FH8620H                              (0x863200B1)
#define FH8856                               (0x885600A1)
#define FH8852                               (0x885600B1)
#define FH8626V100                           (0x8626A100)
#define FH8852V200                           (0x8852A200)
#define FH8856V200                           (0x8856A200)
#define FH8858V200                           (0x8858A200)
#define FH8856V201                           (0x8856A201)
#define FH8858V201                           (0x8858A201)
#define FH8852V210                           (0x8852A210)
#define FH8856V210                           (0x8856A210)
#define FH8858V210                           (0x8858A210)
#define FH8652                               (0x8652A100)
#define FH8656                               (0x8656A100)
#define FH8658                               (0x8658A100)
#define FH8852V201                           (0x8852A201)
#define FH8852V202                           (0x8852A202)
#define FH8636                               (0x8636A100)
#define FH8898                               (0x8898A100)
#define FH8896                               (0x8896A100)
#define FH8210                               (0x8210A100)
#define FH8862                               (0x8862A100)

typedef enum
{
	FH_RO_OPS_0     = 0,//旋转0度 | [ ]
	FH_RO_OPS_90    = 1,//旋转90度 | [ ]
	FH_RO_OPS_180   = 2,//旋转180度 | [ ]
	FH_RO_OPS_270   = 3,//旋转270度 | [ ]
	FH_ROTATE_OPS_DUMMY= 0xffffffff,
}FH_ROTATE_OPS;

typedef enum
{
	VPU_VOMODE_BLK          = 0,  // 宏块格式 | [ ]
	VPU_VOMODE_SCAN         = 1,  // 光栅格式(NV12) | [ ]
	VPU_VOMODE_TILE192      = 2,  // Tile压缩192Byte | [ ]
	VPU_VOMODE_TILE224      = 3,  // Tile压缩224Byte | [ ]
	VPU_VOMODE_TILE256      = 4,  // Tile压缩256Byte | [ ]
	VPU_VOMODE_RGB888       = 5,  // RGB888 | [ ]
	VPU_VOMODE_ARGB888      = 5,  // ARGB888 | [ ]
	VPU_VOMODE_YUYV         = 6,  // YUYV(YUV2) | [ ]
	VPU_VOMODE_RRGGBB       = 7,  // RRGGBB | [ ]
	VPU_VOMODE_NV16         = 10, // NV16 | [ ]
	VPU_VOMODE_Y            = 11, // Y | [ ]
	VPU_VOMODE_UYVY         = 12, // UYVY | [ ]
	VPU_VOMODE_YU12         = 13, // YU12 | [ ]
	VPU_VOMODE_RGB          = 14, // RGB  | [ ]
	VPU_VOMODE_BAYER_RAW    = 15, // BAYER_RAW | [ ]
	VPU_VOMODE_10BIT_NV12   = 16, // yuv420 10bit | [ ]
	VPU_VOMODE_10BIT_NV16   = 17, // yuv422 10bit | [ ]
	VPU_VOMODE_BUTT            ,
	FH_VPU_VO_MODE_DUMMY    = 0xffffffff,
}FH_VPU_VO_MODE;

typedef enum
{
	FH_OBJ_NONE    = 0, // 空 | [ ]
	FH_OBJ_VICAP   = 1, // VICAP | [ ]
	FH_OBJ_ISP     = 2, // ISP | [ ]
	FH_OBJ_VPU_VI  = 3, // VPU输入 | [ ]
	FH_OBJ_VPU_VO  = 4, // VPU通道输出 | [ ]
	FH_OBJ_VPU_BGM = 5, // VPU-BGMY输出 | [ ]
	FH_OBJ_ENC     = 6, // H264＆H265视频编码 | [ ]
	FH_OBJ_JPEG    = 7, // JPEG编码 | [ ]
	FH_OBJ_BGM     = 8, // BGM | [ ]
	FH_OBJ_NN      = 9, // NN | [ ]
	FH_OBJ_VOU     = 10,// VOU | [ ]
	FH_OBJ_VPPU    = 11,// VPPU | [ ]
	FH_OBJ_VDEC    = 12,// H264＆H265视频解码 | [ ]
	FH_OBJ_JPEGD   = 13,// JPEG解码 | [ ]
	FH_OBJ_MAX_NUM,
	FH_BIND_OBJ_ID_DUMMY=0xffffffff,
}FH_BIND_OBJ_ID;

typedef struct fhVERSION_INFO_
{
	FH_UINT32           build_date;  // 编译时间  | [ ]
	FH_UINT32           sw_version;  // 软件版本号  | [ ]
	FH_UINT32           hw_version;  // 硬件驱动版本号  | [ ]
}FH_VERSION_INFO;

typedef struct fhPOINT_
{
	FH_UINT32           u32X;        // 水平坐标 | [ ]
	FH_UINT32           u32Y;        // 垂直坐标 | [ ]
}FH_POINT;

typedef struct fhSIZE_S
{
	FH_UINT32           u32Width;    // 宽度 | [ ]
	FH_UINT32           u32Height;   // 高度 | [ ]
} FH_SIZE;

typedef struct fhRECT_S
{
	FH_UINT32           u32X;        // 起始点水平坐标 | [ ]
	FH_UINT32           u32Y;        // 起始点垂直坐标 | [ ]
	FH_UINT32           u32Width;    // 区域宽度 | [ ]
	FH_UINT32           u32Height;   // 区域高度 | [ ]
}FH_AREA;

typedef struct
{
	FH_ADDR             addr;        // 虚拟地址 | [ ]
	FH_UINT32           size;        // 内存大小 | [ ]
}FH_ADDR_INFO;

typedef struct
{
	FH_PHYADDR          base;        // 物理地址 | [ ]
	FH_VOID *           vbase;       // 虚拟地址 | [ ]
	FH_UINT32           size;        // 内存大小 | [ ]
}FH_MEM_INFO;

typedef struct
{
	FH_UINT16           frame_count; // 帧数 | [ ]
	FH_UINT16           frame_time;  // 统计时间(s) | [ ]
} FH_FRAMERATE;

typedef struct
{
	FH_UINT32           y;           // 亮度 | [ ]
	FH_UINT32           cb;          // 蓝色浓度偏移量 | [ ]
	FH_UINT32           cr;          // 红色浓度偏移量 | [ ]
	FH_UINT32           alpha;       // 透明度 | [ ]
} FH_YC_COLOR;

typedef struct
{
	FH_BIND_OBJ_ID      obj_id;         // 模块号 | [ ]
	FH_UINT32           dev_id;         // 设备号 | [ ]
	FH_UINT32           chn_id;         // 通道号 | [ ]
}FH_BIND_INFO;

typedef struct
{
	FH_MEM_INFO data;                     // 数据地址 | [ ]
	FH_UINT32   stride;                   // 数据stride | [ ]
} FH_FRM_BUF;

typedef struct
{
	FH_FRM_BUF luma;                      // 亮度数据地址 | [ ]
	FH_FRM_BUF chroma;                    // 色度数据地址 | [ ]
} FH_FRM_YUV_2P;

typedef struct
{
	FH_FRM_BUF r_data;                    // R数据地址 | [ ]
	FH_FRM_BUF g_data;                    // G数据地址 | [ ]
	FH_FRM_BUF b_data;                    // B数据地址 | [ ]
} FH_FRM_RRGGBB;

typedef struct
{
	FH_FRM_BUF st_data;                    // 短帧数据 | [ ]
	FH_FRM_BUF lf_data;                    // 长帧数据 | [ ]
	FH_UINT32  sf_crc;                     // 短帧校验值　| [ ]
	FH_UINT32  lf_crc;                     // 长帧校验值　| [ ]
} FH_FRM_RAW;

typedef struct
{
	FH_VPU_VO_MODE         data_format;  // 图像格式 | [ ]
	FH_SIZE                size;         // 图像尺寸 | [ ]
	FH_UINT64              time_stamp;   // 时间戳 | [ ]
	FH_UINT64              frame_id;     // 帧号 | [ ]
	FH_UINT32              pool_id;      // vb pool id(非VB模式建议配置为-1UL) | []
	FH_BIND_INFO           frame_src;    // 数据来源 | []
	FH_UINT64              private[4];   // 私有数据 | []
	FH_SIZE                size_usr;     // 用户配置尺寸(未做对齐) | [ ]
	union {
		FH_FRM_YUV_2P      frm_blk;      // block格式输出信息 | [ ]
		FH_FRM_YUV_2P      frm_scan;     // scan(nv12)格式输出信息 | [ ]
		FH_FRM_BUF         frm_tile192;  // tile192格式输出信息 | [ ]
		FH_FRM_BUF         frm_tile224;  // tile224格式输出信息 | [ ]
		FH_FRM_BUF         frm_tile256;  // tile256格式输出信息 | [ ]
		FH_FRM_BUF         frm_argb8888; // argb8888格式输出信息 | [ ]
		FH_FRM_BUF         frm_yuyv;     // yuyv格式输出信息 | [ ]
		FH_FRM_RRGGBB      frm_rrggbb;   // rrggbb格式输出信息 | [ ]
		FH_FRM_YUV_2P      frm_nv16;     // nv16格式输出信息 | [ ]
		FH_FRM_BUF         frm_y;        // y格式输出信息 | [ ]
		FH_FRM_BUF         frm_uyvy;     // uyvy格式输出信息 | [ ]
		FH_FRM_YUV_2P      frm_yu12;     // yu12格式输出信息 | [ ]
		FH_FRM_BUF         frm_rgb;      // rgb格式输出信息 | [ ]
		FH_FRM_RAW         frm_raw;      // raw格式输出信息 | [ ]
		FH_FRM_YUV_2P      frm_nv12p10;  // nv12 10bit格式输出信息 | [ ]
		FH_FRM_YUV_2P      frm_nv16p10;  // nv16 10bit格式输出信息 | [ ]
	};
}FH_VIDEO_FRAME;

typedef struct
{
	FH_UINT32 avgTime;
	FH_UINT32 maxTime;
	FH_UINT32 avgCycle;
	FH_UINT32 maxCycle;
	FH_UINT32 win_size;
	FH_UINT64 time_stamp;
}FH_HW_AVG_TIME;

#pragma pack()
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _FH_COMMON_H_ */
