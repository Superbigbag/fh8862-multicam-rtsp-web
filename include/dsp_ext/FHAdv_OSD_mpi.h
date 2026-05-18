/**
 * @file     FHAdv_OSD_mpi.h
 * @brief    FHAdv OSD moduel interface
 * @version  V1.0.1
 * @date     11-Dec-2018
 * @author   Software Team
 *
 * @note
 * Copyright (C) 2018 Shanghai Fullhan Microelectronics Co., Ltd.
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

#ifndef _FHADV_OSD_MPI_H_
#define _FHADV_OSD_MPI_H_

#include "FH_typedef.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define FHT_OSD_TAG_CODE_BASE   (0xe401) /*TAG字符起始编号*/
#define FHT_OSD_YEAR4           (0xe401) /*4位年：2019*/
#define FHT_OSD_YEAR2           (0xe402) /*2位年：19*/
#define FHT_OSD_MONTH2          (0xe403) /*2位月份：01～12*/
#define FHT_OSD_DAY             (0xe404) /*2位日期：01～31*/
#define FHT_OSD_WEEK3           (0xe405) /*3位星期：MON～SUN*/
#define FHT_OSD_CWEEK1          (0xe406) /*1位星期：日,一～六*/
#define FHT_OSD_HOUR24          (0xe407) /*2位24时制小时：00～23*/
#define FHT_OSD_HOUR12          (0xe408) /*2位12时制小时：01～12*/
#define FHT_OSD_MINUTE          (0xe409) /*2位分钟: 00～59*/
#define FHT_OSD_SECOND          (0xe40a) /*2位秒: 00～59*/
#define FHT_OSD_AMPM            (0xe40b) /*1位(AM/PM中只取A/P): A/P*/
#define FHT_OSD_CAMPM           (0xe40c) /*一位(上午/下午中只取上/下): 上/下*/
#define FHT_OSD_USER1           (0xe40d) /*user defined*/
#define FHT_OSD_USER2           (0xe40e) /*user defined*/
#define FHT_OSD_USER3           (0xe40f) /*user defined*/
#define FHT_OSD_USER4           (0xe410) /*user defined*/
#define FHT_OSD_USER5           (0xe411) /*user defined*/
#define FHT_OSD_USER6           (0xe412) /*user defined*/
#define FHT_OSD_USER7           (0xe413) /*user defined*/
#define FHT_OSD_USER8           (0xe414) /*user defined*/
#define FHT_OSD_USER9           (0xe415) /*user defined*/
#define FHT_OSD_USER10          (0xe416) /*user defined*/
#define FHT_OSD_USER11          (0xe417) /*user defined*/
#define FHT_OSD_USER12          (0xe418) /*user defined*/
#define FHT_OSD_USER13          (0xe419) /*user defined*/
#define FHT_OSD_USER14          (0xe41a) /*user defined*/
#define FHT_OSD_USER15          (0xe41b) /*user defined*/
#define FHT_OSD_USER16          (0xe41c) /*user defined*/
#define FHT_OSD_USER_MAX        (FHT_OSD_USER16)
#define FHT_OSD_TAG_CNT         (28)     /*最大支持28个TAG*/
#define FHT_OSD_MAX_CHARS_OF_TAG (32)    /*一个TAG所能包含的最大字符数*/

#define FHT_UPDATED_YEAR   (1<<0) /*年变化的时候才更新*/
#define FHT_UPDATED_MONTH  (1<<1) /*月变化的时候才更新*/
#define FHT_UPDATED_DAY    (1<<2) /*日变化的时候才更新*/
#define FHT_UPDATED_HOUR   (1<<5) /*时变化的时候才更新*/
#define FHT_UPDATED_MINUTE (1<<6) /*分变化的时候才更新*/
#define FHT_UPDATED_SECOND (1<<7) /*秒变化的时候才更新*/
#define FHT_UPDATED_500MSECOND (1<<8) /*微秒变化的时候才更新*/
#define FHT_UPDATED_200MSECOND (1<<9) /*微秒变化的时候才更新*/
#define FHT_UPDATED_100MSECOND (1<<10) /*微秒变化的时候才更新*/
#define FHT_UPDATED_50MSECOND (1<<11) /*微秒变化的时候才更新*/

