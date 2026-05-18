#ifndef _ISP_API_H_
#define _ISP_API_H_


#include "isp_common.h"
#include "isp_sensor_if.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#define lift_shift_bit_num(bit_num)			(1<<bit_num)
// #define DEBUG_API 1

#define CHECK_VALIDATION(x, a, b)                                                                                                  \
    do                                                                                                                             \
    {                                                                                                                              \
        int r;                                                                                                                     \
        if ((x < a) || (x > b))                                                                                                    \
        {                                                                                                                          \
            if (x < a)                                                                                                             \
                r = a;                                                                                                             \
            else                                                                                                                   \
                r = b;                                                                                                             \
            fh_printf("[WARNING]parameter out of range @%s %s= %d | range=[%d,%d] | auto clip to %d\n", __func__, #x, x, a, b, r); \
            x = r;                                                                                                                 \
        }                                                                                                                          \
    } while (0)

#define TRACE_API \
do\
{\
    FH_SINT32 s32Ret = isp_core_trace_interface(u32IspDevId, __func__);\
    if (s32Ret)\
        return s32Ret;\
} while (0);

#define FUNC_DEP __attribute__((deprecated))

enum ISP_HW_MODULE_LIST
{
    HW_MODUL_LF_DPC           = lift_shift_bit_num(0),
    HW_MODUL_LF_GB            = lift_shift_bit_num(1),
    HW_MODUL_LF_WB            = lift_shift_bit_num(2),
    HW_MODUL_SF_DPC           = lift_shift_bit_num(3),
    HW_MODUL_SF_GB            = lift_shift_bit_num(4),
    HW_MODUL_SF_WB            = lift_shift_bit_num(5),
    HW_MODUL_WDR              = lift_shift_bit_num(6),
    HW_MODUL_LUT              = lift_shift_bit_num(7),
    HW_MODUL_LSC              = lift_shift_bit_num(8),

    HW_MODUL_NR2D             = lift_shift_bit_num(9),
    HW_MODUL_WB3              = lift_shift_bit_num(10),
    HW_MODUL_DRC              = lift_shift_bit_num(11),
    HW_MODUL_HMIR             = lift_shift_bit_num(12),
    HW_MODUL_CFA              = lift_shift_bit_num(13),
    HW_MODUL_HLR              = lift_shift_bit_num(14),
    HW_MODUL_RGBB             = lift_shift_bit_num(15),
    HW_MODUL_CGAMMA           = lift_shift_bit_num(16),
    HW_MODUL_DEHAZE           = lift_shift_bit_num(17),
    HW_MODUL_YNR              = lift_shift_bit_num(18),
    HW_MODUL_APC              = lift_shift_bit_num(19),
    HW_MODUL_CNR              = lift_shift_bit_num(20),
    HW_MODUL_PFC              = lift_shift_bit_num(21),
    HW_MODUL_YGAMMA           = lift_shift_bit_num(22),
    HW_MODUL_CA               = lift_shift_bit_num(23),
    HW_MODUL_CIE              = lift_shift_bit_num(24),
    HW_MODUL_YIE              = lift_shift_bit_num(25),
    HW_MODUL_LOCAL_CHROMA     = lift_shift_bit_num(26),
    HW_MODUL_LCE              = lift_shift_bit_num(27),

    HW_MODUL_STAT_GLOBE       = lift_shift_bit_num(28),
    HW_MODUL_STAT_HIST        = lift_shift_bit_num(29),
    HW_MODUL_STAT_AF          = lift_shift_bit_num(30),

    HW_MODUL_NR3D             = lift_shift_bit_num(31),

    ISP_HW_MODULE_LIST_DUMMY=0xffffffff,
};

/**SYSTEM_CONTROL*/
/*
*   Name: API_ISP_GetBuffSize
*            获取ISP中分配的buffer大小
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN]  ISP_MEM_INIT* stMemInit
*            ISP初始化内存的参数配置
*
*   Return:
*            ISP中分配的buffer大小
*   Note:
*       只用于统计内存时调用,isp正常运行程序不能调用,否则会出异常
*/
FH_SINT32 API_ISP_GetBuffSize(FH_UINT32 u32IspDevId, ISP_MEM_INIT* stMemInit);
/*
*   Name: API_ISP_GetBuffSizeIspOut
*            获取ISP OUT中分配的单帧的buffer大小
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN]  ISP_MEM_INIT* stMemInit
*            ISP初始化内存的参数配置
*
*   Return:
*            ISP OUT中分配的单帧的buffer大小
*   Note:
*       isp正常运行程序不能调用,否则会出异常
*/
FH_SINT32 API_ISP_GetBuffSizeIspOut(FH_UINT32 u32IspDevId, ISP_MEM_INIT* stMemInit);
/*
*   Name: API_ISP_MemInit
*            ISP内部使用的memory分配与初始化
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN]  ISP_MEM_INIT* stMemInit
*            ISP初始化内存的参数配置
*
*   Return:
*            0(正确)
*           -1(ISP设备驱动打开失败)
*   Note:
*       1. 该函数仅影响初始化内存的参数，实际硬件如何工作按照其他接口实际配置情况
*       2. ISP写DDR数据格式，当ISP工作在离线模式下或者LUT2D工作在离线模式下有效
*       3. LUT2D工作在离线模式下时stMemInit->enIspOutFmt仅能选择10bit模式
*       4. ISP内存按照输出模式为8bit初始化后，不支持切换到10bit，反之可以
*       5. ISP内存按照输出模式为YUV420初始化后，不支持切换到YUV422，反之可以
*/
FH_SINT32 API_ISP_MemInit(FH_UINT32 u32IspDevId, ISP_MEM_INIT* stMemInit);
/*
*   Name: API_ISP_GetBinAddr
*            获取ISP的param参数的地址和大小
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_PARAM_CONFIG* param_conf
*            param的地址和大小
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetBinAddr(FH_UINT32 u32IspDevId, ISP_PARAM_CONFIG* param_conf);
/*
*   Name: API_ISP_SetViAttr
*            配置vi相关的一些幅面信息
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const ISP_VI_ATTR_S *pstViAttr
*            结构体ISP_VI_ATTR_S的指针
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetViAttr(FH_UINT32 u32IspDevId, const ISP_VI_ATTR_S *pstViAttr);
/*
*   Name: API_ISP_GetViAttr
*            获取当前幅面相关信息
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_VI_ATTR_S *pstViAttr
*            结构体ISP_VI_ATTR_S的指针
*
*   Return:
*            0(正确)，
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetViAttr(FH_UINT32 u32IspDevId, ISP_VI_ATTR_S *pstViAttr);
/*
*   Name: API_ISP_Init
*            初始化ISP硬件寄存器，并启动ISP
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*   Return:
*            0(正确)
*        -1003(ISP初始化异常)
*   Note:
*       无
*/
FH_SINT32 API_ISP_Init(FH_UINT32 u32IspDevId);
/*
*   Name: API_ISP_LoadIspParam
*            加载指定参数到DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] char *isp_param_buff
*            指定参数的指针
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_LoadIspParam(FH_UINT32 u32IspDevId, char *isp_param_buff);
/*
*   Name: API_ISP_Pause
*            暂停ISP对图像的处理与输出
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_Pause(FH_UINT32 u32IspDevId);
/*
*   Name: API_ISP_Resume
*            恢复ISP对图像处理与输出
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_Resume(FH_UINT32 u32IspDevId);
/*
*   Name: API_ISP_DetectPicSize
*            检测幅面信息是否符合预期
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*   Return:
*            0(正确)，错误(ERROR_ISP_DETECT_NO_INPUT, ERROR_ISP_UNEXPECTED_PIC_SIZE)
*   Note:
*       无
*/
FH_SINT32 API_ISP_DetectPicSize(FH_UINT32 u32IspDevId);
/*
*   Name: API_ISP_Run
*            ISP策略处理
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*   Return:
*            0(正确)，
*           -1(图像丢失)
*   Note:
*       无
*/
FH_SINT32 API_ISP_Run(FH_UINT32 u32IspDevId);
/*
*   Name: API_ISP_AE_AWB_Run
*            ISP AE&AWB策略处理
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*   Return:
*            0(正确)
*            图像丢失(ERROR_ISP_WAIT_PICEND_FAILED)
*   Note:
*       无
*/
FH_SINT32 API_ISP_AE_AWB_Run(FH_UINT32 u32IspDevId);
/*
*   Name: API_ISP_Exit
*            ISP线程退出，清理状态
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_Exit(FH_UINT32 u32IspDevId);
/*
*   Name: API_ISP_SensorRegCb
*            拷贝sensor的回调函数到目标地址。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_UINT32 u32SensorId
*            无用
*
*       [IN]  struct isp_sensor_if* pstSensorFunc
*            类型为isp_sensor_if的结构体指针，详细成员变量请查看isp_sensor_if结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SensorRegCb(FH_UINT32 u32IspDevId, FH_UINT32 u32SensorId, struct isp_sensor_if* pstSensorFunc);
/*
*   Name: API_ISP_SensorUnRegCb
*            注销ISP中注册的sensor的回调函数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_UINT32 u32SensorId
*            无用
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SensorUnRegCb(FH_UINT32 u32IspDevId, FH_UINT32 u32SensorId);
/*
*   Name: API_ISP_Set_HWmodule_cfg
*            配置ISP模块硬件使能
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const FH_UINT32 u32modulecfg
*            每1bit对应一个硬件使能位0表示关闭，1表示打开，详见枚举ISP_HW_MODULE_LIST。
*
*   Return:
*            0(正确)
*   Note:
*       当需要一次开关多个模块时,使用此函数,若只需控制一个模块,则可使用API_ISP_Set_Determined_HWmodule函数实现
*/
FH_SINT32 API_ISP_Set_HWmodule_cfg(FH_UINT32 u32IspDevId, const FH_UINT32 u32modulecfg);
/*
*   Name: API_ISP_Get_HWmodule_cfg
*            获取当前ISP模块硬件状态
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] FH_UINT32 *u32modulecfg
*            每1bit对应一个硬件使能位0表示关闭，1表示打开，详见枚举ISP_HW_MODULE_LIST。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_Get_HWmodule_cfg(FH_UINT32 u32IspDevId, FH_UINT32 *u32modulecfg);
/*
*   Name: API_ISP_Set_Determined_HWmodule
*            配置ISP某个模块硬件使能
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const HW_MODULE_CFG *pstModuleCfg
*            传入要控制的某个模块枚举变量以及开关状态，详见HW_MODULE_CFG。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       一次只能传入一个模块,否则会出错
*/
FH_SINT32 API_ISP_Set_Determined_HWmodule(FH_UINT32 u32IspDevId, const HW_MODULE_CFG *pstModuleCfg);
/*
*   Name: API_ISP_Get_Determined_HWmodule
*           获取ISP某个模块硬件使能状态
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [INOUT] HW_MODULE_CFG *pstModuleCfg
*            传入要控制的某个模块枚举变量,获取该模块开关状态，详见HW_MODULE_CFG。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       一次只能传入一个模块,否则会出错
*/
FH_SINT32 API_ISP_Get_Determined_HWmodule(FH_UINT32 u32IspDevId, HW_MODULE_CFG *pstModuleCfg);
/*
*   Name: API_ISP_GetAlgCtrl
*            获取软件控制开关寄存器状态
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] FH_UINT32 *u32AlgCtrl
*            每1bit对应一个软件使能位0表示关闭，1表示打开
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAlgCtrl(FH_UINT32 u32IspDevId, FH_UINT32 *u32AlgCtrl);
/*
*   Name: API_ISP_SetAlgCtrl
*            设置软件控制开关寄存器状态
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_UINT32 u32AlgCtrl
*            每1bit对应一个软件使能位0表示关闭，1表示打开
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAlgCtrl(FH_UINT32 u32IspDevId, FH_UINT32 u32AlgCtrl);
/*
*   Name: API_ISP_WaitVD
*            获取ispf中断
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] VOID
*
*   Return:
*            任意值(获取到中断信号时间)
*            0(没有获取到中断信号))
*   Note:
*       无
*/
FH_SINT32 API_ISP_WaitVD(FH_UINT32 u32IspDevId);
/*
*   Name: API_ISP_GetRawSize
*            获取raw数据的大小, 供应用层分配空间
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT]  FH_UINT32* raw_size
*            raw数据大小,单位byte
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       与API_ISP_GetRaw配合使用
*/
FH_SINT32 API_ISP_GetRawSize(FH_UINT32 u32IspDevId, FH_UINT32 *raw_size);
/*
*   Name: API_ISP_GetRaw
*            获取ISP　NR3D处的raw数据
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_BOOL strategy_en
*            关闭硬件影响图像效果模块(0)，打开硬件影响图像效果模块(1)
*
*       [OUT]  FH_VOID* pRawBuff
*            存放raw数据的地址
*
*       [IN]  FH_UINT32 u32Size
*            存放raw数据buffer大小
*
*       [IN]  FH_UINT32 u32FrameCnt
*            需要导出的帧数，导出帧数不连续
*
*       [IN]  FRAME_TYPE type
*            帧类型
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetRaw(FH_UINT32 u32IspDevId, FH_BOOL strategy_en, FH_VOID* pRawBuff, FH_UINT32 u32Size, FH_UINT32 u32FrameCnt, FRAME_TYPE type);
/*
*   Name: API_ISP_SetRawBuf
*            连续导出多帧raw功能, 配置相关信息
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_BOOL strategy_en
*            关闭硬件影响图像效果模块(0)，打开硬件影响图像效果模块(1)
*
*       [IN]  ISP_RAW_BUF *raw_buf
*            类型为ISP_RAW_BUF的结构体指针，详细成员变量请查看ISP_RAW_BUF结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       应用层需申请足够的vmm内存
*/
FH_SINT32 API_ISP_SetRawBuf(FH_UINT32 u32IspDevId, FH_BOOL strategy_en, ISP_RAW_BUF *raw_buf);

/*
*   Name: API_ISP_SetViGenCfg
*            使用VI GEN灌输据方式出图
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_VIGEN_CFG *vi_gen
*            类型为ISP_VIGEN_CFG的结构体指针，详细成员变量请查看ISP_VIGEN_CFG结构体定义。
*
*   Return:
*            0(正确)
*        -3002(空指针异常)
*   Note:
*      无
*/
FH_SINT32 API_ISP_SetViGenCfg(FH_UINT32 u32IspDevId, ISP_VIGEN_CFG *vi_gen);
/*
*   Name: API_ISP_GetIspOutStream
*            获取指定通道ISP输出的一帧数据流
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN/OUT] ISP_OUT_STREAM_S *pstStream
*            配置的信息，以及返回获取到的数据地址
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*      获取的数据格式类型看data_format参数
*/
FH_SINT32 API_ISP_GetIspOutStream(FH_UINT32 u32IspDevId, ISP_OUT_STREAM_S *pstStream);
/*
*   Name: API_ISP_ReleaseIspOutStream
*            释放指定通道ISP输出的一帧数据流
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN/OUT] ISP_OUT_STREAM_S *pstStream
*            配置的信息，以及返回获取到的数据地址
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*        无
*/
FH_SINT32 API_ISP_ReleaseIspOutStream(FH_UINT32 u32IspDevId, ISP_OUT_STREAM_S *pstStream);
/*
*   Name: API_ISP_Open
*            打开isp驱动设备
*
*   Parameters:
*
*       [IN]  FH_VOID
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*        需要与API_ISP_Close配对使用
*/
FH_SINT32 API_ISP_Open(FH_VOID);
/*
*   Name: API_ISP_Close
*            关闭isp驱动设备
*
*   Parameters:
*
*       [IN]  FH_VOID
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*        需要与API_ISP_Open配对使用
*/
FH_SINT32 API_ISP_Close(FH_VOID);

/**SENSOR_CONTROL*/

/*
*   Name: API_ISP_SensorInit
*            sensor预初始化，并未配置sensor寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN]  Sensor_Init_t* initCfg
*            sensor的初始化信息
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SensorInit(FH_UINT32 u32IspDevId, Sensor_Init_t* initCfg);
/*
*   Name: API_ISP_SetSensorFmt
*            初始化sensor
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_UINT32 format
*            传入的时枚举FORMAT中的枚举值，选择幅面
*
*   Return:
*            0(正确)
*        -3002(sensor初始化异常)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetSensorFmt(FH_UINT32 u32IspDevId, FH_UINT32 format);

/*
*   Name: API_ISP_SensorKick
*            启动sensor输出，有的sensor需要用到
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*   Return:
*            0(正确返回)
*           -1(sensor相关的回调函数未被注册)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SensorKick(FH_UINT32 u32IspDevId);
/*
*   Name: API_ISP_SetSensorIntt
*            配置sensor的曝光值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_UINT32 intt
*            传入的曝光值
*
*   Return:
*            0(正确返回)
*           -1(sensor相关的回调函数未被注册)。
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetSensorIntt(FH_UINT32 u32IspDevId, FH_UINT32 intt);
/*
*   Name: API_ISP_SetSensorGain
*            配置sensor增益值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_UINT32 gain
*            增益值
*
*   Return:
*            0(正确返回)
*           -1(sensor相关的回调函数未被注册)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetSensorGain(FH_UINT32 u32IspDevId, FH_UINT32 gain);
/*
*   Name: API_ISP_MapInttGain
*            不同幅面切换时根据当前幅面曝光值和增益值转换成目标幅面曝光值和增益值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_SENSOR_COMMON_CMD_DATA0 *pstMapInttGainCfg
*            类型为ISP_SENSOR_COMMON_CMD_DATA0的结构体指针，详细成员变量请查看ISP_SENSOR_COMMON_CMD_DATA0结构体定义。
*
*   Return:
*            0(正确返回)
*           -1(sensor相关的回调函数未被注册)
*   Note:
*       无
*/
FH_SINT32 API_ISP_MapInttGain(FH_UINT32 u32IspDevId, ISP_SENSOR_COMMON_CMD_DATA0 *pstMapInttGainCfg);
/*
*   Name: API_ISP_SetSensorReg
*            配置sensor寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_UINT16 addr
*            sensor寄存器地址
*
*       [IN] FH_UINT16 data
*            配置的值
*
*   Return:
*            0(正确返回)
*           -1(sensor相关的回调函数未被注册)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetSensorReg(FH_UINT32 u32IspDevId, FH_UINT16 addr,FH_UINT16 data);
/*
*   Name: API_ISP_GetSensorReg
*            读取sensor寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_UINT16 addr
*            sensor寄存器地址
*
*       [OUT]  FH_UINT16 *data
*            读取的值
*
*   Return:
*            0(正确返回)
*           -1(sensor相关的回调函数未被注册)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetSensorReg(FH_UINT32 u32IspDevId, FH_UINT16 addr, FH_UINT16 *data);

/** AE **/
/*
*   Name: API_ISP_SetAeDefaultCfg
*            设置ae相关参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] AE_DEFAULT_CFG *pstAeDefaultCfg
*            类型为AE_DEFAULT_CFG的结构体指针，详细成员变量请查看AE_DEFAULT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAeDefaultCfg(FH_UINT32 u32IspDevId, AE_DEFAULT_CFG *pstAeDefaultCfg);
/*
*   Name: API_ISP_GetAeDefaultCfg
*            获取ae相关参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] AE_DEFAULT_CFG *pstAeDefaultCfg
*            类型为AE_DEFAULT_CFG的结构体指针，详细成员变量请查看AE_DEFAULT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAeDefaultCfg(FH_UINT32 u32IspDevId, AE_DEFAULT_CFG *pstAeDefaultCfg);
/*
*   Name: API_ISP_SetAeRouteCfg
*            设置ae路线模式相关参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] AE_ROUTE_CFG *pstAeRouteCfg
*            类型为AE_ROUTE_CFG的结构体指针，详细成员变量请查看AE_ROUTE_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAeRouteCfg(FH_UINT32 u32IspDevId, AE_ROUTE_CFG *pstAeRouteCfg);
/*
*   Name: API_ISP_GetAeRouteCfg
*            获取ae路线模式相关参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] AE_ROUTE_CFG *pstAeRouteCfg
*            类型为AE_ROUTE_CFG的结构体指针，详细成员变量请查看AE_ROUTE_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAeRouteCfg(FH_UINT32 u32IspDevId, AE_ROUTE_CFG *pstAeRouteCfg);
/*
*   Name: API_ISP_SetAeInfo
*            设置ae曝光时间及增益参数至sensor及硬件寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const ISP_AE_INFO *pstAeInfo
*            类型为ISP_AE_INFO的结构体指针，详细成员变量请查看ISP_AE_INFO结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAeInfo(FH_UINT32 u32IspDevId, const ISP_AE_INFO *pstAeInfo);
/*
*   Name: API_ISP_GetAeInfo
*           从sensor及硬件寄存器获取ae曝光时间及增益参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_AE_INFO *pstAeInfo
*            类型为ISP_AE_INFO的结构体指针，详细成员变量请查看ISP_AE_INFO结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAeInfo(FH_UINT32 u32IspDevId, ISP_AE_INFO *pstAeInfo);
/*
*   Name: API_ISP_SetAeInfo2
*            设置ae曝光时间及增益参数至sensor及硬件寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const ISP_AE_INFO_2 *pstAeInfo2
*            类型为ISP_AE_INFO_2的结构体指针，详细成员变量请查看ISP_AE_INFO_2结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       与API_ISP_SetAeInfo的区别在于isp gain分为pre和post两部分配置
*/
FH_SINT32 API_ISP_SetAeInfo2(FH_UINT32 u32IspDevId, const ISP_AE_INFO_2 *pstAeInfo2);
/*
*   Name: API_ISP_GetAeInfo2
*           从sensor及硬件寄存器获取ae曝光时间及增益参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_AE_INFO_2 *pstAeInfo2
*            类型为ISP_AE_INFO_2的结构体指针，详细成员变量请查看ISP_AE_INFO_2结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       与API_ISPGetAeInfo的区别在于isp gain分为pre和post两部分获取
*/
FH_SINT32 API_ISP_GetAeInfo2(FH_UINT32 u32IspDevId, ISP_AE_INFO_2 *pstAeInfo2);
/*
*   Name: API_ISP_GetAeStatus
*            获取ae状态值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_AE_STATUS *pstAeStatus
*            类型为ISP_AE_STATUS的结构体指针，详细成员变量请查看ISP_AE_STATUS结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAeStatus(FH_UINT32 u32IspDevId, ISP_AE_STATUS *pstAeStatus);
/*
*   Name: API_ISP_SetAeUserStatus
*            设置ae用户状态值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] AE_USER_STATUS *pstAeUserStatus
*            类型为AE_USER_STATUS的结构体指针，详细成员变量请查看AE_USER_STATUS结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       若用户使用自定义ae策略,则需要调用该函数配置ae相关状态值,提供给isp的其他策略使用,否则其他策略可能运行会有异常
*/
FH_SINT32 API_ISP_SetAeUserStatus(FH_UINT32 u32IspDevId, AE_USER_STATUS *pstAeUserStatus);

/** AWB **/
/*
*   Name: API_ISP_SetAwbDefaultCfg
*            设置awb相关参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] AWB_DEFAULT_CFG *pstAwbDefaultCfg
*            类型为AWB_DEFAULT_CFG的结构体指针，详细成员变量请查看AWB_DEFAULT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAwbDefaultCfg(FH_UINT32 u32IspDevId, AWB_DEFAULT_CFG *pstAwbDefaultCfg);
/*
*   Name: API_ISP_GetAwbDefaultCfg
*            获取awb相关参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] AWB_DEFAULT_CFG *pstAwbDefaultCfg
*            类型为AWB_DEFAULT_CFG的结构体指针，详细成员变量请查看AWB_DEFAULT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAwbDefaultCfg(FH_UINT32 u32IspDevId, AWB_DEFAULT_CFG *pstAwbDefaultCfg);
/*
*   Name: API_ISP_GetAwbStatus
*            获取awb状态值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_AWB_STATUS *pstAwbStatus
*            类型为ISP_AWB_STATUS的结构体指针，详细成员变量请查看ISP_AWB_STATUS结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAwbStatus(FH_UINT32 u32IspDevId, ISP_AWB_STATUS *pstAwbStatus);
/*
*   Name: API_ISP_SetAwbGain
*            设置awb增益至硬件寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_AWB_GAIN *pstAwbGain
*            类型为ISP_AWB_GAIN的结构体指针，详细成员变量请查看ISP_AWB_GAIN结构体定义。
*
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAwbGain(FH_UINT32 u32IspDevId, const ISP_AWB_GAIN *pstAwbGain);
/*
*   Name: API_ISP_GetAwbGain
*            从硬件寄存器获取awb增益值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] const ISP_AWB_GAIN *pstAwbGain
*            类型为ISP_AWB_GAIN的结构体指针，详细成员变量请查看ISP_AWB_GAIN结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)

*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAwbGain(FH_UINT32 u32IspDevId, ISP_AWB_GAIN *pstAwbGain);

/**  AF*/
/*
*   Name: API_ISP_AFAlgEn
*            设置获取af开关。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_BOOL bEn
*          使能(bEn=1)，关闭(bEn=0)
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_AFAlgEn(FH_UINT32 u32IspDevId, FH_BOOL bEn);
/*
*   Name: API_ISP_SetAFFilter
*            设置滤波器参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_AF_FILTER *pstAfFilter
*            类型为ISP_AF_FILTER的结构体指针，详细成员变量请查看ISP_AF_FILTER结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAFFilter(FH_UINT32 u32IspDevId, ISP_AF_FILTER *pstAfFilter);
/*
*   Name: API_ISP_GetAFFilter
*            获取滤波器参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_AF_FILTER *pstAfFilter
*            类型为ISP_AF_FILTER的结构体指针，详细成员变量请查看ISP_AF_FILTER结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAFFilter(FH_UINT32 u32IspDevId, ISP_AF_FILTER *pstAfFilter);
/**BLC*/
/*
*   Name: API_ISP_SetBlcCfg
*            配置BLC的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_BLC_CFG *pstBlcCfg
*            类型为ISP_BLC_ATTR的结构体指针，详细成员变量请查看ISP_BLC_ATTR结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetBlcCfg(FH_UINT32 u32IspDevId, ISP_BLC_CFG *pstBlcCfg);
/*
*   Name: API_ISP_GetBlcCfg
*            获取当前配置的BLC的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_BLC_CFG *pstBlcCfg
*            类型为ISP_BLC_ATTR的结构体指针，详细成员变量请查看ISP_BLC_ATTR结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetBlcCfg(FH_UINT32 u32IspDevId, ISP_BLC_CFG *pstBlcCfg);

/** GB*/
/*
*   Name: API_ISP_SetGbCfg
*            配置GB的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_GB_CFG *pstGbCfg
*            类型为ISP_GB_CFG的结构体指针，详细成员变量请查看ISP_GB_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetGbCfg(FH_UINT32 u32IspDevId, ISP_GB_CFG *pstGbCfg);
/*
*   Name: API_ISP_GetGbCfg
*            获取当前配置的GB的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_GB_CFG *pstGbCfg
*            类型为ISP_GB_CFG的结构体指针，详细成员变量请查看ISP_GB_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetGbCfg(FH_UINT32 u32IspDevId, ISP_GB_CFG *pstGbCfg);
/** DPC*/
/*
*   Name: API_ISP_SetDpcCfg
*            配置动态DPC的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_DPC_CFG *pstDpcCfg
*            类型为ISP_DPC_CFG的结构体指针，详细成员变量请查看ISP_DPC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetDpcCfg(FH_UINT32 u32IspDevId, ISP_DPC_CFG *pstDpcCfg);
/*
*   Name: API_ISP_GetDpcCfg
*            获取当前配置的动态DPC的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_DPC_CFG *pstDpcCfg
*            类型为ISP_DPC_CFG的结构体指针，详细成员变量请查看ISP_DPC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetDpcCfg(FH_UINT32 u32IspDevId, ISP_DPC_CFG *pstDpcCfg);
/** LSC*/
/*
*   Name: API_ISP_SetLscCfg
*            配置lsc参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_LSC_CFG *pstLscCfg
*            类型为ISP_LSC_CFG的结构体指针，详细成员变量请查看ISP_LSC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetLscCfg(FH_UINT32 u32IspDevId, ISP_LSC_CFG *pstLscCfg);
/** NR3D*/
/*
*   Name: API_ISP_SetNr3dCfg
*            配置NR3D的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_NR3D_CFG *pstNr3dCfg
*            类型为ISP_NR3D_CFG的结构体指针，详细成员变量请查看ISP_NR3D_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetNr3dCfg(FH_UINT32 u32IspDevId, ISP_NR3D_CFG *pstNr3dCfg);
/*
*   Name: API_ISP_GetNr3dCfg
*            获取当前配置的NR3D的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_NR3D_CFG *pstNr3dCfg
*            类型为ISP_NR3D_CFG的结构体指针，详细成员变量请查看ISP_NR3D_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetNr3dCfg(FH_UINT32 u32IspDevId, ISP_NR3D_CFG *pstNr3dCfg);
/*
*   Name: API_ISP_SetNr3dCoeffCfg
*            该函数可以配置NR3D的Coeff曲线，通过配置四对坐标可以配置Coeff曲线。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const ISP_NR3D_COEFF_CFG *pstNr3dCoeffCfg
*            类型为ISP_NR3D_COEFF_CFG的结构体指针，详细成员变量请查看ISP_NR3D_COEFF_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetNr3dCoeffCfg(FH_UINT32 u32IspDevId, ISP_NR3D_COEFF_CFG *pstNr3dCoeffCfg);
/** NR2D*/
/*
*   Name: API_ISP_SetNr2dCfg
*            配置NR2D的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_NR2D_CFG *pstNr2dCfg
*            类型为ISP_NR2D_CFG的结构体指针，详细成员变量请查看ISP_NR2D_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetNr2dCfg(FH_UINT32 u32IspDevId, ISP_NR2D_CFG *pstNr2dCfg);
/*
*   Name: API_ISP_GetNr2dCfg
*            获取当前配置的NR2D的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_NR2D_CFG *pstNr2dCfg
*            类型为ISP_NR2D_CFG的结构体指针，详细成员变量请查看ISP_NR2D_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetNr2dCfg(FH_UINT32 u32IspDevId, ISP_NR2D_CFG *pstNr2dCfg);
/*
*   Name: API_ISP_SetNr2dDpcCfg
*            配置NR2D DPC的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_NR2D_DPC_CFG *pstNr2dDpcCfg
*            类型为ISP_NR2D_DPC_CFG的结构体指针，详细成员变量请查看ISP_NR2D_DPC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetNr2dDpcCfg(FH_UINT32 u32IspDevId, ISP_NR2D_DPC_CFG *pstNr2dDpcCfg);
/*
*   Name: API_ISP_GetNr2dDpcCfg
*            配置NR2D DPC的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_NR2D_DPC_CFG *pstNr2dDpcCfg
*            类型为ISP_NR2D_DPC_CFG的结构体指针，详细成员变量请查看ISP_NR2D_DPC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetNr2dDpcCfg(FH_UINT32 u32IspDevId, ISP_NR2D_DPC_CFG *pstNr2dDpcCfg);

/** DRC **/
/*
*   Name: API_ISP_SetDrcCfg
*            配置Drc的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_DRC_CFG *pstDrcCfg
*            类型为ISP_DRC_CFG的结构体指针，详细成员变量请查看ISP_DRC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetDrcCfg(FH_UINT32 u32IspDevId, ISP_DRC_CFG *pstDrcCfg);
/*
*   Name: API_ISP_GetDrcCfg
*            获取当前配置的DRC的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_DRC_CFG *pstDrcCfg
*            类型为ISP_DRC_CFG的结构体指针，详细成员变量请查看ISP_DRC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetDrcCfg(FH_UINT32 u32IspDevId, ISP_DRC_CFG *pstDrcCfg);

/** CFA **/
/*
*   Name: API_ISP_SetCfaCfg
*            配置Cfa的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_CFA_CFG *pstCfaCfg
*            类型为ISP_CFA_CFG的结构体指针，详细成员变量请查看ISP_CFA_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCfaCfg(FH_UINT32 u32IspDevId, ISP_CFA_CFG *pstCfaCfg);
/*
*   Name: API_ISP_GetCfacCfg
*            获取当前配置的Cfa的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_CFA_CFG *pstCfaCfg
*            类型为ISP_CFA_CFG的结构体指针，详细成员变量请查看ISP_CFA_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetCfaCfg(FH_UINT32 u32IspDevId, ISP_CFA_CFG *pstCfaCfg);

/**HLR*/
/*
*   Name: API_ISP_SetHlrCfg
*            配置HLR的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_HLR_CFG *pstHlrCfg
*            类型为ISP_HLR_CFG的结构体指针，详细成员变量请查看ISP_HLR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetHlrCfg(FH_UINT32 u32IspDevId, ISP_HLR_CFG *pstHlrCfg);
/*
*   Name: API_ISP_GetHlrCfg
*            获取当前配置的HLR的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_HLR_CFG *pstHlrCfg
*            类型为ISP_HLR_CFG的结构体指针，详细成员变量请查看ISP_HLR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetHlrCfg(FH_UINT32 u32IspDevId, ISP_HLR_CFG *pstHlrCfg);
/**IE*/
/*
*   Name: API_ISP_SetContrastCfg
*            配置对比度相关的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_CONTRAST_CFG *pstContrastCfg
*            类型为ISP_CONTRAST_CFG的结构体指针，详细成员变量请查看ISP_CONTRAST_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetContrastCfg(FH_UINT32 u32IspDevId, ISP_CONTRAST_CFG *pstContrastCfg);
/*
*   Name: API_ISP_GetContrastCfg
*            获取当前配置的对比度相关的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_CONTRAST_CFG *pstContrastCfg
*            类型为ISP_CONTRAST_CFG的结构体指针，详细成员变量请查看ISP_CONTRAST_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetContrastCfg(FH_UINT32 u32IspDevId, ISP_CONTRAST_CFG *pstContrastCfg);
/*
*   Name: API_ISP_SetBrightnessCfg
*            配置亮度相关的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_BRIGHTNESS_CFG *pstBrightnessCfg
*            类型为ISP_BRIGHTNESS_CFG的结构体指针，详细成员变量请查看ISP_BRIGHTNESS_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetBrightnessCfg(FH_UINT32 u32IspDevId, ISP_BRIGHTNESS_CFG *pstBrightnessCfg);
/*
*   Name: API_ISP_GetBrightnessCfg
*            获取当前配置的亮度相关的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_BRIGHTNESS_CFG *pstBrightnessCfg
*            类型为ISP_BRIGHTNESS_CFG的结构体指针，详细成员变量请查看ISP_BRIGHTNESS_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetBrightnessCfg(FH_UINT32 u32IspDevId, ISP_BRIGHTNESS_CFG *pstBrightnessCfg);
/**CE*/
/*
*   Name: API_ISP_SetSaturation
*            配置对比度相关的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_SAT_CFG *pstCeCfg
*            类型为ISP_SAT_CFG的结构体指针，详细成员变量请查看ISP_SAT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetSaturation(FH_UINT32 u32IspDevId, ISP_SAT_CFG *pstCeCfg);
/*
*   Name: API_ISP_GetSaturation
*            获取当前配置的对比度相关的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_SAT_CFG *pstCeCfg
*            类型为ISP_SAT_CFG的结构体指针，详细成员变量请查看ISP_SAT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetSaturation(FH_UINT32 u32IspDevId, ISP_SAT_CFG *pstCeCfg);
/**APC*/
/*
*   Name: API_ISP_SetApcCfg
*            配置锐度相关的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_APC_CFG *pstApcCfg
*            类型为ISP_APC_CFG的结构体指针，详细成员变量请查看ISP_APC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetApcCfg(FH_UINT32 u32IspDevId, ISP_APC_CFG *pstApcCfg);
/*
*   Name: API_ISP_GetApcCfg
*            获取当前配置的锐度相关的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_APC_CFG *pstApcCfg
*            类型为ISP_APC_CFG的结构体指针，详细成员变量请查看ISP_APC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetApcCfg(FH_UINT32 u32IspDevId, ISP_APC_CFG *pstApcCfg);
/*
*   Name: API_ISP_SetApcMtCfg
*            配置apc与nr3d的联动参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_APC_MT_CFG *pstApcMtCfg
*            类型为ISP_APC_MT_CFG的结构体指针，详细成员变量请查看ISP_APC_MT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetApcMtCfg(FH_UINT32 u32IspDevId, ISP_APC_MT_CFG *pstApcMtCfg);
/*
*   Name: API_ISP_GetApcMtCfg
*            获取APC与nr3d的联动参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_APC_MT_CFG *pstApcMtCfg
*             类型为ISP_APC_MT_CFG的结构体指针，详细成员变量请查看ISP_APC_MT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetApcMtCfg(FH_UINT32 u32IspDevId, ISP_APC_MT_CFG *pstApcMtCfg);
/**GAMMA*/
/*
*   Name: API_ISP_SetGammaCfg
*            配置gamma相关的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_GAMMA_CFG *pstGammaCfg
*            类型为ISP_GAMMA_CFG的结构体指针，详细成员变量请查看ISP_GAMMA_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetGammaCfg(FH_UINT32 u32IspDevId, ISP_GAMMA_CFG *pstGammaCfg);
/*
*   Name: API_ISP_GetGammaCfg
*            获取当前配置的gamma相关的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_GAMMA_CFG *pstGammaCfg
*            类型为ISP_GAMMA_CFG的结构体指针，详细成员变量请查看ISP_GAMMA_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetGammaCfg(FH_UINT32 u32IspDevId, ISP_GAMMA_CFG *pstGammaCfg);

/**YCNR*/
/*
*   Name: API_ISP_SetYnrCfg
*            配置YNR相关的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_YNR_CFG *pstYnrCfg
*            类型为ISP_YNR_CFG的结构体指针，详细成员变量请查看ISP_YNR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetYnrCfg(FH_UINT32 u32IspDevId, ISP_YNR_CFG *pstYnrCfg);
/*
*   Name: API_ISP_GetYnrCfg
*            获取当前配置的YNR相关的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_YNR_CFG *pstYnrCfg
*            类型为ISP_YNR_CFG的结构体指针，详细成员变量请查看ISP_YNR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetYnrCfg(FH_UINT32 u32IspDevId, ISP_YNR_CFG *pstYnrCfg);
/*
*   Name: API_ISP_SetYnrMtCfg
*            配置YNR与nr3d的联动参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_YNR_MT_CFG *pstYnrMtCfg
*             类型为ISP_YNR_MT_CFG的结构体指针，详细成员变量请查看ISP_YNR_MT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetYnrMtCfg(FH_UINT32 u32IspDevId, ISP_YNR_MT_CFG *pstYnrMtCfg);
/*
*   Name: API_ISP_GetYnrMtCfg
*           获取YNR与nr3d的联动参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_YNR_MT_CFG *pstYnrMtCfg
*             类型为ISP_YNR_MT_CFG的结构体指针，详细成员变量请查看ISP_YNR_MT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetYnrMtCfg(FH_UINT32 u32IspDevId, ISP_YNR_MT_CFG *pstYnrMtCfg);
/*
*   Name: API_ISP_SetCnrCfg
*            配置CNR相关的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_CNR_CFG *pstCnrCfg
*            类型为ISP_CNR_CFG的结构体指针，详细成员变量请查看ISP_CNR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCnrCfg(FH_UINT32 u32IspDevId, ISP_CNR_CFG *pstCnrCfg);
/*
*   Name: API_ISP_GetCnrCfg
*            获取当前配置的CNR相关的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_CNR_CFG *pstCnrCfg
*            类型为ISP_CNR_CFG的结构体指针，详细成员变量请查看ISP_CNR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetCnrCfg(FH_UINT32 u32IspDevId, ISP_CNR_CFG *pstCnrCfg);
/*
*   Name: API_ISP_SetCnrMtCfg
*           设置CNR与nr3d的联动参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_CNR_MT_CFG *pstCnrMtCfg
*             类型为ISP_CNR_MT_CFG的结构体指针，详细成员变量请查看ISP_CNR_MT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCnrMtCfg(FH_UINT32 u32IspDevId, ISP_CNR_MT_CFG *pstCnrMtCfg);
/*
*   Name: API_ISP_GetCnrMtCfg
*           获取CNR与nr3d的联动参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_CNR_MT_CFG *pstCnrMtCfg
*             类型为ISP_CNR_MT_CFG的结构体指针，详细成员变量请查看ISP_CNR_MT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetCnrMtCfg(FH_UINT32 u32IspDevId, ISP_CNR_MT_CFG *pstCnrMtCfg);
/**PURPLE*/
/*
*   Name: API_ISP_SetAntiPurpleBoundary
*            配置去紫边相关的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_PURPLEFRI_CFG *pstPurplefriCfg
*            类型为ISP_PURPLEFRI_CFG的结构体指针，详细成员变量请查看ISP_PURPLEFRI_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAntiPurpleBoundary(FH_UINT32 u32IspDevId, ISP_PURPLEFRI_CFG *pstPurplefriCfg);
/*
*   Name: API_ISP_GetAntiPurpleBoundary
*            获取当前配置的去紫边的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_PURPLEFRI_CFG *pstPurplefriCfg
*            类型为ISP_PURPLEFRI_CFG的结构体指针，详细成员变量请查看ISP_PURPLEFRI_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAntiPurpleBoundary(FH_UINT32 u32IspDevId, ISP_PURPLEFRI_CFG *pstPurplefriCfg);

/**LC*/
/*
*   Name: API_ISP_SetLcCfg
*            配置Local Chroma相关的DRV寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_LC_CFG *pstLCCfg
*            类型为ISP_LC_CFG的结构体指针，详细成员变量请查看ISP_LC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetLcCfg(FH_UINT32 u32IspDevId, ISP_LC_CFG *pstLCCfg);
/*
*   Name: API_ISP_GetLcCfg
*            获取当前配置的Local Chroma相关的DRV寄存器值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_LC_CFG *pstLCCfg
*            类型为ISP_LC_CFG的结构体指针，详细成员变量请查看ISP_LC_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetLcCfg(FH_UINT32 u32IspDevId, ISP_LC_CFG *pstLCCfg);

/**Debug Interface**/
/*
*   Name: API_ISP_ReadMallocedMem
*            读取指定偏移的VMM分配的内存的值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_SINT32 intMemSlot
*            分配的内存的类型，决定基地址。
*
*       [IN]  FH_UINT32 offset
*            偏移地址，选定的内存会给定其基地址。
*
*       [OUT]  FH_UINT32 *pstData
*            存放读取到数据的地址。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_ReadMallocedMem(FH_UINT32 u32IspDevId, FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstData);
/*
*   Name: API_ISP_WriteMallocedMem
*            写指定偏移的VMM分配的内存的值
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_SINT32 intMemSlot
*            分配的内存的类型，决定基地址。
*
*       [IN]  FH_UINT32 offset
*            偏移地址，选定的内存会给定其基地址。
*
*       [IN]  FH_UINT32 *pstData
*            目标值，将该值写入目标地址。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_WriteMallocedMem(FH_UINT32 u32IspDevId, FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstData);
/*
*   Name: API_ISP_ImportMallocedMem
*            导入指定大小的数据到指定偏移的VMM分配的内存
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_SINT32 intMemSlot
*            分配的内存的类型，决定基地址。
*
*       [IN]  FH_UINT32 offset
*            偏移地址，选定的内存会给定其基地址。
*
*       [IN]  FH_UINT32 *pstSrc
*            导入数据的起始地址
*
*       [IN]  FH_UINT32 size
*            需要导入的数据大小
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_ImportMallocedMem(FH_UINT32 u32IspDevId, FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstSrc, FH_UINT32 size);
/*
*   Name: API_ISP_ExportMallocedMem
*            从指定偏移的VMM分配的内存导出指定大小的数据
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_SINT32 intMemSlot
*            分配的内存的类型，决定基地址。
*
*       [IN]  FH_UINT32 offset
*            偏移地址，选定的内存会给定其基地址。
*
*       [OUT]  FH_UINT32 *pstDst
*            存放导出数据的起始地址
*
*       [IN]  FH_UINT32 size
*            需要导出的数据大小
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_ExportMallocedMem(FH_UINT32 u32IspDevId, FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstDst, FH_UINT32 size);
/*
*   Name: API_ISP_GetVIState
*            获取当前ISP的一些运行状态信息
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_VI_STAT_S *pstStat
*            类型为ISP_VI_STAT_S的结构体指针，详细成员变量请查看ISP_VI_STAT_S结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetVIState(FH_UINT32 u32IspDevId, ISP_VI_STAT_S *pstStat);
/*
*   Name: API_ISP_SetSensorFrameRate
*            配置SENSOR的垂直消隐至指定倍率
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] int m
*            垂直消隐的倍率,U.8,也即0x100表示一倍
*
*   Return:
*            0(正确)
*   Note:
*       当ae策略关闭时可使用该函数,策略打开时的帧消隐由策略参数控制,且只支持大于1倍的降帧
*/
FH_SINT32 API_ISP_SetSensorFrameRate(FH_UINT32 u32IspDevId, int m);
/*
*   Name: API_ISP_Dump_Param
*            拷贝所有DRV寄存器值到指定地址
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] FH_UINT32 *addr
*            存放DRV参数的地址
*
*       [IN] FH_UINT32 *size
*            拷贝数据的大小
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_Dump_Param(FH_UINT32 u32IspDevId, FH_UINT32 *addr,FH_UINT32 *size);
/**MIRROR*/
/*
*   Name: API_ISP_MirrorEnable
*            ISP的MIRROR模块，可以实现镜像,镜像后的pattern不需要配置,软件会自动转换。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] MIRROR_CFG_S *pMirror
*            类型为MIRROR_CFG_S的结构体指针，详细成员变量请查看MIRROR_CFG_S结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_MirrorEnable(FH_UINT32 u32IspDevId, MIRROR_CFG_S *pMirror);
/*
*   Name: API_ISP_SetMirrorAndflip
*            配置SENSOR的镜像和水平翻转。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_BOOL mirror
*            镜像(mirror=1)，正常(mirror=0)
*
*       [IN]  FH_BOOL flip
*            水平翻转(flip=1)，正常(flip=0)
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetMirrorAndflip(FH_UINT32 u32IspDevId, FH_BOOL mirror, FH_BOOL flip);
/*
*   Name: API_ISP_SetMirrorAndflipEx
*            配置SENSOR的镜像和水平翻转，同时会更改ISP中相关bayer配置。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] FH_BOOL mirror
*            镜像(mirror=1)，正常(mirror=0)
*
*       [IN]  FH_BOOL flip
*            水平翻转(flip=1)，正常(flip=0)
*
*       [IN] FH_UINT32 bayer
*            镜像和水平翻转影响之后的BAYER格式。
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetMirrorAndflipEx(FH_UINT32 u32IspDevId, FH_BOOL mirror, FH_BOOL flip,FH_UINT32 bayer);
/*
*   Name: API_ISP_GetMirrorAndflip
*            获取当前SENSOR镜像和水平翻转的状态
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] FH_BOOL *mirror
*            镜像(mirror=1)，正常(mirror=0)
*
*       [OUT]  FH_BOOL *flip
*            水平翻转(flip=1)，正常(flip=0)
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetMirrorAndflip(FH_UINT32 u32IspDevId, FH_BOOL *mirror, FH_BOOL *flip);

/**POST_GAIN*/
/*
*   Name: API_ISP_SetPostGain
*            设置postgain参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const ISP_POST_GAIN_CFG *pstPostGainCfg
*            类型为ISP_POST_GAIN_CFG的结构体指针，详细成员变量请查看ISP_POST_GAIN_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       post_gain模块目前作为一部分数字增益使用,不建议随意配置增益,防止ae策略出现一些异常
*/
FH_SINT32 API_ISP_SetPostGain(FH_UINT32 u32IspDevId, const ISP_POST_GAIN_CFG *pstPostGainCfg);
/*
*   Name: API_ISP_GetPostGain
*           获取postgain参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_POST_GAIN_CFG *pstPostGainCfg
*            类型为ISP_POST_GAIN_CFG的结构体指针，详细成员变量请查看ISP_POST_GAIN_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetPostGain(FH_UINT32 u32IspDevId, ISP_POST_GAIN_CFG *pstPostGainCfg);
/**SMART IR**/
/*
*   Name: API_ISP_SetSmartIrCfg
*            设置智能切换日夜的参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] SMART_IR_CFG *pstSmartIrCfg
*            类型为SMART_IR_CFG的结构体指针，详细成员变量请查看SMART_IR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetSmartIrCfg(FH_UINT32 u32IspDevId, SMART_IR_CFG *pstSmartIrCfg);
/*
*   Name: API_ISP_GetSmartIrCfg
*            获取智能切换日夜的参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] SMART_IR_CFG *pstSmartIrCfg
*            类型为SMART_IR_CFG的结构体指针，详细成员变量请查看SMART_IR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetSmartIrCfg(FH_UINT32 u32IspDevId, SMART_IR_CFG *pstSmartIrCfg);
/**WDR**/
/*
*   Name: API_ISP_SetWdrMergeCfg
*            该函数可以配置wdr下长短帧的merge曲线，通过配置十二对坐标可以配置短帧的merge曲线。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const ISP_WDR_MERGE_CFG *pstWdrMergeCfg
*            类型为ISP_WDR_MERGE_CFG的结构体指针，详细成员变量请查看ISP_WDR_MERGE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetWdrMergeCfg(FH_UINT32 u32IspDevId, ISP_WDR_MERGE_CFG *pstWdrMergeCfg);
/*
*   Name: API_ISP_GetWdrCfg
*            用于获得wdr配置参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_WDR_CFG *pstWdrCfg
*            类型为ISP_WDR_CFG的结构体指针，详细成员变量请查看ISP_WDR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetWdrCfg(FH_UINT32 u32IspDevId, ISP_WDR_CFG *pstWdrCfg);
/*
*   Name: API_ISP_SetWdrCfg
*            用于设置wdr配置参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_WDR_CFG *pstWdrCfg
*            类型为ISP_WDR_CFG的结构体指针，详细成员变量请查看ISP_WDR_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetWdrCfg(FH_UINT32 u32IspDevId, ISP_WDR_CFG *pstWdrCfg);
/**OTHERS*/
/*
*   Name: API_ISP_SetCropInfo
*            配置输入幅面的水平和垂直的处理偏移。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] int offset_x
*            水平方向的偏移
*
*       [IN] int offset_y
*            垂直方向的偏移。
*
*   Return:
*            0(正确)
*        -3004(偏移值超过输入幅面或者为奇数)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCropInfo(FH_UINT32 u32IspDevId, int offset_x,int offset_y);
/*
*   Name: *FH_ISP_Version
*            获取、打印ISP版本号。
*
*   Parameters:
*
*       [IN] FH_UINT32 print_enable
*            打印ISP库版本号(1)，不打印ISP库版本号(0)
*
*   Return:
*            ISP库版本号的字符串。
*   Note:
*       无
*/
FH_CHAR *FH_ISP_Version(FH_UINT32 print_enable);
/*
*   Name: *FH_ISPCORE_Version
*            获取、打印ISP版本号。
*
*   Parameters:
*
*       [IN]  void
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 FH_ISPCORE_Version(void);
/**FAST_BOOT**/
/*
*   Name: API_ISP_RegisterPicStartCallback
*            在ISP PicStartB的时候的回调函数，可以用在RTT下统计时间。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ispIntCallback cb
*            void型的函数指针，指向回调函数的位置。
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_RegisterPicStartCallback(FH_UINT32 u32IspDevId, ispIntCallback cb);
/*
*   Name: API_ISP_RegisterPicEndCallback
*            在ISP PicEndP的时候的回调函数，可以用在RTT下统计时间。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ispIntCallback cb
*            void型的函数指针，指向回调函数的位置。
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_RegisterPicEndCallback(FH_UINT32 u32IspDevId, ispIntCallback cb);
/*
*   Name: API_ISP_RegisterIspInitCfgCallback
*            ISP硬件初始化回调函数，其执行位置在API_ISP_Init之前，此时ISP未启动，流程中仅执行一次。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ispInitCfgCallback cb
*            void型的函数指针，指向回调函数的位置。
*
*   Return:
*            0(正确)
*   Note:
*       无
*/
FH_SINT32 API_ISP_RegisterIspInitCfgCallback(FH_UINT32 u32IspDevId, ispInitCfgCallback cb);
/*
*   Name: API_ISP_SetBlcInitCfg
*            初始化BLC所有通道的减DC值，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const BLC_INIT_CFG *pstBlcInitCfg
*            类型为BLC_INIT_CFG的结构体指针，详细成员变量请查看BLC_INIT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetBlcInitCfg(FH_UINT32 u32IspDevId, const BLC_INIT_CFG *pstBlcInitCfg);
/*
*   Name: API_ISP_SetWbInitCfg
*            初始化WB三个通道增益值，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const WB_INIT_CFG *pstWbInitCfg
*            类型为WB_INIT_CFG的结构体指针，详细成员变量请查看WB_INIT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetWbInitCfg(FH_UINT32 u32IspDevId, const WB_INIT_CFG *pstWbInitCfg);
/*
*   Name: API_ISP_SetCcmInitCfg
*            初始化CCM矩阵硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] CCM_INIT_CFG *pstCcmInitCfg
*            类型为DPC_INIT_CFG的结构体指针，详细成员变量请查看DPC_INIT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCcmInitCfg(FH_UINT32 u32IspDevId, const CCM_INIT_CFG *pstCcmInitCfg);
/*
*   Name: API_ISP_SetDpcInitCfg
*            初始化DPC硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const DPC_INIT_CFG *pstDpcInitCfg
*            类型为DPC_INIT_CFG的结构体指针，详细成员变量请查看DPC_INIT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetDpcInitCfg(FH_UINT32 u32IspDevId, const DPC_INIT_CFG *pstDpcInitCfg);
/*
*   Name: API_ISP_SetApcInitCfg
*            初始化APC硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const APC_INIT_CFG *pstApcInitCfg
*            类型为APC_INIT_CFG的结构体指针，详细成员变量请查看APC_INIT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetApcInitCfg(FH_UINT32 u32IspDevId, const APC_INIT_CFG *pstApcInitCfg);
/*
*   Name: API_ISP_SetYnrInitCfg
*            初始化YNR硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const YNR_INIT_CFG *pstYnrInitCfg
*            类型为YNR_INIT_CFG的结构体指针，详细成员变量请查看YNR_INIT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetYnrInitCfg(FH_UINT32 u32IspDevId, const YNR_INIT_CFG *pstYnrInitCfg);
/*
*   Name: API_ISP_SetCtrInitCfg
*            配置对比度值到硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const CTR_INIT_CFG *pstCtrInitCfg
*            类型为CTR_INIT_CFG的结构体指针，详细成员变量请查看CTR_INIT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCtrInitCfg(FH_UINT32 u32IspDevId, const CTR_INIT_CFG *pstCtrInitCfg);
/*
*   Name: API_ISP_SetSatInitCfg
*            配置饱和度值到硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const SAT_INIT_CFG *pstSatInitCfg
*            SAT_INIT_CFG的结构体指针，详细参数查看结构体SAT_INIT_CFG注释。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetSatInitCfg(FH_UINT32 u32IspDevId, const SAT_INIT_CFG *pstSatInitCfg);
/*
*   Name: API_ISP_SetGammaModeInitCfg
*            根据传入的gamma mode值，配置相应硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const GAMMA_MODE_INIT_CFG *pstGammaModeInitCfg
*            目标配置的gamma mode。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetGammaModeInitCfg(FH_UINT32 u32IspDevId, const GAMMA_MODE_INIT_CFG *pstGammaModeInitCfg);
/*
*   Name: API_ISP_SetCGammaInitCfg
*            配置cgamma table到硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const GAMMA_INIT_CFG *pstCGammaInitCfg
*            结构体GAMMA_INIT_CFG的指针，目标配置cgamma表。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCGammaInitCfg(FH_UINT32 u32IspDevId, const GAMMA_INIT_CFG *pstCGammaInitCfg);
/*
*   Name: API_ISP_SetYGammaInitCfg
*            配置ygamma table到硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const GAMMA_INIT_CFG *pstYGammaInitCfg
*            结构体GAMMA_INIT_CFG的指针，目标配置的ygamma表。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetYGammaInitCfg(FH_UINT32 u32IspDevId, const GAMMA_INIT_CFG *pstYGammaInitCfg);
/*
*   Name: API_ISP_SetIspGainInitCfg
*            配置Isp Gain到硬件寄存器，调用阶段是在API_ISP_RegisterIspInitCfgCallback中。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const ISP_GAIN_INIT_CFG *pstIspGainInitCfg
*            结构体ISP_GAIN_INIT_CFG的指针，目标配置的Isp Gain。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetIspGainInitCfg(FH_UINT32 u32IspDevId, const ISP_GAIN_INIT_CFG *pstIspGainInitCfg);
/**CCM**/
/*
*   Name: API_ISP_SetCcmCfg
*            配置CCM。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] CCM_TABLE *pstCcmCfg
*             类型为CCM_TABLE的结构体指针，详细成员变量请查看CCM_TABLE结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCcmCfg(FH_UINT32 u32IspDevId, CCM_TABLE *pstCcmCfg);
/*
*   Name: API_ISP_GetCcmCfg
*           获取CCM。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] CCM_TABLE *pstCcmCfg
*             类型为CCM_TABLE的结构体指针，详细成员变量请查看CCM_TABLE结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetCcmCfg(FH_UINT32 u32IspDevId, CCM_TABLE *pstCcmCfg);
/*
*   Name: API_ISP_SetCcmHwCfg
*            配置ccm参数至硬件寄存器
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const ISP_CCM_CFG *pstCcmCfg
*             类型为ISP_CCM_CFG的结构体指针，详细成员变量请查看ISP_CCM_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetCcmHwCfg(FH_UINT32 u32IspDevId, const ISP_CCM_CFG *pstCcmCfg);
/*
*   Name: API_ISP_GetCcmHwCfg
*            从硬件寄存器获取ccm参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_CCM_CFG *pstCcmCfg
*            类型为ISP_CCM_CFG的结构体指针，详细成员变量请查看ISP_CCM_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetCcmHwCfg(FH_UINT32 u32IspDevId, ISP_CCM_CFG *pstCcmCfg);
/*
*   Name: API_ISP_SetAcrCfg
*            设置ccm自动弱化参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_ACR_CFG *pstAcrCfg
*            类型为ISP_ACR_CFG的结构体指针，详细成员变量请查看ISP_ACR_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAcrCfg(FH_UINT32 u32IspDevId, ISP_ACR_CFG *pstAcrCfg);
/*
*   Name: API_ISP_GetAcrCfg
*            获取ccm自动弱化参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_ACR_CFG *pstAcrCfg
*            类型为ISP_ACR_CFG的结构体指针，详细成员变量请查看ISP_ACR_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAcrCfg(FH_UINT32 u32IspDevId, ISP_ACR_CFG *pstAcrCfg);
/**DEHAZE**/
/*
*   Name: API_ISP_SetDehazeCfg
*           设置去雾参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_DEHAZE_CFG *pstDehazeCfg
*             类型为ISP_DEHAZE_CFG的结构体指针，详细成员变量请查看ISP_DEHAZE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetDehazeCfg(FH_UINT32 u32IspDevId, ISP_DEHAZE_CFG *pstDehazeCfg);
/*
*   Name: API_ISP_GetDehazeCfg
*           获得去雾参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_DEHAZE_CFG *pstDehazeCfg
*             类型为ISP_DEHAZE_CFG的结构体指针，详细成员变量请查看ISP_DEHAZE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetDehazeCfg(FH_UINT32 u32IspDevId, ISP_DEHAZE_CFG *pstDehazeCfg);
/*
*   Name: API_ISP_SetDeCfg
*           设置暗部增强参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_DE_CFG *pstDeCfg
*             类型为ISP_DE_CFG的结构体指针，详细成员变量请查看ISP_DE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetDeCfg(FH_UINT32 u32IspDevId, ISP_DE_CFG *pstDeCfg);
/*
*   Name: API_ISP_GetDeCfg
*           获得暗部参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_DE_CFG *pstDeCfg
*             类型为ISP_DE_CFG的结构体指针，详细成员变量请查看ISP_DE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetDeCfg(FH_UINT32 u32IspDevId, ISP_DE_CFG *pstDeCfg);
/**LCE**/
/*
*   Name: API_ISP_SetLceCfg
*           设置局部色度参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_LCE_CFG *pstLceCfg
*             类型为ISP_LCE_CFG的结构体指针，详细成员变量请查看ISP_LCE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetLceCfg(FH_UINT32 u32IspDevId, ISP_LCE_CFG *pstLceCfg);
/*
*   Name: API_ISP_GetLceCfg
*           获得局部色度参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_LCE_CFG *pstLceCfg
*             类型为ISP_LCE_CFG的结构体指针，详细成员变量请查看ISP_LCE_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetLceCfg(FH_UINT32 u32IspDevId, ISP_LCE_CFG *pstLceCfg);

/** STATISTICS **/
/*
*   Name: API_ISP_GetAFStat
*           读取af统计结果信息。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_AF_STAT *pstAfStat
*            类型为ISP_AF_STAT的结构体指针，详细成员变量请查看ISP_AF_STAT结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAFStat(FH_UINT32 u32IspDevId, ISP_AF_STAT *pstAfStat);
/*
*   Name: API_ISP_SetAFStatCfg
*            设置af统计配置相关参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const ISP_AF_STAT_CFG *pstAfStatCfg
*            类型为ISP_AF_STAT_CFG的结构体指针，详细成员变量请查看ISP_AF_STAT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       1. af的win0和win1两个窗口不能有交叠,否则统计数据可能会出错
*       2. 统计窗的大小参数输入范围为0-512，实际生效的统计窗的大小为2-512
*       3. 统计窗的大小和偏移都只支持偶数，输入非偶数时API会自动校正为偶数
*/
FH_SINT32 API_ISP_SetAFStatCfg(FH_UINT32 u32IspDevId, const ISP_AF_STAT_CFG *pstAfStatCfg);
/*
*   Name: API_ISP_GetAFStatCfg
*            获取af统计配置相关参数。
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] const ISP_AF_STAT_CFG *pstAfStatCfg
*            类型为ISP_AF_STAT_CFG的结构体指针，详细成员变量请查看ISP_AF_STAT_CFG结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAFStatCfg(FH_UINT32 u32IspDevId, ISP_AF_STAT_CFG *pstAfStatCfg);
/*
*   Name: API_ISP_GetAwbAdvStat
*            获取awb高级统计信息
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_AWB_ADV_STAT * pstAwbAdvStat
*            类型为ISP_AWB_ADV_STAT的结构体指针，详细成员变量请查看ISP_AWB_ADV_STAT结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       统计窗个数默认16*16,也可通过API_ISP_SetAwbAdvStatCfg进行重新配置,最大支持32*32
*       使用示例:
*              ISP_AWB_ADV_STAT awbAdvStat[256];  // 256是默认窗口配置,若改动的话通过API_ISP_GetAwbAdvStatCfg获取当前统计窗个数
*              API_ISP_GetAwbAdvStat(awbAdvStat);
*/
FH_SINT32 API_ISP_GetAwbAdvStat(FH_UINT32 u32IspDevId, ISP_AWB_ADV_STAT * pstAwbAdvStat);
/*
*   Name: API_ISP_SetAwbAdvStatCfg
*            设置awb高级统计配置相关参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const ISP_AWB_ADV_STAT_CFG *pstAwbStatCfg
*            类型为ISP_AWB_ADV_STAT_CFG的结构体指针，详细成员变量请查看ISP_AWB_ADV_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetAwbAdvStatCfg(FH_UINT32 u32IspDevId, const ISP_AWB_ADV_STAT_CFG *pstAwbStatCfg);
/*
*   Name: API_ISP_GetAwbAdvStatCfg
*            获取awb高级统计配置相关参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_AWB_ADV_STAT_CFG *pstAwbStatCfg
*            类型为ISP_AWB_ADV_STAT_CFG的结构体指针，详细成员变量请查看ISP_AWB_ADV_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetAwbAdvStatCfg(FH_UINT32 u32IspDevId, ISP_AWB_ADV_STAT_CFG *pstAwbStatCfg);

/*
*   Name: API_ISP_GetShortAwbStat
*            获取awb短帧8*8统计信息
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_AWB_FRONT_STAT * pstAwbFrontStat
*            类型为ISP_AWB_FRONT_STAT的结构体指针，详细成员变量请查看ISP_AWB_FRONT_STAT结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetShortAwbStat(FH_UINT32 u32IspDevId, ISP_AWB_FRONT_STAT * pstAwbFrontStat);
/*
*   Name: API_ISP_SetShortAwbStatCfg
*            设置awb短帧8*8统计配置相关参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const ISP_AWB_STAT_CFG * pstAwbFrontStatCfg
*            类型为ISP_AWB_STAT_CFG的结构体指针，详细成员变量请查看ISP_AWB_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       传入的参数经过计算后可能由于对齐问题与获取的参数不完全一致
*/
FH_SINT32 API_ISP_SetShortAwbStatCfg(FH_UINT32 u32IspDevId, const ISP_AWB_STAT_CFG * pstAwbFrontStatCfg);
/*
*   Name: API_ISP_GetShortAwbStatCfg
*            获取awb短帧8*8统计配置相关参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_AWB_STAT_CFG * pstAwbFrontStatCfg
*            类型为ISP_AWB_STAT_CFG的结构体指针，详细成员变量请查看ISP_AWB_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetShortAwbStatCfg(FH_UINT32 u32IspDevId, ISP_AWB_STAT_CFG * pstAwbFrontStatCfg);
/*
*   Name: API_ISP_GetHistStat
*            获取hist统计结果
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_HIST_STAT *psthistStat
*            类型为ISP_HIST_STAT的结构体指针，详细成员变量请查看ISP_HIST_STAT结构体定义。
*
*   Return:
*            0(正确)
*            非0(失败，详见错误码)
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetHistStat(FH_UINT32 u32IspDevId, ISP_HIST_STAT *psthistStat);
/*
*   Name: API_ISP_SetHistStatCfg
*            设置hist统计配置相关参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const ISP_HIST_STAT_CFG *pstHistStatCfg
*            类型为ISP_HIST_STAT_CFG的结构体指针，详细成员变量请查看ISP_HIST_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetHistStatCfg(FH_UINT32 u32IspDevId, const ISP_HIST_STAT_CFG *pstHistStatCfg);
/*
*   Name: API_ISP_GetHistStatCfg
*            获取hist统计配置相关参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] ISP_HIST_STAT_CFG *pstHistStatCfg
*            类型为ISP_HIST_STAT_CFG的结构体指针，详细成员变量请查看ISP_HIST_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetHistStatCfg(FH_UINT32 u32IspDevId, ISP_HIST_STAT_CFG *pstHistStatCfg);
/*
*   Name: API_ISP_GetGlobeStat
*            获取global统计信息
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] GLOBE_STAT *pstGlobeStat
*            类型为GLOBE_STAT的结构体指针，详细成员变量请查看GLOBE_STAT结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       使用示例:
*               GLOBE_STAT glStat[256];  // 256是默认窗口配置,若改动的话通过API_ISP_GetGlobeStatCfg获取当前统计窗个数
*               API_ISP_GetGlobeStat(glStat);
*/
FH_SINT32 API_ISP_GetGlobeStat(FH_UINT32 u32IspDevId, GLOBE_STAT *pstGlobeStat);
/*
*   Name: API_ISP_SetGlobeStatCfg
*            设置global统计配置相关参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] const GLOBE_STAT_CFG *pstGlobeStatCfg
*            类型为GLOBE_STAT_CFG的结构体指针，详细成员变量请查看GLOBE_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_SetGlobeStatCfg(FH_UINT32 u32IspDevId, const GLOBE_STAT_CFG *pstGlobeStatCfg);
/*
*   Name: API_ISP_GetGlobeStatCfg
*            获取global统计配置相关参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] GLOBE_STAT_CFG *pstGlobeStatCfg
*            类型为GLOBE_STAT_CFG的结构体指针，详细成员变量请查看GLOBE_STAT_CFG结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetGlobeStatCfg(FH_UINT32 u32IspDevId, GLOBE_STAT_CFG *pstGlobeStatCfg);
/*
*   Name: API_ISP_GetDehazeStat
*            获取Dehaze统计
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] DEHAZE_STAT *pstDehazeStat
*            类型为DEHAZE_STAT的结构体指针，详细成员变量请查看DEHAZE_STAT结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetDehazeStat(FH_UINT32 u32IspDevId, DEHAZE_STAT *pstDehazeStat);
/*
*   Name: API_ISP_GetGroupGlobeStat
*            获取拼接组的global统计信息
*
*   Parameters:
*
*       [IN]  FH_UINT8 u8GrpId
*            拼接组的ID
*
*       [OUT] GROUP_GLOBE_STAT *pstGroupGlobeStat
*            类型为GROUP_GLOBE_STAT的结构体指针，详细成员变量请查看GROUP_GLOBE_STAT结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetGroupGlobeStat(FH_UINT8 u8GrpId, GROUP_GLOBE_STAT *pstGroupGlobeStat);
/*
*   Name: API_ISP_GetGroupAwbAdvStat
*            获取拼接组的qwb_adv统计信息
*
*   Parameters:
*
*       [IN]  FH_UINT8 u8GrpId
*            拼接组的ID
*
*       [OUT] GROUP_AWB_ADV_STAT *pstGroupAwbAdvStat
*            类型为GROUP_AWB_ADV_STAT的结构体指针，详细成员变量请查看GROUP_AWB_ADV_STAT结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetGroupAwbAdvStat(FH_UINT8 u8GrpId, GROUP_AWB_ADV_STAT *pstGroupAwbAdvStat);
/*
*   Name: API_ISP_GetGroupHistStat
*            获取拼接组的hist统计信息
*
*   Parameters:
*
*       [IN]  FH_UINT8 u8GrpId
*            拼接组的ID
*
*       [OUT] GROUP_Hist_STAT *pstGroupHistStat
*            类型为GROUP_Hist_STAT的结构体指针，详细成员变量请查看GROUP_Hist_STAT结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_GetGroupHistStat(FH_UINT8 u8GrpId, GROUP_HIST_STAT *pstGroupHistStat);
/**DBG**/
/*
*   Name: API_ISP_DbgDumpGetConfig
*            传入参数名字，获取合适的DBG模块的配置
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN/OUT] DbgDump_T *dbgConf
*            类型为DbgDump_T的结构体指针，详细成员变量请查看DbgDump_T结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*       无
*/
FH_SINT32 API_ISP_DbgDumpGetConfig(FH_UINT32 u32IspDevId, DbgDump_T* dbgCfg);
/*
*   Name: API_ISP_DbgDumpGetConfig
*            配置DBG模块的参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [OUT] DbgDump_T *dbgConf
*            类型为DbgDump_T的结构体指针，详细成员变量请查看DbgDump_T结构体定义。
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*      建议调用该API前首先，通过API_ISP_DbgDumpGetConfig获取合适的配置
*/
FH_SINT32 API_ISP_DbgDumpSetConfig(FH_UINT32 u32IspDevId, DbgDump_T* dbgCfg);
/**ISP OUT**/
/*
*   Name: API_ISP_SetIspOutVgsCfg
*            配置DBG模块的参数
*
*   Parameters:
*
*       [IN]  FH_UINT32 u32IspDevId
*            ISP的设备号
*
*       [IN] ISP_ROTATE_OPS_E enIspRotateOps
*            类型为ISP_ROTATE_OPS_E枚举中的值
*
*   Return:
*           0(成功)
*           非0(失败，详见错误码)
*
*   Note:
*      1. 该接口会重新注册media设备，调用完之后需要重新绑定
*/
FH_SINT32 API_ISP_SetIspOutVgsCfg(FH_UINT32 u32IspDevId, ISP_ROTATE_OPS_E enIspRotateOps);
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*_ISP_API_H_*/

