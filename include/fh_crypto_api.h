/*
 * fh_crypto_api.h
 *
 *  Created on: Dec 6, 2016
 *      Author: duobao
 */

#ifndef __FH_CRYPTO_API_H__
#define __FH_CRYPTO_API_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "types/type_def.h"

/*
成员名称                 描述
CRYPTO_ALG_DES          DES 算法
CRYPTO_ALG_3DES         3DES 算法
CRYPTO_ALG_AES          AES 算法
*/
typedef enum FH_CRYPTO_ALG_E
{
    CRYPTO_ALG_DES = 0,
    CRYPTO_ALG_3DES = 1,
    CRYPTO_ALG_AES = 2,
    CRYPTO_ALG_BUTT
}CRYPTO_ALG_E;

/*
成员名称                    描述
CRYPTO_WORK_MODE_ECB        ECB（Electronic CodeBook）模式
CRYPTO_WORK_MODE_CBC        CBC（Cipher Block Chaining）模式
CRYPTO_WORK_MODE_CFB        CFB（Cipher FeedBack）模式
CRYPTO_WORK_MODE_OFB        OFB（Output FeedBack）模式
CRYPTO_WORK_MODE_CTR        CTR（Counter）模式
CRYPTO_WORK_MODE_CBC_CTS    CBC CTS（Community Tissue Services）模式
CRYPTO_WORK_MODE_BUTT       无效模式
*/
typedef enum FH_CRYPTO_WORK_MODE_E
{
    CRYPTO_WORK_MODE_ECB = 0,
    CRYPTO_WORK_MODE_CBC = 1,
    CRYPTO_WORK_MODE_CFB = 2,
    CRYPTO_WORK_MODE_OFB = 3,
    CRYPTO_WORK_MODE_CTR = 4,
    CRYPTO_WORK_MODE_BUTT
}CRYPTO_WORK_MODE_E;

/*
成员名称                    描述
CRYPTO_BIT_WIDTH_64BIT      64bit 位宽
CRYPTO_BIT_WIDTH_8BIT       8bit 位宽
CRYPTO_BIT_WIDTH_1BIT       1bit 位宽
CRYPTO_BIT_WIDTH_128BIT     128bit 位宽
*/
typedef enum FH_CRYPTO_BIT_WIDTH_E
{
    CRYPTO_BIT_WIDTH_64BIT = 0,
    CRYPTO_BIT_WIDTH_8BIT = 1,
    CRYPTO_BIT_WIDTH_1BIT = 2,
    CRYPTO_BIT_WIDTH_128BIT = 3,
}CRYPTO_BIT_WIDTH_E;

/*
成员名称                    描述
CRYPTO_KEY_AES_128BIT       AES 运算方式下采用 128bit 密钥长度
CRYPTO_KEY_AES_192BIT       AES 运算方式下采用 192bit 密钥长度
CRYPTO_KEY_AES_256BIT       AES 运算方式下采用 256bit 密钥长度
CRYPTO_KEY_DES_3KEY         3DES 运算方式下采用 3 个 key
*/
typedef enum FH_CRYPTO_KEY_LENGTH_E
{
    CRYPTO_KEY_AES_128BIT = 0,
    CRYPTO_KEY_AES_192BIT = 1,
    CRYPTO_KEY_AES_256BIT = 2,
    CRYPTO_KEY_DES_3KEY = 3,
    CRYPTO_KEY_DES = 4,
}CRYPTO_KEY_LENGTH_E;

/*
成员名称                    描述
CRYPTO_IV_KEY_AES_0BIT       AES或DES 运算方式下采用 0bit IV长度，一般ECB模式下设置
CRYPTO_IV_KEY_AES_64BIT      DES 运算方式下采用 64bit IV长度
CRYPTO_IV_KEY_AES_128BIT     AES 运算方式下采用 128bit IV长度
*/
typedef enum FH_CRYPTO_IV_LENGTH_E
{
    CRYPTO_IV_KEY_AES_0BIT = 0,
    CRYPTO_IV_KEY_AES_64BIT = 1,
    CRYPTO_IV_KEY_AES_128BIT = 2,
} CRYPTO_IV_LENGTH_E;