/*OSD时间格式*/
typedef enum
{
    FHTEN_OSD_TimeFmt0  = 0,      /* YYYY-MM-DD 00:00:00 */
    FHTEN_OSD_TimeFmt1  = 1,      /* MM-DD-YYYY 00:00:00 */
    FHTEN_OSD_TimeFmt2  = 2,      /* DD-MM-YYYY 00:00:00 */
    FHTEN_OSD_TimeFmt3  = 3,      /* YYYY/MM/DD 00:00:00 */
    FHTEN_OSD_TimeFmt4  = 4,      /* MM/DD/YYYY 00:00:00 */
    FHTEN_OSD_TimeFmt5  = 5,      /* DD/MM/YYYY 00:00:00 */
    FHTEN_OSD_TimeFmt6  = 6,      /* YYYY-MM-DD 00:00:00 weekFlag 打开时显示中文星期 */
    FHTEN_OSD_TimeFmt7  = 7,      /* MM-DD-YYYY 00:00:00 weekFlag 打开时显示中文星期 */
    FHTEN_OSD_TimeFmt8  = 8,      /* DD-MM-YYYY 00:00:00 weekFlag 打开时显示中文星期 */
    FHTEN_OSD_TimeFmt9  = 9,      /* xxxx年xx月xx日 00:00:00 */
    FHTEN_OSD_TimeFmt10 = 10,    /* xx月xx日xxxx年 00:00:00 */
    FHTEN_OSD_TimeFmt11 = 11,    /* xx日xx月xxxx年 00:00:00 */
    FHTEN_OSD_TimeFmt12 = 12,     /* YYYY/MM/DD 00:00:00 显示中文星期 */
    FHTEN_OSD_TimeFmt13 = 13,     /* MM/DD/YYYY 00:00:00 显示中文星期 */
    FHTEN_OSD_TimeFmt14 = 14,     /* DD/MM/YYYY 00:00:00 显示中文星期 */
    FHTEN_OSD_TimeFmt_BUTT,      /* 判断限值 非交互项 上层不必关心 */
} FHT_OSD_TimeFmt_e;

typedef enum
{
    FHTEN_OSD_GB2312  = 0, /* gb2312 */
    FHTEN_OSD_UNICODE = 1, /* unicode(4字节) */
    FHTEN_OSD_UTF8    = 2, /* utf-8 */
}FHT_OSD_EncType_e;        /* 自定义字库类型枚举 */

typedef enum
{
    FHTEN_OSD_GBOX_Pixel  = 0, /* Gbox类型 */
    FHTEN_OSD_MASK_Pixel = 1, /* Mask类型 */
}FHT_OSD_PixelType_e;        /* 自定义位宽配置类型枚举 */

typedef struct
{
    FH_SINT32 width;    /* 汉字字符宽度像素， 取值范围[16, 32, 48, 64] */
    FH_SINT32 height;   /* 汉字字符宽度像素， 取值范围[16, 32, 48, 64] */
} FHT_OSD_Size_t;

typedef struct
{
    FH_UINT8 high_level; /* 大于等于此值，进行反色 */
    FH_UINT8 low_level;  /* 小于等于此值，恢复正常颜色 */
}FHT_OSD_Invert_Attr_t;

typedef struct
{
    FH_SINT16 year;  /*The real year, for example, now is year 2019*/
    FH_SINT16 month; /*The number of months since January,in the range 1 to 12*/
    FH_SINT16 day;  /*The day of the month, in the range 1 to 31*/
    FH_SINT16 dayOfWeek; /*The number of days since Sunday, in the range 0 to 6*/
    FH_SINT16 hour; /*The number of hours past midnight, in the range 0 to 23*/
    FH_SINT16 minute;/*The number of minutes after the hour, in the range 0 to 59*/
    FH_SINT16 second;/*The number of seconds after the minute, in the range 0 to 59*/
    FH_SINT16 msecond_500;
    FH_SINT16 msecond_200;
    FH_SINT16 msecond_100;
    FH_SINT16 msecond_50;
} FHT_DATE_TIME;

/*字库配置*/
typedef struct
{
    FH_UINT32 libSize;    /* 字库大小 */
    FH_ADDR   pLibData;  /* 字库数据地址 */
} FHT_OSD_FontLib_t;

enum
{
    FH_OSD_INVERT_DISABLE  = 0,
    FH_OSD_INVERT_BY_CHAR = 1,
    FH_OSD_INVERT_BY_LINE = 2,
} FHT_OSD_Invert_t;

#define	FHT_OSD_GRAPH_CTRL_DEFAULT (0)  /*默认的graph分配，(FHT_OSD_GRAPH_CTRL_LOGO_BEFORE_VP | FHT_OSD_GRAPH_CTRL_TOSD_BEFORE_VP)*/
#define	FHT_OSD_GRAPH_CTRL_LOGO_BEFORE_VP (1<<0)
#define	FHT_OSD_GRAPH_CTRL_TOSD_BEFORE_VP (1<<1)
#define	FHT_OSD_GRAPH_CTRL_GBOX_BEFORE_VP (1<<2)
#define	FHT_OSD_GRAPH_CTRL_MASK_BEFORE_VP (1<<3)
#define FHT_OSD_GRAPH_CTRL_CIRCLE_BEFORE_VP (1<<4)
#define	FHT_OSD_GRAPH_CTRL_LOGO_AFTER_VP (1<<16)
#define	FHT_OSD_GRAPH_CTRL_TOSD_AFTER_VP (1<<17)
#define	FHT_OSD_GRAPH_CTRL_GBOX_AFTER_VP (1<<18)
#define	FHT_OSD_GRAPH_CTRL_MASK_AFTER_VP (1<<19)
#define FHT_OSD_GRAPH_CTRL_CIRCLE_AFTER_VP (1<<20)

