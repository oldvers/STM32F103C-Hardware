#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include "types.h"

extern U32 CPUClock;
extern U32 AHBClock;
extern U32 APB1Clock;
extern U32 APB2Clock;

FW_BOOLEAN SYS_IsInExceptionMode(void);
FW_BOOLEAN SYS_SetAPB2Prescaler(U8 value);

#endif /* __SYSTEM_H__ */
