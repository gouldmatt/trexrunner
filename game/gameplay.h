/*
 * gameplay.h
 *
 *  Created on: Mar 7, 2020
 *      Author: ecrisost
 */

#ifndef SRC_GAMEPLAY_H_
#define SRC_GAMEPLAY_H_
#include "xparameters.h"
#include "xbasic_types.h"


int LFSR(); //random number generator
int gameplay(); //main gameplay
void displayScore(); //display score
void displaySprite(int x, int y, int width, int height, int addr);

//pointer to sprite address
static volatile Xuint32 *slaveaddr_p = (Xuint32 *) XPAR_GPU_0_S00_AXI_BASEADDR;

/*GAME CONSTANTS
 * The constants that we use for the game
 * */
//gameplay constants
const int END_SCORE = 5000;
const int NIGHT_INTERVAL = 100;
const int SPEED_INTERVAL = 200;
const int CACTI_INTERVAL = 400;
const int PT_INTERVAL = 70;

const int BASE_HEIGHT = 512;


//addresses
const int ZERO_ADDR = 0x020BB00C;
const int ONE_ADDR = 0x020BBB0C;
const int TWO_ADDR = 0x020BC60C;
const int THREE_ADDR = 0x020BD10C;
const int FOUR_ADDR = 0x020BDC0C;
const int FIVE_ADDR = 0x020BE70C;
const int SIX_ADDR = 0x020BF20C;
const int SEVEN_ADDR = 0x020BFD0C;
const int EIGHT_ADDR = 0x020C080C;
const int NINE_ADDR = 0x020C130C;

const int DINO_ADDR = 0x020D830C;
const int CACTUS_ADDR = 0x020C7B0C;
const int PT_ADDR_0 = 0x020CED0C;

//widths
const int DINO_WIDTH = 64;
const int CACTUS_WIDTH = 32;
const int PT_WIDTH = 96;

//heights
const int DINO_HEIGHT = 47;
const int CACTUS_HEIGHT  = 51;
const int PT_HEIGHT = 76;





#endif /* SRC_GAMEPLAY_H_ */