#define FHT_OSD_DEBUG_LEVEL_OFF   (0) /*关闭debug功能*/
#define FHT_OSD_DEBUG_LEVEL_ERROR (1) /*打印错误信息*/
#define FHT_OSD_DEBUG_LEVEL_ALL   (7) /*打印所有相关信息*/


#define FHT_OSD_TIME_BIT_HOUR12 (1<<0)
#define FHT_OSD_TIME_BIT_WEEK   (1<<1)
#define FHT_OSD_TIME_BIT_AFTER  (1<<2)

#define FHT_OSD_TEXT_DEFAULT_ALIGN (0) /*text line默认显示设置，无右对齐，无闪烁*/
#define FHT_OSD_TEXT_RIGHT_ALIGN   (1<<0) /*text line右对齐*/
#define FHT_OSD_TEXT_TWINKLE       (1<<1) /*text line闪烁*/

#define FHT_OSD_LAYER_DEFAULT    (0)  /*layer默认设置， 单buffer*/
#define FH_OSD_LAYER_USE_TWO_BUF (1 << 0) /*layer双buffer， 可避免乱码*/

/*字符行块配置*/
typedef struct {
    FH_CHAR*  textInfo; /* 自定义字符内容 */
    FH_UINT8  textEnable; /* 使能自定义字符显示 */

    FH_UINT8  timeOsdEnable; /* 格式化时间显示 */
    /*
     * timeOsdFlags的取值为这几个宏定义的bit or值, FHT_OSD_TIME_BIT_XXX
     * bit0:12小时制[注：0:24小时制 1:12小时制]，bit1:显示星期，bit2:时间OSD在后面
     */
    FH_UINT8  timeOsdFlags;
    FH_UINT8  timeOsdFormat;

    FH_UINT32 linePositionX; /* 字符行块在幅面上的左上角起始x坐标， 编码旋转后 */
    FH_UINT32 linePositionY; /* 字符行块在幅面上的左上角起始y坐标， 编码旋转后 */

    FH_UINT32 textLineWidth; /* 字符行最大长度，超过自动换行 */

    FH_UINT8  showFlag; /* 字符显示选项，闪烁，右对齐 */

    FH_UINT8  lineId; /* 字符行块id */
    FH_UINT8  enable; /* 字符行块显示使能，1 显示， 0 不显示 */
}FHT_OSD_TextLine_t;

/*字符行块配置*/
typedef struct {
    FH_UINT32   LineNum;    /* 配置的字符数量 */
    FH_UINT32   Reconfig;   /* 此次配置是否清空之前的所有配置， 1-清空，0-不清空 */
    FHT_OSD_TextLine_t *pLineCfg;  /* 字符行块结构体数组地址 */
}FHT_OSD_Ex_TextLine_t;

/*TEXT OSD LAYER配置*/
typedef struct {

    FH_UINT16 layerStartX;    /* layer起始x坐标，编码旋转后 */
    FH_UINT16 layerStartY;    /* layer起始y坐标，编码旋转后 */
    FH_UINT16 layerMaxWidth;  /* layer显示的像素最大宽度， 内存分配相关，第一次设置，请按照最大使用内存设置 */
    FH_UINT16 layerMaxHeight; /* layer显示的像素最大高度， 内存分配相关，第一次设置，请按照最大使用内存设置 */

    FH_UINT32             osdSize;                   /* 字符大小 */
    FHT_RgbColor_t        normalColor;               /* 钩边色 支持反色 */
    FHT_RgbColor_t        invertColor;                  /* 钩边色 支持反色 */
    FHT_RgbColor_t        edgeColor;                    /* 钩边色 */
    FHT_RgbColor_t        bkgColor;                     /* 背景色, 和钩边功能互斥，钩边开启后，bkg设置失效*/

    FH_UINT8              edgePixel;                    /* 镶边像素，0: 不镶边，1：1个像素， 2：两个像素。*/
    FH_UINT8              osdInvertEnable;              /*FH_OSD_INVERT_XXX*/
    FHT_OSD_Invert_Attr_t osdInvertThreshold;           /* 设置osd反色阈值 */

    FH_UINT8 layerFlag;   /*layer设置标志，例如 是否使用双buffer*/
    FH_UINT8  layerId;    /*用户layer的单独管理，范围： 0 - (MAX_LAYER_NUM - 1)，MAX_LAYER_NUM为vpu规格中的每个通道的最大graph层数，例如YGV2中，该值为6*/
}FHT_OSD_Layer_Config_t;  /*每个layer对应一层graph*/

