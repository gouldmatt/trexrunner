/*
 * gameplay.cc
 *
 *  Created on: Mar 7, 2020
 *      Author: ecrisost
 */

#include "gameplay.h"
#include "sprite.h"


int LFSR(){
	return 0;
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
			displaySprite(scoreX+offset,scoreY,32,22,ZERO_ADDR);
		} else if(digit == 1){
			displaySprite(scoreX+offset,scoreY,32,22,ONE_ADDR);
		} else if(digit == 2){
			displaySprite(scoreX+offset,scoreY,32,22,TWO_ADDR);
		} else if(digit == 3){
			displaySprite(scoreX+offset,scoreY,32,22,THREE_ADDR);
		} else if(digit == 4){
			displaySprite(scoreX+offset,scoreY,32,22,FOUR_ADDR);
		} else if(digit == 5){
			displaySprite(scoreX+offset,scoreY,32,22,FIVE_ADDR);
		} else if(digit == 6){
			displaySprite(scoreX+offset,scoreY,32,22,SIX_ADDR);
		} else if(digit == 7){
			displaySprite(scoreX+offset,scoreY,32,22,SEVEN_ADDR);
		} else if(digit == 8){
		   displaySprite(scoreX+offset,scoreY,32,22,EIGHT_ADDR);
		} else { // 9
		   displaySprite(scoreX+offset,scoreY,32,22,NINE_ADDR);
		}

	}
}

int gameplay(){

	Dino dino;

	std::vector<Obstacle> obstacles;

	int movementDelay = 100000;
	int obstacleMovement = 5;
	int nextCactiScore = CACTI_INTERVAL+LFSR();
	int nextPterodactylScore = PT_INTERVAL+LFSR();
	int score = 0;
	bool nightModeActive = false;

	    // white screen
		displaySprite(0,0,1280,1024,0x018D2008);


	    for(score = 0; score < END_SCORE; score++){
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
				 nextCactiScore = score+CACTI_INTERVAL+LFSR();

				 Obstacle cactus(64,104,CACTUS_ADDR);

				 cactus.x = 1290;
				 cactus.y = 512;
				 cactus.display();

				 // push new cacti on to vector
				 obstacles.push_back(cactus);
			}

			// generate new pterodactyl

			// enable night mode if score is multiple of night
			// mode interval
			if(score % NIGHT_INTERVAL == 0 && score != 0) {
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
			if(score % SPEED_INTERVAL == 0 && score != 0) {
				// increase obstacleMovement
				printf("increase obstacle speed\n");
				movementDelay-=10;
			}
			/*
			for(int delay = 0; delay < movementDelay; delay++){

			}*/

	    }

	    return(score);

}


