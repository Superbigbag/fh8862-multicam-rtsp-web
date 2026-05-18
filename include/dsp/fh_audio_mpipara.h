#ifndef FH_AUIDO_MPIPARA_H_
#define FH_AUIDO_MPIPARA_H_

typedef enum
{
    AC_SR_8K   = 8000,
    AC_SR_16K  = 16000,
    AC_SR_32K  = 32000,
    AC_SR_48K  = 48000,

    AC_SR_110K = 11025,
    AC_SR_220K = 22050,
    AC_SR_441K = 44100,
    AC_SR_DUMMY = 0x1fffffff,
}FH_AC_SAMPLE_RATE_E;

typedef enum
{
    AC_BW_8  = 8,   /*not supported*/
    AC_BW_16 = 16,
    AC_BW_24 = 24,  /*not supported*/
    AC_BW_DUMMY = 0x1fffffff,
}FH_AC_BIT_WIDTH_E;


typedef struct
{
    FH_UINT32 len;
    FH_UINT8 *data;
}FH_AC_AO_FRAME_S;

typedef enum
{
    FH_AC_MIC_IN   = 0,
    FH_AC_LINE_IN  = 1,
    FH_AC_SPK_OUT  = 2,
    FH_AC_LINE_OUT = 3,
    FH_AC_IO_TYPE_MAX = 4,
    FH_AC_IO_DUMMY = 0x1fffffff,
}FH_AC_IO_TYPE_E;

typedef enum
{
    FH_AO_MODE_LEFT  = 0, /*It's the default value, supported by all chips*/
    FH_AO_MODE_RIGHT = 1, /*Now only support for FH8856*/
    FH_AO_MODE_BOTH  = 2, /*left channel and right channel output the same audio samples*/
    FH_AO_MODE_DUMMY = 0x1fffffff,
}FH_AC_AO_MODE_E;

typedef enum
{
    FH_PT_LPCM     = 0,
    FH_PT_G711A    = 1, /*not supported*/
    FH_PT_G711U    = 2, /*not supported*/
    FH_PT_G726_16K = 3, /*not supported*/
    FH_PT_G726_32K = 4, /*not supported*/
    FH_PT_AAC      = 5, /*not supported*/
    FH_PT_MAX      = 6,
    FH_PT_DUMMY = 0x1fffffff,
}FH_AC_PT_TYPE_E;

typedef struct
{
    FH_AC_IO_TYPE_E io_type;
    FH_AC_SAMPLE_RATE_E sample_rate;
    FH_AC_BIT_WIDTH_E bit_width;
	FH_AC_PT_TYPE_E enc_type;   /*encoding type,只支持FH_PT_LPCM*/    
    FH_UINT32 period_size;  /*一帧数据中的采样点个数 */
	
	FH_UINT32 channel_mask; /*bit0代表channel0,bit1代表channel1,bit2代表channel2*/

	FH_UINT32 frame_num;    /*一般置0即可, 表示设置为系统默认值*/
	
	FH_UINT32 reserved;	 /*保留值,赋值为0即可*/
}FH_AC_CONFIG;

typedef struct
{
	FH_UINT32 mix_enable;
	FH_UINT32 mix_channel_mask;
	FH_UINT32 reserved;
}FH_AC_MIX_CONFIG;

#pragma pack(4)
#define FH_AI_CHANNEL_NUM (3)
typedef struct
{
    FH_UINT64 pts;          //该帧的pts时间戳,微秒为单位,和视频的时间戳是同一个时钟基准
    FH_UINT32 sample_rate;  //该帧的采样率
    FH_UINT32 reserved;
    FH_UINT32 ch_data_len;  //该帧单通道的字节长度
    char     *far;          //远端参考数据,客户可以用来做自己的回声消除算法
    char     *mix;          //FH_AC_AI_MIX_Set_Config配置的虚拟mix通道数据
    char     *ch_data[FH_AI_CHANNEL_NUM]; //各个mic通道的数据
}FH_AC_AI_Frame_S;
#pragma pack()

/**********************************************************************************************
 * The following is just for internal use, dont' care it!
 **********************************************************************************************/
#define FH_AC_EXT_CMD_TP_GET_TP_NUM     (13)
#define FH_AC_EXT_CMD_TP_CLR            (14)
#define FH_AC_EXT_CMD_TP_RESET          (15)
#define FH_AC_EXT_CMD_FLAG_MASK         (0xffff<<16) /*高16bit是特殊标志,小心使用*/
#define FH_AC_EXT_CMD_FLAG_LARGE_STACK  (1<<31)  /*firmware使用大堆栈标志,目前,audio 3A service需要大堆栈*/
typedef struct
{
    FH_UINT32 cmd;
    FH_UINT32 arg_num; /*real arg number...*/
    FH_UINT32 args[8];
}FH_AC_EXT_IOCTL_CMD;

#define FH_AC_EXT2_CMD_READBACK_FLAG     (0x80) //don't care it
#define FH_AC_EXT2_CMD_GET_ALG_PARAM     (3 | FH_AC_EXT2_CMD_READBACK_FLAG) //don't care it
#define FH_AC_EXT2_CMD_SET_ALG_PARAM     (4) //don't care it
#define FH_AC_EXT2_CMD_AI_MIX_SET_CONFIG (5) //don't care it
#define FH_AC_EXT2_CMD_GET_FEATURE_CHMASK (6 | FH_AC_EXT2_CMD_READBACK_FLAG) //don't care it
#define FH_AC_EXT2_CMD_GET_ALG_VERSION    (7 | FH_AC_EXT2_CMD_READBACK_FLAG) //don't care it
typedef struct
{
    FH_UINT32 cmd;
    FH_UINT32 subcmd;
    FH_UINT32 arg_bytes; /*real arg bytes...*/
    FH_UINT8  arg[0];
}FH_AC_EXT2_IOCTL_CMD;

#endif /* FH_AUIDO_MPIPARA_H_ */
