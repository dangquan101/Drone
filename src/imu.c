#include "stm32f4xx.h"
#include "imu.h"

I2C_HandleTypeDef hi2c1;

void IMU_Init(void) {
    __HAL_RCC_I2C1_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    HAL_I2C_Init(&hi2c1);

    uint8_t data = 0x00;
    HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x6B, 1, &data, 1, 1000);
    data = 0x03;
    HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x1B, 1, &data, 1, 1000);
    data = 0x03;
    HAL_I2C_Mem_Write(&hi2c1, 0xD0, 0x1C, 1, &data, 1, 1000);
}

void IMU_Read(float* roll, float* pitch, float* yaw) {
    uint8_t buffer[14];
    HAL_I2C_Mem_Read(&hi2c1, 0xD0, 0x3B, 1, buffer, 14, 1000);

    int16_t accel_x = (buffer[0] << 8) | buffer[1];
    int16_t accel_y = (buffer[2] << 8) | buffer[3];
    int16_t accel_z = (buffer[4] << 8) | buffer[5];
    int16_t gyro_x = (buffer[8] << 8) | buffer[9];
    int16_t gyro_y = (buffer[10] << 8) | buffer[11];
    int16_t gyro_z = (buffer[12] << 8) | buffer[13];

    *roll = accel_x / 16384.0f;
    *pitch = accel_y / 16384.0f;
    *yaw = gyro_z / 131.0f;
}