/*
成员名称                    描述
CRYPTO_KEY_SRC_USER         用户配置的 Key
CRYPTO_KEY_SRC_EFUSE        Efuse传输key
CRYPTO_KEY_SRC_BUTT         无效类型
*/
typedef enum FH_CRYPTO_KEY_SRC_E
{
	CRYPTO_KEY_SRC_USER  = 1<<0,
	CRYPTO_KEY_SRC_EFUSE = 1<<1,
	CRYPTO_KEY_SRC_BUTT
} CRYPTO_KEY_SRC_E;

/*
成员名称                    描述
CRYPTO_ADDR_ATTR_PHY        地址属性为物理地址
CRYPTO_ADDR_ATTR_VIR        地址属性为虚拟地址
*/
typedef enum FH_CRYPTO_ADDR_ATTR_E {
	CRYPTO_ADDR_ATTR_PHY,
	CRYPTO_ADDR_ATTR_VIR,
} CRYPTO_ADDR_ATTR_E;

/*
成员名称             描述
key[8]              密钥
iv[4]               初始向量
alg                 加密算法
work_mode           工作模式
key_len             密钥长度
iv_len              初始向量长度
bit_width           加密或解密的位宽
key_src             密钥的来源
*/

typedef struct FH_CRYPTO_CTRL_S
{
    FH_UINT32 u32Key[8];
    FH_UINT32 u32IV[4];

    CRYPTO_ALG_E enAlg;
    CRYPTO_WORK_MODE_E  enWorkMode;
    CRYPTO_KEY_LENGTH_E enKeyLen;
    CRYPTO_IV_LENGTH_E  enIVLen;
    CRYPTO_BIT_WIDTH_E  enBitWidth;
    CRYPTO_KEY_SRC_E    enKeySrc;
} CRYPTO_CTRL_S;

/* 加解密句柄 */
typedef FH_UINT32 CRYPTO_HANDLE;


/*
功能说明
    初始化加密模块设备。
输入参数
    无
输出参数
    无
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
*/
FH_SINT32 FH_CRYPTO_Init(FH_VOID);

/*
功能说明
    去初始化加密模块设备。
输入参数
    无。
输出参数
    无
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
*/
FH_SINT32 FH_CRYPTO_DeInit(FH_VOID);

/*
功能说明
    创建一路加密通道，并获取句柄。
输入参数
    phCipher：加解密通道句柄指针；
输出参数
    phCipher：加解密通道句柄；。
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
*/
FH_SINT32 FH_CRYPTO_CreateHandle(CRYPTO_HANDLE *phCipher);

/*
功能说明
    销毁一路加密句柄。
输入参数
    phCipher：加解密通道句柄；
输出参数
    无。
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
*/
FH_SINT32 FH_CRYPTO_DestroyHandle(CRYPTO_HANDLE hCipher);

/*
功能说明
    配置加解密控制信息。详细配置请参见结构体CRYPTO_CTRL_S。
输入参数
    phCipher：加解密通道句柄；
    pstCtrl：控制信息。
输出参数
    无。
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
*/
FH_SINT32 FH_CRYPTO_ConfigHandle(CRYPTO_HANDLE hCipher, CRYPTO_CTRL_S *pstCtrl);

/*
功能说明
    对数据进行加密。
输入参数
    phCipher：加解密通道句柄；
    u32SrcPhyAddr：源数据（待加密的数据）的物理地址；
    u32DestPhyAddr：存放加密结果的物理地址；
    u32ByteLength：数据的长度（单位：字节）；
输出参数
    无。
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
注意
    加密通道句柄必须已创建。
    可多次调用。
    数据的长度至少为 16 字节，且不能大于或等于 1024*1024 字节。
*/
FH_SINT32 FH_CRYPTO_Encrypt(CRYPTO_HANDLE hCipher, FH_UINT32 u32SrcPhyAddr,
        FH_UINT32 u32DestPhyAddr, FH_UINT32 u32ByteLength);

