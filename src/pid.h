#ifndef PID_H
#define PID_H

void PID_Init(void);
void PID_Compute(float roll, float pitch, float yaw, float* pid_roll, float* pid_pitch, float* pid_yaw);

#endif