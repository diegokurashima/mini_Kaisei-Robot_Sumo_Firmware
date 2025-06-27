/**
 * @file infrared_receiver.h
 *
 * @brief infrared_receiver related
 */

#ifndef __IR_RCV_H__
#define __IR_RCV_H__

#include "tim.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/*****************************************
 * DEFINES
 *****************************************/
#define IR_START (0)
#define IR_READ_DATA (1)

/*****************************************
 * Public Function Prototypes
 *****************************************/

/**
 * @brief return value of 3 bits from ir receiver. Works between 1-8 on IR remote control.
 */
void ir_read_edge_3bits(void);

/**
 * @brief return value of 2 bits from ir receiver. Works between 1-4 on IR remote control.
 */
void ir_read_edge_2bits(void);

#endif // __IR_RCV_H__
