/*
 * Shared.h
 *
 *  Created on: Mar 20, 2020
 *      Author: elain
 */

#ifndef SRC_HELPERS_SHARED_H_
#define SRC_HELPERS_SHARED_H_

/*																											*
 * 								MACROS TO INTERACT WITH PS0 - VIDEO CORE									*
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	*/

/* AUDIO/VIDEO STATES */
#define IDLE  0x0 //ack has been recieved
#define ACK  0x01 //ack sent

/* GAMEPLAY MACROS */

#define START 0x03 //start game
#define JUMP  0x05 //jump
#define  POINT   0x07 //scores a point
#define DEATH  0x09 //death state
#define VRISKA 0x0B //night mode

/* ADDRESSES IN MEMORY TO RECIEVE CORE STATE ACKNOLEDGEMENTS*/
#define VIDEO_ACK_ADDR  0x025A328C
#define AUDIO_ACK_ADDR  0x025A0290


//gameplay constants
const int END_SCORE = 100000;
const int NIGHT_INTERVAL = 500;
const int SPEED_INTERVAL = 100;
const int SCORE_INC_INTERVAL = 3;

const int BASE_HEIGHT = 512;

const int JUMP_INTERVAL = 50;
const int IDLE_COUNT = 2;

const int BR_INTERVAL = 600; // interval at which one cactus is replaced with brachiosaurus sprite
const int CACTI_INTERVAL = 70;
const int PT_INTERVAL = 350;
const int PT_ANIMATION_INTERVAL = 6;
const int BACK_GROUND_INTERVAL = 42;


