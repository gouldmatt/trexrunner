/*
 * gameplay.h
 *
 *  Created on: Mar 7, 2020
 *      Author: ecrisost
 */

#ifndef SRC_GAMEPLAY_H_
#define SRC_GAMEPLAY_H_
#include "xparameters.h"
#include "xbasic_types.h"
#include "../helpers/Shared.h"
#include <vector>


class GamePlay{

	public:

	GamePlay();
	bool volatile bJumpState;
	bool volatile bDuckState;
	bool bStartGame;
	bool bFalling;


	int LFSR(); //random number generator
	int gameplay(int highScore); //main gameplay
	void displayScore(int x, int y, int score, bool nightMode); //display score
	void displaySprite(int x, int y, int width, int height, int addr);
	void switchBuffer();
	void GameplayInit(); //initial screen of the game

	private:
		//pointer to sprite address
		volatile Xuint32 *slaveaddr_p = (Xuint32 *) XPAR_GPU_0_S00_AXI_BASEADDR;;
};




#endif /* SRC_GAMEPLAY_H_ */
