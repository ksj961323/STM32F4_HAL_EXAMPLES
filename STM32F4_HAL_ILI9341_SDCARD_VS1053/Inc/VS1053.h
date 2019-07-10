#include "stdint.h"

#ifndef _VS1053_H_
#define _VS1053_H_

#include <stdbool.h>
#include "stm32f4xx_hal.h"

extern SPI_HandleTypeDef 			hspi3;
#define HSPI_VS1053					&hspi3
#define VS1053_DREQ_PORT			GPIOD
#define VS1053_DREQ_PIN				GPIO_PIN_0
#define	VS1053_XRST_PORT			GPIOD
#define	VS1053_XRST_PIN				GPIO_PIN_1
#define VS1053_XCS_PORT				GPIOD
#define VS1053_XCS_PIN				GPIO_PIN_2
#define VS1053_XDCS_PORT			GPIOD
#define VS1053_XDCS_PIN				GPIO_PIN_3

extern const uint8_t _VS1053_WRITE_CMD;
extern const uint8_t _VS1053_READ_CMD;

extern const uint8_t _VS1053_BASE_ADDR;
extern const uint8_t _VS1053_MODE_ADDR;
extern const uint8_t _VS1053_STATUS_ADDR;
extern const uint8_t _VS1053_BASS_ADDR;
extern const uint8_t _VS1053_CLOCKF_ADDR;
extern const uint8_t _VS1053_DECODE_TIME_ADDR ;
extern const uint8_t _VS1053_AUDATA_ADDR;
extern const uint8_t _VS1053_WRAM_ADDR;
extern const uint8_t _VS1053_WRAMADDR_ADDR;
extern const uint8_t _VS1053_HDAT0_ADDR;
extern const uint8_t _VS1053_HDAT1_ADDR;
extern const uint8_t _VS1053_AIADDR_ADDR;
extern const uint8_t _VS1053_VOL_ADDR;
extern const uint8_t _VS1053_AICTRL0_ADDR;
extern const uint8_t _VS1053_AICTRL1_ADDR;
extern const uint8_t _VS1053_AICTRL2_ADDR;
extern const uint8_t _VS1053_AICTRL3_ADDR;

void VS1053_Init();
void VS1053_Reset();
bool VS1053_IsBusy();
bool VS1053_CmdWrite(uint8_t address, uint16_t input);
bool VS1053_CmdRead(uint8_t address, uint16_t *res);
bool VS1053_DataWrite(uint8_t input);
bool VS1053_DataWrite32(uint8_t *input32);

#endif
