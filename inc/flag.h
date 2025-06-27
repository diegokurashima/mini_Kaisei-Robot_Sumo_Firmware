/**
 * @file flag.h
 *
 * @brief flag related
 */

#ifndef __FLAG_H__
#define __FLAG_H__

#include "tim.h"
#include <stdint.h>
#include <stdio.h>

/*****************************************
 * DEFINES
 *****************************************/
#define SERVO_LEFT (1200)
#define SERVO_CENTER (750)
#define SERVO_RIGHT (300)

/*****************************************
 * LOW LEVEL MODULES
 *****************************************/

/**
 * @brief Control servo motor position. Raw Input 0-10000
 */
void servo_motor_control(int servo_counter_period);

/*****************************************
 * MID LEVEL MODULES
 *****************************************/

/**
 * @brief Turn flag 100% to left
 */
void flag_set_left();

/**
 * @brief Turn flag to center
 */
void flag_set_center();

/**
 * @brief Turn flag 100% to right
 */
void flag_set_right();

#endif // __FLAG_H__
