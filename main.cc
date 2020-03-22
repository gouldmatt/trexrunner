#include "../src/game/gameplay.h"
#include "../src/game/sprite.h"
#include "../src/helpers/AppInitializer.h"
#include "../src/helpers/Shared.h"

#include <xgpio.h>
#include <algorithm>
#include "xgpiops.h"
#include "xgpio_l.h"
#include "xscugic.h"

XGpio input; //input to the buttons
struct states_t {
	bool bStartGame = false;
	bool bJumpState = false;
	bool bDuckState = false;
};


 /*
  * INITIALIZE INTERRUPTS
  * Put it here to make our lives easier
  */

XScuGic InterruptController; /* Instance of the Interrupt Controller */
static XScuGic_Config *GicConfig;/* The configuration parameters of the controller */
GamePlay trexRunner;


void ButtonInterruptHandler(void *InstancePtr){
	//Disable GPIO Interrupts
	XGpio_InterruptDisable(&input, XGPIO_IR_CH1_MASK);
	//Ignore additional button presses
	if((XGpio_InterruptGetStatus(&input) & XGPIO_IR_CH1_MASK) != XGPIO_IR_CH1_MASK){
		return;
	}

	int btn_value = readButtons(input);

	if(btn_value == BUTTON_UP){
		trexRunner.bJumpState = true;
		xil_printf("JUMP!");
	}
	else if(btn_value == BUTTON_DOWN){
		trexRunner.bDuckState = true;
		xil_printf("DUCK!");
	}
	else if(btn_value == BUTTON_CENTRE){
		trexRunner.bStartGame = true;
		xil_printf("Start game!");
	}
	(void) XGpio_InterruptClear(&input, XGPIO_IR_CH1_MASK);
	XGpio_InterruptEnable(&input, XGPIO_IR_CH1_MASK);

}

int SetUpInterruptSystem(XScuGic *XScuGicInstancePtr){
	//Enable Interrupt
	XGpio_InterruptEnable(&input, XGPIO_IR_CH1_MASK);
	XGpio_InterruptGlobalEnable(&input);

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
	(Xil_ExceptionHandler) XScuGic_InterruptHandler,
		XScuGicInstancePtr);
	Xil_ExceptionEnable();

	return XST_SUCCESS;
}

/*Setup all interrupts of the system*/
int ScuGicInterrupt_Init(u16 DeviceId, XGpio *GpioInstancePtr){

	int Status;
	GicConfig = XScuGic_LookupConfig(DeviceId);
	if (NULL == GicConfig) {
		return XST_FAILURE;
	}
	Status = XScuGic_CfgInitialize(&InterruptController, GicConfig,
	GicConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	//call to interrupt system
	Status = SetUpInterruptSystem(&InterruptController);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}
	/*Connect a device driver handler that will be called when an interrupt for the device occurs, the device driver handler performs the specific interrupt processing for the device*/
	Status = XScuGic_Connect(&InterruptController,
	61,
	(Xil_ExceptionHandler)ButtonInterruptHandler,
	(void *)GpioInstancePtr);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	// Enable GPIO interrupts interupt
	XGpio_InterruptEnable(GpioInstancePtr, 1);
	XGpio_InterruptGlobalEnable(GpioInstancePtr);

	// Enable GPIO interrupts in the controller
	XScuGic_Enable(&InterruptController, XPAR_FABRIC_AXI_GPIO_0_IP2INTC_IRPT_INTR);


	return XST_SUCCESS;

}

//Initializes the buttons
//Taken from: https://reference.digilentinc.com/learn/programmable-logic/tutorials/zedboard-getting-started-with-zynq/start
int InitializeButtons(){
	int status = XGpio_Initialize(&input, XPAR_GPIO_0_DEVICE_ID);
	if(status != XST_SUCCESS){
		return XST_FAILURE;
	}

	XGpio_SetDataDirection(&input, 1, 0xF); //set first channel tristate buffer to input

	//status initialize interrupt controller
	status = ScuGicInterrupt_Init(XPAR_PS7_SCUGIC_0_DEVICE_ID, &input);
}

/*
 * END INTERRUPT INITIALIZE
 */

int main(){

	InitializeButtons(); //Initialize Buttons
    int score = 0;
    bool showStart = true;

    std::vector<int> highScores(5,0);

    while(1){
    	trexRunner.GameplayInit();
	trexRunner.GameplayInit();

    while(1){
    	if(trexRunner.bStartGame == true){
    		score = trexRunner.gameplay(highScores[0]);
    		trexRunner.bStartGame = false;
    		//game ends, put score into high score vector
    		highScores.push_back(score);
    		std::sort(highScores.begin(), highScores.end());
    		std::reverse(highScores.begin(), highScores.end());
    		highScores.pop_back();

    		//display high scores
<<<<<<< HEAD
    		trexRunner.displaySprite(0,0,SCREEN_WIDTH,100,BLANK_SCR_ADDR);
    		trexRunner.displaySprite(890,0,HIGH_SCORE_WIDTH,HIGH_SCORE_HEIGHT,HIGH_SCORE_ADDR);
    		trexRunner.displayScore(950,0,highScores[0]);
    		trexRunner.displayScore(1100,0,score);

    		for(int i = 0; i < 5; i++){
    		   trexRunner.displayScore(575,240+50*i,highScores[i]);
=======
    		trexRunner.displaySprite(0,0,SCREEN_WIDTH,100,BLANK_ADDR);
    		trexRunner.displaySprite(890,0,HIGH_SCORE_WIDTH,HIGH_SCORE_HEIGHT,HIGH_SCORE_ADDR);
    		trexRunner.displayScore(950,0,highScores[0],false);
    		trexRunner.displayScore(1100,0,score,false);

    		for(int i = 0; i < 5; i++){
    		   trexRunner.displayScore(575,140+50*i,highScores[i],false);
>>>>>>> 018ded042ad1fc48de78f71f8e81d6540c3fbc8d
    		}

    		//Option to restart

<<<<<<< HEAD
    		trexRunner.displaySprite(592,500,RESTART_WIDTH,RESTART_HEIGHT,RESTART_ADDR);

    		trexRunner.displaySprite(448,180,GAME_OVER_WIDTH,GAME_OVER_HEIGHT,GAME_OVER_ADDR);
=======
    		trexRunner.displaySprite(592,400,RESTART_WIDTH,RESTART_HEIGHT,RESTART_ADDR);

    		trexRunner.displaySprite(448,80,GAME_OVER_WIDTH,GAME_OVER_HEIGHT,GAME_OVER_ADDR);
>>>>>>> 018ded042ad1fc48de78f71f8e81d6540c3fbc8d
    		trexRunner.switchBuffer();

    		// display high scores
    		printf("Display high scores screens: press button to play again\n");


    	}
    	else{
    		printf("Press middle button to start!");
    	}


    }
    return 0;
}
