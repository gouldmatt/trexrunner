#include "xil_printf.h"
#include "xbasic_types.h"
#include "xparameters.h"
#include <stdio.h>
#include "xil_types.h"

#include "xparameters.h"

#include "xil_io.h"
#include "xil_exception.h"
#include "xscugic.h"

#include <stdlib.h>

#include <xgpio.h>

#include "xgpiops.h"
#include "xscugic.h"
#include "xplatform_info.h"
#include <xil_printf.h>

#include <sleep.h>
#include <xil_cache.h>

#include "xbasic_types.h"
#include "sprite.h"
#include <sleep.h>
#include <vector>


// constants
const int endScore = 100000;
const int nightInterval = 100;
const int speedIncreaseInterval = 200;
const int cactiInterval = 400;
const int pterodactylInterval = 70;
const int zeroAddr = 0x020BB00C;
const int oneAddr = 0x020BBB0C;
const int twoAddr = 0x020BC60C;
const int threeAddr = 0x020BD10C;
const int fourAddr = 0x020BDC0C;
const int fiveAddr = 0x020BE70C;
const int sixAddr = 0x020BF20C;
const int sevenAddr = 0x020BFD0C;
const int eightAddr = 0x020C080C;
const int nineAddr = 0x020C130C;

const int dinoAddr = 0x020C130C;
const int cactusAddr = 0x020C7B0C;


volatile Xuint32 *slaveaddr_p = (Xuint32 *) XPAR_GPU_0_S00_AXI_BASEADDR;

// function declarations
int gamePlay();

int lfsr();

int readButtons(XGpio input);

void displaySprite(int x, int y, int width, int height, int addr);

void displayScore(int score);

int main(){


	XGpio input;
	XGpio_Initialize(&input, XPAR_AXI_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(&input, 1, 0xF);
	int buttonData = 0;
    int score = 0;
    bool showStart = true;

    while(1){


    	// white screen
    	displaySprite(0,0,1280,1024,0x018D2008);

    	//displaySprite(100,100,64,104,cactusAddr);

    	if(showStart){
    		// display start screen
			printf("Display start screen: press button to start\n");

			// check for button press then set screen to gameplay
			buttonData = 0b00000;
			while(buttonData == 0b00000){
				buttonData = readButtons(input);
			}
			showStart = false;
    	}

        // main gameplay loop
        score = gamePlay();

        // display high scores
        printf("Display high scores screens: press button to play again\n");

        // wait for button press to play again
        buttonData = 0b00000;
        while(buttonData == 0b00000){
               	buttonData = readButtons(input);
        }

    }
    return 0;
}


int gamePlay(){

	Dino dino;

	std::vector<Obstacle> obstacles;

	int movementDelay = 100000;
    int obstacleMovement = 5;
    int nextCactiScore = cactiInterval+lfsr();
    int nextPterodactylScore = pterodactylInterval+lfsr();
    int score = 0;
    bool nightModeActive = false;

    // white screen
	displaySprite(0,0,1280,1024,0x018D2008);


    for(score = 0; score < endScore; score++){
		// clear buffer

    	// update score
    	displaySprite(1120,20,190,22,0x018D2008);
    	displayScore(score);

		// update obstacle positions
    	for(int i = 0; i < obstacles.size(); i++){
    		obstacles[i].x--;
    		obstacles[i].display();
    	}

        // animate dino and move dino


		// check if obstacle hit
		if(dino.detectCollision()){
			 printf("Obstacle Hit!\n");
			return(score);
		}

		// remove last obstacle if off the screen
		if(obstacles[0].isOffScreen() && obstacles.size() == 1){
			obstacles.erase(obstacles.begin());
		}


		// generate new cacti
		if(score == nextCactiScore) {
			 nextCactiScore = score+cactiInterval+lfsr();

			 Obstacle cactus(64,104,cactusAddr);
			 xil_printf("Address: %d\n\r", cactus.addr);
			 xil_printf("Width: %d\n\r", cactus.width);
			 xil_printf("Height: %d\n\r", cactus.height);

			 cactus.x = 1290;
			 cactus.y = 512;
			 cactus.display();

			 // push new cacti on to vector
			 obstacles.push_back(cactus);
		}

		// generate new pterodactyl

		// enable night mode if score is multiple of night
		// mode interval
		if(score % nightInterval == 0 && score != 0) {
			// set all sprites to night mode
			if(nightModeActive){
				printf("finish night mode\n");
				nightModeActive = false;
			} else {
				nightModeActive = true;
				printf("start night mode\n");
			}
		}

		// move obstacles at increasing amount if score is multiple of
		// speed interval
		if(score % speedIncreaseInterval == 0 && score != 0) {
			// increase obstacleMovement
			printf("increase obstacle speed\n");
			movementDelay-=10;
		}

		for(int delay = 0; delay < movementDelay; delay++){

		}

    }

    return(score);
}

int lfsr(){
    return(rand() % 300);
}

int readButtons(XGpio input){
	int button_data = 0;
	int last = 0;
	int count = 0;

	while(count < 150000){
		button_data = XGpio_DiscreteRead(&input, 1); //get button data
		if(last == button_data){
			count ++;
		} else {
			count = 0;
		}
		last = button_data;
	}
	return(last);
}

void displaySprite(int x, int y, int width, int height, int addr){
	// sprite addr
	*(slaveaddr_p+3) = addr;

	// x
	*(slaveaddr_p+4) = x;


	// y
	*(slaveaddr_p+5) = y;


	// height
	*(slaveaddr_p+6) = height;


	// width
	*(slaveaddr_p+7) = width;


	*(slaveaddr_p+0) = 0x00000001;
	*(slaveaddr_p+0) = 0x00000000;

	int done =  *(slaveaddr_p+1);
		while(done != 1){
		done =  *(slaveaddr_p+1);
	}

	*(slaveaddr_p+0) = 0x00000000;
}

void displayScore(int score){
	int scoreX = 1120;
	int scoreY = 20;
	int offset = 0;
	int digit = 0;

	// loop through and extract digits starting with most significant
	for(int i = 4; i >= 0; i--){
		// remainder gives most significant digit and division reduces for next iteration
		digit = score % 10;
		score = score / 10;

		// increase the x pixel offset for next digit
		offset = 18*i + 6;

		if(digit == 0){
			displaySprite(scoreX+offset,scoreY,32,22,zeroAddr);
		} else if(digit == 1){
			displaySprite(scoreX+offset,scoreY,32,22,oneAddr);
		} else if(digit == 2){
			displaySprite(scoreX+offset,scoreY,32,22,twoAddr);
		} else if(digit == 3){
			displaySprite(scoreX+offset,scoreY,32,22,threeAddr);
		} else if(digit == 4){
			displaySprite(scoreX+offset,scoreY,32,22,fourAddr);
		} else if(digit == 5){
			displaySprite(scoreX+offset,scoreY,32,22,fiveAddr);
		} else if(digit == 6){
			displaySprite(scoreX+offset,scoreY,32,22,sixAddr);
		} else if(digit == 7){
			displaySprite(scoreX+offset,scoreY,32,22,sevenAddr);
		} else if(digit == 8){
		   displaySprite(scoreX+offset,scoreY,32,22,eightAddr);
		} else { // 9
		   displaySprite(scoreX+offset,scoreY,32,22,nineAddr);
		}

	}
}