/*
功能说明
    对数据进行解密。
输入参数
    phCipher：加解密通道句柄；
    u32SrcPhyAddr：源数据（待解密的数据）的物理地址；
    u32DestPhyAddr：存放解密结果的物理地址；
    u32ByteLength：数据的长度（单位：字节）；
输出参数
    无。
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
注意
    加密通道句柄必须已创建。
    可多次调用。
    数据的长度至少为 16 字节，且不能大于或等于 1024*1024 字节。
*/
FH_SINT32 FH_CRYPTO_Decrypt(CRYPTO_HANDLE hCipher, FH_UINT32 u32SrcPhyAddr, FH_UINT32 u32DestPhyAddr, FH_UINT32 u32ByteLength);

/*
功能说明
    烧写 Key 到 OTP 区域。
输入参数
    u32OptId：烧写的 OTP 区域，取值范围[0, 2]；
    pu8Key：待烧写的 Key 数据；
    u32KeyLen：Key 数据长度，最大不超过 16*3，单位是 byte。
输出参数
    无；
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
注意
    调用此接口之前，加解密模块必须已初始化。
    可烧写的 OTP 区域共有 3 个，分别为 0，1，2。
    每个 OTP 区域只能烧写一次，且不能读取。烧写的 Key 长度最大不超过 16*3 个字节。
*/
FH_SINT32 FH_CRYPTO_WriteOTPKey(FH_UINT32 u32OptId, FH_UINT8 *pu8Key, FH_UINT32 u32KeyLen);

/*
功能说明
    烧写 Device ID 到 OTP 区域。
输入参数
    pu8DeveiceId：待烧写的Device ID数据；
    u32IdLen：Key 数据长度，最大不超过 8，单位是 byte。
输出参数
    无；
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
注意
    调用此接口之前，加解密模块必须已初始化。
    可烧写的 OTP 区域共有 1 个，
    OTP 区域只能烧写一次。烧写的Device ID长度最大不超过 8 个字节。
*/
FH_SINT32 FH_CRYPTO_WriteOTPDeviceID(FH_UINT8 *pu8DeveiceId, FH_UINT32 u32IdLen);

/*
功能说明
    烧写 Device ID 到 OTP 区域。
输入参数
    pu8DeveiceId：待输出的数据buffer；
    u32IdLen：数据buffer长度，最大不超过 8，单位是 byte。
输出参数
    无；
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
注意
    调用此接口之前，加解密模块必须已初始化。
*/
FH_SINT32 FH_CRYPTO_ReadOTPDeviceID(FH_UINT8 *pu8DeveiceId, FH_UINT32 u32IdLen);

/*
功能说明
    烧写 IV 到 OTP 区域。
输入参数
    iv_buf：待输入的数据buffer；
    ivLen：数据buffer长度，4字节对齐。
输出参数
    无；
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
注意
    默认从OTP区域ENTRY 16开始读取数据
    调用此接口之前，加解密模块必须已初始化。
*/
FH_SINT32 FH_CRYPTO_WriteOTPIV(FH_UINT8 *iv_buf, FH_UINT32 ivLen);

/*
功能说明
    OTP 区域 输出IV。
输入参数
    iv_buf：待输出的数据buffer；
    ivLen：数据buffer长度，4字节对齐。
输出参数
    无；
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
注意
    默认从OTP区域ENTRY 16开始读取数据
    调用此接口之前，加解密模块必须已初始化。
*/
FH_SINT32 FH_CRYPTO_ReadOTPIV(FH_UINT8 *iv_buf, FH_UINT32 ivLen);

