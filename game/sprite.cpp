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

Sprite::Sprite(int w, int h, int dayAddress, int nightAddress){
	width = w;
	height = h;
	dayAddr = dayAddress;
	nightAddr = nightAddress;
	isNight = false;
}

void Sprite::display(){
	int currAddr = 0;

	if(isNight){
		currAddr = nightAddr;
	} else {
		currAddr = dayAddr;
	}

	// sprite addr
	*(slaveaddrPtr+3) = currAddr;

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
	isNight = false;

	width = DINO_IDLE_WIDTH;
	height = DINO_IDLE_HEIGHT;

	dayAddr = DINO_IDLE_ADDR;
	nightAddr = DINO_IDLE_NIGHT_ADDR;
}

void Dino::updateJump(){
	y -= JUMP_INTERVAL;

}

void Dino::falling(){
	y += JUMP_INTERVAL;
}

void Dino::updateDuck(){

}

void Dino::idle(){
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
	}

}

bool Dino::detectCollision(){
	// for now generate a random number to determine if collision
	int randVal = rand() ;//% 700;
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

Obstacle::Obstacle(int w, int h, int dayAddress, int nightAddress){
	width = w;
    height = h;
	dayAddr = dayAddress;
	nightAddr = nightAddress;
	isNight = false;
	frameOneDay = 0;
	frameOneNight = 0;
	frameTwoDay = 0;
	frameTwoNight = 0;
}

Obstacle::Obstacle(int w, int h, int dayAddress, int dayAddressTwo, int nightAddress, int nightAddressTwo){
	width = w;
	height = h;
	dayAddr = dayAddress;
	nightAddr = nightAddress;
	isNight = false;
	frameOneDay = dayAddress;
	frameOneNight = nightAddress;
	frameTwoDay = dayAddressTwo;
	frameTwoNight = nightAddressTwo;
}


void Obstacle::animate(){
	if(frameOneDay != 0 && frameOneNight != 0){
		if(dayAddr == frameOneDay){
			dayAddr = frameTwoDay;
			nightAddr = frameTwoNight;
		} else{
			dayAddr = frameOneDay;
			nightAddr = frameOneNight;
		}

	}
}

bool Obstacle::isOffScreen(){
	if(x < -100){
		return(true);
	} else {
		return(false);
	}
}

