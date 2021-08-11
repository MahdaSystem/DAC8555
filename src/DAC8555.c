#include "DAC8555.h"

/*
  DAC8555
  D00: DAC Data 00
  D01: DAC Data 01
  D02: DAC Data 02
  D03: DAC Data 03
  D04: DAC Data 04
  D05: DAC Data 05
  D06: DAC Data 06
  D07: DAC Data 07
  D08: DAC Data 08
  D09: DAC Data 09
  D10: DAC Data 10
  D11: DAC Data 11
  D12: DAC Data 12
  D13: DAC Data 13
  D14: DAC Data 14 (or PD2)
  D15: DAC Data 15 (or PD1)
  D16: PD0 (Power Down Mode Flag)
  D17: DAC Channel Select 0
  D18: DAC Channel Select 1
  D19: Dont Care Bit
  D20: LD0
  D21: LD1
  D22: Always 0
  D23: Always 0 
*/

#define Dac8555_BIT_HIGH(REG, BIT)  ((REG) |= (BIT))
#define Dac8555_BIT_LOW(REG, BIT)   ((REG) &= ~(BIT))

#define Dac8555_lowByte(w) ((uint8_t) ((w) & 0xff))
#define Dac8555_highByte(w) ((uint8_t) ((w) >> 8))

static uint8_t dac8555_header;
static uint8_t dac8555_hiByte;
static uint8_t dac8555_loByte;
bool DAC8555_Init(DAC8555_SpiDriver_Typedef * dac8555_SpiDriver,
 void (*Dac8555_CS_Low)(void),
 void (*Dac8555_CS_High)(void),
 void (*Dac8555_Spi_WriteByte)(uint8_t),
 void (*Dac8555_Delay_1ms)(void)) {
  if(Dac8555_CS_Low && Dac8555_CS_High && Dac8555_Spi_WriteByte && Dac8555_Delay_1ms) {
    dac8555_SpiDriver->Dac8555_CS_Low = Dac8555_CS_Low;
    dac8555_SpiDriver->Dac8555_CS_High = Dac8555_CS_High;
    dac8555_SpiDriver->Dac8555_Spi_WriteByte = Dac8555_Spi_WriteByte;
    dac8555_SpiDriver->Dac8555_Delay_1ms = Dac8555_Delay_1ms;
    return true;
  }
  else {
    return false;
  }
}

