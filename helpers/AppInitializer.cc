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



//read the buttons
//int ReadButtons(XGpio* input){
//	int button_data = XGpio_DiscreteRead(input, 1);
//
//	return button_data;
//}

int readButtons(XGpio input){
	int button_data = 0;
	int last = 0;
	int count = 0;

	button_data = XGpio_DiscreteRead(&input, 1); //get button data
//	while(count < 150000){
//		button_data = XGpio_DiscreteRead(&input, 1); //get button data
//		if(last == button_data){
//			count ++;
//		} else {
//			count = 0;
//		}
//		last = button_data;
//	}
	return(button_data);
}



