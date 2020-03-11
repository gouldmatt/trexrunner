/*
 * AppInitializer.cc
 *
 *  Created on: Mar 3, 2020
 *      Author: Elaine Crisostomo
 *      This initializes all of our fun stuff
 *      Like buttons and what not
 */

#include "../helpers/AppInitializer.h"

//Flushes the cache
void FlushCache(){
	Xil_DCacheDisable();

	Xil_DCacheInvalidate();
	Xil_DCacheFlush();
	Xil_ICacheInvalidate();

}

//Initializes the buttons
//Taken from: https://reference.digilentinc.com/learn/programmable-logic/tutorials/zedboard-getting-started-with-zynq/start
void InitializeButtons(XGpio* input){
	XGpio_Initialize(input, XPAR_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(input, XPAR_GPIO_0_DEVICE_ID, 0xF); //set first channel tristate buffer to input

}

//read the buttons
int ReadButtons(XGpio* input){
	int button_data = XGpio_DiscreteRead(input, 1);

	return button_data;
}

