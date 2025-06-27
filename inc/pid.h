/**
 * @file pid.h
 *
 * @brief PID related
 */

#ifndef __PID_H__
#define __PID_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/*****************************************
 * DEFINES
 *****************************************/

#define PID_ERROR_BUFFER_SIZE (10)

typedef struct {
    // Gains
    float kp;
    float ki;
    float kd;

    // Setpoint
    float sp;

    // Error handling
    int   error_buffer_pointer;
    float error_buffer[PID_ERROR_BUFFER_SIZE];

    float proportional;
    float derivative;
    float integral;

    // Output limits
    float limMin;
    float limMax;
} pid_type;

/*****************************************
 * HIGH LEVEL MODULES
 *****************************************/

/*****************
 * PID
 *****************/

/**
 * @brief Set the initial conditions for the PID controller
 *
 * @param pid PID object with PID paramenters
 *
 */
void pid_reset(pid_type* pid, float sp, float kp, float ki, float kd, float limMax, float limMin);

/**
 * @brief Set the PID controller to update
 *
 * @param pid PID object with PID paramenters
 *
 * @return PID output
 *
 */
float pid_update(pid_type* pid, float pv);

#endif // __PID_H__
