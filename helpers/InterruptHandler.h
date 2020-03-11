/*
 * InterruptHandler.h
 *
 *  Created on: Mar 7, 2020
 *      Author: ecrisost
 */

#ifndef SRC_HELPERS_INTERRUPTHANDLER_H_
#define SRC_HELPERS_INTERRUPTHANDLER_H_

#include "xtmrctr.h"
#include "xscugic.h"

static volatile bool TIMER_INTR_FLG;
static XScuGic InterruptController; /* Instance of the Interrupt Controller */
static XScuGic_Config *GicConfig;/* The configuration parameters of thecontroller */


void Timer_InterruptHandler(XTmrCtr *data, u8 TmrCtrNumber);
int SetUpInterruptSystem(XScuGic *XScuGicInstancePtr);
/*Setup all interrupts of the system*/
int ScuGicInterrupt_Init(u16 DeviceId,XTmrCtr *TimerInstancePtr);



#endif /* SRC_HELPERS_INTERRUPTHANDLER_H_ */
