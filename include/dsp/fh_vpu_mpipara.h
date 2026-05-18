#ifndef __FH_VPU_MPIPARA_H__
#define __FH_VPU_MPIPARA_H__
/**|VPU|**/
#include "types/type_def.h"
#include "fh_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */
#pragma pack(4)

#define MAX_MASK_AREA                        (8)

typedef enum
{
	VPU_MODE_ISP            = 0, // ISP输入模式 | [ ]
	VPU_MODE_MEM            = 1, // 内存输入模式 | [ ]
	VPU_MODE_OFFLINE_VPU    = 1, // 内存输入模式(VPU读入数据) | [ ]
	VPU_MODE_OFFLINE_2DLUT  = 2, // 内存输入模式(2DLUT读入数据) | [ ]
	VPU_MODE_ONLINE_2DLUT   = 3, // ISP输入模式(2DLUT读入ISP数据) | [ ]
	FH_VPU_VI_MODE_DUMMY    = 0xffffffff,
}FH_VPU_VI_MODE;

///VPU 输出模式
typedef enum
{
	PIXEL_FORMAT_NOCHROME   = 0, // 亮度 | [ ]
	PIXEL_FORMAT_420        = 1, // YUV420 | [ ]
	PIXEL_FORMAT_422        = 2, // YUV422 | [ ]
	PIXEL_FORMAT_444        = 3, // YUV444 | [ ]
	PIXEL_FORMAT_RGB888     = 4, // RGB888 | [ ]
	FH_VPU_PIXELFORMAT_DUMMY= 0xffffffff,
}FH_VPU_PIXELFORMAT;

typedef enum
{
	VPU_CROP_SCALER = 0, //  | [ ]
	VPU_CROP_VI     = 1, // FH889x不支持 | [ ]
	VPU_CROP_CHN    = 2, // FH889x不支持 | [ ]
}FH_VPU_CROP_SEL;

typedef struct
{
	FH_UINT32               crop_en;                     //　裁剪使能 | [0-1]
	FH_AREA                 vpu_crop_area;               //　裁剪区域 | [ ]
}FH_VPU_CROP;

typedef struct
{
	FH_SIZE                 vi_size;      // 输入幅面 | [16-最大处理幅面]
	FH_VPU_CROP             crop_area;    // 通道裁剪区域(FH889x不支持) | [ ]
}FH_VPU_SIZE;

typedef struct
{
	FH_SIZE                 vpu_chn_size; // 通道输出幅面 | [16-最大处理幅面]
	FH_VPU_CROP             crop_area;    // 通道裁剪区域(FH889x不支持) | [ ]
	FH_UINT32               stride;       // 通道输出stride(配置为0时为通道幅面宽,以pixel为单位) | [ ]
	FH_UINT32               offset;       // 通道输出地址偏移(以pixel为单位) | [ ]
	FH_UINT32               depth;        // 通道输出队列深度(需要小于通道buffer个数) | [1-6]
}FH_VPU_CHN_CONFIG;

typedef struct
{
	FH_UINT32               bind_chan;   // 绑定通道 | [ ]
	FH_VPU_CHN_CONFIG       chn_info;    // 通道信息 | [ ]
}FH_VPU_EXT_CHN_CONFIG;

typedef struct
{
	FH_SIZE                 pic_size;     // 图像幅面 | [ ]
	FH_PHYADDR              yluma;        // 图像亮度物理地址 | [ ]
	FH_PHYADDR              chroma;       // 图像色度物理地址 | [ ]
	FH_UINT32               ystride;      // 图像亮度行偏移 | [ ]
	FH_UINT32               cstride;      // 图像色度行偏移 | [ ]
	FH_UINT64               time_stamp;   // 时间戳 | [ ]
	FH_VPU_VO_MODE          data_format;  // DDR输入格式,支持格式参考开发手册 | [ ]
	FH_UINT32               work_mode;    // 工作模式 | [ ]
	FH_UINT32               pool_id;      // vb pool id(非VB模式建议配置为-1UL) | []
	FH_UINT64               frame_id;     // 帧号 | [ ]
	FH_UINT64               private[4];   // 私有数据 | []
}FH_VPU_USER_PIC;

typedef struct
{
	FH_MEM_INFO data;                     // 数据地址 | [ ]
	FH_UINT32   stride;                   // 数据stride | [ ]
} FH_VPU_ONEBUF_DATA;

typedef struct
{
	FH_VPU_ONEBUF_DATA luma;              // 亮度数据地址 | [ ]
	FH_VPU_ONEBUF_DATA chroma;            // 色度数据地址 | [ ]
} FH_VPU_YC_DATA;

