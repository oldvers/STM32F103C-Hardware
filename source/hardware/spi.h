#ifndef __SPI_H__
#define __SPI_H__

#include "types.h"

typedef enum SPI_e
{
  SPI_1 = 0,
  SPI_2,
  SPI_COUNT
} SPI_t;

/* Callback Function Declarations */
typedef FW_BOOLEAN (*SPI_CbComplete_t)(FW_RESULT aResult, U32 aParam);

/* Function Declarations */
void       SPI_IrqHandler           (SPI_t aSPI);
void       SPI_Init      (SPI_t aSPI, SPI_CbComplete_t pCbComplete, U32 aParam);
void       SPI_MExchange            (SPI_t aSPI, U8 * pTx, U8 * pRx, U32 aSize);
void       SPI_DeInit               (SPI_t aSPI);
FW_BOOLEAN SPI_SetBaudratePrescaler (SPI_t aSPI, U16 value);

#endif /* __SPI_H__ */
