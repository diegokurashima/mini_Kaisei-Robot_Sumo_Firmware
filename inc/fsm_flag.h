/**
 * @file fsm_flag.h
 *
 * @brief Flag control Finite State Machine related
 */

#ifndef __FSM_FLAG_H__
#define __FSM_FLAG_H__

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

/*****************************************
 * DEFINES
 *****************************************/

typedef enum {
    FLAG_CENTER,
    FLAG_RIGHT,
    FLAG_LEFT
} fsm_flag_state_type;

/*****************************************
 * HIGH LEVEL MODULES
 *****************************************/

/**
 * @brief init flag control state machine
 */
void fsm_flag_init();

/**
 * @brief stop flag control state machine
 */
void fsm_flag_stop();

/**
 * @brief defines action within each state in flag state machine
 */
void fsm_flag_state_running();

/**
 * @brief defines action in state initialization
 */
void fsm_flag_state_init(fsm_flag_state_type next_state);

/**
 * @brief set the flag state machine event transitions handler
 */
void fsm_flag_transition();

/**
 * @brief set the flag state machine to run
 */
void fsm_flag_run();

#endif // __FSM_FLAG_H__
