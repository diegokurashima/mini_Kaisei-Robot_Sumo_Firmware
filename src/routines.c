/**
 * @file routines.c
 *
 * @brief Robot general routines related
 */

#include "routines.h"

#include "motors.h"
#include "distance_sensors.h"
#include "mcu.h"

/*****************************************
 * DEFINES
 *****************************************/
#define STEP_SPEED (50)
#define STEP_WAIT_TIME (2000)
#define STEP_MOVE_TIME (20)
#define STEP_AHEAD_MAX (2)

#define STEP_FORCE_TIME (500)

/*****************************************
 * PRIVATE VARIABLES
 *****************************************/

// STEP VARIABLES
uint32_t step_timer;
uint8_t step_ahead_count;

/*****************************************
 * HIGH LEVEL MODULES
 *****************************************/

/*****************
 * STEP ROUTINES
 *****************/

void routine_step_reset() {
    reset_timer(step_timer);
    step_ahead_count = 0;
}

void routine_step_run() {
    /*
     * STEP SEARCH CYCLE
     */
    if (get_timer(step_timer) < STEP_WAIT_TIME) {
        /* Robot STOPPED
         */
        motors_control(0, 0);
    } else if (get_timer(step_timer) < STEP_WAIT_TIME + STEP_MOVE_TIME) {
        /* Robot STEP
         */
        if (step_ahead_count < STEP_AHEAD_MAX) {
            motors_control(STEP_SPEED, STEP_SPEED); // AHEAD step
        } else {
            motors_control(-STEP_SPEED, -STEP_SPEED); // BACK step
        }
    } else {
        /* Reset Step Cycle
         */
        motors_control(0, 0);
        step_ahead_count++;

        // step_cycles_count++;

        if (step_ahead_count > STEP_AHEAD_MAX) {
            step_ahead_count = 0;
        }

        reset_timer(step_timer);
    }
}
