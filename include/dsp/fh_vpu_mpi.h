#ifndef __FH_VPU_MPI_H__
#define __FH_VPU_MPI_H__
/**VPU**/
#include "types/type_def.h"
#include "fh_vpu_mpipara.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/*
*   Name: FH_VPSS_SetViAttr
*            设置视频输入属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_VPU_SIZE *pstViconfig
*            视频输入幅面
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          输入幅面必须和ISP输出幅面完全一致,否则会导致图像错误或者无法完成。
*          若在FH_VPSS_SetGrpParam选择自适应模式则此API只需要在初始化时调用一次设置初始值即可，后续无需调用。
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_SetViAttr(FH_UINT32 grpidx,FH_VPU_SIZE *pstViconfig);

/*
*   Name: FH_VPSS_GetViAttr
*            获取视频输入属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [out] FH_VPU_SIZE *pstViconfig
*            视频输出幅面
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetViAttr后调用。
*/
FH_SINT32 FH_VPSS_GetViAttr(FH_UINT32 grpidx,FH_VPU_SIZE *pstViconfig);

/*
*   Name: FH_VPSS_CreateGrp
*            创建视频输入
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_VPU_SET_GRP_INFO *pstChnconfig
*            视频输入幅面和ycmean相关信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VPSS_CreateGrp(FH_UINT32 grpidx,FH_VPU_SET_GRP_INFO *pstChnconfig);

/*
*   Name: FH_VPSS_DestroyGrp
*            销毁视频输入
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_DestroyGrp(FH_UINT32 grpidx);

/*
*   Name: FH_VPSS_CreateChn
*            创建通道
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] FH_VPU_CHN_INFO *chn_info
*            创建通道需要用到的相关信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          CPY,BGM和SAD在使用编码时必须打开。
*          BGM在使用背景建模时必须打开。
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_CreateChn(FH_UINT32 grpidx,FH_UINT32 chan,FH_VPU_CHN_INFO *chn_info);

/*
*   Name: FH_VPSS_DestroyChn
*            销毁VPU通道
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateChn后调用。
*/
FH_SINT32 FH_VPSS_DestroyChn(FH_UINT32 grpidx,FH_UINT32 chan);

/*
*   Name: FH_VPSS_GetBGMData
*            获取视频处理模块中供BGM使用的图像数据
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [out] FH_PIC_DATA *pstBGMData
*            供BGM使用图像数据信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          阻塞接口,超时时间为1s。
*          需要在FH_VPSS_SetChnAttr后调用。
*/
FH_SINT32 FH_VPSS_GetBGMData(FH_UINT32 grpidx,FH_PIC_DATA *pstBGMData);

/*
*   Name: FH_VPSS_GetCPYData
*            获取视频处理模块中纹理复杂度数据
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [out] FH_PIC_DATA *pstCPYData
*            纹理复杂度数据信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          阻塞接口,超时时间为1s。
*          需要在FH_VPSS_SetChnAttr后调用。
*/
FH_SINT32 FH_VPSS_GetCPYData(FH_UINT32 grpidx,FH_PIC_DATA *pstCPYData);

/*
*   Name: FH_VPSS_Enable
*            使能视频处理模块
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_VPU_VI_MODE mode
*            视频处理模块工作模式
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          更换工作模式时，需先调用FH_VPSS_Disable,然后再调用此函数。
*          需要在FH_VPSS_SetViAttr后调用。
*/
FH_SINT32 FH_VPSS_Enable(FH_UINT32 grpidx,FH_VPU_VI_MODE mode);

/*
*   Name: FH_VPSS_Disable
*            关闭视频处理模块
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetViAttr后调用。
*/
FH_SINT32 FH_VPSS_Disable(FH_UINT32 grpidx);

/*
*   Name: FH_VPSS_FreezeVideo
*            视频冻结,视频处理模块将会向后面数据处理模块,不断发送最后一帧的数据.直到调用FH_VPSS_UnfreezeVideo。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          当通道的输出缓存数量为1帧或者特殊工作模式时,此接口无效。
*          需要在FH_VPSS_CreateGrp后调用,需要注意在设置通道属性后该配置会失效,需要重新设置。
*/
FH_SINT32 FH_VPSS_FreezeVideo(FH_UINT32 grpidx);

/*
*   Name: FH_VPSS_UnfreezeVideo
*            视频解冻
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateGrp后调用
*/
FH_SINT32 FH_VPSS_UnfreezeVideo(FH_UINT32 grpidx);

/*
*   Name: FH_VPSS_GetChnFrameAdv
*            获取视频处理模块通道输出的图像数据
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [out] FH_VPU_STREAM_ADV *pstVpuframeinfo
*            图像数据信息
*
*       [in] FH_UINT32 timeout_ms
*            接口阻塞超时时间(ms)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetChnAttr后调用
*/
FH_SINT32 FH_VPSS_GetChnFrameAdv(FH_UINT32 grpidx,FH_UINT32 chan,FH_VPU_STREAM_ADV *pstVpuframeinfo,FH_UINT32 timeout_ms);

