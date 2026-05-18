#ifndef _ISP_SENSOR_IF_H_
#define _ISP_SENSOR_IF_H_

#include "types/type_def.h"
#include "isp_common.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */
#pragma pack(4)

#define MIRROR_FLIP_BAYER_FORMATE_SIZE    16   // 对应get_sensor_mirror_flip_bayer_format函数指针返回的数据大小
#define USER_AWB_GAIN_SIZE                48   // 对应get_user_awb_gain函数指针返回的数据大小
#define USER_LTM_CURVE_SIZE               512  // 对应get_user_ltm_curve函数指针返回的数据大小
#define SENSOR_AWB_GAIN_SIZE              12   // 对应get_awb_gain/set_awb_gain函数指针传参的数据大小
#define SENSOR_USER_DEFINED_DATA_SIZE     512  // 对应SENSOR_USER_DEFINED_DATA* data指针返回的数据大小

typedef struct _Sensor_AE_Default_S
{
    unsigned int  minIntt;  // 最小曝光时间，单位为行
    unsigned int  maxIntt;  // 最大曝光时间(非降帧时)，单位为行
    unsigned int  minAGain;  // 最小曝光增益,U.6精度
    unsigned int  maxAGain;  // 最大曝光增益,U.6精度
    unsigned int  fullLineStd;  // 框架高度(非降帧时)
    unsigned int  MinRstLine;  // 计算最大曝光时间时的最小复位行数
}Sensor_AE_Default_S;

typedef struct _Sensor_AE_INFO_S
{
    unsigned int  currIntt;  // 当前曝光时间，单位为行
    unsigned int  currAGain;  // 当前曝光增益，u.6精度
    unsigned int  currHsf;  // 当前行频
    unsigned int  currFrameH;  // 当前框架高度
}Sensor_AE_INFO_S;

typedef union
{
    unsigned int dw[128];
} SENSOR_USER_DEFINED_DATA;

typedef struct
{
	FH_UINT8 u8CsiDeviceId;
	FH_UINT8 u8CciDeviceId;
	FH_BOOL  bGrpSync;//是否需要多sensor同步,
} Sensor_Init_t;

/**
 * @brief		ISP sensor 接口，每个sensor模块应该使用该接口以便与ISP对接，通过安装sensor，
 *				将其加入ISP Core中。
 */
struct isp_sensor_if		// module interface
{
	FH_CHAR*	name;			/*!< sensor名称 */

/**
 * @brief		获取配置幅面信息
 * @param[in]	无
 * @return 		幅面信息
 */
	FH_SINT32 	(*get_vi_attr)(void *obj, ISP_VI_ATTR_S *vi_attr);

/**
 * @brief		设置sensor图像的水平翻转和垂直翻转
 * @param[in]	sensor_en_stat 最低位为flip(vertical)翻转 次低位为mirror(horizontal)翻转
 * @return 		无
 */
	FH_SINT32	(*set_flipmirror)(void *obj, FH_UINT32 sensor_en_stat);

/**
 * @brief		获取sensor图像的水平翻转和垂直翻转
 * @param[out]	sensor_en_stat 最低位为flip(vertical)翻转 次低位为mirror(horizontal)翻转
 * @return 		无
 */
	FH_SINT32	(*get_flipmirror)(void *obj, FH_UINT32 *sensor_en_stat);

/**
 * @brief		设置光圈大小
 * @param[in]	无
 * @return 		设置光圈大小
 */
	FH_SINT32	(*set_iris)(void *obj, FH_UINT32 iris);

/**
 * @brief		sensor初始化
 * @param[in]	选择当前使用哪个设备来初始化sensor
 * @return 		错误信息，详见错误码
 */
	FH_SINT32	(*init)(void *obj, Sensor_Init_t* initCfg);

/**
 * @brief		sensor复位
 * @param[in]	无
 * @return 		无
 */
	FH_VOID		(*reset)(void *obj);

/**
 * @brief		sensor退出
 * @param[in]	无
 * @return 		无
 */
	FH_SINT32	(*deinit)(void *obj);

	FH_SINT32	(*set_sns_fmt)(void *obj, int format);

	/**
 * @brief		sensor
 * @param[in]
 * @return
 */
	FH_SINT32   (*kick)(void *obj);

	FH_SINT32	(*set_sns_reg)(void *obj, FH_UINT16 addr, FH_UINT16 data);

	FH_SINT32	(*set_exposure_ratio)(void *obj, FH_UINT32 exposure_ratio);

	FH_SINT32	(*get_exposure_ratio)(void *obj, FH_UINT32 *exposure_ratio);

	FH_SINT32	(*get_sensor_attribute)(void *obj, char * name,FH_UINT32 *value);

	FH_SINT32	(*set_lane_num_max)(void *obj, FH_UINT32 lane_num_max);

	FH_SINT32	(*get_sns_reg)(void *obj, FH_UINT16 addr, FH_UINT16 *data);

	FH_SINT32	(*get_awb_gain)(void *obj, FH_UINT32 *awb_gain);

	FH_SINT32	(*set_awb_gain)(void *obj, FH_UINT32 *awb_gain);

	SENSOR_USER_DEFINED_DATA*		data;

	void*                           para;

