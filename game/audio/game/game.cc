/*
 * game.cc
 *
 *  Created on: Mar 26, 2020
 *      Author: Elaine Crisostomo
 *      Implementation of gameplay
 */

#include "game.h"

Game::Game(){

}

void Game::gameplay(std::vector<Audio> &sound){

	u32 ack;

	while(1){
		//read game state from state address
		ack = Xil_In32(AUDIO_ACK_ADDR);

		if(ack == JUMP){
			//ack recieves jump state, play associated sound
			sound[0].PlayAudio();

			//reset start values for sound
			sound[0].startLeft = JUMP_ADDR_LEFT;
			sound[0].startRight = JUMP_ADDR_RIGHT;

			 //write to audio state address, turn off sound
			Xil_Out32(AUDIO_ACK_ADDR, IDLE);
		}

		if(ack == DEATH){
			//ack recieves death state, play associated sound
			sound[1].PlayAudio();

			//reset start values for sound
			sound[1].startLeft = DEATH_ADDR_LEFT;
			sound[1].startRight = DEATH_ADDR_RIGHT;

			//write idle to state address, turn off sound
			Xil_Out32(AUDIO_ACK_ADDR, IDLE);

		}

		if(ack == POINT){
			//ack recieves score threshold state, play associated sound
			sound[2].PlayAudio();

			//reset start values for the sound
			sound[2].startLeft = SCORE_ADDR_LEFT;
			sound[2].startRight = SCORE_ADDR_RIGHT;

			//write idle to state address, turn off sound
			Xil_Out32(AUDIO_ACK_ADDR,IDLE);
		}

		if(ack == VRISKA){
			//ack recieves night mode state, play associated sound
			sound[3].PlayAudio();

			//reset start values
			sound[3].startLeft = VRISKA_ADDR_LEFT;
			sound[3].startRight = VRISKA_ADDR_RIGHT;

			//write idle to state address, turn off sound
			Xil_Out32(AUDIO_ACK_ADDR, IDLE);
		}


	}
}