/*
功能说明
    OTP 区域 输出OTP连续entry信息。
输入参数
    startEntry: 起始entry序号，4字节对齐
    pu8Buf：待输入的数据buffer；
    pu8BufLen：数据buffer长度，单位是 byte，4字节对齐。
输出参数
    无；
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
注意
    调用此接口之前，加解密模块必须已初始化。
*/

FH_SINT32 FH_CRYPTO_WriteOTPEntry(FH_UINT32 startEntry, FH_UINT8 *pu8Buf, FH_UINT32 pu8BufLen);
/*
功能说明
    OTP 区域 输出OTP连续entry信息。
输入参数
    startEntry: 起始entry序号，4字节对齐
    pu8Buf：待输出的数据buffer；
    pu8BufLen：数据buffer长度，单位是 byte，4字节对齐。
输出参数
    无；
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
注意
    调用此接口之前，加解密模块必须已初始化。
*/
FH_SINT32 FH_CRYPTO_ReadOTPEntry(FH_UINT32 startEntry, FH_UINT8 *pu8Buf, FH_UINT32 pu8BufLen);

/*
功能说明
    EFUSE传输不同的key到AES进行加密。
输入参数
    phCipher：加解密通道句柄；
    u32MapBuf：映射配置参数地址；
    u32MapBufSize：映射配置参数长度；
输出参数
    无。
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
注意
    加密通道句柄必须已创建。
    可多次调用。
    8830 & 8810 & 8630 没有此项功能
示例
    u32MapBuf[0] = 0;
    u32MapBuf[1] = 8;
    u32MapBuf[2] = 4;
    u32MapBuf[3] = 12;
    u32MapBufSize = 4;
    参数意思如下:
    [efuse_entry(0~3)]=>[aes_key(0)]
    [efuse_entry(8~11)]=>[aes_key(1)]
    [efuse_entry(4~7)]=>[aes_key(2)]
    [efuse_entry(12~15)]=>[aes_key(3)]
*/
FH_SINT32 FH_CRYPTO_Mapswitch(CRYPTO_HANDLE hCipher, FH_UINT32 *u32MapBuf, FH_UINT32 u32MapBufSize);

/*
 * 功能说明
 *     设置加密通道的地址属性。
 * 输入参数
 *     hCipher：加解密通道句柄；
 *     eSrcAddrAttr：源数据的地址属性；
 *     eDstAddrAttr：目的数据的地址属性；
 * 输出参数
 *     无。
 * 返回值
 *     0：函数调用成功。
 *     其他：失败，函数调用失败的原因见出错信息。
 * 注意
 *     加密通道句柄必须已创建。
 *     加密通道创建后SRC和DST默认都是物理地址属性。
 *     可根据应用需求随时切换SRC和DST的地址属性。
 *     每个加密通道都有自己的地址属性，互不干扰。
 */
FH_SINT32 FH_CRYPTO_AddrAttr(CRYPTO_HANDLE hCipher, CRYPTO_ADDR_ATTR_E eSrcAddrAttr, CRYPTO_ADDR_ATTR_E eDstAddrAttr);

/*
功能说明
    对efuse进行lock，
输入参数
    u32Efuse_LockBits: 对efuse区域进行lock，每一个bit对应一个区域,如下所示。
    bit0 : efuse entry[0~15]
    bit1 : efuse entry[16~31]
    bit2 : efuse entry[32~47]

输出参数
    无。
返回值
    0：函数调用成功。
    其他：失败，函数调用失败的原因见出错信息。
注意
    lock信息也是只能写一次，且不能修改，一定要一次写进去。
示例：
    crypto_efuse_set_lock(3);
    意思就是把efuse的[0 ~ 31]entry lock
*/
FH_SINT32 FH_CRYPTO_SetLock(FH_UINT32 u32Efuse_LockBits);

FH_SINT8 *FH_CRYPTO_Version(FH_UINT32 print_enable);

#ifdef __cplusplus
}
#endif

#endif /* FH_CRYPTO_API_H_ */