	FH_SINT32	(*common_if)(void *obj, unsigned int cmd, ISP_SENSOR_COMMON_CMD_DATA0* data0, ISP_SENSOR_COMMON_CMD_DATA1* data1);

// new add interface

/**
 * @brief		获取sensor的默认配置
 * @param[out]	此款sensor在当前配置下的最大最小曝光时间，单位为行;最大最小增益，U.6精度;框架高度;降帧条件下最大曝光时间，单位为行
 * @return 		0
 */
	FH_SINT32	(*get_sns_ae_default)(void *obj, Sensor_AE_Default_S *sensAEDefault);

/**
 * @brief		获取当前sensor的曝光状态
 * @param[out]	当前曝光时间，单位为行;当前曝光增益，U.6;当前行频以及当前框架高度
 * @return 		0
 */
	FH_SINT32	(*get_sns_ae_info)(void *obj, Sensor_AE_INFO_S *sensAEInfo);

/**
 * @brief		设置sensor曝光时间
 * @param[in]	sensor的曝光时间设置，单位为行;fNo:表示帧号，当且仅当wdr下使用，0表示第0帧，1表示第1帧，以此类推,
 *				若长短帧intt生效时机不一样,则需要根据帧号分开写,若时机一样,可统一放在fNo=0的条件下实现
 * @return 		0
 */
	FH_SINT32	(*set_sns_intt)(void *obj, FH_UINT32 intt, FH_UINT8 fNo);

/**
 * @brief		获取当前实际可配置曝光时间
 * @param[inout]	输入需要配置的sensor的曝光时间,单位为行, 输出实际可配置的sensor的曝光时间，单位为行, 若无限制则可直接return
 * @return		0
 */
	FH_SINT32	(*calc_sns_valid_intt)(void *obj, FH_UINT32 *u32Intt);

/**
 * @brief		设置sensor增益
 * @param[in]	gain sensor的增益，6位小数(0x40 表示 x1.0);fNo:表示帧号，当且仅当wdr下使用，0表示第0帧，1表示第1帧，以此类推
 *				若长短帧gain生效时机不一样,则需要根据帧号分开写,若时机一样,可统一放在fNo=0的条件下实现
 * @return 		0
 */
	FH_SINT32	(*set_sns_gain)(void *obj, FH_UINT32 again, FH_UINT8 fNo);

/**
 * @brief		获取当前实际可配置增益值
 * @param[inout]	输入需要配置的sensor的增益值，6位小数（0x40 表示 x1.0）,输出实际可配置的sensor的增益值，6位小数（0x40 表示 x1.0）,若无限制则可直接return
 * @return 		0
 */

	FH_SINT32	(*calc_sns_valid_gain)(void *obj, FH_UINT32 *u32Gain);

/**
 * @brief		设置sensor框架高度,达到降帧目的
 * @param[in]	frame_H:框架高度, 用于通过降低帧率来增加曝光时间
 * @return		无
 */
	FH_SINT32	(*set_sns_frame_height)(void *obj, FH_UINT32 frameH);

/**
 * @brief		获取sensor各种幅面切换下的bayer值
 * @param[in]	无
 * @return		bayer值对应的指针, sensor.h中定义数组如下格式:
* static unsigned int MirrorFlipBayerFormat[4]=
	{
		正常输出时的pattern, flip时的pattern, mirror时的pattern, 同时flip和mirror的pattern
	};
 */
 	FH_UINT32*	(*get_sensor_mirror_flip_bayer_format)(void *obj);
/**
 * @brief		获取不同色温下的白平衡参数指针
 * @param[in]	idx:参数索引，不同的索引值对应不同的色温下的白平衡参数
 * @return		白平衡参数指针,目前支持4组色温下的r/g/b gain, sensor.h中定义数组如下格式:
 * static unsigned int AwbGain[4][3] = {
		{rgain, ggain, bgain},//色温0
		{rgain, ggain, bgain},//色温1
		{rgain, ggain, bgain},//色温2
		{rgain, ggain, bgain},//色温3
};
 */
 	FH_UINT32*	(*get_user_awb_gain)(void *obj, FH_UINT32 idx);
/**
 * @brief		根据传入的索引值，返回不同的LTM参数指针
 * @param[in]	idx:参数索引，不同的索引值对应不同的LTM参数
 * @return		LTM参数指针,一根曲线对应128个寄存器
 */
 	FH_UINT32*	(*get_user_ltm_curve)(void *obj, FH_UINT32 idx);
/**
 * @brief		判断sensor是否链接上,仅用于RTT多sensor下
 * @param[in]	选择当前使用哪个设备来初始化sensor
 * @return		0表示未连接，1表示已连接
 */
 	FH_SINT32	(*is_sensor_connect)(void *obj, FH_UINT8 deviceId);
};

enum COMMON_IF_CMD{
    CMD_INIT = 0,
    CMD_MAP_INTT_GAIN = 1,
    CMD_GET_BLC_VALUE = 2,
    CMD_GET_GPIO_PARAM = 3,
    CMD_GET_REGS_INFO  = 4,
    COMMON_IF_CMD_DUMMY =0xffffffff,
};

struct isp_sensor_if* Sensor_Create(void);
FH_VOID Sensor_Destroy(struct isp_sensor_if *s_if);

#pragma pack()
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _ISP_SENSOR_H_ */
