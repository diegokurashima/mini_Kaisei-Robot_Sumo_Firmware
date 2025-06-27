/**
 * @file routines.h
 *
 * @brief Robot general routines related
 */

#ifndef __ROUTINES_H__
#define __ROUTINES_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/*****************************************
 * HIGH LEVEL MODULES
 *****************************************/

/*****************
 * STEP ROUTINES
 *****************/

/**
 * @brief Set the initial conditions for the STEP routine
 */
void routine_step_reset();

/**
 * @brief Set the STEP routine to run
 */
void routine_step_run();

#endif // __ROUTINES_H__