/*
*   Name: FH_VPSS_LockChnFrameAdv
*            获取视频处理模块通道输出的图像数据,并锁定此缓存不被硬件继续使用.建议至少分配3buf及以上才使用此接口．
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [out] FH_VPU_STREAM_ADV *pstVpuframeinfo
*            图像数据信息
*
*       [in] FH_UINT32 timeout_ms
*            接口阻塞超时时间(ms)
*
*       [out] FH_UINT32 *handle_lock
*            通道缓存的lock句柄
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*          使用Lock接口且该通道绑定后续编码模块时建议需要至少配置3个buf以上.
*          且建议需要保持非lock的buf数量至少为2个,只有1个可用buf时驱动将不再做内存保护(可能出现图像割线)．
*          当底层所有buf都被lock住时，后续所有帧都会被丢弃．
*          需要在FH_VPSS_SetChnAttr后调用
*/
FH_SINT32 FH_VPSS_LockChnFrameAdv(FH_UINT32 grpidx,FH_UINT32 chan,FH_VPU_STREAM_ADV *pstVpuframeinfo,FH_UINT32 timeout_ms,FH_UINT32 *handle_lock);

/*
*   Name: FH_VPSS_GetChnFrameAdv_NoRpt
*            获取视频处理模块通道输出的图像数据
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [out] FH_VPU_STREAM_ADV *pstVpuframeinfo
*            图像数据信息
*
*       [in] FH_UINT32 timeout_ms
*            接口阻塞超时时间(ms)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          timeout_ms为0时不返回已经已经被获取过的帧
*          timeout_ms不为0时若前一帧未被取走则直接返回前一帧，否则进入等待
*          此接口不支持并发获取相同通道数据，否则多线程间会相互竞争资源
*          需要在FH_VPSS_SetChnAttr后调用
*/
FH_SINT32 FH_VPSS_GetChnFrameAdv_NoRpt(FH_UINT32 grpidx,FH_UINT32 chan,FH_VPU_STREAM_ADV *pstVpuframeinfo,FH_UINT32 timeout_ms);

/*
*   Name: FH_VPSS_LockChnFrameAdv_NoRpt
*            获取视频处理模块通道输出的图像数据,并锁定此缓存不被硬件继续使用.建议至少分配3buf及以上才使用此接口．
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [out] FH_VPU_STREAM_ADV *pstVpuframeinfo
*            图像数据信息
*
*       [in] FH_UINT32 timeout_ms
*            接口阻塞超时时间(ms)
*
*       [out] FH_UINT32 *handle_lock
*            通道缓存的lock句柄
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*          使用Lock接口且该通道绑定后续编码模块时建议需要至少配置3个buf以上.
*          且建议需要保持非lock的buf数量至少为2个,只有1个可用buf时驱动将不再做内存保护(可能出现图像割线)．
*          当底层所有buf都被lock住时，后续所有帧都会被丢弃．
*          timeout_ms为0时不返回已经已经被获取过的帧
*          timeout_ms不为0时若前一帧未被取走则直接返回前一帧，否则进入等待
*          此接口不支持并发获取相同通道数据，否则多线程间会相互竞争资源
*          需要在FH_VPSS_SetChnAttr后调用
*/
FH_SINT32 FH_VPSS_LockChnFrameAdv_NoRpt(FH_UINT32 grpidx,FH_UINT32 chan,FH_VPU_STREAM_ADV *pstVpuframeinfo,FH_UINT32 timeout_ms,FH_UINT32 *handle_lock);

/*
*   Name: FH_VPSS_UnlockChnFrameAdv
*            释放被FH_VPSS_LockChnFrameAdv锁定的缓存
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] FH_VPU_STREAM_ADV *pstVpuframeinfo
*            图像数据信息
*
*       [in] FH_UINT32 handle_lock
*            通道缓存的lock句柄
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetChnAttr后调用
*/
FH_SINT32 FH_VPSS_UnlockChnFrameAdv(FH_UINT32 grpidx,FH_UINT32 chan,FH_VPU_STREAM_ADV *pstVpuframeinfo,FH_UINT32 lock_handle);

/*
*   Name: FH_VPSS_GetChnFrame
*            获取视频处理模块通道输出的图像数据
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [out] FH_VIDEO_FRAME *pstVpuframeinfo
*            图像数据信息
*
*       [in] FH_UINT32 timeout_ms
*            接口阻塞超时时间(ms)
*
*       [out] FH_UINT32 *handle_lock
*            通道缓存的lock句柄
*
*       [in] FH_UINT32 is_lock
*            是否阻塞
*
*       [in] FH_UINT32 is_norpt
*            是否使用NoRpt模式
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetChnAttr后调用
*/
FH_SINT32 FH_VPSS_GetChnFrame(FH_UINT32 grpidx,FH_UINT32 chan,FH_VIDEO_FRAME *pstVpuframeinfo,
	FH_UINT32 timeout_ms,FH_UINT32 *handle_lock,FH_UINT32 is_lock,FH_UINT32 is_norpt);

