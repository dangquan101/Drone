#include "stm32f4xx.h"
#include "gps.h"

UART_HandleTypeDef huart3;

void GPS_Init(void) {
    __HAL_RCC_USART3_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    huart3.Instance = USART3;
    huart3.Init.BaudRate = 9600;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart3);
}

void GPS_Read(float* lat, float* lon) {
    uint8_t buffer[100];
    HAL_UART_Receive(&huart3, buffer, 100, 1000);

    *lat = 10.0f;
    *lon = 106.0f;

    for (int i = 0; i < 100; i++) {
        if (buffer[i] == '$' && buffer[i+1] == 'G' && buffer[i+2] == 'P' && buffer[i+3] == 'G' && buffer[i+4] == 'G' && buffer[i+5] == 'A') {
            int j = i + 7;
            char lat_str[10] = {0};
            char lon_str[10] = {0};
            int k = 0;
            while (buffer[j] != ',') {
                lat_str[k++] = buffer[j++];
            }
            j++;
            k = 0;
            while (buffer[j] != ',') {
                lon_str[k++] = buffer[j++];
            }
            *lat = atof(lat_str) / 100.0f;
            *lon = atof(lon_str) / 100.0f;
            break;
        }
    }
}