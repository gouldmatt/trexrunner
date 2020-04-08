/*
 * AppInitializer.h
 *
 *  Created on: Mar 3, 2020
 *      Author: Elaine Crisostomo
 *		Initializes any functions used throughout the game
 */

#ifndef SRC_APPINITIALIZER_H_
#define SRC_APPINITIALIZER_H_

#include <xil_cache.h>
#include "xparameters.h"
#include <xgpio.h>


//push button constants
const int BUTTON_NONE =  0b00000;
const int BUTTON_CENTRE =  0b00001;
const int BUTTON_UP  = 0b10000;
const int BUTTON_DOWN = 0b00010;



int readButtons(XGpio input); //reads button values
void clearRegisters(); //clears communication registers

#endif /* SRC_APPINITIALIZER_H_ */
