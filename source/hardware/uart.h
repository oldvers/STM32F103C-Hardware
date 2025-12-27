#ifndef __UART_H__
#define __UART_H__

#include "types.h"

typedef enum UART_STOPBITS_e
{
  UART_STOPBITS_1 = 0,
  UART_STOPBITS_2,
} UART_STOPBITS_t;

typedef enum UART_PARITY_e
{
  UART_PARITY_NONE = 0,
  UART_PARITY_EVEN,
  UART_PARITY_ODD,
} UART_PARITY_t;

typedef enum UART_e
{
  UART1 = 0,
  UART2,
  UART3,
  UARTS_COUNT
} UART_t;

/* Callback Function Declarations */
typedef FW_BOOLEAN (*UART_CbByte)(U32 aParam, U8 * pByte);

/* Function Declarations */
void UART_Init          (UART_t aUART, U32 aBaudRate, U32 aParam);
void UART_SetCB_Break   (UART_t aUART, UART_CbByte pCb);
void UART_SetCB_RxByte  (UART_t aUART, UART_CbByte pCb);
void UART_SetCB_RxCmplt (UART_t aUART, UART_CbByte pCb);
void UART_SetCB_TxByte  (UART_t aUART, UART_CbByte pCb);
void UART_SetCB_TxCmplt (UART_t aUART, UART_CbByte pCb);
void UART_DeInit        (UART_t aUART);
void UART_TxStart       (UART_t aUART);
void UART_RxStart       (UART_t aUART);
void UART_SetBaudrate   (UART_t aUART, U32 aValue);
void UART_BiDirModeEn   (UART_t aUART);
void UART_Break         (UART_t aUART);

/* Interrupt Handler Declaration */
void UART_IrqHandler (UART_t aUART);

#endif  /* __UART_H__ */
