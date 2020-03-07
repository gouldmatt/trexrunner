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
	//void displaySprite(int x, int y, int width, int height, int addr){

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
	//}
}

///////////////////////////////////////////////
// dino class 
Dino::Dino(){

}

void Dino::updateJump(){

}

bool Dino::detectCollision(){
	// for now generate a random number to determine if collision
	int randVal = rand() % 7000;
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