/*通道TEXT OSD配置*/
typedef struct
{
    FH_UINT8                osdRotate;      /*OSD旋转角度， 0: 不旋转  1: 90度  2: 180度  3: 270度*/
    FH_UINT8                nOsdLayerNum;   /*当前配置的layer个数, 数量不能大于vpu规格中graph的最大层数*/
    FHT_OSD_Layer_Config_t  *pOsdLayerInfo; /*layer配置数组起始地址，数组大小需和nOsdLayerNum对应*/
} FHT_OSD_CONFIG_t;

/*logo配置*/
typedef struct
{
    FH_UINT32  enable;                      /* logo使能 */
    FH_UINT32  rotate;                      /* logo旋转角度 */
    FH_UINT32  maxW;                        /* logo最大宽度 */
    FH_UINT32  maxH;                        /* logo最大高度 */
    FH_UINT32  alpha;                       /* logo透明度 */
    FHT_Rect_t area;                        /* logo位置及大小 */
    FH_ADDR    pData;                       /* logo数据 */
} FHT_OSD_Logo_t;

typedef struct
{
    FH_UINT32  enable;                      /* logo使能 */
    FH_UINT32  rotate;                      /* logo旋转角度 */
    FH_UINT32  maxW;                        /* logo最大宽度 */
    FH_UINT32  maxH;                        /* logo最大高度 */
    FH_UINT32  alpha;                       /* logo透明度 */
    FHT_Rect_t area;                        /* logo位置及大小 */
    FH_ADDR    pData;                       /* logo数据 */
    FH_UINT32  autoInvertEn;                /* logo自动反色使能 */
    FH_ADDR    pDataInvert;                 /* 反色logo数据 */
    FHT_OSD_Invert_Attr_t logoInvThreshold; /* 设置osd反色阈值 */
} FHT_OSD_Logo_Invert_t;

/*mask配置*/
typedef struct
{
    FH_UINT32      enable;   /* mask使能 0: 关闭  1: 开启 */
    FH_UINT32      maskId;   /* mask id */
    FH_UINT32      rotate;   /*旋转控制,目前无效,填0即可*/
    FHT_Rect_t     area;     /* OSD位置及大小 */
    FHT_RgbColor_t osdColor; /* OSD颜色 */

    FH_UINT32      max_frame_w;   /* 用于内存分配，仅第一次设置有效, 注意要初始化，不能为随机值 */
    FH_UINT32      max_frame_h;   /* 用于内存分配，仅第一次设置有效, 注意要初始化，不能为随机值 */
} FHT_OSD_Mask_t;

/*circle配置*/
typedef struct
{
    FH_UINT32      enable;   /* circle使能 0: 关闭  1: 开启 */
    FH_UINT32      center_x;
    FH_UINT32      center_y;
    FH_UINT32      radius;
    FH_UINT32      max_frame_w;
    FH_UINT32      max_frame_h;
    FHT_RgbColor_t osdColor; /* OSD颜色 */
} FHT_OSD_Circle_Cover_t;

/*gbox配置*/
typedef struct
{
    FH_UINT32      enable;        /* gbox使能 0: 关闭  1: 开启 */
    FH_UINT32      gboxId;        /* gbox id */
    FH_UINT32      rotate;        /*旋转控制,目前无效,填0即可*/
    FH_UINT32      gboxLineWidth; /* gbox线条宽度 */
    FHT_Rect_t     area;          /* gbox位置及大小 */
    FHT_RgbColor_t osdColor;      /* gbox颜色 */

    FH_UINT32      max_frame_w;   /* 用于内存分配，仅第一次设置有效, 注意要初始化，不能为随机值 */
    FH_UINT32      max_frame_h;   /* 用于内存分配，仅第一次设置有效, 注意要初始化，不能为随机值 */
} FHT_OSD_Gbox_t;

typedef struct
{
    FH_UINT32      enable;           /* 多边形使能 0: 关闭  1: 开启 */
    FH_UINT32      polygonId;        /* 多边形 id */
    FH_UINT32      rotate;           /*旋转控制,目前无效,填0即可*/
    FH_UINT32      polygonLineWidth; /* 多边形线条宽度 */
    FH_UINT32      vertexNum;        /* 多边形顶点个数 */
    FHT_LeftTopNode_t *vertexSet;    /* 多边形顶点位置 */
    FHT_RgbColor_t osdColor;         /* 多边形颜色 */

    FH_UINT32      max_frame_w;   /* 用于内存分配，仅第一次设置有效, 注意要初始化，不能为随机值 */
    FH_UINT32      max_frame_h;   /* 用于内存分配，仅第一次设置有效, 注意要初始化，不能为随机值*/
} FHT_OSD_Polygon_t;

/*mask配置*/
typedef struct
{
    FH_UINT8            nPolygonMaskNum;   /*多边形mask数量*/
    FHT_OSD_Polygon_t  *pPolygoncfg; /*多边形mask配置数组起始地址，数组大小需和nPolygonMaskNum对应*/
} FHT_OSD_Layer_Polygon_t;

