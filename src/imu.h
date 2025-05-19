#ifndef IMU_H
#define IMU_H

void IMU_Init(void);
void IMU_Read(float* roll, float* pitch, float* yaw);

#endif