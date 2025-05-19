#include "pid.h"

float kp = 1.0f;
float ki = 0.1f;
float kd = 0.05f;

float roll_error_sum = 0.0f;
float pitch_error_sum = 0.0f;
float yaw_error_sum = 0.0f;

float last_roll_error = 0.0f;
float last_pitch_error = 0.0f;
float last_yaw_error = 0.0f;

void PID_Init(void) {
    roll_error_sum = 0.0f;
    pitch_error_sum = 0.0f;
    yaw_error_sum = 0.0f;
    last_roll_error = 0.0f;
    last_pitch_error = 0.0f;
    last_yaw_error = 0.0f;
}

void PID_Compute(float roll, float pitch, float yaw, float* pid_roll, float* pid_pitch, float* pid_yaw) {
    float roll_error = 0.0f - roll;
    float pitch_error = 0.0f - pitch;
    float yaw_error = 0.0f - yaw;

    roll_error_sum += roll_error;
    pitch_error_sum += pitch_error;
    yaw_error_sum += yaw_error;

    float roll_d_error = roll_error - last_roll_error;
    float pitch_d_error = pitch_error - last_pitch_error;
    float yaw_d_error = yaw_error - last_yaw_error;

    *pid_roll = kp * roll_error + ki * roll_error_sum + kd * roll_d_error;
    *pid_pitch = kp * pitch_error + ki * pitch_error_sum + kd * pitch_d_error;
    *pid_yaw = kp * yaw_error + ki * yaw_error_sum + kd * yaw_d_error;

    last_roll_error = roll_error;
    last_pitch_error = pitch_error;
    last_yaw_error = yaw_error;
}