typedef struct
{
	FH_VPU_ONEBUF_DATA r_data;            // R数据地址 | [ ]
	FH_VPU_ONEBUF_DATA g_data;            // G数据地址 | [ ]
	FH_VPU_ONEBUF_DATA b_data;            // B数据地址 | [ ]
} FH_VPU_RRGGBB_DATA;

typedef struct
{
	FH_VPU_VO_MODE          data_format;  // 图像格式 | [ ]
	FH_SIZE                 size;         // 图像尺寸 | [ ]
	FH_SIZE                 size_usr;     // 用户配置尺寸(未做对齐) | [ ]
	FH_UINT64               time_stamp;   // 时间戳 | [ ]
	FH_UINT64               frame_id;     // 帧号 | [ ]
	FH_UINT32               pool_id;      // vb pool id(非VB模式建议配置为-1UL) | []
	FH_UINT64               private[4];   // 私有数据 | [ ]
	union
	{
		FH_VPU_YC_DATA      frm_blk;      // block格式输出信息 | [ ]
		FH_VPU_YC_DATA      frm_scan;     // scan(nv12)格式输出信息 | [ ]
		FH_VPU_YC_DATA      frm_nv16;     // nv16格式输出信息 | [ ]
		FH_VPU_ONEBUF_DATA  frm_tile192;  // tile192格式输出信息 | [ ]
		FH_VPU_ONEBUF_DATA  frm_tile224;  // tile224格式输出信息 | [ ]
		FH_VPU_ONEBUF_DATA  frm_tile256;  // tile256格式输出信息 | [ ]
		FH_VPU_ONEBUF_DATA  frm_rgb888;   // rgb888格式输出信息 | [ ]
		FH_VPU_ONEBUF_DATA  frm_yuyv;     // yuyv格式输出信息 | [ ]
		FH_VPU_ONEBUF_DATA  frm_y;        // y格式输出信息 | [ ]
		FH_VPU_RRGGBB_DATA  frm_rrggbb;   // rrggbb格式输出信息 | [ ]
	};
}FH_VPU_STREAM_ADV;

typedef struct
{
	FH_SIZE                 pic;          // 幅面 | [ ]
	FH_MEM_INFO             data;         // 数据地址信息 | [ ]
	FH_UINT32               stride;       // 行偏移 | [ ]
	FH_UINT64               time_stamp;   // 时间戳 | [ ]
	FH_UINT64               frame_id;     // 帧号 | [ ]
}FH_PIC_DATA;

typedef struct
{
	FH_UINT32              masaic_enable; // 隐私屏蔽形式 0:单色 1:马赛克 | [0-1]
	FH_UINT32              masaic_size;   // 马赛克单块大小 0:16x16,1:32x32,2:64x64(FH889x不支持64x64) | [0-2]
}FH_MASK_MASAIC;

typedef struct
{
	FH_BOOL                 mask_enable[MAX_MASK_AREA]; // 隐私屏蔽使能 | [0-1]
	FH_AREA                 area_value[MAX_MASK_AREA];  // 隐私屏蔽区域 | [ ]
	FH_UINT32               color;                      // 隐私显示颜色(格式AYCbCr,Alpha无效) | [ ]
	FH_MASK_MASAIC          masaic;                     // 马赛克属性 | [ ]
}FH_VPU_MASK;

typedef struct
{
	FH_UINT32               magic_color_en; // 是否使用magic_color,仅在16bit模式下有效 | [0-1]
	FH_UINT32               magic_color;    // magic_color的值,16bit,此颜色将作为透明 | [0-0xffff]
	FH_UINT32               global_alpha_en;// 全局透明度使能 | [0-1]
	FH_UINT32               global_alpha;   // 全局透明度 | [0-255]
	FH_UINT32               rgb16_type;     // 位宽16模式时颜色格式:1:ARGB0565,2:ARGB1555,3:ARGB4444 | [1-3]
	FH_UINT32               extmode;        // 0为LSB填0，1为MSB复制到LSB | [0-1]
	FH_UINT32               dtvmode;        // 0为SDTV模式，1为HDTV模式 | [0-1]
	FH_UINT32               rgbmode;        // 0为stdio RGB，1为computer RGB | [0-1]
	FH_SIZE                 logo_size;      // 图像叠加覆盖大小 | [ ]
}FH_LOGOV2_CFG;

