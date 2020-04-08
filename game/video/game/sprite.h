/*
 * Created by: Matthew Gould
 *	Sprite class: contains position and size of the sprite
 *	Child classes:
 *		Dino - contains functions and variables necessary for the dino sprite
 *		Obstacles - contains functions and variables necessary for the different obstacles
 */
#ifndef SPRITE_H
#define SPRITE_H

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

static volatile Xuint32 *slaveaddrPtr = (Xuint32 *) XPAR_GPU_0_S00_AXI_BASEADDR;

using namespace std;

// base class for all game sprites 
class Sprite {
    public:
		Sprite();

        // intialize the width,height of the sprite and location of the day/night sprite 
        Sprite(int w, int h, int dayAddress, int nightAddress);

        // interface with the GPU to display the sprite object, using day/night address based on isNight 
        void display();

        bool isOffScreen();

        // the coordinates to display the sprite at, with the top left of the screen being (0,0)
        int x; 

        int y; 
    
        // the address of the day and night sprite in memory 
        int dayAddr;

        int nightAddr;

        // the sprite size in pixels 
        int width; 

        int height;

        // is the night mode of the game currently activated 
        bool isNight;
};

class Dino : public Sprite {
    public:
        Dino();

        // detect if the dino has collided with an obstacle 
        bool detectCollision(int obstacleX, int obstacleY, int obstacleHeight, int speed, bool ptr);

        void idle();

        void animateRun();

        void updateJump();

        void updateDuck();

        void falling();

        void showDead();

        bool isJumping;

        bool isFalling;

        bool isJumpIdle;

        bool isDead;

        int addr_run_one;

        int addr_run_two;

};

class Obstacle : public Sprite {
    public:

        Obstacle();

        // constructor for obstacle without animation  
        Obstacle(int w, int h, int dayAddress, int nightAddress);

        // constructor for obstacle with animation  
        Obstacle(int w, int h, int dayAddress, int dayAddressTwo, int nightAddress, int nightAddressTwo);

        // address members for the obstacle with animation if both frames have a value  
        int frameOneDay = 0;

        int frameOneNight = 0;

        int frameTwoDay = 0;

        int frameTwoNight = 0;

        // switch the sprite to to its second address to animate if possible 
        void animate();
};

#endif //SPRITE_H


