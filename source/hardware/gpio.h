#ifndef __GPIO_H__
#define __GPIO_H__

#include "types.h"

typedef enum GPIO_e
{
  GPIO_A = 0,
  GPIO_B,
  GPIO_C,
  GPIO_D,
  GPIO_E,
} GPIO_t;

/* --- Pin Mode (MODE) --- */
/* 0b00 = 0 - Input mode (reset state).
 * 0b01 = 1 - Output mode, max speed 10 MHz.
 * 0b10 = 2 - Output mode, max speed 2 MHz.
 * 0b11 = 3 - Output mode, max speed 50 MHz.
 */
/* --- Pin Configuration (CNF) --- */
/* In input mode (MODE[1:0] = 00).
 * 0b00 = 0 - Analog mode.
 * 0b01 = 1 - Floating input (reset state).
 * 0b10 = 2 - Input with Pull-Down / Pull-Up.
 * 0b11 = 3 - Reserved.
 * In output mode (MODE[1:0] > 00).
 * 0b00 = 0 - General purpose output Push-Pull.
 * 0b01 = 1 - General purpose output Open-Drain.
 * 0b10 = 2 - Alternate function output Push-Pull.
 * 0b11 = 3 - Alternate function output Open-Drain.
 */
typedef enum GPIO_TYPE_e
{
  GPIO_TYPE_MASK          = ((U32)0x0F),
  /* --- */
  GPIO_TYPE_IN_ANALOG     = ((U32)0x00),
  GPIO_TYPE_IN_FLOATING   = ((U32)0x04),
  GPIO_TYPE_IN_PUP_PDN    = ((U32)0x08),
  /* --- */
  GPIO_TYPE_OUT_PP_10MHZ  = ((U32)0x01),
  GPIO_TYPE_OUT_PP_2MHZ   = ((U32)0x02),
  GPIO_TYPE_OUT_PP_50MHZ  = ((U32)0x03),
  GPIO_TYPE_OUT_OD_10MHZ  = ((U32)0x05),
  GPIO_TYPE_OUT_OD_2MHZ   = ((U32)0x06),
  GPIO_TYPE_OUT_OD_30MHZ  = ((U32)0x07),
  GPIO_TYPE_ALT_PP_10MHZ  = ((U32)0x09),
  GPIO_TYPE_ALT_PP_2MHZ   = ((U32)0x0A),
  GPIO_TYPE_ALT_PP_50MHZ  = ((U32)0x0B),
  GPIO_TYPE_ALT_OD_10MHZ  = ((U32)0x0D),
  GPIO_TYPE_ALT_OD_2MHZ   = ((U32)0x0E),
  GPIO_TYPE_ALT_OD_50MHZ  = ((U32)0x0F),
} GPIO_TYPE_t;

void       GPIO_Init ( GPIO_t aPort, U8 aPin, GPIO_TYPE_t aType, U8 aValue );
void       GPIO_Hi   ( GPIO_t aPort, U8 aPin );
void       GPIO_Lo   ( GPIO_t aPort, U8 aPin );
FW_BOOLEAN GPIO_In   ( GPIO_t aPort, U8 aPin );

#endif /* __GPIO_H__ */