/*
*   Name: FH_VPSS_ReleaseChnFrame
*            释放被FH_VPSS_GetChnFrame锁定的缓存
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] FH_VIDEO_FRAME *pstVpuframeinfo
*            图像数据信息
*
*       [in] FH_UINT32 handle_lock
*            通道缓存的lock句柄
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetChnAttr后调用
*/
FH_SINT32 FH_VPSS_ReleaseChnFrame(FH_UINT32 grpidx,FH_UINT32 chan,FH_VIDEO_FRAME *pstVpuframeinfo,FH_UINT32 lock_handle);

/*
*   Name: FH_VPSS_SendUserPic
*            提交用户图像给视频处理模块进行处理,仅在处于非直通模式下有效。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] const FH_VPU_USER_PIC *pstUserPic
*            用户图像信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetViAttr后调用
*/
FH_SINT32 FH_VPSS_SendUserPic(FH_UINT32 grpidx,const FH_VPU_USER_PIC *pstUserPic);
/*
*   Name: FH_VPSS_SendUserPicAdv
*            提交用户图像给视频处理模块进行处理,仅在处于非直通模式下有效。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 blkidx
*            BLK号
*
*       [in] const FH_VPU_USER_PIC *pstUserPic
*            用户图像信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetViAttr后调用
*/
FH_SINT32 FH_VPSS_SendUserPicAdv(FH_UINT32 grpidx,FH_UINT32 blkidx,const FH_VPU_USER_PIC *pstUserPic);

/*
*   Name: FH_VPSS_SendFrame
*            提交用户图像给视频处理模块进行处理,仅在处于非直通模式下有效。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 blkidx
*            BLK号
*
*       [in] FH_UINT32 timeout_ms
*            提交图像入队列阻塞超时时间(ms)
*
*       [in] const FH_VIDEO_FRAME *pstUserPic
*            用户图像信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetViAttr后调用
*/
FH_SINT32 FH_VPSS_SendFrame(FH_UINT32 grpidx,FH_UINT32 blkidx,FH_UINT32 timeout_ms,const FH_VIDEO_FRAME *pstUserPic);

/*
*   Name: FH_VPSS_SetChnAttr
*            设置视频处理模块通道属性。修改通道属性时不需要停止视频处理模块。但建议先停止该通道的使能。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32  chan
*            通道号
*
*       [in] const FH_VPU_CHN_CONFIG *pstChnconfig
*            通道属性信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          在设置通道属性后,包含帧率控制,视频冻结等通道配置会失效,需要重新设置。
*          需要在FH_VPSS_CreateChn后调用
*/
FH_SINT32 FH_VPSS_SetChnAttr(FH_UINT32 grpidx,FH_UINT32  chan,const FH_VPU_CHN_CONFIG *pstChnconfig);

/*
*   Name: FH_VPSS_GetChnAttr
*            获取视频处理模块通道属性。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32  chan
*            通道号
*
*       [out]  FH_VPU_CHN_CONFIG *pstChnconfig
*            通道属性信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetChnAttr后调用
*/
FH_SINT32 FH_VPSS_GetChnAttr(FH_UINT32 grpidx,FH_UINT32  chan, FH_VPU_CHN_CONFIG *pstChnconfig);

/*
*   Name: FH_VPSS_SetExtChnAttr
*            设置视频处理模块扩展通道属性。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32  chan
*            通道号
*
*       [in]  FH_VPU_EXT_CHN_CONFIG pstChnconfig
*            扩展通道属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          扩展通道只支持光栅和YUYV模式,要求绑定的通道输出模式与扩展通道相同。
*          在设置扩展通道属性后,包含帧率控制,视频冻结等通道配置会失效,需要重新设置。
*          需要在FH_VPSS_CreateChn(扩展通道与绑定通道都创建)后调用
*/
FH_SINT32 FH_VPSS_SetExtChnAttr(FH_UINT32 grpidx,FH_UINT32 chan,const FH_VPU_EXT_CHN_CONFIG *pstChnconfig);

/*
*   Name: FH_VPSS_SetVOMode
*            设置视频处理模块通道输出组织格式
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32  chan
*            通道号
*
*       [in]  FH_VPU_VO_MODE mode
*            图像数据输出组织格式
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          各模块支持的组织格式在各平台有所不同,详见《视频函数开发参考手册》。
*          需要在FH_VPSS_SetChnAttr后调用
*/
FH_SINT32 FH_VPSS_SetVOMode(FH_UINT32 grpidx,FH_UINT32  chan, FH_VPU_VO_MODE mode);

