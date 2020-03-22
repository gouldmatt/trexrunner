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

int GamePlay::gameplay(int highScore){
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
	int moonPhase = 0;
	int nextCacti = 0;
	int nextStar = 0;
	bool nightModeActive = false;
	bool moonDisplayed = false;
	//bool bJumpDone = false;
	bool bJumpIdle = false;
	int jump_height = (512-DINO_IDLE_HEIGHT+15) - 100;
	int DINO_BASE_HEIGHT = 512-DINO_IDLE_HEIGHT+15;
	int jump_count = 0;

	 Obstacle cloud(CLOUD_WIDTH,CLOUD_HEIGHT,CLOUD_ADDR,CLOUD_NIGHT_ADDR);

	// possible cacti obstacle vector
	vector<Obstacle>  allCacti{
		// small cacti
	    Obstacle(SMALL_CACTUS_1_WIDTH,SMALL_CACTUS_1_HEIGHT,SMALL_CACTUS_1_ADDR,SMALL_CACTUS_1_NIGHT_ADDR),
		Obstacle(SMALL_CACTUS_2_WIDTH,SMALL_CACTUS_2_HEIGHT,SMALL_CACTUS_2_ADDR,SMALL_CACTUS_2_NIGHT_ADDR),
		Obstacle(SMALL_CACTUS_3_WIDTH,SMALL_CACTUS_3_HEIGHT,SMALL_CACTUS_3_ADDR,SMALL_CACTUS_3_NIGHT_ADDR),
		Obstacle(SMALL_CACTUS_4_WIDTH,SMALL_CACTUS_4_HEIGHT,SMALL_CACTUS_4_ADDR,SMALL_CACTUS_4_NIGHT_ADDR),
		Obstacle(SMALL_CACTUS_5_WIDTH,SMALL_CACTUS_5_HEIGHT,SMALL_CACTUS_5_ADDR,SMALL_CACTUS_5_NIGHT_ADDR),
		Obstacle(SMALL_CACTUS_6_WIDTH,SMALL_CACTUS_6_HEIGHT,SMALL_CACTUS_6_ADDR,SMALL_CACTUS_6_NIGHT_ADDR),
		// large cacti
		Obstacle(LARGE_CACTUS_1_WIDTH,LARGE_CACTUS_1_HEIGHT,LARGE_CACTUS_1_ADDR,LARGE_CACTUS_1_NIGHT_ADDR),
		Obstacle(LARGE_CACTUS_2_WIDTH,LARGE_CACTUS_2_HEIGHT,LARGE_CACTUS_2_ADDR,LARGE_CACTUS_2_NIGHT_ADDR),
		Obstacle(LARGE_CACTUS_3_WIDTH,LARGE_CACTUS_3_HEIGHT,LARGE_CACTUS_3_ADDR,LARGE_CACTUS_3_NIGHT_ADDR),
		Obstacle(LARGE_CACTUS_4_WIDTH,LARGE_CACTUS_4_HEIGHT,LARGE_CACTUS_4_ADDR,LARGE_CACTUS_4_NIGHT_ADDR),
		// cacti group
		Obstacle(CACTUS_GROUP_WIDTH,CACTUS_GROUP_HEIGHT,CACTUS_GROUP_ADDR,CACTUS_GROUP_NIGHT_ADDR)
	};

	// possible moon background sprite vector
	vector<Sprite>  moonPhases{
		Obstacle(MOON_1_WIDTH,MOON_1_HEIGHT,MOON_1_ADDR,MOON_1_ADDR),
		Obstacle(MOON_2_WIDTH,MOON_2_HEIGHT,MOON_2_ADDR,MOON_2_ADDR),
		Obstacle(MOON_3_WIDTH,MOON_3_HEIGHT,MOON_3_ADDR,MOON_3_ADDR),
		Obstacle(MOON_4_WIDTH,MOON_4_HEIGHT,MOON_4_ADDR,MOON_4_ADDR),
		Obstacle(MOON_5_WIDTH,MOON_5_HEIGHT,MOON_5_ADDR,MOON_5_ADDR),
		Obstacle(MOON_6_WIDTH,MOON_6_HEIGHT,MOON_6_ADDR,MOON_6_ADDR),
		Obstacle(MOON_7_WIDTH,MOON_7_HEIGHT,MOON_7_ADDR,MOON_7_ADDR)
	};

	// possible star background sprite vector
	vector<Obstacle>  allStars{
		Obstacle(STAR_1_WIDTH,STAR_1_HEIGHT,STAR_1_ADDR,STAR_1_ADDR),
		Obstacle(STAR_2_WIDTH,STAR_2_HEIGHT,STAR_2_ADDR,STAR_2_ADDR),
		Obstacle(STAR_3_WIDTH,STAR_3_HEIGHT,STAR_3_ADDR,STAR_3_ADDR),
	};



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
		for(int i = 0; i < int(background.size()); i++){

			background[i].x-= int(0.75*speedUpdatePixels);

			// isNight does not need to be updated for background
			background[i].isNight = nightModeActive;
			background[i].display();
		}

		// update obstacle positions
		for(int i = 0; i < int(obstacles.size()); i++){
			obstacles[i].x-=speedUpdatePixels;
			obstacles[i].isNight = nightModeActive;
			if(distance % PT_ANIMATION_INTERVAL == 0){
				obstacles[i].animate();
			}
			obstacles[i].display();
		}

		// animate dino and move dino

			if(bJumpState == true || (dino.isJumping == true)){
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
				if(distance % SCORE_INC_INTERVAL == 0){
					dino.animateRun();
				}
			}




		dino.display();

		// check if obstacle hit
		if(dino.detectCollision()){
			 printf("Obstacle Hit!\n");
			 dino.idle();
			 break;
		}

		// remove background elements if off the screen
		if(background[0].isOffScreen() && background.size() >= 1){
			background.erase(background.begin());
		}

		// remove last obstacle if off the screen
		if(obstacles[0].isOffScreen() && obstacles.size() >= 1){
			obstacles.erase(obstacles.begin());
		}

		// generate moon
		if(nightModeActive && !moonDisplayed){
			// generate the moon
			moonPhases[moonPhase].x = 1100;
			moonPhases[moonPhase].y = 200;
			moonPhases[moonPhase].display();
			if(moonPhase == 6){
				moonPhase = 0;
			}
			moonPhase++;
			moonDisplayed = true;
		} else if(nightModeActive){
			moonPhases[moonPhase-1].display();
		} else {
			moonDisplayed = false;
		}

		// generate new background elements
		if(distance % nextBackgroundDistance == 0) {
			nextBackgroundDistance = distance+BACK_GROUND_INTERVAL+(LFSR() % 70);

			if(nightModeActive){
				// choose a star from group of 3
			    nextStar = (LFSR() % 3);

				 allStars[nextStar].x = 1290;
				 // y somewhere between 100 and 400
				 allStars[nextStar].y = 100 + (LFSR() % (400 - 100 + 1 ));
				 allStars[nextStar].display();


				background.push_back(allStars[nextStar]);

			} else {
				 cloud.x = 1290;
				 // y somewhere between 100 and 400
				 cloud.y = 100 + (LFSR() % (400 - 100 + 1 ));
				 cloud.display();

				 background.push_back(cloud);
			}
		}


		// generate new cacti
		if(distance % nextCactiDistance == 0) {
			nextCactiDistance = distance+CACTI_INTERVAL+(LFSR() % 20);

			// choose a cacti from group of 11
			nextCacti = (LFSR() % 11);

			if(nextCacti <= 6){
				allCacti[nextCacti].x = 1290;
				allCacti[nextCacti].y = 512-SMALL_CACTUS_1_HEIGHT+23;
				allCacti[nextCacti].display();
			} else {
				allCacti[nextCacti].x = 1290;
				allCacti[nextCacti].y = 512-LARGE_CACTUS_1_HEIGHT+23;
				allCacti[nextCacti].display();
			}
			 // push new cacti on to vector
			 obstacles.push_back(allCacti[nextCacti]);
		}

		// generate new pterodactyl
		if(distance % nextPterodactylDistance == 0) {
			nextPterodactylDistance = distance+PT_INTERVAL+(LFSR() % 20);

			 Obstacle pt(PTERODACTYL_1_WIDTH,PTERODACTYL_1_HEIGHT,PTERODACTYL_1_ADDR,PTERODACTYL_2_ADDR,PTERODACTYL_1_NIGHT_ADDR,PTERODACTYL_2_NIGHT_ADDR);

			 pt.x = 1290;
			 pt.y = 200 + (LFSR() % (400 - 200 + 1 ));

			 pt.display();

			 // push new pt on to vector
			 obstacles.push_back(pt);
		}

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