//addresses
const int BLANK_ADDR = 0x018D2008;
const int ZERO_ADDR = 0x01DD2008;
const int ONE_ADDR = 0x01DD2B08;
const int TWO_ADDR = 0x01DD3608;
const int THREE_ADDR = 0x01DD4108;
const int FOUR_ADDR = 0x01DD4C08;
const int FIVE_ADDR = 0x01DD5708;
const int SIX_ADDR = 0x01DD6208;
const int SEVEN_ADDR = 0x01DD6D08;
const int EIGHT_ADDR = 0x01DD7808;
const int NINE_ADDR = 0x01DD8308;
const int DINO_IDLE_ADDR = 0x01DD8E08;
const int DINO_HIT_ADDR = 0x01DE2408;
const int DINO_RUN_1_ADDR = 0x01DEBA08;
const int DINO_RUN_2_ADDR = 0x01DF5008;
const int DINO_DUCK_1_ADDR = 0x01DFE608;
const int DINO_DUCK_2_ADDR = 0x01E05E08;
const int SMALL_CACTUS_1_ADDR = 0x01E0D608;
const int SMALL_CACTUS_2_ADDR = 0x01E11C08;
const int SMALL_CACTUS_3_ADDR = 0x01E16208;
const int SMALL_CACTUS_4_ADDR = 0x01E1A808;
const int SMALL_CACTUS_5_ADDR = 0x01E1EE08;
const int SMALL_CACTUS_6_ADDR = 0x01E23408;
const int LARGE_CACTUS_1_ADDR = 0x01E27A08;
const int LARGE_CACTUS_2_ADDR = 0x01E2DE08;
const int LARGE_CACTUS_3_ADDR = 0x01E34208;
const int LARGE_CACTUS_4_ADDR = 0x01E3A608;
const int CACTUS_GROUP_ADDR = 0x01E40A08;
const int PTERODACTYL_1_ADDR = 0x01E4D208;
const int PTERODACTYL_2_ADDR = 0x01E54288;
const int CLOUD_ADDR = 0x01E5B308;
const int RESTART_ADDR = 0x01E5DD08;
const int GAME_OVER_ADDR = 0x01E64188;
const int HIGH_SCORE_ADDR = 0x01E6DD88;
const int GROUND_ADDR = 0x01E6F788;
const int BR_ADDR = 0x01EB1188;
const int BLANK_NIGHT_ADDR = 0x01EF2B88;
const int ZERO_NIGHT_ADDR = 0x023F2B88;
const int ONE_NIGHT_ADDR = 0x023F3688;
const int TWO_NIGHT_ADDR = 0x023F4188;
const int THREE_NIGHT_ADDR = 0x023F4C88;
const int FOUR_NIGHT_ADDR = 0x023F5788;
const int FIVE_NIGHT_ADDR = 0x023F6288;
const int SIX_NIGHT_ADDR = 0x023F6D88;
const int SEVEN_NIGHT_ADDR = 0x023F7888;
const int EIGHT_NIGHT_ADDR = 0x023F8388;
const int NINE_NIGHT_ADDR = 0x023F8E88;
const int DINO_IDLE_NIGHT_ADDR = 0x023F9988;
const int DINO_HIT_NIGHT_ADDR = 0x02402F88;
const int DINO_RUN_1_NIGHT_ADDR = 0x0240C588;
const int DINO_RUN_2_NIGHT_ADDR = 0x02415B88;
const int DINO_DUCK_1_NIGHT_ADDR = 0x0241F188;
const int DINO_DUCK_2_NIGHT_ADDR = 0x02426988;
const int SMALL_CACTUS_1_NIGHT_ADDR = 0x0242E188;
const int SMALL_CACTUS_2_NIGHT_ADDR = 0x02432788;
const int SMALL_CACTUS_3_NIGHT_ADDR = 0x02436D88;
const int SMALL_CACTUS_4_NIGHT_ADDR = 0x0243B388;
const int SMALL_CACTUS_5_NIGHT_ADDR = 0x0243F988;
const int SMALL_CACTUS_6_NIGHT_ADDR = 0x02443F88;
const int LARGE_CACTUS_1_NIGHT_ADDR = 0x02448588;
const int LARGE_CACTUS_2_NIGHT_ADDR = 0x0244E988;
const int LARGE_CACTUS_3_NIGHT_ADDR = 0x02454D88;
const int LARGE_CACTUS_4_NIGHT_ADDR = 0x0245B188;
const int CACTUS_GROUP_NIGHT_ADDR = 0x02461588;
const int PTERODACTYL_1_NIGHT_ADDR = 0x0246DD88;
const int PTERODACTYL_2_NIGHT_ADDR = 0x02474E08;
const int CLOUD_NIGHT_ADDR = 0x0247BE88;
const int RESTART_NIGHT_ADDR = 0x0247E888;
const int GAME_OVER_NIGHT_ADDR = 0x02484D08;
const int HIGH_SCORE_NIGHT_ADDR = 0x0248E908;
const int GROUND_NIGHT_ADDR = 0x02490308;
const int MOON_1_ADDR = 0x024D1D08;
const int MOON_2_ADDR = 0x024D6D08;
const int MOON_3_ADDR = 0x024DBD08;
const int MOON_4_ADDR = 0x024E0D08;
const int MOON_5_ADDR = 0x024E8508;
const int MOON_6_ADDR = 0x024ED508;
const int MOON_7_ADDR = 0x024F2508;
const int STAR_1_ADDR = 0x024F7508;
const int STAR_2_ADDR = 0x024F7D88;
const int STAR_3_ADDR = 0x024F8608;
const int BR_NIGHT_ADDR = 0x024F8E88;
const int CREDIT_ADDR = 0x02508E88;
const int HIGH_SCORES_ADDR = 0x02533C88;
const int TITLE_ADDR = 0x02546288;