/*
*   Name: FH_VPSS_SetVORotate
*            根据后续编码模块处理的旋转角度设置视频处理模块通道输出组织方式
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32  chan
*            通道号
*
*       [in]  FH_ROTATE_OPS rotate
*            后续编码模块需要进行的旋转角度
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          此接口不会对输出数据进行旋转，而是根据编码旋转角度的需求对数据存放位置做一些调整
*          仅在Tile压缩时此接口才会对输出有影响，其他格式实际存放在配置不同角度时不变。但接口通用于各个格式。
*          需要在FH_VPSS_SetChnAttr后调用
*/
FH_SINT32 FH_VPSS_SetVORotate(FH_UINT32 grpidx,FH_UINT32 chan, FH_ROTATE_OPS rotate);

/*
*   Name: FH_VPSS_OpenChn
*            开启通道使能
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32  chan
*            通道号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetChnAttr后调用
*/
FH_SINT32 FH_VPSS_OpenChn(FH_UINT32 grpidx,FH_UINT32  chan);

/*
*   Name: FH_VPSS_CloseChn
*            关闭通道使能
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32  chan
*            通道号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateChn后调用
*/
FH_SINT32 FH_VPSS_CloseChn(FH_UINT32 grpidx,FH_UINT32  chan);

/*
*   Name: FH_VPSS_SetMask
*            设置视频处理模块隐私屏蔽属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] const FH_VPU_MASK *pstVpumaskinfo
*            隐私屏蔽属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          各平台支持功能有所差异,详见《视频函数开发参考手册》。
*          需要在FH_VPSS_CreateGrp后调用
*/
FH_SINT32 FH_VPSS_SetMask(FH_UINT32 grpidx,const FH_VPU_MASK *pstVpumaskinfo);

/*
*   Name: FH_VPSS_GetMask
*            获取视频处理模块隐私屏蔽属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [out] FH_VPU_MASK *pstVpumaskinfo
*            隐私屏蔽属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateGrp后调用
*/
FH_SINT32 FH_VPSS_GetMask(FH_UINT32 grpidx,FH_VPU_MASK *pstVpumaskinfo);

/*
*   Name: FH_VPSS_ClearMask
*            关闭对应隐私屏蔽区域
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 clearmaskarea
*            隐私屏蔽区域索引,范围0-7
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateGrp后调用
*/
FH_SINT32 FH_VPSS_ClearMask(FH_UINT32 grpidx,FH_UINT32 clearmaskarea);

/*
*   Name: FH_VPSS_EnableYCmean
*           开启均值统计
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateGrp后调用
*/
FH_SINT32 FH_VPSS_EnableYCmean(FH_UINT32 grpidx);

/*
*   Name: FH_VPSS_DisableYCmean
*            关闭均值统计
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateGrp后调用
*/
FH_SINT32 FH_VPSS_DisableYCmean(FH_UINT32 grpidx);

/*
*   Name: FH_VPSS_SetYCmeanMode
*            配置均值统计下采样模式
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 mode
*            下采样模式(4/8/16)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateGrp后调用
*/
FH_SINT32 FH_VPSS_SetYCmeanMode(FH_UINT32 grpidx,FH_UINT32 mode);

/*
*   Name: FH_VPSS_GetYCmeanMode
*            配置均值统计下采样模式
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [out] FH_UINT32 mode
*            下采样模式(4/8/16)
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateGrp后调用
*/
FH_SINT32 FH_VPSS_GetYCmeanMode(FH_UINT32 grpidx,FH_UINT32 *mode);

/*
*   Name: FH_VPSS_GetYCmean
*            获取均值统计结果
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [out] FH_VPU_YCMEAN *pstVpuycmeaninfo
*            均值统计结果
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetViAttr后调用。
*/
FH_SINT32 FH_VPSS_GetYCmean(FH_UINT32 grpidx,FH_VPU_YCMEAN *pstVpuycmeaninfo);

/*
*   Name: FH_VPSS_SetFramectrl
*            设置帧率控制参数
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] const FH_FRAMERATE *pstVpuframectrl
*            帧率控制参数
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          1. 通道处于特殊工作模式时不支持帧率控制。
*          2. 帧率控制时,图像时间戳将被修改为目标帧间隔。
*          3. 只有在通道缓存大于等于3个时,才支持增帧模式。
*          需要在FH_VPSS_SetChnAttr后调用。
*/
FH_SINT32 FH_VPSS_SetFramectrl(FH_UINT32 grpidx,FH_UINT32 chan,const FH_FRAMERATE *pstVpuframectrl);

/*
*   Name: FH_VPSS_GetFramectrl
*            获取帧率控制参数
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [out]  FH_FRAMERATE *pstVpuframectrl
*            帧率控制参数
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetChnAttr后调用。
*/
FH_SINT32 FH_VPSS_GetFramectrl(FH_UINT32 grpidx,FH_UINT32 chan, FH_FRAMERATE *pstVpuframectrl);

