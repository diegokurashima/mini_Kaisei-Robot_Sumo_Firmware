/**
 * @file fsm_flag.c
 *
 * @brief Flag control Finite State Machine related
 */

#include "fsm_flag.h"
#include "fsm_main.h"
#include "fsm_control.h"

#include "flag.h"

/*****************************************
 * GLOBAL VARIABLES
 *****************************************/

// FSM_FLAG VARIABLES
fsm_flag_state_type fsm_flag_state_current;
bool fsm_flag_transition_enabled; // flag to enable flag transition

// FSM_MAIN VARIABLES
extern fsm_main_state_type fsm_main_state_current;
extern uint8_t strategy_1, strategy_2;

// FSM_CONTROL VARIABLES
extern fsm_control_state_type fsm_control_state_current;

/*****************************************
 * HIGH LEVEL MODULES
 *****************************************/

void fsm_flag_init() {
    fsm_flag_state_init(FLAG_CENTER);
}

void fsm_flag_stop() {
    fsm_flag_state_current = -1;
}

void fsm_flag_state_running() {
    switch (fsm_flag_state_current) {
        case FLAG_CENTER:
            flag_set_center();
            break;

        case FLAG_RIGHT:
            flag_set_right();
            break;

        case FLAG_LEFT:
            flag_set_left();
            break;

        default:
            break;
    }
}

void fsm_flag_state_init(fsm_flag_state_type next_state) {
    switch (next_state) {
        case FLAG_CENTER:
            flag_set_center();
            break;

        case FLAG_RIGHT:
            flag_set_right();
            break;

        case FLAG_LEFT:
            flag_set_left();
            break;

        default:
            break;
    }
}

void fsm_flag_transition() {
    switch (fsm_flag_state_current) {
        case FLAG_CENTER:

            // Transition must be ENABLED
            if (!fsm_flag_transition_enabled) {
                break;
            }

            // Check if START
            if (fsm_main_state_current == MAIN_RUNNING) {
                if ((strategy_2 % 2) == 0) {
                    // strategy_2 is even -> flag to RIGHT
                    fsm_flag_state_init(FLAG_RIGHT);
                } else if ((strategy_2 % 2) == 1) {
                    // strategy_2 is odd -> flag to LEFT
                    fsm_flag_state_init(FLAG_LEFT);
                }

                fsm_flag_transition_enabled = 0; // set transition flag as false
            }

            break;

        case FLAG_RIGHT:

            // Transition must be ENABLED
            if (!fsm_flag_transition_enabled) {
                break;
            }

            break;

        case FLAG_LEFT:

            // Transition must be ENABLED
            if (!fsm_flag_transition_enabled) {
                break;
            }

            break;

        default:
            break;
    }
}

void fsm_flag_run() {
    fsm_flag_state_running();
    fsm_flag_transition();
}
