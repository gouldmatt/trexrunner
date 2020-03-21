/*
 * Shared.h
 *
 *  Created on: Mar 20, 2020
 *      Author: elain
 */

#ifndef SRC_HELPERS_SHARED_H_
#define SRC_HELPERS_SHARED_H_


//gameplay constants
const int END_SCORE = 100000;
const int NIGHT_INTERVAL = 100;
const int SPEED_INTERVAL = 100;
const int SCORE_INC_INTERVAL = 3;

const int BASE_HEIGHT = 512;
const int JUMP_INTERVAL = 50;
const int IDLE_COUNT = 3;

const int CACTI_INTERVAL = 50;
const int PT_INTERVAL = 70;


//addresses
const int BLANK_SCR_ADDR = 0x18D2008;

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

const int CACTUS_ADDR = 0x020C7B0C;

const int DINO_IDLE_ADDR = 0x020D110C;
const int DINO_RUN_1_ADDR = 0x020DA70C;
const int DINO_RUN_2_ADDR = 0x020E3D0C;

const int GAME_OVER_ADDR = 0x020ED30C;
const int GROUND_ADDR = 0x020F6F0C;
const int HIGH_SCORE_ADDR = 0x0213890C;
const int RESTART_ADDR = 0x0213A30C;

//const int PT_ADDR_0 = 0x020CED0C;

//widths
const int RESTART_WIDTH = 96;
const int GAME_OVER_WIDTH = 384;
const int GROUND_WIDTH = 2400;
const int HIGH_SCORE_WIDTH = 64;
const int DINO_WIDTH = 96;
const int CACTUS_WIDTH = 64;
const int PT_WIDTH = 96;
const int SCREEN_WIDTH = 1280;
const int NUM_WIDTH = 32;

//heights
const int RESTART_HEIGHT = 67;
const int GAME_OVER_HEIGHT = 26;
const int GROUND_HEIGHT = 28;
const int HIGH_SCORE_HEIGHT = 26;
const int DINO_HEIGHT = 100;
const int CACTUS_HEIGHT  = 104;
const int PT_HEIGHT = 76;
const int SCREEN_HEIGHT = 1024;
const int NUM_HEIGHT = 22;




#endif /* SRC_HELPERS_SHARED_H_ */
