/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DAC8555_H
#define __DAC8555_H

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
/* Private define ------------------------------------------------------------*/

typedef struct DAC8555_SpiDriver_Struct {
  void (*Dac8555_CS_Low)(void);
  void (*Dac8555_CS_High)(void);
  void (*Dac8555_Spi_WriteByte)(uint8_t);
  void (*Dac8555_Delay_1ms)(void);
} DAC8555_SpiDriver_Typedef;

/* Functions -----------------------------------------------------------------*/
//void DAC_LoadOne(uint8_t cardSelect, uint8_t channel, int16_t dac_val);
bool DAC8555_Init(DAC8555_SpiDriver_Typedef * dac8555_SpiDriver,
 void (*Dac8555_CS_Low)(void),
 void (*Dac8555_CS_High)(void),
 void (*Dac8555_Spi_WriteByte)(uint8_t),
 void (*Dac8555_Delay_1ms)(void));
void DAC8555_LoadAll(DAC8555_SpiDriver_Typedef * dac8555_SpiDriver, int16_t dac_val1, int16_t dac_val2, int16_t dac_val3, int16_t dac_val4);

#endif /* __DAC8555_H */
