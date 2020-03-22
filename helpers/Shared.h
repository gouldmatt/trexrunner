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
const int NIGHT_INTERVAL = 500;
const int SPEED_INTERVAL = 100;
const int SCORE_INC_INTERVAL = 3;

const int BASE_HEIGHT = 512;
const int JUMP_INTERVAL = 60;//50;
const int IDLE_COUNT = 3;

const int CACTI_INTERVAL = 50;
const int PT_INTERVAL = 250;
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
const int BLANK_NIGHT_ADDR = 0x01EB1188;
const int ZERO_NIGHT_ADDR = 0x023B1188;
const int ONE_NIGHT_ADDR = 0x023B1C88;
const int TWO_NIGHT_ADDR = 0x023B2788;
const int THREE_NIGHT_ADDR = 0x023B3288;
const int FOUR_NIGHT_ADDR = 0x023B3D88;
const int FIVE_NIGHT_ADDR = 0x023B4888;
const int SIX_NIGHT_ADDR = 0x023B5388;
const int SEVEN_NIGHT_ADDR = 0x023B5E88;
const int EIGHT_NIGHT_ADDR = 0x023B6988;
const int NINE_NIGHT_ADDR = 0x023B7488;
const int DINO_IDLE_NIGHT_ADDR = 0x023B7F88;
const int DINO_HIT_NIGHT_ADDR = 0x023C1588;
const int DINO_RUN_1_NIGHT_ADDR = 0x023CAB88;
const int DINO_RUN_2_NIGHT_ADDR = 0x023D4188;
const int DINO_DUCK_1_NIGHT_ADDR = 0x023DD788;
const int DINO_DUCK_2_NIGHT_ADDR = 0x023E4F88;
const int SMALL_CACTUS_1_NIGHT_ADDR = 0x023EC788;
const int SMALL_CACTUS_2_NIGHT_ADDR = 0x023F0D88;
const int SMALL_CACTUS_3_NIGHT_ADDR = 0x023F5388;
const int SMALL_CACTUS_4_NIGHT_ADDR = 0x023F9988;
const int SMALL_CACTUS_5_NIGHT_ADDR = 0x023FDF88;
const int SMALL_CACTUS_6_NIGHT_ADDR = 0x02402588;
const int LARGE_CACTUS_1_NIGHT_ADDR = 0x02406B88;
const int LARGE_CACTUS_2_NIGHT_ADDR = 0x0240CF88;
const int LARGE_CACTUS_3_NIGHT_ADDR = 0x02413388;
const int LARGE_CACTUS_4_NIGHT_ADDR = 0x02419788;
const int CACTUS_GROUP_NIGHT_ADDR = 0x0241FB88;
const int PTERODACTYL_1_NIGHT_ADDR = 0x0242C388;
const int PTERODACTYL_2_NIGHT_ADDR = 0x02433408;
const int CLOUD_NIGHT_ADDR = 0x0243A488;
const int RESTART_NIGHT_ADDR = 0x0243CE88;
const int GAME_OVER_NIGHT_ADDR = 0x02443308;
const int HIGH_SCORE_NIGHT_ADDR = 0x0244CF08;
const int GROUND_NIGHT_ADDR = 0x0244E908;
const int MOON_1_ADDR = 0x02490308;
const int MOON_2_ADDR = 0x02495308;
const int MOON_3_ADDR = 0x0249A308;
const int MOON_4_ADDR = 0x0249F308;
const int MOON_5_ADDR = 0x024A6B08;
const int MOON_6_ADDR = 0x024ABB08;
const int MOON_7_ADDR = 0x024B0B08;
const int STAR_1_ADDR = 0x024B5B08;
const int STAR_2_ADDR = 0x024B6388;
const int STAR_3_ADDR = 0x024B6C08;

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




#endif /* SRC_HELPERS_SHARED_H_ */
