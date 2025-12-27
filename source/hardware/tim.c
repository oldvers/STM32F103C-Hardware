#include "stm32f1xx.h"
#include "types.h"
#include "interrupts.h"
#include "tim.h"

/* -------------------------------------------------------------------------- */

typedef struct
{
  TIM_CbComplete_t pCb;
  U32              Param;
} TIM_ContextChannel_t;

/* -------------------------------------------------------------------------- */

static TIM_ContextChannel_t gTim2[TIM_CH_COUNT] = {0};

/* -------------------------------------------------------------------------- */
/** @brief Processes the TIM2 interrupt
 *  @param None
 *  @return None
 */

void TIM2_IrqHandler(void)
{
  U16 value = 0;

  if ((0 != (TIM2->SR & TIM_SR_CC3IF)) && (0 != (TIM2->DIER & TIM_DIER_CC3IE)))
  {
    value = TIM2->CCR3;
    if (NULL != gTim2[TIM_CH3].pCb)
    {
      gTim2[TIM_CH3].pCb(TIM_CH3, value, gTim2[TIM_CH3].Param);
    }
  }
}

/* -------------------------------------------------------------------------- */
/** @brief Initializes the TIM2 input capture
 *  @param aChannel - A number of TIM2 channel
 *  @param pCbComplete - Pointer to the TIM2 input capture callback function
 *  @param aParam - Optional parameter to use in the callback function
 *  @return None
 */

void TIM2_InitInputCapture
(
  U8 aChannel,
  TIM_CbComplete_t pCbComplete,
  U32 aParam
)
{
  U16 ccmr1, ccmr2, ccer, dier;

  ccmr1 = TIM2->CCMR1;
  ccmr2 = TIM2->CCMR2;
  ccer  = TIM2->CCER;
  dier  = TIM2->DIER;

  /* Configure CHx as input, no filter, no prescaller */
  /* Configure CHx to input capture mode, non-inverted */
  /* Enable timer interrupts */
  switch(aChannel)
  {
    case TIM_CH1:
      ccmr1 &= (0xFF00);
      ccmr1 |= TIM_CCMR1_CC1S_0;
      ccer  &= (0xFFF0);
      ccer  |= TIM_CCER_CC1E;
      dier  &= ~(TIM_DIER_CC1DE | TIM_DIER_CC1IE);
      dier  |= TIM_DIER_CC1IE;
      break;
    case TIM_CH2:
      ccmr1 &= (0x00FF);
      ccmr1 |= TIM_CCMR1_CC2S_0;
      ccer  &= (0xFF0F);
      ccer  |= TIM_CCER_CC2E;
      dier  &= ~(TIM_DIER_CC2DE | TIM_DIER_CC2IE);
      dier  |= TIM_DIER_CC2IE;
      break;
    case TIM_CH3:
      ccmr2 &= (0xFF00);
      ccmr2 |= TIM_CCMR2_CC3S_0;
      ccer  &= (0xF0FF);
      ccer  |= TIM_CCER_CC3E;
      dier  &= ~(TIM_DIER_CC3DE | TIM_DIER_CC3IE);
      dier  |= TIM_DIER_CC3IE;
      break;
    case TIM_CH4:
      ccmr2 &= (0x00FF);
      ccmr2 |= TIM_CCMR2_CC4S_0;
      ccer  &= (0x0FFF);
      ccer  |= TIM_CCER_CC4E;
      dier  &= ~(TIM_DIER_CC4DE | TIM_DIER_CC4IE);
      dier  |= TIM_DIER_CC4IE;
      break;
    default:
      return;
  }

  /* Enable timer clock, reset timer */
  RCC->APB1ENR  |= RCC_APB1ENR_TIM2EN;
  RCC->APB1RSTR |= RCC_APB1RSTR_TIM2RST;
  RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST);

  /* Setup TIM2 channel to input capture */
  TIM2->CR1   = TIM_CR1_URS;
  TIM2->CR2   = 0;
  TIM2->PSC   = 0;
  TIM2->ARR   = 0xFFFF;
  TIM2->CCMR1 = ccmr1;
  TIM2->CCMR2 = ccmr2;
  TIM2->CCER  = ccer;
  TIM2->DIER  = dier;

  gTim2[aChannel].pCb   = pCbComplete;
  gTim2[aChannel].Param = aParam;

  IRQ_TIM2_Enable();
}

/* -------------------------------------------------------------------------- */
/** @brief Deinitializes the TIM2
 *  @param None
 *  @return None
 */

void TIM2_DeInit(void)
{
  /* Reset timer, disable timer clock */
  RCC->APB1RSTR |= RCC_APB1RSTR_TIM2RST;
  RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST);
  RCC->APB1ENR  &= ~(RCC_APB1ENR_TIM2EN);

  /* Disable interrupts */
  IRQ_TIM2_Disable();
}

/* -------------------------------------------------------------------------- */
/** @brief Enables the TIM2 interrupt
 *  @param None
 *  @return None
 */

void TIM2_Enable(void)
{
  TIM2->CR1 |= TIM_CR1_CEN;
}

/* -------------------------------------------------------------------------- */
/** @brief Disables the TIM2 interrupt
 *  @param None
 *  @return None
 */

void TIM2_Disable(void)
{
  TIM2->CR1 &= ~(TIM_CR1_CEN);
}

/* -------------------------------------------------------------------------- */
