/*
 * AppInitializer.cc
 *
 *  Created on: Mar 3, 2020
 *      Author: Elaine Crisostomo
 *      This initializes all of our fun stuff
 *      Like buttons and what not
 */

#include "../helpers/AppInitializer.h"
#include "Shared.h"



/*
 * Read button inputs with debounce
 */
int readButtons(XGpio input){
	int button_data = 0;
	int last = 0;
	int count = 0;
  
	while(count < 150000){
		button_data = XGpio_DiscreteRead(&input, 1); //get button data

		//wait until button data is stable
		if(last == button_data){
			count ++;
		} else {
			count = 0;
		}
		last = button_data;
	}
	return(last);
}
/*
 * Clears communication addresses between video and audio
 */
void clearRegisters(){
	Xil_Out32(VIDEO_ACK_ADDR, IDLE);
	Xil_Out32(AUDIO_ACK_ADDR, IDLE);
}


