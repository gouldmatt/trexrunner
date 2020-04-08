/*
 * Shared.h
 *
 *  Created on: Mar 26, 2020
 *      Author: Elaine Crisostomo
 *		Constants and macros used throughout the project
 */

#ifndef SRC_AUDIO_HELPERS_SHARED_H_
#define SRC_AUDIO_HELPERS_SHARED_H_

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

/* AUDIO SAMPLE ADDRESSES */
const int JUMP_ADDR_LEFT = 0x0258D28C;
const int JUMP_ADDR_RIGHT = 0x0269028C;
const int SCORE_ADDR_LEFT = 0x0279328C;
const int SCORE_ADDR_RIGHT = 0x0289828C;
const int DEATH_ADDR_LEFT =  0x0299D28C;
const int DEATH_ADDR_RIGHT = 0x030A028C;
const int VRISKA_ADDR_RIGHT = 0x031A028C; //night mode, the megalovania sample
const int VRISKA_ADDR_LEFT = 0x032A028C;




#endif /* SRC_AUDIO_HELPERS_SHARED_H_ */
