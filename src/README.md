Drone Development Project
This is a drone project built with STM32 microcontroller. It has basic flight control, stabilization, GPS tracking, and RF communication.
Hardware

STM32F4 microcontroller
MPU6050 IMU (gyroscope + accelerometer)
NEO-6M GPS module
NRF24L01 RF module
Drone frame, motors, ESCs, battery

Software

Written in C/C++
Uses STM32 HAL library
Implements PID for stabilization
Reads IMU and GPS data
Sends telemetry via RF
Syscalls for UART output (printf debugging)

Files

main.c: Main program loop, initializes modules
imu.c, imu.h: IMU sensor handling
gps.c, gps.h: GPS module handling
pid.c, pid.h: PID control for stabilization
rf.c, rf.h: RF communication
syscalls.c: System calls for UART output

How to Use

Connect STM32 to IMU (I2C), GPS (UART), RF (SPI)
Flash code to STM32 using PlatformIO or STM32CubeIDE
Power on drone
Calibrate IMU and GPS
Test flight and monitor telemetry via serial monitor (115200 baud on USART2)

Notes

PID values (kp, ki, kd) may need tuning
GPS parsing is basic, improve for better accuracy
RF range is limited, test in open area
Use a serial monitor to view debug output

Requirements

PlatformIO or STM32CubeIDE
STM32F4 hardware
Sensors and RF module
Drone components

