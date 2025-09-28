#include "stm32f1xx.h"

#include "gpio.h"

/* -------------------------------------------------------------------------- */

typedef struct
{
  volatile U32 CR[2];
  volatile U32 IDR;
  volatile U32 ODR;
  volatile U32 BSRR;
  volatile U32 BRR;
  volatile U32 LCKR;
} GPIO;

/* -------------------------------------------------------------------------- */

static const GPIO_TypeDef * gGPIO[] =
{
  [GPIO_A] = GPIOA,
  [GPIO_B] = GPIOB,
  [GPIO_C] = GPIOC,
  [GPIO_D] = GPIOD,
  [GPIO_E] = GPIOE,
};

/* -------------------------------------------------------------------------- */

void GPIO_Init(GPIO_t aPort, U8 aPin, GPIO_TYPE_t aType, U8 aValue)
{
  GPIO_TypeDef * pPort = (GPIO_TypeDef *)gGPIO[aPort];
  U32 temp  = 0;

  /* Enable GPIO clock */
  temp = (1 << (((U32)pPort >> 10) & 0x0F));
  temp |= (RCC_APB2ENR_AFIOEN * (U8)(aType > 8));
  RCC->APB2ENR |= temp;

  /* Set default value */
  if (0 == aValue)
  {
    pPort->BSRR = (1 << (aPin + 16));
  }
  else
  {
    pPort->BSRR = (1 << aPin);
  }

  /* Set GPIO operation mode */
  temp = ((GPIO *)pPort)->CR[aPin / 8];
  temp &= ~(GPIO_TYPE_MASK << ((aPin % 8) * 4));
  temp |= (aType << ((aPin % 8) * 4));
  ((GPIO *)pPort)->CR[aPin / 8] = temp;
}

/* -------------------------------------------------------------------------- */

void GPIO_Hi(GPIO_t aPort, U8 aPin)
{
  ((GPIO_TypeDef *)gGPIO[aPort])->BSRR = (1 << aPin);
}

/* -------------------------------------------------------------------------- */

void GPIO_Lo(GPIO_t aPort, U8 aPin)
{
  ((GPIO_TypeDef *)gGPIO[aPort])->BSRR = (1 << (aPin + 16));
}

/* -------------------------------------------------------------------------- */

FW_BOOLEAN GPIO_In(GPIO_t aPort, U8 aPin)
{
  return (FW_BOOLEAN)((((GPIO_TypeDef *)gGPIO[aPort])->IDR >> aPin) & FW_TRUE);
}

/* -------------------------------------------------------------------------- */
