/*
 * main.c
 *
 * Main source file for audio. Contains main() and LoadSounds () functions.
 */
#include "../src/game/audio.h"
#include "../src/game/game.h"
#include <vector>
#include "audio_helpers/AudioInitializer.h"
#include "audio_helpers/Shared.h"

using namespace std;


XGpio input; //button input, for just loading sounds

Game trexRunner; //instances of game
std::vector<Audio> sounds; //vector to hold all sound effects used in the game

//initialize sounds to use
Audio jump;
Audio positive;
Audio death;
Audio vriska;


int main()
{
	//Clears AUDIO and VIDEO shared registers
	clearRegisters();

	InitializeAudio();

	//intialize start positions for all sound used in the game
	jump.startLeft = JUMP_ADDR_LEFT;
	jump.startRight = JUMP_ADDR_RIGHT;

	positive.startLeft = SCORE_ADDR_LEFT;
	positive.startRight = SCORE_ADDR_RIGHT;

	death.startLeft = DEATH_ADDR_LEFT;
	death.startRight = DEATH_ADDR_RIGHT;

	vriska.startLeft = VRISKA_ADDR_LEFT;
	vriska.startRight = VRISKA_ADDR_RIGHT;

	//load sound into memory
	LoadSound();

	u32 ack_ = Xil_In32(AUDIO_ACK_ADDR);

	//wait for video to be initialized
	while(ack_ != ACK){
		ack_ = Xil_In32(AUDIO_ACK_ADDR);
	}
	Xil_Out32(AUDIO_ACK_ADDR, IDLE); //has been acknowledged

	while(1){
		//start game
		u32 start_ = Xil_In32(AUDIO_ACK_ADDR);
		if(start_ == START){
			Xil_Out32(AUDIO_ACK_ADDR, IDLE);
			trexRunner.gameplay(sounds);
		}
	}

    return 1;
}

/*
 * LoadSound() - records sound from LINE-IN and loads into memory
 * Modified from Zynbook tutorial chapter 4 - Adventures with IP
 */
void LoadSound(){
	u8 inp = 0x00;
	u32 CntrlRegister;
	CntrlRegister = XUartPs_ReadReg(XPAR_PS7_UART_1_BASEADDR, XUARTPS_CR_OFFSET);

	//initialize gpio
	XGpio gpio;
	XGpio_Initialize(&gpio, XPAR_GPIO_0_DEVICE_ID);

	XGpio_SetDataDirection(&gpio, 1, 0xF);

	int button_data = 0;

	xil_printf("Loading Sound... \n\r");
	XUartPs_WriteReg(XPAR_PS7_UART_1_BASEADDR, XUARTPS_CR_OFFSET,
					  ((CntrlRegister & ~XUARTPS_CR_EN_DIS_MASK) |
					   XUARTPS_CR_TX_EN | XUARTPS_CR_RX_EN));

	while(inp != 'q'){
		// Wait for input from UART via the terminal
		inp = XUartPs_ReadReg(XPAR_PS7_UART_1_BASEADDR, XUARTPS_FIFO_OFFSET);
		button_data = XGpio_DiscreteRead(&gpio, 1);
		if(button_data == 0b00001){
			//record jump sound
			//centre button
			jump.RecordAudio();
			jump.max = jump.startLeft;


		}
		else if (button_data == 0b10000){
			//record score sound
			//up
			positive.RecordAudio();
			positive.max = positive.startLeft;


		}
		else if(button_data == 0b00010){
			//record death sound
			death.RecordAudio();
			death.max = death.startLeft;

		}
		else if(button_data == 0b00100){
			//record night sound
			vriska.RecordAudio();
			vriska.max = vriska.startLeft;
		}

	}

	xil_printf("Finish Recording Sound!");
	xil_printf("max jump %X\n\r", jump.max);
	xil_printf("max jump %X\n\r", jump.startRight);

	xil_printf("max death %X\n\r", death.max);
	xil_printf("max death %X\n\r", death.startRight);


	Xil_Out32(VIDEO_ACK_ADDR, ACK); //tells video audio is all recorded and intialized
	jump.startLeft = JUMP_ADDR_LEFT;
	jump.startRight = JUMP_ADDR_RIGHT;

    //put sounds used in sound vector
	sounds.push_back(jump);
	sounds.push_back(death);
	sounds.push_back(positive);
	sounds.push_back(vriska);

}