/*gbox配置*/
typedef struct
{
    FH_UINT8         nGboxNum;   /*多边形gbox数量*/
    FHT_OSD_Gbox_t  *pGboxcfg; /*gbox配置数组起始地址，数组大小需和nGboxNum对应*/
    FH_UINT8           nPolygonMaskNum;   /*多边形数量, 这个多边形不填充内部*/
    FHT_OSD_Polygon_t  *pPolygoncfg; /*多边形mask配置数组起始地址，数组大小需和nPolygonMaskNum对应*/
    FH_UINT32      max_frame_w;   /* 用于内存分配，仅第一次设置有效, 注意要初始化，不能为随机值, 此结构体仅这里参数有效，成员内部的max_frame_w不生效 */
    FH_UINT32      max_frame_h;   /* 用于内存分配，仅第一次设置有效, 注意要初始化，不能为随机值, 此结构体仅这里参数有效，成员内部的max_frame_h不生效 */
} FHT_OSD_Gbox_Unitary_t;

/*
 *函数指针类型定义
 *参数:
 *   code[IN], 字符的ASC/GB2312/Unicode码
 *   pWidth[OUT], 用来接收此字符的像素点阵宽度
 *   pHeight[OUT], 用来接收此字符的像素点阵高度
 *返回值: 点阵像素的内存,当次有效,ADVAPI库内部会马上拷贝走.
 *        注意,点阵像素的内存不可使用函数内部的stack内存,因为函数返回会马上无效,最好使用一段static定义的内存.
 */
typedef FH_UINT8* (* FHT_OSD_GET_FONT_FUNC_t)(FH_UINT32 code, FH_UINT32 *pWidth, FH_UINT32 *pHeight);

/*
 *函数指针类型定义
 *参数:
 *   code[IN], 字符的ASC/GB2312/Unicode码
 *   pWidth[OUT], 用来接收此字符的像素点阵宽度
 *   pHeight[OUT], 用来接收此字符的像素点阵高度
 *   pStride[OUT], 用来接收此字符的像素点阵每行所占内存bit数(即点阵行内存比特跨度)
 *   pFontShowScale[OUT], 字符显示宽高比例，0 使用默认显示比例，1 宽高比为1:2， 2 宽高比为1:1
 *返回值: 点阵像素的内存,当次有效,ADVAPI库内部会马上拷贝走.
 *        注意,点阵像素的内存不可使用函数内部的stack内存,因为函数返回会马上无效,最好使用一段static定义的内存.
 */
typedef FH_UINT8* (* FHT_OSD_GET_FONT_EXT_FUNC_t)(FH_UINT32 code, FH_UINT32 *pWidth, FH_UINT32 *pHeight, FH_UINT32 *pStride, FH_UINT32 *pFontShowScale);

/*
 * 参数:
 *    vpuId vpu group id, 范围： 0 - 256
 *    debug_level: 取值FHT_OSD_DEBUG_LEVEL_XXX
 *    graph_ctrl: 取值FHT_OSD_GRAPH_CTRL_XXX，一般取FHT_OSD_GRAPH_CTRL_DEFAULT即可
 *    reserved1:  保留值,填0即可
 *    reserved2:  保留值,填0即可
 */
FH_SINT32 FHAdv_Osd_Init(FH_SINT32 vpuId, FH_UINT32 debug_level, FH_UINT32 graph_ctrl, FH_UINT32 reserved1, FH_UINT32 reserved2);


/*********
 * 函数名：  FHAdv_OSD_UnInit
 * 函数功能: uninit. 如果vpuId为-1， 表示全部unInit
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 *********/
FH_SINT32 FHAdv_Osd_UnInit(FH_SINT32 vpuId);

/*
 *功能: 加载字库
 *参数:
 *   type,本次加载字库的类型
 *   pFontData,结构体包含字库点阵数据大小及指针,需要注意的是,此结构体中pLibData指向的
 *   内存在FHAdv_Osd_UnLoadFontLib被调用前不可释放,因为我们的ADVAPI库里面不做内存拷贝.
 *返回值: 见错误码ADV_ERR_XXX
 */
FH_SINT32 FHAdv_Osd_LoadFontLib(FHT_OSD_FontType_e type, FHT_OSD_FontLib_t *pFontData);

/*
 *功能: 卸载字库,与FHAdv_Osd_LoadFontLib对应,需要注意的是,此函数调用后,ADVAPI内部将不再
 *      引用之前加载的字库.
 *参数: type,本次卸载字库的类型
 *返回值: 见错误码ADV_ERR_XXX
 */
FH_SINT32 FHAdv_Osd_UnLoadFontLib(FHT_OSD_FontType_e type);

/*
 *功能: 释放当前Cache的所有Font,实现一些特殊功能,一般来说,这个函数不需要调用.
 *      注意,要调用此函数,需要先Disable所有的TOSD,否则它会失败.
 *返回值: 见错误码ADV_ERR_XXX
 */
FH_SINT32 FHAdv_Osd_InvalidateFont(FH_VOID);

