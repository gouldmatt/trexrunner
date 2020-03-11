#include "../src/game/gameplay.h"
#include "../src/game/sprite.h"
#include "../src/helpers/AppInitializer.h"

#include <xgpio.h>

#include "xgpiops.h"

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

    	displaySprite(0,0,PT_WIDTH, PT_HEIGHT, PT_ADDR_0);

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
        score = gameplay();

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
