#ifndef FH_AC_MPI_H_
#define FH_AC_MPI_H_

#include "types/type_def.h"
#include "fh_audio_mpipara.h"
#include "FHSES_param.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

FH_SINT32 FH_AC_Init(void);
FH_SINT32 FH_AC_Init_WithExternalCodec(void);
FH_SINT32 FH_AC_DeInit(void);

FH_SINT32 FH_AC_AI_Get_Feature_ChannelMask(FH_UINT32 *p_channel_mask);
FH_SINT32 FH_AC_Set_Config(FH_AC_CONFIG *pstConfig);
FH_SINT32 FH_AC_AI_AO_SYNC_Enable(void);
FH_SINT32 FH_AC_Get_Algo_Version(FH_UINT32 *pVersion1, FH_UINT32 *pVersion2); /*获得音频算法版本*/
FH_SINT32 FH_AC_Print_Algo_Param(void *param, FH_UINT32 len);

/*for AI*/
FH_SINT32 FH_AC_AI_Enable(void);
FH_SINT32 FH_AC_AI_Disable(void);
FH_SINT32 FH_AC_AI_CH_SetAnologVol (FH_UINT32 channel_mask, FH_UINT32 mic_vol, FH_UINT32 vol);
FH_SINT32 FH_AC_AI_CH_SetDigitalVol(FH_UINT32 channel_mask, FH_UINT32 vol);
FH_SINT32 FH_AC_AI_GetFrame(FH_AC_AI_Frame_S *pstFrame);
FH_SINT32 FH_AC_AI_QueryBufSize(FH_UINT32 *pBufSize);
FH_SINT32 FH_AC_AI_ClearBuf(void);
FH_SINT32 FH_AC_AI_Pause(void);
FH_SINT32 FH_AC_AI_Resume(void);
FH_SINT32 FH_AC_AI_Get_Algo_Param(FH_UINT32 channel, void *param, FH_UINT32 len);
FH_SINT32 FH_AC_AI_Set_Algo_Param(FH_UINT32 channel, void *param, FH_UINT32 len);
FH_SINT32 FH_AC_AI_MIX_Set_Config(FH_AC_MIX_CONFIG *pstConfig);
FH_SINT32 FH_AC_AI_MIX_Get_Algo_Param(void *param, FH_UINT32 len);
FH_SINT32 FH_AC_AI_MIX_Set_Algo_Param(void *param, FH_UINT32 len);


/*for AO*/
FH_SINT32 FH_AC_AO_Enable(void);
FH_SINT32 FH_AC_AO_Disable(void);
FH_SINT32 FH_AC_AO_Set_Mode(FH_AC_AO_MODE_E mode);
FH_SINT32 FH_AC_AO_Pause(void);
FH_SINT32 FH_AC_AO_Resume(void);
FH_SINT32 FH_AC_AO_SetAnologVol(FH_SINT32 volume);
FH_SINT32 FH_AC_AO_SetDigitalVol(FH_SINT32 volume);
FH_SINT32 FH_AC_AO_SendFrame(FH_AC_AO_FRAME_S *pstFrame);
FH_SINT32 FH_AC_AO_QueryBufSize(FH_UINT32 *pBufSize);
FH_SINT32 FH_AC_AO_ClearBuf(void);
FH_SINT32 FH_AC_AO_WaitPlayComplete(void);
FH_SINT32 FH_AC_AO_Get_Algo_Param(void *param, FH_UINT32 len);
FH_SINT32 FH_AC_AO_Set_Algo_Param(void *param, FH_UINT32 len);


/* extended ioctl interface, for special case, don't use it */
FH_SINT32 FH_AC_Ext_Ioctl(FH_AC_EXT_IOCTL_CMD *pIoctl);
FH_SINT32 FH_AC_Ext2_Ioctl(FH_UINT32 cmd, FH_UINT32 subcmd, void *param,  FH_UINT32 len);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* FH_AC_MPI_H_ */
