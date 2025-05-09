//
// Created by ashhar on 09/05/2025.
//

#ifndef ADS1115_H
#define ADS1115_H

#include "stm32f4xx_hal.h"

#define ADDR_CONV 0x0
#define ADDR_CONFIG 0x1
#define ADDR_Lo_thresh 0x2
#define ADDR_Hi_thresh 0x3

#define CONFIG_OS 0x80

#define CONFIG_MUX_DIFF_01 0x00
#define CONFIG_MUX_DIFF_03 0x10
#define CONFIG_MUX_DIFF_13 0x20
#define CONFIG_MUX_DIFF_23 0x30
#define CONFIG_MUX_COMM_0 0x40
#define CONFIG_MUX_COMM_1 0x50
#define CONFIG_MUX_COMM_2 0x60
#define CONFIG_MUX_COMM_3 0x70

#define CONFIG_PGA_FSR_6 0x00
#define CONFIG_PGA_FSR_4 0x02
#define CONFIG_PGA_FSR_2 0x04
#define CONFIG_PGA_FSR_1 0x06
#define CONFIG_PGA_FSR_05 0x08
#define CONFIG_PGA_FSR_02 0x0A
#define CONFIG_PGA_FSR_022 0x0C
#define CONFIG_PGA_FSR_0222 0x0E

#define CONFIG_MODE_CONT 0x00
#define CONFIG_MODE_SS 0x01

#define CONFIG_DR_8 0x00
#define CONFIG_DR_16 0x20
#define CONFIG_DR_32 0x40
#define CONFIG_DR_64 0x60
#define CONFIG_DR_128 0x80
#define CONFIG_DR_250 0xA0
#define CONFIG_DR_475 0xC0
#define CONFIG_DR_860 0xE0

#define CONFIG_COMP_MODE_TRAD 0x00
#define CONFIG_COMP_MODE_WINDOW 0x10

#define CONFIG_COMP_POL_ALOW 0x00
#define CONFIG_COMP_POL_AHIGH 0x08

#define CONFIG_COMP_LAT_OFF 0x00
#define CONFIG_COMP_LAT_ON 0x04

#define CONFIG_COMP_QUE_1 0x00
#define CONFIG_COMP_QUE_2 0x01
#define CONFIG_COMP_QUE_4 0x02
#define CONFIG_COMP_QUE_0 0x03

typedef struct{
    I2C_HandleTypeDef* hi2c;
    uint8_t I2C_Addr;
    uint8_t OS;
    uint8_t MUX;
    uint8_t PGA;
    uint8_t MODE;
    uint8_t DR;
    uint8_t COMP_MODE;
    uint8_t COMP_POL;
    uint8_t COMP_LAT;
    uint8_t COMP_QUE;
    uint8_t Hi_Thres[2];
    uint8_t Lo_Thres[2];
    float scale;
    float captured;
}ads1115_t;

HAL_StatusTypeDef ADS1115_init(ads1115_t* ads);
HAL_StatusTypeDef ADS1115_read(ads1115_t* ads);

#endif //ADS1115_H
