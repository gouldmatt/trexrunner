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
#include "../helpers/InterruptHandler.h"



void FlushCache();
void InitializeButtons(XGpio* input);
int readButtons(XGpio input);

//XTmrCtr InitializeInterrupts();



#endif /* SRC_APPINITIALIZER_H_ */
