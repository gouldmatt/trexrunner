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

class Sprite {
    public:
		Sprite();

        Sprite(int w, int h, int dayAddress, int nightAddress);

        void display();

        bool isOffScreen();

        int x; 

        int y; 

        int dayAddr;

        int nightAddr;

        int width; 

        int height;

        bool isNight;
};

class Dino : public Sprite {
    public:
        Dino();

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

        Obstacle(int w, int h, int dayAddress, int nightAddress);

        Obstacle(int w, int h, int dayAddress, int dayAddressTwo, int nightAddress, int nightAddressTwo);

        int frameOneDay = 0;

        int frameOneNight = 0;

        int frameTwoDay = 0;

        int frameTwoNight = 0;


        void animate();
};

#endif //SPRITE_H

