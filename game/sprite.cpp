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


Sprite::Sprite(int w, int h, int address){
	width = w;
	height = h;
	addr = address;
}

void Sprite::display(){
	// sprite addr
	*(slaveaddrPtr+3) = addr;

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
}

Dino::Dino(int w, int h, int address_idle, int address_run_one, int address_run_two){
	width = w;
	height = h;
	addr_idle = address_idle;
	addr = address_idle;
	addr_run_one = address_run_one;
	addr_run_two = address_run_two;
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
	addr = addr_idle;
}

void Dino::animateRun(){
	if(addr == addr_run_one){
		addr = addr_run_two;
	} else {
		addr = addr_run_one;
	}

}

bool Dino::detectCollision(){
	// for now generate a random number to determine if collision
	int randVal = 100;//rand() % 500;
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

Obstacle::Obstacle(int w, int h, int address){
	width = w;
    height = h;
    addr = address;
}



bool Obstacle::isOffScreen(){
	if(x < 0){
		return(true);
	} else {
		return(false);
	}
}
