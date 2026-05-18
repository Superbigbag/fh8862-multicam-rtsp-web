#ifndef _ISP_STRATEGY_IF_H_
#define _ISP_STRATEGY_IF_H_

#include "types/type_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */
#pragma pack(4)

/**
 * @brief		ISP策略模块基类，每个策略模块应该继承该类，并初始化。通过安装策略，
 *				将其加入ISP Core中。
 */
struct isp_strategy		// module interface
{
	FH_CHAR*	name;			/*!< 策略名称 */
	FH_VOID	(*run)(FH_UINT32 u32Id);	/*!< 策略运行函数指针 */
};

#pragma pack()
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* _ISP_STRATEGY_H_ */