/*
*   Name: FH_VPSS_GetFrameRate
*            获取当前通道帧率统计结果
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [out] FH_FRAMERATE *fps
*            帧率统计结果
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetChnAttr后调用。
*/
FH_SINT32 FH_VPSS_GetFrameRate(FH_UINT32 grpidx,FH_UINT32 chan,FH_FRAMERATE *fps);

/*
*   Name: FH_VPSS_SetChnCrop
*            设置通道裁剪属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] FH_VPU_CROP_SEL sel
*            位置
*
*       [in] const FH_VPU_CROP *pstVpucropinfo
*            裁剪属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          各平台支持功能有所差异,详见《视频函数开发参考手册》。
*          需要在FH_VPSS_SetChnAttr后调用。
*/
FH_SINT32 FH_VPSS_SetChnCrop(FH_UINT32 grpidx,FH_UINT32 chan,FH_VPU_CROP_SEL sel,const FH_VPU_CROP *pstVpucropinfo);

/*
*   Name: FH_VPSS_GetChnCrop
*            获取通道裁剪属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] FH_VPU_CROP_SEL sel
*            位置
*
*       [out] FH_VPU_CROP *pstVpucropinfo
*            裁剪属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetChnAttr后调用。
*/
FH_SINT32 FH_VPSS_GetChnCrop(FH_UINT32 grpidx,FH_UINT32 chan,FH_VPU_CROP_SEL sel,FH_VPU_CROP * pstVpucropinfo);

/*
*   Name: FH_VPSS_SetGlbCrop
*            设置VI裁剪属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_VPU_CROP_SEL sel
*            位置
*
*       [in] const FH_VPU_CROP *pstVpucropinfo
*            裁剪属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          各平台支持功能有所差异,详见《视频函数开发参考手册》。
*          需要在FH_VPSS_SetViAttr后调用。
*/
FH_SINT32 FH_VPSS_SetGlbCrop(FH_UINT32 grpidx,FH_VPU_CROP_SEL sel,const FH_VPU_CROP *pstVpucropinfo);

/*
*   Name: FH_VPSS_GetGlbCrop
*            获取VI裁剪属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_VPU_CROP_SEL sel
*            位置
*
*       [out] FH_VPU_CROP *pstVpucropinfo
*            裁剪属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetViAttr后调用。
*/
FH_SINT32 FH_VPSS_GetGlbCrop(FH_UINT32 grpidx,FH_VPU_CROP_SEL sel,FH_VPU_CROP * pstVpucropinfo);

/*
*   Name: FH_VPSS_SetScalerCoeff
*            设置图像缩放的滤波器系数,可以将图像效果从平滑到锐利。
*            建议输入输出缩放比差不多或放大时，设的较强。反之设弱些。
*            另外在编码压力较大时可以使用此接口对图像进行一定程度滤波降低编码压力。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in]  FH_UINT32 level
*            滤波等级，0-15,越大越清晰
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetChnAttr后调用。
*/
FH_SINT32 FH_VPSS_SetScalerCoeff(FH_UINT32 grpidx,FH_UINT32 chan, FH_UINT32 level);

/*
*   Name: FH_VPSS_SetChnScalerAttr
*            设置图像缩放相关信息。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] const FH_VPU_SCALER_ATTR *attr
*            缩放相关信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          当图像缩放比比较大时会出现锯齿效应，可使用此接口调整参数改善。
*          Fix2ds是scaler输出目标幅面*2的大小后进行2x2的均值得到目标幅面。
*          目标幅面宽度小于配置宽度且小于通道最大幅面一半，高度小于2048时开启Fix2ds。
*          若选择自动模式，需要在FH_VPSS_SetChnAttr后调用。
*/
FH_SINT32 FH_VPSS_SetChnScalerAttr(FH_UINT32 grpidx,FH_UINT32 chan,const FH_VPU_SCALER_ATTR *attr);

/*
*   Name: FH_VPSS_GetChnScalerAttr
*            获取图像缩放相关信息。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [out]  FH_VPU_SCALER_ATTR *attr
*            缩放相关信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VPSS_GetChnScalerAttr(FH_UINT32 grpidx,FH_UINT32 chan,FH_VPU_SCALER_ATTR *attr);

/*
*   Name: FH_VPSS_GetFrameBufferSize
*            获取对应通道设的内存块数量需要的内存大小。供快速启动应用增加临时输出缓存数量。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] FH_UINT32 bufnum
*            增加buf数量
*
*       [out] FH_UINT32 *needsize
*            需要分配的内存数量
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateChn后调用。
*/
FH_SINT32 FH_VPSS_GetFrameBufferSize(FH_UINT32 grpidx,FH_UINT32 chan,FH_UINT32 bufnum,FH_UINT32 *needsize);

