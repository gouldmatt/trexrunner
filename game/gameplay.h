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

//gameplay constants
const int END_SCORE = 100000;
const int NIGHT_INTERVAL = 100;
const int SPEED_INTERVAL = 200;
const int CACTI_INTERVAL = 400;
const int PT_INTERVAL = 70;


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

const int DINO_ADDR = 0x020C130C;
const int CACTUS_ADDR = 0x020C7B0C;



#endif /* SRC_GAMEPLAY_H_ */
