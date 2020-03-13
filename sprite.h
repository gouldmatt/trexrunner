//header file for base class sprite and child classes Dino and Obstacle 
#ifndef SPRITE_H
#define SPRITE_H

static volatile Xuint32 *slaveaddrPtr = (Xuint32 *) XPAR_GPU_0_S00_AXI_BASEADDR;

using namespace std;

class Sprite {
    public:
		Sprite();

        Sprite(int w, int h, int address);

        void display();

        int x; 

        int y; 

        int addr; 

        int width; 

        int height; 

        bool isNightMode; 
};

class Dino : public Sprite {
    public:
        Dino();

        bool detectCollision();

        void updateJump();

        bool isJumping; 
};

class Obstacle : public Sprite {
    public:
        Obstacle();

        Obstacle(int w, int h, int address);

        bool isOffScreen();
};

#endif //SPRITE_H


