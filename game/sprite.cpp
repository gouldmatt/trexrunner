#include "xil_printf.h"
#include "xbasic_types.h"
#include "xparameters.h"
#include <stdio.h>
#include "xil_types.h"

#include "xparameters.h"

#include "xil_io.h"
#include "xil_exception.h"
#include "xscugic.h"

#include <stdlib.h>

#include <xgpio.h>

#include "xgpiops.h"
#include "xscugic.h"
#include "xplatform_info.h"
#include <xil_printf.h>

#include <sleep.h>
#include <xil_cache.h>

#include "xbasic_types.h"
#include "sprite.h"
#include <sleep.h>
#include <vector>

#include "../helpers/Shared.h"

using namespace std;

///////////////////////////////////////////////
// sprite class 
Sprite::Sprite(){

}

<<<<<<< HEAD

Sprite::Sprite(int w, int h, int address){
	width = w;
	height = h;
	addr = address;
}

void Sprite::display(){
	// sprite addr
	*(slaveaddrPtr+3) = addr;
=======
Sprite::Sprite(int w, int h, int dayAddress, int nightAddress){
	width = w;
	height = h;
	dayAddr = dayAddress;
	nightAddr = nightAddress;
	currAddr = dayAddress;
	isNight = false;
}

void Sprite::display(){
	if(isNight){
		currAddr = nightAddr;
	} else {
		currAddr = dayAddr;
	}

	// sprite addr
	*(slaveaddrPtr+3) = currAddr;
>>>>>>> 018ded042ad1fc48de78f71f8e81d6540c3fbc8d

	// x
	*(slaveaddrPtr+4) = x;


	// y
	*(slaveaddrPtr+5) = y;


	// height
	*(slaveaddrPtr+6) = height;


	// width
	*(slaveaddrPtr+7) = width;


	*(slaveaddrPtr+0) = 0x00000001;
	*(slaveaddrPtr+0) = 0x00000000;

	int done =  *(slaveaddrPtr+1);
		while(done != 1){
		done =  *(slaveaddrPtr+1);
	}

	*(slaveaddrPtr+0) = 0x00000000;
}

///////////////////////////////////////////////
// dino class 
Dino::Dino(){
	isJumping = false;
	isFalling = false;
	isJumpIdle = false;
<<<<<<< HEAD
}

Dino::Dino(int w, int h, int address_idle, int address_run_one, int address_run_two){
	width = w;
	height = h;
	addr_idle = address_idle;
	addr = address_idle;
	addr_run_one = address_run_one;
	addr_run_two = address_run_two;
}

=======
	isNight = false;

	width = DINO_IDLE_WIDTH;
	height = DINO_IDLE_HEIGHT;

	dayAddr = DINO_IDLE_ADDR;
	nightAddr = DINO_IDLE_NIGHT_ADDR;
}
>>>>>>> 018ded042ad1fc48de78f71f8e81d6540c3fbc8d

void Dino::updateJump(){
	y -= JUMP_INTERVAL;

}

void Dino::falling(){
	y += JUMP_INTERVAL;
}

void Dino::updateDuck(){

}

void Dino::idle(){
<<<<<<< HEAD
	addr = addr_idle;
}

void Dino::animateRun(){
	if(addr == addr_run_one){
		addr = addr_run_two;
	} else {
		addr = addr_run_one;
=======
	width = DINO_IDLE_WIDTH;
	height = DINO_IDLE_HEIGHT;

	dayAddr = DINO_IDLE_ADDR;
	nightAddr = DINO_IDLE_NIGHT_ADDR;
}

void Dino::animateRun(){
	width = DINO_IDLE_WIDTH;
	height = DINO_IDLE_HEIGHT;

	if(dayAddr == DINO_RUN_1_ADDR){
		dayAddr = DINO_RUN_2_ADDR;
		nightAddr = DINO_RUN_2_ADDR;

	} else {
		dayAddr = DINO_RUN_1_ADDR;
	    nightAddr = DINO_RUN_1_ADDR;
>>>>>>> 018ded042ad1fc48de78f71f8e81d6540c3fbc8d
	}

}

bool Dino::detectCollision(){
	// for now generate a random number to determine if collision
<<<<<<< HEAD
	int randVal = 100;//rand() % 500;
=======
	int randVal = rand() % 700;
>>>>>>> 018ded042ad1fc48de78f71f8e81d6540c3fbc8d
	if(randVal == 10){
		return(true);
	} else {
		return(false);
	}
}

///////////////////////////////////////////////
// obstacle class 
Obstacle::Obstacle(){
}

<<<<<<< HEAD
Obstacle::Obstacle(int w, int h, int address){
	width = w;
    height = h;
    addr = address;
}



bool Obstacle::isOffScreen(){
	if(x < 0){
=======
Obstacle::Obstacle(int w, int h, int dayAddress, int nightAddress){
	width = w;
    height = h;
	dayAddr = dayAddress;
	nightAddr = nightAddress;
	currAddr = dayAddress;
	isNight = false;
}

bool Obstacle::isOffScreen(){
	if(x < -100){
>>>>>>> 018ded042ad1fc48de78f71f8e81d6540c3fbc8d
		return(true);
	} else {
		return(false);
	}
}
<<<<<<< HEAD
=======

>>>>>>> 018ded042ad1fc48de78f71f8e81d6540c3fbc8d