//widths
const int SCREEN_WIDTH = 1280;
const int NUM_WIDTH = 32;
const int DINO_IDLE_WIDTH = 96;
const int DINO_HIT_WIDTH = 96;
const int DINO_RUN_1_WIDTH = 96;
const int DINO_RUN_2_WIDTH = 96;
const int DINO_DUCK_1_WIDTH = 128;
const int DINO_DUCK_2_WIDTH = 128;
const int SMALL_CACTUS_1_WIDTH = 64;
const int SMALL_CACTUS_2_WIDTH = 64;
const int SMALL_CACTUS_3_WIDTH = 64;
const int SMALL_CACTUS_4_WIDTH = 64;
const int SMALL_CACTUS_5_WIDTH = 64;
const int SMALL_CACTUS_6_WIDTH = 64;
const int LARGE_CACTUS_1_WIDTH = 64;
const int LARGE_CACTUS_2_WIDTH = 64;
const int LARGE_CACTUS_3_WIDTH = 64;
const int LARGE_CACTUS_4_WIDTH = 64;
const int CACTUS_GROUP_WIDTH = 128;
const int PTERODACTYL_1_WIDTH = 96;
const int PTERODACTYL_2_WIDTH = 96;
const int CLOUD_WIDTH = 96;
const int RESTART_WIDTH = 96;
const int GAME_OVER_WIDTH = 384;
const int HIGH_SCORE_WIDTH = 64;
const int GROUND_WIDTH = 2400;
const int BR_WIDTH = 128;
const int DINO_IDLE_NIGHT_WIDTH = 96;
const int DINO_HIT_NIGHT_WIDTH = 96;
const int DINO_RUN_1_NIGHT_WIDTH = 96;
const int DINO_RUN_2_NIGHT_WIDTH = 96;
const int DINO_DUCK_1_NIGHT_WIDTH = 128;
const int DINO_DUCK_2_NIGHT_WIDTH = 128;
const int SMALL_CACTUS_1_NIGHT_WIDTH = 64;
const int SMALL_CACTUS_2_NIGHT_WIDTH = 64;
const int SMALL_CACTUS_3_NIGHT_WIDTH = 64;
const int SMALL_CACTUS_4_NIGHT_WIDTH = 64;
const int SMALL_CACTUS_5_NIGHT_WIDTH = 64;
const int SMALL_CACTUS_6_NIGHT_WIDTH = 64;
const int LARGE_CACTUS_1_NIGHT_WIDTH = 64;
const int LARGE_CACTUS_2_NIGHT_WIDTH = 64;
const int LARGE_CACTUS_3_NIGHT_WIDTH = 64;
const int LARGE_CACTUS_4_NIGHT_WIDTH = 64;
const int CACTUS_GROUP_NIGHT_WIDTH = 128;
const int PTERODACTYL_1_NIGHT_WIDTH = 96;
const int PTERODACTYL_2_NIGHT_WIDTH = 96;
const int CLOUD_NIGHT_WIDTH = 96;
const int RESTART_NIGHT_WIDTH = 96;
const int GAME_OVER_NIGHT_WIDTH = 384;
const int HIGH_SCORE_NIGHT_WIDTH = 64;
const int GROUND_NIGHT_WIDTH = 2400;
const int MOON_1_WIDTH = 64;
const int MOON_2_WIDTH = 64;
const int MOON_3_WIDTH = 64;
const int MOON_4_WIDTH = 96;
const int MOON_5_WIDTH = 64;
const int MOON_6_WIDTH = 64;
const int MOON_7_WIDTH = 64;
const int STAR_1_WIDTH = 32;
const int STAR_2_WIDTH = 32;
const int STAR_3_WIDTH = 32;
const int CREDIT_WIDTH = 896;
const int HIGH_SCORES_WIDTH = 384;
const int TITLE_WIDTH = 960;