void DAC8555_LoadOne(DAC8555_SpiDriver_Typedef * dac8555_SpiDriver, uint8_t channel, int16_t dac_val) {
	// dac8555_header : configuration byte
	// dac8555_hiByte : data bytes 15 to 8
	// dac8555_loByte : data bytes 7 to 0
	switch(channel) {
		case 0: { // Channel A
			dac8555_SpiDriver->Dac8555_CS_Low();
      dac8555_SpiDriver->Dac8555_Delay_1ms();
			dac8555_header = 0x10;
			dac8555_hiByte = Dac8555_highByte(dac_val); //Divides the integer into two bytes
			dac8555_loByte = Dac8555_lowByte(dac_val);
			dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_header);
      dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_hiByte);
      dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_loByte);
			dac8555_SpiDriver->Dac8555_CS_High();
      dac8555_SpiDriver->Dac8555_Delay_1ms();
			break;
		}
		case 1: { // Channel B
			dac8555_SpiDriver->Dac8555_CS_Low();
      dac8555_SpiDriver->Dac8555_Delay_1ms();
			dac8555_header = 0x12;
			dac8555_hiByte = Dac8555_highByte(dac_val); //Divides the integer into two bytes
			dac8555_loByte = Dac8555_lowByte(dac_val);
			dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_header);
      dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_hiByte);
      dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_loByte);
			dac8555_SpiDriver->Dac8555_CS_High();
      dac8555_SpiDriver->Dac8555_Delay_1ms();
			break;
		}
		case 2: { // Channel C
			dac8555_SpiDriver->Dac8555_CS_Low();
      dac8555_SpiDriver->Dac8555_Delay_1ms();
			dac8555_header = 0x14;
			dac8555_hiByte = Dac8555_highByte(dac_val); //Divides the integer into two bytes
			dac8555_loByte = Dac8555_lowByte(dac_val);
			dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_header);
      dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_hiByte);
      dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_loByte);
			dac8555_SpiDriver->Dac8555_CS_High();
      dac8555_SpiDriver->Dac8555_Delay_1ms();
			break;
		}
		case 3: { // Channel D
			dac8555_SpiDriver->Dac8555_CS_Low();
      dac8555_SpiDriver->Dac8555_Delay_1ms();
			dac8555_header = 0x16;
			dac8555_hiByte = Dac8555_highByte(dac_val); //Divides the integer into two bytes
			dac8555_loByte = Dac8555_lowByte(dac_val);
			dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_header);
      dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_hiByte);
      dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_loByte);
			dac8555_SpiDriver->Dac8555_CS_High();
      dac8555_SpiDriver->Dac8555_Delay_1ms();
			break;
		}
	}
}
void DAC8555_LoadAll(DAC8555_SpiDriver_Typedef * dac8555_SpiDriver, int16_t dac_val1, int16_t dac_val2, int16_t dac_val3, int16_t dac_val4) {
	// dac8555_header : configuration byte
	// dac8555_hiByte : data bytes 15 to 8
	// dac8555_loByte : data bytes 7 to 0
	
	// Channel A
	dac8555_SpiDriver->Dac8555_CS_Low();
  dac8555_SpiDriver->Dac8555_Delay_1ms();
	dac8555_header = 0;
	dac8555_hiByte = Dac8555_highByte(dac_val1); //Divides the integer into two bytes
	dac8555_loByte = Dac8555_lowByte(dac_val1);
  dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_header);
  dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_hiByte);
  dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_loByte);
	dac8555_SpiDriver->Dac8555_CS_High();
  dac8555_SpiDriver->Dac8555_Delay_1ms();
	
	// Channel B
	dac8555_SpiDriver->Dac8555_CS_Low();
  dac8555_SpiDriver->Dac8555_Delay_1ms();
	dac8555_header = 0x2;
	dac8555_hiByte = Dac8555_highByte(dac_val2); //Divides the integer into two bytes
	dac8555_loByte = Dac8555_lowByte(dac_val2);
	dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_header);
  dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_hiByte);
  dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_loByte);
	dac8555_SpiDriver->Dac8555_CS_High();
  dac8555_SpiDriver->Dac8555_Delay_1ms();
	
	// Channel C
	dac8555_SpiDriver->Dac8555_CS_Low();
  dac8555_SpiDriver->Dac8555_Delay_1ms();
	dac8555_header = 0x4;
	dac8555_hiByte = Dac8555_highByte(dac_val3); //Divides the integer into two bytes
	dac8555_loByte = Dac8555_lowByte(dac_val3);
	dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_header);
  dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_hiByte);
  dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_loByte);
	dac8555_SpiDriver->Dac8555_CS_High();
  dac8555_SpiDriver->Dac8555_Delay_1ms();
	
	// Channel D
	dac8555_SpiDriver->Dac8555_CS_Low();
  dac8555_SpiDriver->Dac8555_Delay_1ms();
	dac8555_header = 0x6;
	dac8555_hiByte = Dac8555_highByte(dac_val4); //Divides the integer into two bytes
	dac8555_loByte = Dac8555_lowByte(dac_val4);
	dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_header);
  dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_hiByte);
  dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_loByte);
	dac8555_SpiDriver->Dac8555_CS_High();
	dac8555_SpiDriver->Dac8555_Delay_1ms();
  
	dac8555_SpiDriver->Dac8555_CS_Low();
  dac8555_SpiDriver->Dac8555_Delay_1ms();
	dac8555_header = 0x30;
	dac8555_hiByte = 0;
	dac8555_loByte = 0;
	dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_header);
  dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_hiByte);
  dac8555_SpiDriver->Dac8555_Spi_WriteByte(dac8555_loByte);
	dac8555_SpiDriver->Dac8555_CS_High();
  dac8555_SpiDriver->Dac8555_Delay_1ms();
}
