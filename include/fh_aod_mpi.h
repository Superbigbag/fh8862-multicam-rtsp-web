#ifndef __FH_AOD_MPI_H__
#define __FH_AOD_MPI_H__
/**AOD**/

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#define MAX_ABONDON_OBJ_CNT (100)

typedef struct _aod_rect
{
    unsigned int x;
    unsigned int y;
    unsigned int w;
    unsigned int h;
} FH_AOD_RECT_T;

typedef struct _fh_aod_obj_info
{
	unsigned int aodCnt;
	FH_AOD_RECT_T aodRects[MAX_ABONDON_OBJ_CNT];
} FH_AOD_OBJ_INFO_t;

typedef struct _fh_aod_init_param
{
    unsigned int alarm_cnt;     //default 45
    unsigned int max_miss_cnt;  //default 7
} FH_AOD_INIT_PARAM_t;

void FH_AOD_Init(FH_AOD_INIT_PARAM_t *pParam);
void FH_AOD_Process(FH_AOD_OBJ_INFO_t *aodIn, FH_AOD_OBJ_INFO_t *aodOut);
void FH_AOD_Exit(void);
void FH_AOD_PrintVersion(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /*__FH_AOD_MPI_H__ */