/*
 *功能: 注册自定义字库回调函数
 *参数:
 *   func, 回调函数, 当func为NULL时,ADVAPI库内部将不再调用上一次注册的回调函数.
 *   enc_type, 结构体FHT_OSD_TextLine_t中textInfo指向字符的编码类型.
 *返回值: 见错误码ADV_ERR_XXX
 */
FH_SINT32 FHAdv_Osd_Font_RegisterCallback(FHT_OSD_GET_FONT_FUNC_t func, FHT_OSD_EncType_e enc_type);

/*
 *功能: 注册自定义字库回调函数
 *参数:
 *   func, 回调函数, 当func为NULL时,ADVAPI库内部将不再调用上一次注册的回调函数.
 *   enc_type, 结构体FHT_OSD_TextLine_t中textInfo指向字符的编码类型.
 *返回值: 见错误码ADV_ERR_XXX
 */
FH_SINT32 FHAdv_Osd_Ex_Font_RegisterCallback(FHT_OSD_GET_FONT_EXT_FUNC_t func, FHT_OSD_EncType_e enc_type);

typedef FH_UINT32 (* FHT_OSD_Traverse_Chars_FUNC_t)(FH_UINT32 tagCode, FH_UINT32 nSequence);
typedef FH_UINT32 (* FHT_OSD_Refresh_Chars_FUNC_t)(FH_UINT32 tagCode, FHT_DATE_TIME *time, FH_UINT32 *pCodeArray);
FH_SINT32 FHAdv_Osd_SetTagCallback(
        FH_SINT32 vpuId,
        FH_UINT32 tagCode,
        FH_UINT32 refreshControl, /*bit or of these flags, FHT_UPDATED_XXX*/
        FHT_OSD_Traverse_Chars_FUNC_t funcTraverse,
        FHT_OSD_Refresh_Chars_FUNC_t funcRefresh);

/*
 *功能: 设置OSD字符，参数为OSD配置结构体指针.
 *参数: vpuId: vpu group id, 范围： 0 - 256
 *      chn,通道号,如果TOSD被安排在VPU分通道前,那么chn填0即可,如果TOSD被安排在VPU分通道后,那么
 *          对于主码流,其chn等于0; 对于子码流,其chn等于1
 *      pOsdcfg, TEXT OSD配置参数
 *返回值: 见错误码ADV_ERR_XXX
 */
FH_SINT32 FHAdv_Osd_Ex_SetText(FH_SINT32 vpuId, FH_UINT32 chn, FHT_OSD_CONFIG_t *pOsdcfg);

/*
 *功能: 等效于参数chn0为0的FHAdv_Osd_Ex_SetText调用
 *参数: vpuId: vpu group id, 范围： 0 - 256
 *      pOsdcfg, TEXT OSD配置参数
 *返回值: 见错误码ADV_ERR_XXX
 */
FH_SINT32 FHAdv_Osd_SetText(FH_SINT32 vpuId, FHT_OSD_CONFIG_t *pOsdcfg);

/*
 *功能: 配置对应通道的最大宽高幅面
 *参数: vpuId: vpu group id, 范围： 0 - 256
 *      chn,通道号
 *       Max_Width, 通道最大宽度
 *       Max_Height, 通道最大高度
 *说明: 此接口用于解决独立的OSD项目开发中无法获取通道最大宽高幅面的问题，通常无需调用！最大宽高幅面配置使用
 *       FHAdv_Osd_SetText接口配置FHT_OSD_CONFIG_t结构体参数即可，此接口配置后该通道上所有TOSD图层
 *       都将默认以此大小申请VMM内存！
 *       最大幅面配置优先顺序：FHT_OSD_CONFIG_t结构体配置 > FHAdv_Osd_SetMaxframe > OSD当前通道幅面
 */
FH_SINT32 FHAdv_Osd_SetMaxframe(FH_SINT32 vpuId, FH_UINT32 chn, FH_UINT32 Max_Width, FH_UINT32 Max_Height);

/*
 *功能: 单独设置OSD字符块.
 *参数: vpuId: vpu group id, 范围： 0 - 256
 *      chn,通道号,如果TOSD被安排在VPU分通道前,那么chn填0即可,如果TOSD被安排在VPU分通道后,那么
 *          对于主码流,其chn等于0; 对于子码流,其chn等于1
 *      lineIndex 字符块序号，从0开始，不能超过最大字符块个数
 *      pLineCfg, TEXT LINE OSD配置参数
 *返回值: 见错误码ADV_ERR_XXX
 *
 * 注意： 这个接口只能在FHAdv_Osd_SetText或者FHAdv_Osd_Ex_SetText已经被调用之后才能调用，否则返回错误
 *        在字库被卸载的情况下，设置的textInfo不能有新的字符，即只能设置字库卸载之前已经使用过的字符
 */
FH_SINT32 FHAdv_Osd_SetTextLine(FH_SINT32 vpuId,  FH_SINT32 chn, FH_UINT32 layerId, FHT_OSD_TextLine_t *pLineCfg);

