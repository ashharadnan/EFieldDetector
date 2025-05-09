//
// Created by ashhar on 09/05/2025.
//

#include "ADS1115.h"
#include "main.h"

HAL_StatusTypeDef ADS1115_init(ads1115_t* ads){
    uint8_t config[2];
    config[0] = ads->OS | ads->MUX | ads->PGA | ads->MODE;
    config[1] = ads->DR | ads->COMP_MODE | ads->COMP_POL | ads->COMP_LAT | ads->COMP_QUE;

    if (HAL_I2C_IsDeviceReady(ads->hi2c, (uint16_t) (ads->I2C_Addr) << 1, 5, 100) != HAL_OK) return HAL_ERROR;
    if (HAL_I2C_Mem_Write(ads->hi2c, (uint16_t) (ads->I2C_Addr) << 1, ADDR_Hi_thresh, 1, ads->Hi_Thres, 2, 1000) != HAL_OK) return HAL_ERROR;
    if (HAL_I2C_Mem_Write(ads->hi2c, (uint16_t) (ads->I2C_Addr) << 1, ADDR_Lo_thresh, 1, ads->Lo_Thres, 2, 1000) != HAL_OK) return HAL_ERROR;
    if (HAL_I2C_Mem_Write(ads->hi2c, (uint16_t) (ads->I2C_Addr) << 1, ADDR_CONFIG, 1, config, 2, 1000) != HAL_OK) return HAL_ERROR;
    print("HAL_OK\n");
    return HAL_OK;
}

HAL_StatusTypeDef ADS1115_read(ads1115_t* ads){
    uint8_t capture[2];
    if (HAL_I2C_Mem_Read(ads->hi2c,  (uint16_t) (ads->I2C_Addr) << 1, ADDR_CONV, 1, capture, 2, 1) != HAL_OK) return HAL_ERROR;
    float voltage;
    voltage = (((int16_t) (capture[0] << 8) | capture[1]) * ads->scale);
    ads->captured = voltage;
    return HAL_OK;
}