typedef struct
{
	FH_UINT32               logo_enable;   // 图片叠加使能 | [ ]
	FH_UINT32               logo_idx;      // 图像叠加索引号 | [见芯片能力定义]
	FH_UINT32               logo_pixdepth; // 图片像素位宽 | [见芯片能力定义]
	FH_PHYADDR              logo_addr;     // 图片叠加数据的物理地址 | [ ]
	FH_LOGOV2_CFG           logo_cfg;      // 图片叠加配置 | [ ]
	FH_POINT                logo_startpos; // 图片叠加起始坐标 | [ ]
	FH_UINT32               stride_value;  // 行偏移 | [ ]
	FH_UINT32               color[256];    // 颜色索引库,ARGB8888 | [ ]
}FH_VPU_LOGOV2;

typedef struct
{
	FH_SIZE                 size;                        // 下采样后图像大小 | [ ]
	FH_ADDR_INFO            ymean;                       // 亮度均值地址 | [ ]
	FH_ADDR_INFO            cmean;                       // 色度均值地址 | [ ]
	FH_UINT32               ystride;                     // y数据stride | [ ]
	FH_UINT32               cstride;                     // c数据stride | [ ]
	FH_UINT64               time_stamp;                  // 时间戳 | [ ]
	FH_UINT64               frame_id;                    // 帧号 | [ ]
}FH_VPU_YCMEAN;

typedef struct
{
	FH_UINT32               base;
	FH_VOID *               vbase;
	FH_UINT32               size;
}FH_PKG_INFO;

typedef struct
{
	FH_UINT32 bgm_enable;    // bgm使能,只有通道0时有效 | [0-1]
	FH_UINT32 cpy_enable;    // cpy使能,只有通道0时有效 | [0-1]
	FH_UINT32 sad_enable;    // sad使能,只有通道0时有效 | [0-1]
	FH_UINT32 bgm_ds;        // bgm采样模式,只有通道0时有效 | [ ]
	FH_UINT32 out_mode;      // 通道当前输出格式 | [ ]
	FH_UINT32 support_mode;  // 通道支持的输出格式 | [ ]
	FH_SIZE   chn_max_size;  // 通道最大幅面 | [ ]
	FH_UINT32 bufnum;        // 通道分配buffer个数,配置为0时为VBPool模式(默认使用CommVB,可以通过FH_VPSS_AttachVbPool指定从私有VB获取内存) | [ ]
	FH_UINT32 max_stride;    // 通道输出最大stride(配置为0时为通道最大幅面宽,以pixel为单位) | [ ]
}FH_VPU_CHN_INFO;

typedef struct
{
	FH_UINT32 ycmean_en;     // ycmean使能 | [0-1]
	FH_UINT32 ycmean_ds;     // ycmean采样模式 | [ ]
	FH_SIZE   vi_max_size;   // vi输入最大幅面 | [ ]
}FH_VPU_SET_GRP_INFO;

typedef struct
{
	FH_UINT32 bEnable;          // LDC使能 | [0-1]
	FH_UINT32 centerX;          // 矫正中心水平坐标 | [ ]
	FH_UINT32 centerY;          // 矫正中心垂直坐标 | [ ]
	FH_UINT32 distortionRatio;  // LDC矫正比例，单位千分之几 | [0-1000]
}FH_VPU_LDC;

typedef struct
{
	FH_UINT32 Enable;           // APC使能 | [0-1]
	FH_UINT32 Mergesel;         // 细节增强和边界锐化合并模式 | [0-1]
	FH_UINT32 PGain;            // 总体APC正向增益 | [0-255]
	FH_UINT32 NGain;            // 总体APC负向增益 | [0-255]
	FH_UINT32 DetailPGain;      // 细节增强正向增益 | [0-255]
	FH_UINT32 DetailNGain;      // 细节增强负向增益 | [0-255]
	FH_UINT32 DetailThL;        // 细节增强门限值 | [0-1023]
	FH_UINT32 DetailThH;        // 细节增强门限值 | [0-1023]
	FH_UINT32 DetailFilterIdx;  // 细节增强滤波器索引　| [0-4]
	FH_UINT32 DetailLutIdx;     // 细节增强映射表索引　| [0-8]
	FH_UINT32 EdgePGain;        // 边界锐化正向增益 | [0-255]
	FH_UINT32 EdgeNGain;        // 边界锐化负向增益 | [0-255]
	FH_UINT32 EdgeThL;          // 边界锐化门限值 | [0-1023]
	FH_UINT32 EdgeThH;          // 边界锐化门限值 | [0-1023]
	FH_UINT32 EdgeFilterIdx;    // 边界锐化滤波器索引　| [0-4]
	FH_UINT32 EdgeLutIdx;       // 边界锐化映射表索引　| [0-8]
}FH_VPU_APC;

