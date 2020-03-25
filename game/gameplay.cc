/*
 * gameplay.cc
 *
 *  Created on: Mar 7, 2020
 *      Author: ecrisost
 */

#include "gameplay.h"
#include "sprite.h"
#include "../helpers/AppInitializer.h"


GamePlay::GamePlay(){
	bJumpState = false;
	bStartGame = false;
	bDuckState = false;
    bGameOver = false;;
}

int GamePlay::LFSR(){
	return rand();
}

void GamePlay::displaySprite(int x, int y, int width, int height, int addr){
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

void GamePlay::switchBuffer(){

	// switch buffer
	*(slaveaddr_p+8) = 0x00000001;

	//*(slaveaddr_p+8) = 0x00000000;

	// switch buffer ack
	int done =  *(slaveaddr_p+9);
			while(done != 1){
			done =  *(slaveaddr_p+9);
	}

	*(slaveaddr_p+8) = 0x00000000;
}

void GamePlay::displayScore(int x, int y, int score, bool nightMode){
	int scoreX = x;
	int scoreY = y;
	int offset = 0;
	int digit = 0;

	if(nightMode){
		// loop through and extract digits starting with most significant
		for(int i = 4; i >= 0; i--){
			// remainder gives most significant digit and division reduces for next iteration
			digit = score % 10;
			score = score / 10;

			// increase the x pixel offset for next digit
			offset = 18*i + 12;

			if(digit == 0){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,ZERO_NIGHT_ADDR);
			} else if(digit == 1){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,ONE_NIGHT_ADDR);
			} else if(digit == 2){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,TWO_NIGHT_ADDR);
			} else if(digit == 3){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,THREE_NIGHT_ADDR);
			} else if(digit == 4){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,FOUR_NIGHT_ADDR);
			} else if(digit == 5){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,FIVE_NIGHT_ADDR);
			} else if(digit == 6){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,SIX_NIGHT_ADDR);
			} else if(digit == 7){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,SEVEN_NIGHT_ADDR);
			} else if(digit == 8){
			   displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,EIGHT_NIGHT_ADDR);
			} else { // 9
			   displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,NINE_NIGHT_ADDR);
			}

		}
	} else {
		// loop through and extract digits starting with most significant
		for(int i = 4; i >= 0; i--){
			// remainder gives most significant digit and division reduces for next iteration
			digit = score % 10;
			score = score / 10;

			// increase the x pixel offset for next digit
			offset = 18*i + 12;

			if(digit == 0){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,ZERO_ADDR);
			} else if(digit == 1){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,ONE_ADDR);
			} else if(digit == 2){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,TWO_ADDR);
			} else if(digit == 3){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,THREE_ADDR);
			} else if(digit == 4){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,FOUR_ADDR);
			} else if(digit == 5){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,FIVE_ADDR);
			} else if(digit == 6){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,SIX_ADDR);
			} else if(digit == 7){
				displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,SEVEN_ADDR);
			} else if(digit == 8){
			   displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,EIGHT_ADDR);
			} else { // 9
			   displaySprite(scoreX+offset,scoreY,NUM_WIDTH,NUM_HEIGHT,NINE_ADDR);
			}

		}
	}
}

void GamePlay::GameplayInit(){
  		// white screen
    	displaySprite(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,BLANK_ADDR);

      	displaySprite(0,512,GROUND_WIDTH,GROUND_HEIGHT,GROUND_ADDR);

      	displaySprite(100,512-DINO_IDLE_HEIGHT+15,DINO_IDLE_WIDTH,DINO_IDLE_HEIGHT,DINO_IDLE_ADDR);

    	switchBuffer();

    	displaySprite(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,BLANK_ADDR);

     	displaySprite(0,512,GROUND_WIDTH,GROUND_HEIGHT,GROUND_ADDR);

     	displaySprite(100,512-DINO_IDLE_HEIGHT+15,DINO_IDLE_WIDTH,DINO_IDLE_HEIGHT,DINO_IDLE_ADDR);

}

