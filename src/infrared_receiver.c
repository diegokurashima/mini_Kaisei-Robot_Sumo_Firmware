/**
 * @file infrared_receiver.c
 *
 * @brief infrared receiver related
 */

#include "infrared_receiver.h"

/*****************************************
 * GLOBAL VARIABLES
 *****************************************/

// INFRARED_RECEIVER VARIABLES
uint8_t dataArray3bits[3];
uint8_t dataArray2bits[2];
uint8_t arrayIndex, statusIR = 0;
uint8_t rawdata3bits, rawdata2bits = 0;

/* flagDone
 * 0 -> not started.
 * 1 -> 2 bits completed.
 * 2 -> 3 bits completed.
 */
uint8_t flagDone = 0;

/* final outputs for IR receiver
 */
uint8_t ir_value3bits, ir_value2bits = 0;

// FSM_MAIN VARIABLES
extern bool changeNumBits;

/*****************************************
 * LOW LEVEL MODULES
 *****************************************/

// Interrupt function
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_6) {
        if (!changeNumBits) {
            ir_read_edge_2bits();

            if (flagDone == 1) {
                ir_value2bits = rawdata2bits + 1;
            }
        } else {
            ir_read_edge_3bits();

            if (flagDone == 2) {
                ir_value3bits = rawdata3bits + 1;
            }
        }
    }
}

void ir_read_edge_2bits(void) {
    switch (statusIR) {
        case IR_START:

            if ((__HAL_TIM_GET_COUNTER(&htim4) > 290) && (__HAL_TIM_GET_COUNTER(&htim4) < 320)) {
                flagDone = 0;
                arrayIndex = 0;
                statusIR = IR_READ_DATA;
                __HAL_TIM_SET_COUNTER(&htim4, 0);
            }

            break;

        case IR_READ_DATA:

            if ((__HAL_TIM_GET_COUNTER(&htim4) > 170) && (__HAL_TIM_GET_COUNTER(&htim4) < 200)) {
                dataArray2bits[arrayIndex] = 1;
            } else if ((__HAL_TIM_GET_COUNTER(&htim4) > 100) && (__HAL_TIM_GET_COUNTER(&htim4) < 140)) {
                dataArray2bits[arrayIndex] = 0;
            } else {
                __HAL_TIM_SET_COUNTER(&htim4, 0);
                statusIR = IR_START;
                break;
            }

            arrayIndex++;

            if (arrayIndex >= 3) {
                rawdata2bits = 0;

                for (uint8_t i = 0; i < 2; i++) {
                    rawdata2bits |= dataArray2bits[i] << i;
                }

                flagDone = 1;
                statusIR = IR_START;
                __HAL_TIM_SET_COUNTER(&htim4, 0);
                break;
            }

        default:
            break;
    }

    __HAL_TIM_SET_COUNTER(&htim4, 0);
}

void ir_read_edge_3bits(void) {
    switch (statusIR) {
        case IR_START:

            if ((__HAL_TIM_GET_COUNTER(&htim4) > 290) && (__HAL_TIM_GET_COUNTER(&htim4) < 320)) {
                flagDone = 0;
                arrayIndex = 0;
                statusIR = IR_READ_DATA;
                __HAL_TIM_SET_COUNTER(&htim4, 0);
            }

            break;

        case IR_READ_DATA:

            if ((__HAL_TIM_GET_COUNTER(&htim4) > 170) && (__HAL_TIM_GET_COUNTER(&htim4) < 200)) {
                dataArray3bits[arrayIndex] = 1;
            } else if ((__HAL_TIM_GET_COUNTER(&htim4) > 100) && (__HAL_TIM_GET_COUNTER(&htim4) < 140)) {
                dataArray3bits[arrayIndex] = 0;
            } else {
                __HAL_TIM_SET_COUNTER(&htim4, 0);
                statusIR = IR_START;
                break;
            }

            arrayIndex++;

            if (arrayIndex >= 4) {
                rawdata3bits = 0;

                for (uint8_t i = 0; i < 3; i++) {
                    rawdata3bits |= dataArray3bits[i] << i;
                }

                flagDone = 2;
                statusIR = IR_START;
                __HAL_TIM_SET_COUNTER(&htim4, 0);
                break;
            }

        default:
            break;
    }

    __HAL_TIM_SET_COUNTER(&htim4, 0);
}
