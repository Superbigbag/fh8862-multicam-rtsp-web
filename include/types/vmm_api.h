/*
 * vmm_api.h
 *
 * Copyright (c) Fullhan Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 */


#ifndef VMM_API_H_
#define VMM_API_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

#include "types/type_def.h"


/* alloc mmz memory in user context                                         */
FH_SINT32 FH_SYS_VmmAlloc(FH_UINT32 *pu32PhyAddr, FH_VOID **ppVirtAddr,
        const FH_CHAR *strMmb, const FH_CHAR *strZone, FH_UINT32 u32Len);
FH_SINT32 FH_SYS_VmmAllocEx(FH_UINT32 *pu32PhyAddr, FH_VOID **ppVirtAddr,
                const FH_CHAR *strMmb, const FH_CHAR *strZone, FH_UINT32 u32Len,
                FH_UINT32 u32Align);

/* alloc mmz memory with cache */
FH_SINT32 FH_SYS_VmmAlloc_Cached(FH_UINT32 *pu32PhyAddr, FH_VOID **ppVirtAddr,
        const FH_CHAR *pstrMmb, const FH_CHAR *pstrZone, FH_UINT32 u32Len);
FH_SINT32 FH_SYS_VmmAllocEx_Cached(FH_UINT32 *pu32PhyAddr, FH_VOID **ppVirtAddr,
        const FH_CHAR *pstrMmb, const FH_CHAR *pstrZone, FH_UINT32 u32Len,
        FH_UINT32 u32Align);

/* 64bit api */
FH_SINT32 FH_SYS_VmmAlloc64(FH_UINT64 *pu64PhyAddr, FH_VOID **ppVirtAddr,
        const FH_CHAR *strMmb, const FH_CHAR *strZone, FH_UINT32 u32Len);
FH_SINT32 FH_SYS_VmmAllocEx64(FH_UINT64 *pu64PhyAddr, FH_VOID **ppVirtAddr,
                const FH_CHAR *strMmb, const FH_CHAR *strZone, FH_UINT32 u32Len,
                FH_UINT32 u32Align);

/* alloc mmz memory with cache */
FH_SINT32 FH_SYS_VmmAlloc_Cached64(FH_UINT64 *pu64PhyAddr, FH_VOID **ppVirtAddr,
        const FH_CHAR *pstrMmb, const FH_CHAR *pstrZone, FH_UINT32 u32Len);
FH_SINT32 FH_SYS_VmmAllocEx_Cached64(FH_UINT64 *pu64PhyAddr, FH_VOID **ppVirtAddr,
        const FH_CHAR *pstrMmb, const FH_CHAR *pstrZone, FH_UINT32 u32Len,
        FH_UINT32 u32Align);

/* free mmz memory in user context                                          */

FH_SINT32 FH_SYS_VmmFree(FH_UINT32 u32PhyAddr);
FH_SINT32 FH_SYS_VmmFree64(FH_UINT64 u64PhyAddr);

FH_SINT32 FH_SYS_VmmFreeOne(FH_UINT32 u32PhyAddr);
FH_SINT32 FH_SYS_VmmFreeOne64(FH_UINT64 u64PhyAddr);

/* fulsh cache */
FH_SINT32 FH_SYS_VmmFlushCache(FH_UINT32 u32PhyAddr, FH_VOID *pVirtAddr, FH_UINT32 u32Size);
FH_SINT32 FH_SYS_VmmFlushCache64(FH_UINT64 u64PhyAddr, FH_VOID *pVirtAddr, FH_UINT32 u32Size);

/*
** Call the mmap function to map physical address to virtual address
** The system function mmap is too complicated, so we packge it.
** 存储映射接口
*/
FH_VOID *FH_SYS_Mmap(FH_UINT32 u32PhyAddr, FH_UINT32 u32Size);
FH_VOID *FH_SYS_Mmap64(FH_UINT64 u64PhyAddr, FH_UINT32 u32Size);
FH_VOID *FH_SYS_MmapCached(FH_UINT32 u32PhyAddr, FH_UINT32 u32Size);
FH_VOID *FH_SYS_MmapCached64(FH_UINT64 u64PhyAddr, FH_UINT32 u32Size);
FH_SINT32 FH_SYS_Munmap(FH_VOID* pVirtAddr, FH_UINT32 u32Size);

/* Get address of virtual register */
FH_SINT32 FH_SYS_GetVRegAddr(FH_UINT32 *pu32Addr);

/* Get physical address by virtual address */
FH_SINT32 FH_SYS_VmmGetPaddr_ByVaddr(FH_UINT32 *u32PhyAddr, FH_VOID *pVirtAddr);
FH_SINT32 FH_SYS_VmmGetPaddr_ByVaddr64(FH_UINT64 *u64PhyAddr, FH_VOID *pVirtAddr);

/* Close all the FD which is used by sys module */
FH_SINT32 FH_SYS_CloseFd(FH_VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* VMM_API_H_ */
