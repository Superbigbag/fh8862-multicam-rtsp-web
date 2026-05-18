#ifndef _FIFO_H_
#define _FIFO_H_


#include "types/type_def.h"
#include "fh_std_osal_usr.h"
typedef fh_mutex_t fh_lock_t;
#define fh_lock_init(x)     fh_mutex_init((fh_lock_t *)&x, "isp_lock")
#define fh_lock_destroy(x)  fh_mutex_destroy((fh_lock_t *)&x)
#define fh_lock(x)          fh_mutex_lock((fh_lock_t *)&x)
#define fh_unlock(x)        fh_mutex_unlock((fh_lock_t *)&x)

//fix me! Dynamic FIFO size need Heap support
#define FIFO_DEPTH		1024			// should be power of 2

typedef volatile struct _FifoDesc
{
	FH_UINT8 			fifo[FIFO_DEPTH];
	FH_UINT16 			rp;		// read pointer
	FH_UINT16 			wp;		// write pointer
	FH_UINT8			empty;
	FH_UINT8			full;
	FH_UINT8			overflow;
	fh_lock_t		    lock;
}FifoDesc;

int Fifo_Init(FifoDesc *desc);
int Fifo_Destroy(FifoDesc *desc);
int Fifo_Clear(FifoDesc *desc);
int Fifo_Read(FifoDesc *desc, FH_UINT8 *buf, int size);
int Fifo_Write(FifoDesc *desc, FH_UINT8 *buf, int size);
int Fifo_DataLeft(FifoDesc *desc);
int Fifo_Inspect(FifoDesc *desc, FH_UINT8 *buf, FH_UINT32 size);

#endif