typedef struct
{
	FH_UINT32 Enable;    // RGB前处理使能 | [0-1]
	FH_UINT32 MeansR;    // R通道均值 | [0-255]
	FH_UINT32 MeansG;    // G通道均值 | [0-255]
	FH_UINT32 MeansB;    // B通道均值| [0-255]
	FH_UINT32 Gain;      // 增益系数 | [0-255]
}FH_VPU_RGB_PRE;

typedef struct {
	FH_UINT32 mode;           // 0:手动模式，用户配置其他参数决定当前相关缩放参数 1:自动模式，驱动基于缩放比自适应旋转缩放参数 | [0-1]
	FH_UINT32 fix2ds_width;   // fix2ds生效门限，小于此幅面且对应通道输出能力满足时开启，部分通道不支持 | []
	FH_UINT32 scaler_coeff_h; // 水平方向滤波器系数，从模糊到清晰 | [0-15]
	FH_UINT32 scaler_coeff_v; // 垂直方向滤波器系数，从模糊到清晰 | [0-15]
}FH_VPU_SCALER_ATTR;

typedef struct
{
	FH_UINT32      sub_blk;        // 分块数量(0:不分块/2/4) | [ ]
	FH_UINT32      shadow;         // 分块时的shadow | []
	FH_UINT32      vi_auto;        // 驱动是否对visize进行自适应更改 | [0-1]
}FH_VPU_GRP_PARAM;

typedef struct
{
	FH_UINT32      align_patch_mode_w[4];    // 宽度四种角度的拉伸模式,在180和270时需要使用0,否则会显示异常　0:拉伸到对齐后幅面 1:拉伸到有效幅面,非对齐部分为冗余图像 | [0-1]
	FH_UINT32      align_patch_mode_h[4];    // 高度四种角度的拉伸模式,在180和90时需要使用0,否则会显示异常　0:拉伸到对齐后幅面 1:拉伸到有效幅面,非对齐部分为冗余图像 | [0-1]
	FH_UINT32      fcmode;                   // 是否进行插帧 | [0-1]
}FH_VPU_CHN_PARAM;

#define VPU_MAX_MERGE_BLK_NUM    (3)

typedef struct
{
	FH_UINT32 left;  // 块左边值　| [ ]
	FH_UINT32 right; // 块右边值　| [ ]
}FH_VPU_SIDE;

typedef struct
{
	FH_VPU_VI_MODE work_mode;   // VPU工作模式 | [ ]
	FH_SIZE        vi_size;     // 输入幅面 | [ ]
	FH_VPU_CROP    vi_crop;     // 输入裁剪属性 | [ ]
	FH_UINT32      offset_x;    // 当前图像在整张图像中的坐标(经过输入裁剪后的图像) | [ ]
	FH_VPU_SIDE    merge_width; // 拼接图像的大小 | [ ]
	FH_VPU_SIDE    shadow_width;// 冗余图像的大小 | [ ]
	FH_UINT32      out_mode;    // 块右边补齐模式 | [ ]
	FH_UINT32      shadow_stat; // 块冗余图像是否作为统计输出 | [ ]
}FH_VPU_MERGE_BLK;

typedef struct
{
	FH_SINT32        merge_num; // 拼接块数量 | [ ]
	FH_VPU_MERGE_BLK merge_attr[VPU_MAX_MERGE_BLK_NUM]; // 拼接块属性 | [ ]
}FH_VPU_MERGE_ATTR;

typedef struct
{
	FH_UINT32      enable;     // lut2d使能 | [ ]
	FH_UINT32      blkidx;     // 块序号 | [ ]
	FH_SIZE        vi_size;    // 输入幅面 | [ ]
	FH_SIZE        vo_size;    // 输出幅面 | [ ]
	FH_UINT32      out_mode;   // 输出模式 | [ ]
	FH_VPU_CROP    crop_info;  // 输出裁剪属性 | [ ]
	FH_UINT32      tabw;       // 映射表水平表项数 | [ ]
	FH_UINT32      tabh;       // 映射表垂直表项数 | [ ]
	FH_UINT32      bound_y;    // 边界固定的y | [ ]
	FH_UINT32      bound_u;    // 边界固定的u | [ ]
	FH_UINT32      bound_v;    // 边界固定的v | [ ]
	FH_PHYADDR     tab_addr;   // 映射表缓存地址 | [ ]
	FH_UINT32      tab_stride; // 映射表stride | [ ]
}FH_VPU_LUT2D_ATTR;


#pragma pack()
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