/*
*   Name: FH_VPSS_FrameBufferRegister
*            给通道输出注册临时内存
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] FH_UINT32 bufnum
*            增加buf数量
*
*       [in] FH_MEM_INFO buf
*            临时内存的信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateChn后调用。
*/
FH_SINT32 FH_VPSS_FrameBufferRegister(FH_UINT32 grpidx,FH_UINT32 chan,FH_UINT32 bufnum,FH_MEM_INFO buf);
/*
*   Name: FH_VPSS_FrameBufferUnRegister
*            将通道输出临时内存注销
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [out] FH_MEM_INFO *buf
*            临时内存的信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          此函数需要等待内存释放,带有阻塞等待,请注意调用时机。
*          需要在FH_VPSS_CreateChn后调用。
*/
FH_SINT32 FH_VPSS_FrameBufferUnRegister(FH_UINT32 grpidx,FH_UINT32 chan,FH_MEM_INFO *buf);

/*
*   Name: FH_VPSS_GetFrameBlkSize
*            获取不同幅面和支持输出类型的内存大小
*
*   Parameters:
*
*       [in] FH_UINT32 width
*            宽度
*
*       [in] FH_UINT32 height
*            高度
*
*       [in] FH_UINT32 support_mode
*            支持的输出类型
*
*       [in] FH_UINT32 *blk_size
*            每块内存需要的Byte
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*          1. VPU通道使用VBPool内存时，需在FH_VPSS_CreateChn时将内存bufnum配置为0。
*/
FH_SINT32 FH_VPSS_GetFrameBlkSize(FH_UINT32 width,FH_UINT32 height,FH_UINT32 support_mode,FH_UINT32 *blk_size);

/*
*   Name: FH_VPSS_AttachVbPool
*            将VPSS的通道绑定到某个视频缓存VB池中
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] FH_UINT32 vbpool
*            视频缓存VB池信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*          1. VPU通道使用VBPool内存时，需在FH_VPSS_CreateChn时将内存bufnum配置为0。
*          2. 可以通过FH_VPSS_GetFrameBlkSize获取到不同幅面和格式的帧内存大小
*          3. 也可以在创建通道后通过FH_VPSS_FrameBufferRegister获取当前通道每帧需要的内存大小.
*          4. 支持多个Grp的多个通道共用VB,但建议在内存大小相近时才进行共用
*          5. 如需切换绑定的VB只需重新调用FH_VPSS_AttachVbPool
*          6. 基于用户获取通道数据和帧率控制等需求，VPU会占用最新的一帧，请合理分配VB的BLK数量
*          7. 需要在FH_VPSS_CreateChn后调用。
*/
FH_SINT32 FH_VPSS_AttachVbPool(FH_UINT32 grpidx,FH_UINT32 chan,FH_UINT32 vbpool);

/*
*   Name: FH_VPSS_DetachVbPool
*            将VPSS的通道从某个视频缓存VB池中解绑
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*          调用此接口返回后,相关VB内存依然有可能被各模块使用,需要用户自行保证相关内存使用完毕后才能销毁
*          需要在FH_VPSS_CreateChn后调用。
*/
FH_SINT32 FH_VPSS_DetachVbPool(FH_UINT32 grpidx,FH_UINT32 chan);

/*
*   Name: FH_VPSS_SetCommVbEnable
*            设置是否允许VPU通道使用CommonVB
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] FH_UINT32 enable
*            使能,默认为FH_TRUE
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*
*   Note:
*          1. 开启VB模式必须在FH_VPSS_CreateChn配置bufnum为0,否则内存将从VMM分配.
*          2. 使能CommVB后,会从CommVB获取内存，但如果调用FH_VPSS_AttachVbPool，会使用指定的私有VB不再从CommVB中申请．
*          3. FH_VPSS_DetachVbPool后，如果使能CommVB会从私有VB切换到CommVB获取．如未使能CommVB则将触发丢帧，等待重新Attach新的私有VB．
*          4. 需要在FH_VPSS_CreateChn后调用。
*/
FH_SINT32 FH_VPSS_SetCommVbEnable(FH_UINT32 grpidx,FH_UINT32 chan,FH_UINT32 enable);

/*
*   Name: FH_VPSS_SetDefaultScalerSize
*            修改各个通道默认的缩放大小，必须在配置vi属性和通道属性之前，用于一些小幅面高帧率的场景。
*            在设置通道属性时对应通道的默认大小会被修改。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_SIZE *picsize
*            默认输出幅面
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_SetDefaultScalerSize(FH_UINT32 grpidx,FH_SIZE *picsize);

/*
*   Name: FH_VPSS_SetLDCAttr
*            设置镜头畸变校正(LDC)属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_VPU_LDC *pLdcAttr
*            LDC属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_SetLDCAttr(FH_UINT32 grpidx,FH_VPU_LDC *pLdcAttr);

/*
*   Name: FH_VPSS_GetLDCAttr
*            获取镜头畸变校正(LDC)属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [out] FH_VPU_LDC *pLdcAttr
*            LDC属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_GetLDCAttr(FH_UINT32 grpidx,FH_VPU_LDC *pLdcAttr);

/*内部接口,不建议用户调用此接口*/
FH_SINT32 FH_VPU_GetPkginfo(FH_UINT32 grpidx,FH_SINT32 intMemSlot,FH_PKG_INFO *pstVpupkginfo);