//heights
const int SCREEN_HEIGHT = 1024;
const int NUM_HEIGHT = 22;
const int DINO_IDLE_HEIGHT = 100;
const int DINO_HIT_HEIGHT = 100;
const int DINO_RUN_1_HEIGHT = 100;
const int DINO_RUN_2_HEIGHT = 100;
const int DINO_DUCK_1_HEIGHT = 60;
const int DINO_DUCK_2_HEIGHT = 60;
const int SMALL_CACTUS_1_HEIGHT = 70;
const int SMALL_CACTUS_2_HEIGHT = 70;
const int SMALL_CACTUS_3_HEIGHT = 70;
const int SMALL_CACTUS_4_HEIGHT = 70;
const int SMALL_CACTUS_5_HEIGHT = 70;
const int SMALL_CACTUS_6_HEIGHT = 70;
const int LARGE_CACTUS_1_HEIGHT = 100;
const int LARGE_CACTUS_2_HEIGHT = 100;
const int LARGE_CACTUS_3_HEIGHT = 100;
const int LARGE_CACTUS_4_HEIGHT = 100;
const int CACTUS_GROUP_HEIGHT = 100;
const int PTERODACTYL_1_HEIGHT = 75;
const int PTERODACTYL_2_HEIGHT = 75;
const int CLOUD_HEIGHT = 28;
const int RESTART_HEIGHT = 67;
const int GAME_OVER_HEIGHT = 26;
const int HIGH_SCORE_HEIGHT = 26;
const int GROUND_HEIGHT = 28;
const int BR_HEIGHT = 128;
const int DINO_IDLE_NIGHT_HEIGHT = 100;
const int DINO_HIT_NIGHT_HEIGHT = 100;
const int DINO_RUN_1_NIGHT_HEIGHT = 100;
const int DINO_RUN_2_NIGHT_HEIGHT = 100;
const int DINO_DUCK_1_NIGHT_HEIGHT = 60;
const int DINO_DUCK_2_NIGHT_HEIGHT = 60;
const int SMALL_CACTUS_1_NIGHT_HEIGHT = 70;
const int SMALL_CACTUS_2_NIGHT_HEIGHT = 70;
const int SMALL_CACTUS_3_NIGHT_HEIGHT = 70;
const int SMALL_CACTUS_4_NIGHT_HEIGHT = 70;
const int SMALL_CACTUS_5_NIGHT_HEIGHT = 70;
const int SMALL_CACTUS_6_NIGHT_HEIGHT = 70;
const int LARGE_CACTUS_1_NIGHT_HEIGHT = 100;
const int LARGE_CACTUS_2_NIGHT_HEIGHT = 100;
const int LARGE_CACTUS_3_NIGHT_HEIGHT = 100;
const int LARGE_CACTUS_4_NIGHT_HEIGHT = 100;
const int CACTUS_GROUP_NIGHT_HEIGHT = 100;
const int PTERODACTYL_1_NIGHT_HEIGHT = 75;
const int PTERODACTYL_2_NIGHT_HEIGHT = 75;
const int CLOUD_NIGHT_HEIGHT = 28;
const int RESTART_NIGHT_HEIGHT = 67;
const int GAME_OVER_NIGHT_HEIGHT = 26;
const int HIGH_SCORE_NIGHT_HEIGHT = 26;
const int GROUND_NIGHT_HEIGHT = 28;
const int MOON_1_HEIGHT = 80;
const int MOON_2_HEIGHT = 80;
const int MOON_3_HEIGHT = 80;
const int MOON_4_HEIGHT = 80;
const int MOON_5_HEIGHT = 80;
const int MOON_6_HEIGHT = 80;
const int MOON_7_HEIGHT = 80;
const int STAR_1_HEIGHT = 17;
const int STAR_2_HEIGHT = 17;
const int STAR_3_HEIGHT = 17;
const int CREDIT_HEIGHT = 49;
const int HIGH_SCORES_HEIGHT = 49;
const int TITLE_HEIGHT = 72;

const int DINO_BASE_HEIGHT =  512-DINO_IDLE_HEIGHT+15;
const int HORIZONTAL_RUN_COLLISION = 100 + DINO_IDLE_WIDTH; //collision for x-axis
const int TALLEST_SPRITE =  512-BR_HEIGHT+48;
#endif /* SRC_HELPERS_SHARED_H_ */