//header file for base class sprite and child classes Dino and Obstacle 
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

<<<<<<< HEAD
        Sprite(int w, int h, int address);
=======
        Sprite(int w, int h, int dayAddress, int nightAddress);
>>>>>>> 018ded042ad1fc48de78f71f8e81d6540c3fbc8d

        void display();

        int x; 

        int y; 

<<<<<<< HEAD
        int addr; 

        int width; 

        int height; 

        bool isNightMode; 
=======
        int currAddr;

        int dayAddr;

        int nightAddr;

        int width; 

        int height;

        bool isNight;
>>>>>>> 018ded042ad1fc48de78f71f8e81d6540c3fbc8d
};

class Dino : public Sprite {
    public:
        Dino();

<<<<<<< HEAD
        Dino(int w, int h, int address_idle, int address_run_one, int address_run_two);

=======
>>>>>>> 018ded042ad1fc48de78f71f8e81d6540c3fbc8d
        bool detectCollision();

        void idle();

        void animateRun();

        void updateJump();

        void updateDuck();

        void falling();

        bool isJumping;

        bool isFalling;

        bool isJumpIdle;
<<<<<<< HEAD

        int addr_idle;

        int addr_run_one;

        int addr_run_two;
=======
>>>>>>> 018ded042ad1fc48de78f71f8e81d6540c3fbc8d
};

class Obstacle : public Sprite {
    public:
        Obstacle();

<<<<<<< HEAD
        Obstacle(int w, int h, int address);
=======
        Obstacle(int w, int h, int dayAddress, int nightAddress);
>>>>>>> 018ded042ad1fc48de78f71f8e81d6540c3fbc8d

        bool isOffScreen();
};

#endif //SPRITE_H