int GamePlay::gameplay(int highScore, XGpio* input_){
	std::vector<Obstacle> background;
	std::vector<Obstacle> obstacles;

	// increasing amount to update sprites to create movement
	int speedUpdatePixels = 4;

	// distances that the first cacti and pt will be generated
 	int nextCactiDistance = CACTI_INTERVAL+(LFSR() % 100);
	int nextPterodactylDistance = PT_INTERVAL+(LFSR() % 100);
	int nextBackgroundDistance = BACK_GROUND_INTERVAL+(LFSR() % 100);

	int distance = 0;
	int score = 0;
	bool nightModeActive = false;
	bool bJumpDone = false;
	bool bJumpIdle = false;
	int jump_height = (512-DINO_IDLE_HEIGHT+15) - 100;
	int DINO_BASE_HEIGHT = 512-DINO_IDLE_HEIGHT+15;
	int jump_count = 0;

	Sprite clearScreen(SCREEN_WIDTH,SCREEN_HEIGHT,BLANK_ADDR,BLANK_NIGHT_ADDR);
	clearScreen.x = 0;
	clearScreen.y = 0;

	clearScreen.display();

   	Dino dino;
   	dino.x = 100;
   	dino.y = 512-DINO_IDLE_HEIGHT+15;

   	Sprite hiScore(HIGH_SCORE_WIDTH,HIGH_SCORE_HEIGHT,HIGH_SCORE_ADDR,HIGH_SCORE_NIGHT_ADDR);
   	hiScore.x = 890;
   	hiScore.y = 0;

   	Sprite groundA(GROUND_WIDTH,GROUND_HEIGHT,GROUND_ADDR,GROUND_NIGHT_ADDR);
   	groundA.x = 0;
   	groundA.y = 512;
    groundA.display();

    Sprite groundB(GROUND_WIDTH,GROUND_HEIGHT,GROUND_ADDR,GROUND_NIGHT_ADDR);
    groundB.x = GROUND_WIDTH;
    groundB.y = 512;

    int buttonData = 0;

	XGpio input;
	XGpio_Initialize(&input, XPAR_AXI_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(&input, 1, 0xF);

	while(score != END_SCORE){

		distance++;
		if(distance % SCORE_INC_INTERVAL == 0){
			score++;
		}

		// clear buffer
		clearScreen.isNight = nightModeActive;
	 	clearScreen.display();

		// update current score and high score
	 	hiScore.isNight = nightModeActive;
	   	hiScore.display();
		displayScore(950,0,highScore,nightModeActive);
		displayScore(1100,0,score, nightModeActive);


	   	// update ground
	    groundA.x -= speedUpdatePixels;
	    groundA.display();

	    groundB.x -= speedUpdatePixels;
	   	groundB.display();

	    if(groundA.x-speedUpdatePixels <= -GROUND_WIDTH){
	    	groundA.x = GROUND_WIDTH;
	    } else if (groundB.x-speedUpdatePixels <= -GROUND_WIDTH){
	    	groundB.x = GROUND_WIDTH;
	    }

	    // update background positions
		for(int i = 0; i < background.size(); i++){
			background[i].x-= int(0.75*speedUpdatePixels);
			background[i].isNight = nightModeActive;
			background[i].display();
		}

		// update obstacle positions
		for(int i = 0; i < obstacles.size(); i++){
			xil_printf("distance %d %d \n\r", i, obstacles[i].distanceX--);
			obstacles[i].x-=speedUpdatePixels;
			obstacles[i].isNight = nightModeActive;
			obstacles[i].display();

			int obsX = obstacles[i].x;
			int obsY = obstacles[i].y;
			if(dino.detectCollision(obsX, obsY)){
				bGameOver = true;
				break;
			}

		}

		// animate dino and move dino
		if(distance % SCORE_INC_INTERVAL == 0){
			if(bGameOver == true){
				dino.isDead = true;
				dino.showDead();
				if(dino.isDead == true){
					bGameOver = false;
					dino.isDead = false;
					break;
				}
			}
			else if(bJumpState == true || (dino.isJumping == true)){
				//jump state
				dino.idle();
				dino.updateJump();
				dino.isJumping = true;
				if(bJumpIdle == true){
					dino.isJumping = false;
					bJumpState = false;
					dino.isJumpIdle = true;
				}
				else if(dino.y <= jump_height){
					bJumpIdle = true;
				}


			}
			else if(bDuckState == true){
				//duck_state
				dino.updateDuck();
				buttonData = readButtons(input);
				if(buttonData == BUTTON_NONE){
					bDuckState = false;
				}
			}
			else if((dino.isJumpIdle == true)){
				//idle state at jump
				dino.idle();
				jump_count++;
				if(jump_count == IDLE_COUNT){
					dino.isJumpIdle = false;
					jump_count = 0;
					bJumpIdle = false;
					dino.isFalling = true;
				}
			}
			else if((dino.isFalling == true)){
				dino.falling();
				if(dino.y >= DINO_BASE_HEIGHT){
					dino.isFalling = false;
					dino.y = DINO_BASE_HEIGHT;
				}
			}
			else{
				dino.y = 512-DINO_IDLE_HEIGHT+15;
				dino.animateRun();
			}


		}

		dino.display();

//		// check if obstacle hit
//		if(dino.detectCollision()){
//			 printf("Obstacle Hit!\n");
//			 dino.idle();
//			 break;
//		}

		// remove background elements if off the screen
		if(background[0].isOffScreen() && background.size() >= 1){
			background.erase(background.begin());
		}

		// remove last obstacle if off the screen
		if(obstacles[0].isOffScreen() && obstacles.size() >= 1){
			obstacles.erase(obstacles.begin());
		}

		// generate new background elements
		if(distance % nextBackgroundDistance == 0) {
			nextBackgroundDistance = distance+BACK_GROUND_INTERVAL+(LFSR() % 100);

			 Obstacle cloud(CLOUD_WIDTH,CLOUD_HEIGHT,CLOUD_ADDR,CLOUD_NIGHT_ADDR);

			 cloud.x = 1290;
			 // y somewhere between 100 and 400
			 cloud.y = 100 + (LFSR() % (400 - 100 + 1 ));
			 cloud.display();

			 // push new cacti on to vector
			 background.push_back(cloud);
		}


		// generate new cacti
		if(distance % nextCactiDistance == 0) {
			nextCactiDistance = distance+CACTI_INTERVAL+(LFSR() % 100);

			 Obstacle cactus(LARGE_CACTUS_1_WIDTH,LARGE_CACTUS_1_HEIGHT,LARGE_CACTUS_1_ADDR,LARGE_CACTUS_1_NIGHT_ADDR);

			 cactus.x = 1290;
			 cactus.y = 512-LARGE_CACTUS_1_HEIGHT+23;
			 cactus.distanceX = 1290;
			 cactus.display();

			 // push new cacti on to vector
			 obstacles.push_back(cactus);
		}

		// generate new pterodactyl

		// enable night mode if score is multiple of night mode interval
		if(distance % NIGHT_INTERVAL == 0) {
			// set all sprites to night mode
			if(nightModeActive){
				printf("finish night mode\n");
				nightModeActive = false;
			} else {
				nightModeActive = true;
				printf("start night mode\n");
			}
		}


		if(distance % SPEED_INTERVAL == 0) {
			speedUpdatePixels++;
		}

		switchBuffer();
	}

	return(score);

}




