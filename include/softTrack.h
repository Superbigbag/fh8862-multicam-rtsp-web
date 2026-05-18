/**
 * Copyright (c) 2018 Shanghai Fullhan Microelectronics Co., Ltd.
 * All rights reserved
 */

#ifndef SOFTTRACK_H_
#define SOFTTRACK_H_

#include <stdint.h>

// ERROR CODE
#define TR_ERR_BASE (-1000)

#define TR_SUCCESS (0)
#define TR_FAILED (TR_ERR_BASE - 1)
#define TR_NULL_PTR (TR_ERR_BASE - 2)   // 空指针错误
#define TR_INV_PARAM (TR_ERR_BASE - 3)  // 输入参数错误

/**
 * 坐标系定义
 * 采用归一化坐标（可避免分辨率带来的影响）
 * 画面左上角坐标为 (0,0)
 * 画面右下角坐标为 (1.0, 1.0)
 */

typedef struct tracObjPos {
    float x;  // 左上角横坐标
    float y;  // 左上角纵坐标
    float w;  // 物体水平宽度
    float h;  // 物体垂直高度
} tracObjPos_t;

typedef struct tracObj {
    tracObjPos_t pos;
    int32_t      id;
    int32_t      drop;
} tracObj_t;

#define MAX_OBJ_IN_GROUP 50  // should be larger than maxTrackNum

typedef struct objGroup {
    tracObj_t objlist[MAX_OBJ_IN_GROUP];  // 目标列表
    int32_t   num;                        // 目标数量
    uint64_t  timestamp;                  // 当前帧时间戳
} objGroup_t;

typedef struct trackerCfg {
    int32_t maxTrackNum;  // 最大追踪数量 should be bigger than MAX_OBJ_IN_GROUP
    int32_t iouThresh;    // 0 - 100, match threshold
    int32_t minHits;      // recommend 3
    int32_t maxAge;       // recommend 1
} trackerCfg_t;

struct softTracker;

/**
 * 创建一个tracker
 * input:   *cfg        tracker相关配置
 * return:  tracHandle  tracker句柄
 */
struct softTracker *trac_create(trackerCfg_t *cfg);

int trac_getcfg(struct softTracker *tracker, trackerCfg_t *cfg);

/**
 * 销毁一个tracker
 * input:   *tracker    tracker句柄
 * return:  ERRNO       TR_SUCCESS
 */
int trac_destory(struct softTracker *tracker);

/**
 * 追踪目标
 * input:   *tracker    tracker句柄
 *          *in         输入目标组指针
 * output:  *out        输出目标组
 * return:  ERRNO       TR_SUCCESS
 */
int trac_trackObjects(struct softTracker *tracker, objGroup_t *in, objGroup_t *out);

void FH_TRACK_PrintVersion(void);

#endif  // !SOFTTRACK_H_