/*
*   Name: FH_VPSS_SetGlbGraphV2
*            设置全局图形叠加信息。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] const FH_VPU_LOGOV2 *pstVpugraphinfo
*            图形叠加信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          各平台支持功能有所差异,详见《视频函数开发参考手册》。
*          需要在FH_VPSS_SetViAttr后调用。
*/
FH_SINT32 FH_VPSS_SetGlbGraphV2(FH_UINT32 grpidx,const FH_VPU_LOGOV2 *pstVpugraphinfo);

/*
*   Name: FH_VPSS_SetGlbGraphV2_Timeout
*            设置全局图形叠加信息,设置生效后返回。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 timeout_ms
*            接口阻塞时间(ms)
*
*       [in] const FH_VPU_LOGOV2 *pstVpugraphinfo
*            图形叠加信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          各平台支持功能有所差异,详见《视频函数开发参考手册》。
*          需要在FH_VPSS_SetViAttr后调用。
*/
FH_SINT32 FH_VPSS_SetGlbGraphV2_Timeout(FH_UINT32 grpidx,FH_UINT32 timeout_ms,const FH_VPU_LOGOV2 *pstVpugraphinfo);

/*
*   Name: FH_VPSS_GetGlbGraphV2
*            获取全局图形叠加信息。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [out] FH_VPU_LOGOV2 * pstVpugraphinfo
*            图形叠加信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetViAttr后调用。
*/
FH_SINT32 FH_VPSS_GetGlbGraphV2(FH_UINT32 grpidx,FH_VPU_LOGOV2 * pstVpugraphinfo);

/*
*   Name: FH_VPSS_SetChnGraphV2
*            设置通道图形叠加信息。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [out]  const FH_VPU_LOGOV2 *pstVpugraphinfo
*            图形叠加信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetChnAttr后调用。
*/
FH_SINT32 FH_VPSS_SetChnGraphV2(FH_UINT32 grpidx, FH_UINT32 chan, const FH_VPU_LOGOV2 *pstVpugraphinfo);

/*
*   Name: FH_VPSS_SetChnGraphV2_Timeout
*            设置通道图形叠加信息,设置生效后返回。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] FH_UINT32 timeout_ms
*            接口阻塞时间(ms)
*
*       [out]  const FH_VPU_LOGOV2 *pstVpugraphinfo
*            图形叠加信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetChnAttr后调用。
*/
FH_SINT32 FH_VPSS_SetChnGraphV2_Timeout(FH_UINT32 grpidx,FH_UINT32 chan,FH_UINT32 timeout_ms, const FH_VPU_LOGOV2 *pstVpugraphinfo);

/*
*   Name: FH_VPSS_GetChnGraphV2
*            获取通道图形叠加信息。
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [out]  FH_VPU_LOGOV2 * pstVpugraphinfo
*            图形叠加信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          需要在FH_VPSS_SetChnAttr后调用。
*/
FH_SINT32 FH_VPSS_GetChnGraphV2(FH_UINT32 grpidx,FH_UINT32 chan, FH_VPU_LOGOV2 * pstVpugraphinfo);

/*
*   Name: FH_VPSS_CheckAddr
*            检查VPSS输入缓存地址是否被使用
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_PHYADDR addr
*            查询地址
*
*       [in] FH_UINT32 size
*            查询大小
*
*       [in] FH_UINT32 timeout_ms
*            接口阻塞时间(ms)
*
*       [in] FH_UINT32 isidle
*            是否正在被使用
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VPSS_CheckAddr(FH_UINT32 grpidx,FH_PHYADDR addr,FH_UINT32 size,FH_UINT32 timeout_ms,FH_UINT32 *isidle);

/*
*   Name: FH_VPSS_SetChnViSel
*            设置通道输入图像源位置
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] FH_UINT32 sel
*            输入图像源位置
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          此接口仅适用于支持选择输入源的通道，参考开发文档VPU框图。
*          AI-RGB通道 sel: 0->LDC之后 1->PM之后 2->Gosd之后
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_SetChnViSel(FH_UINT32 grpidx,FH_UINT32 chan,FH_UINT32 sel);

/*
*   Name: FH_VPSS_SetGrpParam
*            设置group模块参数
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] const FH_VPU_GRP_PARAM *attr
*            group模块参数
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          修改分块和shadow需要在FH_VPSS_SetViAttr前，vi_auto可动态修改
*/
FH_SINT32 FH_VPSS_SetGrpParam(FH_UINT32 grpidx,const FH_VPU_GRP_PARAM *attr);

