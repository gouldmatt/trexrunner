#include "../src/game/gameplay.h"
#include "../src/game/sprite.h"
#include "../src/helpers/AppInitializer.h"

#include <xgpio.h>
#include <algorithm>
#include "xgpiops.h"


int main(){


	XGpio input;
	XGpio_Initialize(&input, XPAR_AXI_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection(&input, 1, 0xF);
	int buttonData = 0;
    int score = 0;
    bool showStart = true;

    std::vector<int> highScores(5,0);

    while(1){
    	// white screen
    	displaySprite(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,BLANK_SCR_ADDR);

      	displaySprite(0,512,GROUND_WIDTH,GROUND_HEIGHT,GROUND_ADDR);

      	displaySprite(100,512-DINO_HEIGHT+15,DINO_WIDTH,DINO_HEIGHT,DINO_IDLE_ADDR);

    	switchBuffer();

    	displaySprite(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,BLANK_SCR_ADDR);

     	displaySprite(0,512,GROUND_WIDTH,GROUND_HEIGHT,GROUND_ADDR);

     	displaySprite(100,512-DINO_HEIGHT+15,DINO_WIDTH,DINO_HEIGHT,DINO_IDLE_ADDR);


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
    	score = gameplay(highScores[0]);
        highScores.push_back(score);
        std::sort(highScores.begin(), highScores.end());
        std::reverse(highScores.begin(), highScores.end());
        highScores.pop_back();

    	displaySprite(0,0,SCREEN_WIDTH,100,BLANK_SCR_ADDR);
     	displaySprite(890,0,HIGH_SCORE_WIDTH,HIGH_SCORE_HEIGHT,HIGH_SCORE_ADDR);
    	displayScore(950,0,highScores[0]);
        displayScore(1100,0,score);

        for(int i = 0; i < 5; i++){
        	displayScore(575,240+50*i,highScores[i]);
        }

    	displaySprite(592,500,RESTART_WIDTH,RESTART_HEIGHT,RESTART_ADDR);

        displaySprite(448,180,GAME_OVER_WIDTH,GAME_OVER_HEIGHT,GAME_OVER_ADDR);
        switchBuffer();

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