/*
 *功能: 单独设置OSD字符块, 一次配置多个字符块.
 *参数: vpuId: vpu group id, 范围： 0 - 256
 *       chn,通道号,如果TOSD被安排在VPU分通道前,那么chn填0即可,如果TOSD被安排在VPU分通道后,那么
 *          对于主码流,其chn等于0; 对于子码流,其chn等于1
 *      layerId Tosd图层序号，从0开始，不能超过最大Tosd图层个数
 *      pTextCfg, TEXT LINE OSD配置参数
 *返回值: 见错误码ADV_ERR_XXX
 *
 * 注意： 这个接口只能在FHAdv_Osd_SetText或者FHAdv_Osd_Ex_SetText已经被调用之后才能调用，否则返回错误
 *        在字库被卸载的情况下，设置的textInfo不能有新的字符，即只能设置字库卸载之前已经使用过的字符
 */
FH_SINT32 FHAdv_Osd_Ex_SetTextLine(FH_SINT32 vpuId, FH_SINT32 chn, FH_UINT32 layerId, FHT_OSD_Ex_TextLine_t *pTextCfg);
/********
 * 函数名：  FHAdv_Osd_Config_TwinkleTime
 * 函数功能: 设置通道上字符闪烁功能的显示隐藏时间
 * 输入参数: chn,通道号,如果TOSD被安排在VPU分通道前,那么chn填0即可,如果TOSD被安排在VPU分通道后,那么
 *          对于主码流,其chn等于0; 对于子码流,其chn等于1
 *          disp_interval 字符闪烁时显示的时间，单位ms,默认500ms,范围200~30000ms,
 *          hide_interval 字符闪烁时隐藏的时间，单位ms,默认500ms,范围200~30000ms
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 *******/
FH_SINT32 FHAdv_Osd_Config_TwinkleTime(FH_SINT32 vpuId, FH_UINT32 chn, FH_UINT32 disp_interval, FH_UINT32 hide_interval);

/*
 *功能: 打印用户配置，在设置osd返回参数错误时，方便用户打印配置信息
 *参数: vpuId: vpu group id, 范围： 0 - 256
 *      chn,通道号,如果TOSD被安排在VPU分通道前,那么chn填0即可,如果TOSD被安排在VPU分通道后,那么
 *          对于主码流,其chn等于0; 对于子码流,其chn等于1
 *      pOsdcfg, TEXT OSD配置参数
 *返回值: 0 成功  -1 通道号不对或者配置参数指针为空
 */
FH_SINT32 FHAdv_Osd_Print_User_Config(FH_UINT32 chn, FHT_OSD_CONFIG_t *pOsdUsrCfg);
FH_SINT32 FHAdv_Osd_Ex_Print_User_Config(FH_SINT32 vpuId, FH_UINT32 chn, FH_UINT32 reserved);
/********
 * 函数名：  FHAdv_Osd_SetLogo
 * 函数功能: 设置Grahp logo.
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 *          pLogoCfg  logo配置信息
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 *******/
FH_SINT32 FHAdv_Osd_SetLogo(FH_SINT32 vpuId, FHT_OSD_Logo_t *pLogoCfg);

FH_SINT32 FHAdv_Osd_Ex_SetLogo(FH_SINT32 vpuId, FH_UINT32 chn, FHT_OSD_Logo_t *pLogoCfg);

/********
 * 函数名：  FHAdv_Osd_SetLogo_Invert
 * 函数功能: 设置Grahp logo, 带有自动反色配置.
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 *          pLogoCfg  logo配置信息
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 *******/
FH_SINT32 FHAdv_Osd_SetLogo_Invert(FH_SINT32 vpuId, FHT_OSD_Logo_Invert_t *pLogoCfg);
FH_SINT32 FHAdv_Osd_Ex_SetLogo_Invert(FH_SINT32 vpuId, FH_UINT32 chn, FHT_OSD_Logo_Invert_t *pLogoCfg);

/********
 * 函数名：  FHAdv_Osd_Config_GboxPixel
 * 函数功能: 设置Gbox 调色板模式位宽，配置位宽模式大于1可使Gbox支持多种颜色
 * 输入参数: 位宽模式Color_pixel，范围为1/2/4/8
 *          配置类型graph_type，0为设置Gbox调色板位宽，1为设置Mask调色板位宽
 * 输出参数: 无
 * return:  FH_SUCCESS
 *          FH_FAILURE
 *
 *******/
FH_SINT32 FHAdv_Osd_Config_GboxPixel(FH_SINT32 vpuId, FH_UINT32 Color_pixel, FHT_OSD_PixelType_e graph_type);

/*********
 * 函数名：  FHAdv_Osd_Ex_SetMask
 * 函数功能: 打开、关闭通道马赛克
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 *          chan     vpu通道
 *          pBoxcfg  box配置信息
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 ********/
FH_SINT32 FHAdv_Osd_Ex_SetMask(FH_SINT32 vpuId, FH_UINT32 chan, FHT_OSD_Mask_t *pMaskcfg);

