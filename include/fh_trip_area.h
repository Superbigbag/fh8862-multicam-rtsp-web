#ifndef __FH_TRIP_AREA_H__
#define __FH_TRIP_AREA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#define FH_TAD_MAX_POINT_NUM  10   /* 最大坐标数 */
#define FH_TAD_MAX_RECT_NUM   30   /* 最大跟踪目标数 */

#define FH_TAD_SUCCESS 0
#define FH_TAD_INVALID_PARAM -1    /* 非法参数 */
#define FH_TAD_NO_MEMORY -2        /* 内存不足 */

typedef void* TAD_HANDLE;

typedef enum
{
    TAD_NO             = 0, /* 无事件 */
    TAD_TRIP_LTOR      = 1, /* 告警从左到右绊线 */
    TAD_TRIP_RTOL      = 2, /* 告警从右到左绊线 */
    TAD_TRIP_ALL       = 3, /* 告警双侧绊线 */
    TAD_AREA_ENTER     = 4, /* 告警进入 */
    TAD_AREA_EXIT      = 5, /* 告警离开 */
    TAD_AREA_INTRUSION = 6, /* 告警入侵 */
    TAD_AREA_ALL       = 7, /* 告警所有区域 */
}FH_TAD_MODE_e;

typedef struct
{
    int x; /* 点的x坐标值 */
    int y; /* 点的y坐标值 */
}FH_TAD_POINT_t;

typedef struct
{
    int x; /* 区域定点坐标x */
    int y; /* 区域定点坐标y */
    int w; /* 区域宽度w */
    int h; /* 区域长度h */
}FH_TAD_RECT_t;

typedef struct
{
    int maxTrackNum;  /* 最大追踪数量 */
    int iouThresh;    /* 最小匹配面积 */
    int minHits;      /* 最小命中次数 */
    int maxAge;       /* 最大跟丢次数 */
}FH_TAD_HANDLE_CFG_t;

typedef struct
{
    FH_TAD_POINT_t	startPoint;	    /* 规则线起点 */
    FH_TAD_POINT_t	endPoint;	    /* 规则线终点 */
}FH_TASK_TRIP_RULE_t;

typedef struct
{
    int	iTimeMin;	                                 /* 区域入侵超告警时间，单位：秒 */
    int iPointNum;                                   /* 组成该区域的顶点的个数 */
    FH_TAD_POINT_t rectPoint[FH_TAD_MAX_POINT_NUM];  /* 任意边形坐标点 */
}FH_TASK_AREA_RULE_t;

typedef struct
{
    int ruleid;         /* 规则id */
    int enable;         /* 规则使能 */
    int curminHits;     /* 最小触发次数， 建议范围[1-5] */
    int preminHits;     /* 最小触发次数， 建议范围[1-5] */
    FH_TAD_MODE_e mode; /* 告警模式 */

    union
    {
        FH_TASK_TRIP_RULE_t trip_cfg; /* 绊线检测配置 */
        FH_TASK_AREA_RULE_t area_cfg; /* 周界检测配置 */
    };
}FH_TASK_RULE_t;

typedef struct
{
    int	objId;		    /* 目标id, id为-1表示不告警 */
    FH_TAD_RECT_t pos;  /* 目标位置 */
    FH_TAD_MODE_e mode; /* 告警模式 */
} FH_TASK_OBJECT_t;

typedef struct
{
    int num;
    FH_TASK_OBJECT_t object[FH_TAD_MAX_RECT_NUM];
}FH_TAD_GROUP_t;

/**
* @ 打印回调函数注册（非必须，用于自定义打印），在最开始调用
* @param [in] callback
*/
void FH_TAD_PrintRegister(int (*callback)(const char* format, ...));

/**
* @ 创建handle
* @param [in] phdcfg
* @param [out] tadhandle
* @return 0: 成功 非0：失败
*/
int FH_TAD_CreatHandle(TAD_HANDLE *tadhandle, FH_TAD_HANDLE_CFG_t *phdcfg);

/**
* @ 获取handle配置
* @param [in] tadhandle
* @param [out] phdcfg
* @return 0: 成功 非0：失败
*/
int FH_TAD_GetHandleCfg(TAD_HANDLE tadhandle, FH_TAD_HANDLE_CFG_t *phdcfg);

/**
* @ 运行检测
* @param [in] tadhandle
* @param [in] rule
* @param [in] tadin
* @param [out] tadout
*/
void FH_TAD_Process(TAD_HANDLE tadhandle, FH_TASK_RULE_t *rule, FH_TAD_GROUP_t *tadin, FH_TAD_GROUP_t *tadout);

/**
* @ 释放handle内存，如有多个handle，则每个都需要释放
* @param [in] tadhandle
*/
void FH_TAD_HandleRelease(TAD_HANDLE tadhandle);

/**
* @ 打印版本信息
*/
void FH_TAD_GetLibInfo();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __FH_TRIP_AREA_H__ */
