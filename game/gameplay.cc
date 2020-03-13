/*
 * gameplay.cc
 *
 *  Created on: Mar 7, 2020
 *      Author: ecrisost
 */

#include "gameplay.h"
#include "sprite.h"


int LFSR(){
	return rand() % 100;
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

void switchBuffer(){

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

void displayScore(int x, int y, int score){
	int scoreX = x;
	int scoreY = y;
	int offset = 0;
	int digit = 0;

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

int gameplay(int highScore){
	std::vector<Obstacle> obstacles;

	// increasing amount to update sprites to create movement
	int speedUpdatePixels = 4;

	// distances that the first cacti and pt will be generated
 	int nextCactiDistance = CACTI_INTERVAL+LFSR();
	int nextPterodactylDistance = PT_INTERVAL+LFSR();

	int distance = 0;
	int score = 0;
	bool nightModeActive = false;

	// white screen
   	displaySprite(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,BLANK_SCR_ADDR);

   	Dino dino(DINO_WIDTH,DINO_HEIGHT,DINO_IDLE_ADDR,DINO_RUN_1_ADDR,DINO_RUN_2_ADDR);
   	dino.x = 100;
   	dino.y = 512-DINO_HEIGHT+15;

   	Sprite groundA(GROUND_WIDTH,GROUND_HEIGHT,GROUND_ADDR);
   	groundA.x = 0;
   	groundA.y = 512;
    groundA.display();

    Sprite groundB(GROUND_WIDTH,GROUND_HEIGHT,GROUND_ADDR);
    groundB.x = GROUND_WIDTH;
    groundB.y = 512;

	while(score != END_SCORE){

		// clear buffer
	   	displaySprite(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,BLANK_SCR_ADDR);

	   	// update ground
	    groundA.x -= speedUpdatePixels;
	    groundA.display();

	    groundB.x -= speedUpdatePixels;
	   	groundB.display();

	    if(groundA.x < -GROUND_WIDTH){
	    	groundA.x = GROUND_WIDTH;
	    } else if (groundB.x < -GROUND_WIDTH){
	    	groundB.x = GROUND_WIDTH;
	    }



		distance++;
		if(distance % SCORE_INC_INTERVAL == 0){
			score++;
		}

	   	displaySprite(890,0,HIGH_SCORE_WIDTH,HIGH_SCORE_HEIGHT,HIGH_SCORE_ADDR);
		displayScore(950,0,highScore);
		displayScore(1100,0,score);

		// update obstacle positions
		for(int i = 0; i < obstacles.size(); i++){
			obstacles[i].x-=speedUpdatePixels;
			obstacles[i].display();
		}

		// animate dino and move dino
		if(distance % SCORE_INC_INTERVAL == 0){
			dino.animateRun();
		}
		dino.display();

		// check if obstacle hit
		if(dino.detectCollision()){
			 printf("Obstacle Hit!\n");
			 dino.idle();
			 break;
		}

		// remove last obstacle if off the screen
		if(obstacles[0].isOffScreen() && obstacles.size() == 1){
			obstacles.erase(obstacles.begin());
		}


		// generate new cacti
		if(distance % nextCactiDistance == 0) {
			nextCactiDistance = distance+CACTI_INTERVAL+LFSR();

			 Obstacle cactus(CACTUS_WIDTH,CACTUS_HEIGHT,CACTUS_ADDR);

			 cactus.x = 1290;
			 cactus.y = 512-CACTUS_HEIGHT+23;
			 cactus.display();

			 // push new cacti on to vector
			 obstacles.push_back(cactus);
		}

		// generate new pterodactyl

		// enable night mode if score is multiple of night
		// mode interval
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


