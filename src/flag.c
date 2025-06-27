/**
 * @file flag.c
 *
 * @brief flag related
 */

#include "flag.h"

/*****************************************
 * LOW LEVEL MODULES
 *****************************************/
void servo_motor_control(int servo_counter_period) {
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, servo_counter_period);
}

/*****************************************
 * MID LEVEL MODULES
 *****************************************/

void flag_set_left() {
    servo_motor_control(SERVO_LEFT);
}

void flag_set_center() {
    servo_motor_control(SERVO_CENTER);
}

void flag_set_right() {
    servo_motor_control(SERVO_RIGHT);
}
