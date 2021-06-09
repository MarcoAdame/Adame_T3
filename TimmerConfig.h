/*
 * TimmerConfig.h
 *
 *  Created on: 8 jun. 2021
 *      Author: Marco Adame
 */

#ifndef TIMMERCONFIG_H_
#define TIMMERCONFIG_H_


#include "fsl_debug_console.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_pit.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_PIT_BASEADDR PIT
#define DEMO_PIT_CHANNEL  kPIT_Chnl_0

#define PIT_IRQ_ID        PIT0_IRQn
/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)

#define TIEMPO 1000000U




void TimmerBegin(){
	/* Structure of initialize PIT */
	    pit_config_t pitConfig;

	    /* Board pin, clock, debug console init */
	    BOARD_InitPins();
	    BOARD_BootClockRUN();
	    BOARD_InitDebugConsole();

	    /* Initialize and enable LED */

	    /*
	     * pitConfig.enableRunInDebug = false;
	     */
	    PIT_GetDefaultConfig(&pitConfig);

	    /* Init pit module */
	    PIT_Init(DEMO_PIT_BASEADDR, &pitConfig);

	    /* Set timer period for channel 0 */
	    PIT_SetTimerPeriod(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, USEC_TO_COUNT(TIEMPO, PIT_SOURCE_CLOCK));

	    /* Enable timer interrupts for channel 0 */
	    PIT_EnableInterrupts(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerInterruptEnable);

	    /* Enable at the NVIC */
	    EnableIRQ(PIT_IRQ_ID);

	    /* Start channel 0 */
	    //PRINTF("\r\nStarting channel No.0 ...");
	    PIT_StartTimer(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL);
}


#endif /* TIMMERCONFIG_H_ */