/*
*   Name: FH_VPSS_GetGrpParam
*            获取group模块参数
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [out] FH_VPU_GRP_PARAM *attr
*            group模块参数
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VPSS_GetGrpParam(FH_UINT32 grpidx,FH_VPU_GRP_PARAM *attr);

/*
*   Name: FH_VPSS_SetChnParam
*            设置通道相关信息
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] const FH_VPU_CHN_PARAM *attr
*            通道相关信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          修改fcmode需要在FH_VPSS_SetFramectrl前，修改align_patch_mode要在FH_VPSS_SetChnAttr前
*/
FH_SINT32 FH_VPSS_SetChnParam(FH_UINT32 grpidx,FH_UINT32 chan,const FH_VPU_CHN_PARAM *attr);

/*
*   Name: FH_VPSS_GetChnParam
*            获取通道相关信息
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [out] const FH_VPU_CHN_PARAM *attr
*            通道相关信息
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*/
FH_SINT32 FH_VPSS_GetChnParam(FH_UINT32 grpidx,FH_UINT32 chan,FH_VPU_CHN_PARAM *attr);

/*
*   Name: FH_VPSS_SetChnApcAttr
*            设置通道 APC属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] FH_VPU_APC * attr
*            APC属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          此接口仅适用于AI-RGB通道。
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_SetChnApcAttr(FH_UINT32 grpidx,FH_UINT32 chan,const FH_VPU_APC *attr);

/*
*   Name: FH_VPSS_GetChnApcAttr
*            获取通道 APC属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [out] FH_VPU_APC * attr
*            APC属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          此接口仅适用于AI-RGB通道。
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_GetChnApcAttr(FH_UINT32 grpidx,FH_UINT32 chan,FH_VPU_APC *attr);

/*
*   Name: FH_VPSS_SetRGBPreAttr
*            设置RGB前处理属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [in] FH_VPU_RGB_PRE * attr
*            RGB前处理属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          此接口仅适用于AI-RGB通道。
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_SetRGBPreAttr(FH_UINT32 grpidx,FH_UINT32 chan,const FH_VPU_RGB_PRE *attr);

/*
*   Name: FH_VPSS_GetRGBPreAttr
*            获取RGB前处理属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_UINT32 chan
*            通道号
*
*       [out] FH_VPU_RGB_PRE * attr
*            RGB前处理属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          此接口仅适用于AI-RGB通道。
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_GetRGBPreAttr(FH_UINT32 grpidx,FH_UINT32 chan,FH_VPU_RGB_PRE *attr);

/*
*   Name: FH_VPSS_SetMergeAttr
*            设置拼接属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [in] FH_VPU_MERGE_ATTR * attr
*            拼接属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          部分平台不支持,详见模块能力级。
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_SetMergeAttr(FH_UINT32 grpidx,const FH_VPU_MERGE_ATTR *attr);

/*
*   Name: FH_VPSS_GetMergeAttr
*            设置拼接属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [out] FH_VPU_MERGE_ATTR * attr
*            拼接属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          部分平台不支持,详见模块能力级。
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_GetMergeAttr(FH_UINT32 grpidx,FH_VPU_MERGE_ATTR *attr);

/*
*   Name: FH_VPSS_SetLut2dAttr
*            设置2DLUT属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [out] FH_VPU_LUT2D_ATTR * attr
*            2DLUT属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          部分平台不支持,详见模块能力级。
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_SetLut2dAttr(FH_UINT32 grpidx,const FH_VPU_LUT2D_ATTR *attr);

/*
*   Name: FH_VPSS_GetLut2dAttr
*            获取2DLUT属性
*
*   Parameters:
*
*       [in] FH_UINT32 grpidx
*            GROUP号
*
*       [out] FH_VPU_LUT2D_ATTR * attr
*            2DLUT属性
*
*   Return:
*           0(成功)
*          非0(失败，详见错误码)
*   Note:
*          部分平台不支持,详见模块能力级。
*          需要在FH_VPSS_CreateGrp后调用。
*/
FH_SINT32 FH_VPSS_GetLut2dAttr(FH_UINT32 grpidx,FH_VPU_LUT2D_ATTR *attr);

/*内部调试函数，不建议用户调用*/
FH_SINT32 FH_VPSS_ReadMallocedMem(FH_UINT32 grpidx,FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstData);
FH_SINT32 FH_VPSS_WriteMallocedMem(FH_UINT32 grpidx,FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstData);
FH_SINT32 FH_VPSS_ImportMallocedMem(FH_UINT32 grpidx,FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstSrc, FH_UINT32 size);
FH_SINT32 FH_VPSS_ExportMallocedMem(FH_UINT32 grpidx,FH_SINT32 intMemSlot, FH_UINT32 offset, FH_UINT32 *pstDst, FH_UINT32 size);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /*__MPI_VO_H__ */
