#ifndef __HARDWARE_CONFIG_H__
#define __HARDWARE_CONFIG_H__

/* Debug interface */
#define DBG_RTT

/* SWD - SWO */
#define SWD_SWO_PORT         GPIOB
#define SWD_SWO_PIN          3

/* USB - Pull Up */
#define USB_PUP_PORT         GPIOB
#define USB_PUP_PIN          2

/* USB - DP/DM */
#define USB_DM_PORT          GPIOA
#define USB_DM_PIN           11
#define USB_DP_PORT          GPIOA
#define USB_DP_PIN           12

/* LED */
#define LED_PORT             GPIOC
#define LED_PIN              13

/* I2C1: PB6 - SCL, PB7 - SDA */
#define I2C1_SCL_PORT        GPIOB
#define I2C1_SCL_PIN         6
#define I2C1_SDA_PORT        GPIOB
#define I2C1_SDA_PIN         7

#endif  /* __HARDWARE_CONFIG_H__ */
