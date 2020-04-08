/*
 * audio.c
 *	Created by: Elaine Crisostomo
 *	Sourced from: Zynqbook, Chapter 4 - Adventures with Ip
 *	Book: http://www.zynqbook.com/
 *	Source repository: https://github.com/alexvonduar/Zynq-Book-Tutorial-Source
 *
 *	Audio class to create sound effects for the game
 */
#include "audio.h"


Audio::Audio(){
	startLeft = 0;
	startRight = 0;
	max = 0;
}

/*
 * RecordAudio()
 * records audio from line in by sample and loads these samples into memory
 */

void Audio::RecordAudio(){

		//get audio samples from register
		in_left = Xil_In32(I2S_DATA_RX_L_REG);
		in_right = Xil_In32(I2S_DATA_RX_R_REG);

		//loads into memory
		Xil_Out32(startLeft, in_left);
		Xil_Out32(startRight, in_right);

		//increment memory position
		startLeft += 0x04;
		startRight += 0x04;

		//plays audio sample, this is purely for testing and see if the correct audio is being recorded
		Xil_Out32(I2S_DATA_TX_L_REG, in_left);
		Xil_Out32(I2S_DATA_TX_R_REG, in_right);

}

/*
 * PlayAudio()
 * plays sound from the samples loaded into memory
 */

void Audio::PlayAudio(){
	while(startLeft < max){
		//load samples from memory
		in_left = Xil_In32(startLeft);
		in_right = Xil_In32(startRight);

		//increment sample position
		startLeft += 0x04;
		startRight += 0x04;

		//load to left and right register in codec
		Xil_Out32(I2S_DATA_TX_L_REG, in_left);
		Xil_Out32(I2S_DATA_TX_R_REG, in_right);

	}

}

