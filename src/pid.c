/**
 * @file pid.c
 *
 * @brief PID related
 */

#include "pid.h"

/*****************************************
 * HIGH LEVEL MODULES
 *****************************************/

/*****************
 * PID
 *****************/

void pid_reset(pid_type* pid, float sp, float kp, float ki, float kd, float limMax, float limMin) {
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->sp = sp;

    pid->limMax = limMax;
    pid->limMin = limMin;

    pid->error_buffer_pointer = 0;

    for (uint16_t i = 0; i < PID_ERROR_BUFFER_SIZE; i++) {
        pid->error_buffer[i] = 0;
    }
}

float pid_update(pid_type* pid, float pv) {
    float mv;

    // Compute current error: PV - SP
    pid->error_buffer[pid->error_buffer_pointer] = pv - pid->sp;

    // Proportional Term - Average of last PID_ERROR_BUFFER_SIZE/2
    float proportional_aux = 0;

    for (int i = 0; i < (PID_ERROR_BUFFER_SIZE / 2); i++) {
        proportional_aux +=
            pid->error_buffer[(PID_ERROR_BUFFER_SIZE + pid->error_buffer_pointer - i) % PID_ERROR_BUFFER_SIZE];
    }

    pid->proportional = proportional_aux / (PID_ERROR_BUFFER_SIZE / 2);

    // Derivative Term - Difference between two halves of errors average
    float derivative_aux = 0;

    for (int i = (PID_ERROR_BUFFER_SIZE / 2); i < PID_ERROR_BUFFER_SIZE; i++) {
        derivative_aux +=
            pid->error_buffer[(PID_ERROR_BUFFER_SIZE + pid->error_buffer_pointer - i) % PID_ERROR_BUFFER_SIZE];
    }

    pid->derivative = pid->proportional - derivative_aux / (PID_ERROR_BUFFER_SIZE / 2);

    // Integral Term - Sum of Errors
    pid->integral += pid->proportional;

    // Anti-Windup
    if (pid->integral > pid->limMax) {
        pid->integral = pid->limMax;
    } else if (pid->integral < pid->limMin) {
        pid->integral = pid->limMin;
    }

    // Compute output
    mv = pid->kp * pid->proportional + pid->ki * pid->integral + pid->kd * pid->derivative;

    if (mv > pid->limMax) {
        mv = pid->limMax;
    } else if (mv < pid->limMin) {
        mv = pid->limMin;
    }

    // Next pointer
    pid->error_buffer_pointer = (pid->error_buffer_pointer + 1) % PID_ERROR_BUFFER_SIZE;

    return mv;
}