/*********
 * 函数名：  FHAdv_OSD_SetMask
 * 函数功能: 打开、关闭马赛克
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 *          pBoxcfg  box配置信息
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 ********/
FH_SINT32 FHAdv_Osd_SetMask(FH_SINT32 vpuId, FHT_OSD_Mask_t *pMaskcfg);

/********
 * 函数名：  FHAdv_Osd_Ex_SetGbox
 * 函数功能: 打开、关闭矩形框
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 *          chan      vpu通道
 *          pBoxcfg   BOX配置信息
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 ********/
FH_SINT32 FHAdv_Osd_Ex_SetGbox(FH_SINT32 vpuId, FH_UINT32 chn, FHT_OSD_Gbox_t *pBoxcfg);

/********
 * 函数名：  FHAdv_Osd_Ex_SetGbox_Unitary
 * 函数功能: 打开、关闭所有矩形框和多边形框
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 *          chan      vpu通道
 *          pBoxLayercfg  所有box和多边形配置信息
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 * 注意：不建议与FHAdv_Osd_Ex_SetGbox和FHAdv_Osd_SetGbox同时使用，该接口每次调用会清空Box图层重画。如果要使用
 * FHAdv_Osd_Ex_SetGbox和FHAdv_Osd_SetGbox接口单独画单个框，需要在该接口之后调用，否则会被该接口清除。
 *
 ********/
FH_SINT32 FHAdv_Osd_Ex_SetGbox_Unitary(FH_SINT32 vpuId, FH_UINT32 chn, FHT_OSD_Gbox_Unitary_t *pBoxLayercfg);

/********
 * 函数名：  FHAdv_Osd_SetPolygonMask
 * 函数功能: 打开、关闭多边形马赛克，默认通道0.
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 *          pPolygonLayercfg   多边形mask配置信息
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 ********/
FH_SINT32 FHAdv_Osd_SetPolygonMask(FH_SINT32 vpuId, FHT_OSD_Layer_Polygon_t *pPolygonLayercfg);

/********
 * 函数名：  FHAdv_Osd_Ex_SetPolygonMask
 * 函数功能: 打开、关闭多边形马赛克
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 *          chan      vpu通道
 *          pPolygonLayercfg   多边形mask配置信息
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 ********/
FH_SINT32 FHAdv_Osd_Ex_SetPolygonMask(FH_SINT32 vpuId, FH_UINT32 chan, FHT_OSD_Layer_Polygon_t *pPolygonLayercfg);
/********
 * 函数名：  FHAdv_OSD_SetGbox
 * 函数功能: 打开、关闭矩形框
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 *          pBoxcfg   BOX配置信息
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 ********/
FH_SINT32 FHAdv_Osd_SetGbox(FH_SINT32 vpuId, FHT_OSD_Gbox_t *pBoxcfg);


/********
 * 函数名：  FHAdv_Osd_Ex_SetPolygon
 * 函数功能: 打开、关闭多边形框
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 *          chan      vpu通道
 *          pPolygoncfg  多边形配置信息
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 ********/
FH_SINT32 FHAdv_Osd_Ex_SetPolygon(FH_SINT32 vpuId, FH_UINT32 chn, FHT_OSD_Polygon_t *pPolygoncfg);

/********
 * 函数名：  FHAdv_Osd_SetPolygon
 * 函数功能: 打开、关闭多边形框
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 *          pPolygoncfg  多边形配置信息
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 ********/
FH_SINT32 FHAdv_Osd_SetPolygon(FH_SINT32 vpuId, FHT_OSD_Polygon_t *pPolygoncfg);


/********
 * 函数名：  FHAdv_Osd_Ex_Circle_Cover
 * 函数功能: 设置圆形遮盖区域
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 *          chn          vpu通道号
 *          pCirclecfg   圆形遮盖区域配置
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 ********/
FH_SINT32 FHAdv_Osd_Ex_Circle_Cover(FH_SINT32 vpuId, FH_UINT32 chn, FHT_OSD_Circle_Cover_t *pCirclecfg);

/********
 * 函数名：  FHAdv_Osd_Circle_Cover
 * 函数功能: 设置圆形遮盖区域
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 *          pCirclecfg   圆形遮盖区域配置
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 ********/
FH_SINT32 FHAdv_Osd_Circle_Cover(FH_SINT32 vpuId, FHT_OSD_Circle_Cover_t *pCirclecfg);

/********
 * 函数名：  FH_ADV_OSD_Version
 * 函数功能: 获取打印库版本信息
 * 输入参数: vpuId: vpu group id, 范围： 0 - 256
 *          print_enable 使能版本打印
 * 输出参数: 无
 * return:  见错误码ADV_ERR_XXX
 *
 ********/
FH_CHAR* FH_ADV_OSD_Version(FH_UINT32 print_enable);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
