/*
 * AppInitializer.h
 *
 *  Created on: Mar 3, 2020
 *      Author: ecrisost
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




void FlushCache();
int readButtons(XGpio input);


#endif /* SRC_APPINITIALIZER_H_ */
