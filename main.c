/*
 * Uso de interrupcciones
 *
 *
 *      Author: Marco Adame
 */
#include <stdio.h>
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"
#include "fsl_debug_console.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_pit.h"

#include "LedConfig.h"
#include "TimmerConfig.h"


uint8_t sw3_press = 0;
uint8_t sw2_press = 0;
volatile bool timer_state = false;

 gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput,
        0,
    };

#define PIN6         6u
#define PIN4         4u

typedef enum{
	RED,
	GREEN,
	BLUE,
	PURPLE,
	WHITE,
	YELLOW,
}State_name_t;

typedef enum{
	ESPERA,
	ESTADO_SW2,
	ESTADO_SW3A,
	ESTADO_SW3B,
}State_name_main_t;

								/* Interrupcciones */
/* Interupcciones externas */
void PORTA_IRQHandler(void)		// Esta funcion se manda llamar automaticmanete por hardware
{

	GPIO_PortClearInterruptFlags(GPIOA, 1U << PIN4);
	sw3_press = true;
    SDK_ISR_EXIT_BARRIER;
}

void PORTC_IRQHandler(void)		// Esta funcion se manda llamar automaticmanete por hardware
{
		GPIO_PortClearInterruptFlags(GPIOC, 1U << PIN6);
		sw2_press = true;
    SDK_ISR_EXIT_BARRIER;
}

/* Timer */
void PIT0_IRQHandler(void)
{
    /* Clear interrupt flag.*/
    PIT_ClearStatusFlags(DEMO_PIT_BASEADDR, DEMO_PIT_CHANNEL, kPIT_TimerFlag);
    timer_state = true;

    __DSB();
}

int main(void) {
 /*Configuracion */
	State_name_t current_state = YELLOW;

	State_name_main_t cs = ESPERA;

	const port_pin_config_t porta_pin_config = {
	    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
	    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
	    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
	    kPORT_HighDriveStrength,                                 /* High drive strength is configured */
	    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
	    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	  };

  CLOCK_EnableClock(kCLOCK_PortA);
  CLOCK_EnableClock(kCLOCK_PortC);

  LedBegin();
  TimmerBegin();

  PORT_SetPinConfig(PORTA, PIN4, &porta_pin_config);
  PORT_SetPinConfig(PORTC, PIN6, &porta_pin_config);

  PORT_SetPinInterruptConfig(PORTA, PIN4, kPORT_InterruptFallingEdge); //1-	Configuración de la interrupción de interés
  PORT_SetPinInterruptConfig(PORTC, PIN6, kPORT_InterruptFallingEdge);

  GPIO_PinInit(GPIOA, PIN4, &sw_config);
  GPIO_PinInit(GPIOC, PIN6, &sw_config);



  NVIC_EnableIRQ(PORTA_IRQn); //2- Habilitar la interrupción en el NVIC
  NVIC_SetPriority(PORTA_IRQn, 2);  //3- Fijar la prioridad

  NVIC_EnableIRQ(PORTC_IRQn);
  NVIC_SetPriority(PORTC_IRQn, 2);

  ledOff();
  /*Ejecucion */
    while(1) {
    	/*  State Machine   */
    	switch(cs){
    	case ESPERA:
    		if(sw2_press){
    			cs=ESTADO_SW2;
    			sw2_press=false;
    			sw3_press=false;
    		}
    		break;
    	case ESTADO_SW2:
    		if(sw3_press){
    		    cs=ESTADO_SW3A;
    		    sw3_press=false;
    		    sw2_press=false;
    		}
    		break;
    	case ESTADO_SW3A:
    		if(sw3_press){
    		    cs=ESTADO_SW3B;
    		    sw3_press=false;
    		    sw2_press=false;
    		}
    		break;
    	case ESTADO_SW3B:
    		if(sw2_press){
    		    cs=ESPERA;
    		    sw3_press=false;
    		    sw2_press=false;
    		}
    		break;
    	default:

    		break;
    	}
    	/*  State Machine   */
    	if(timer_state){
    		switch(current_state){
				case YELLOW:
					LedColor(yellow);
					if(cs==ESPERA){
						current_state = RED;
					}else if(cs==ESTADO_SW2){
						current_state = GREEN;
					}else if(cs==ESTADO_SW3A){
						current_state = BLUE;
					}else {
						current_state = GREEN;
					}
					break;
				case RED:
					LedColor(red);
					if(cs==ESPERA){
						current_state = PURPLE;
					}else if(cs==ESTADO_SW2){
						current_state = GREEN;
					}else if(cs==ESTADO_SW3A){
						current_state = BLUE;
					}else {
						current_state = GREEN;
					}
					break;
				case PURPLE:
					LedColor(purple);
					if(cs==ESPERA){
						current_state = YELLOW;
					}else if(cs==ESTADO_SW2){
						current_state = GREEN;
					}else if(cs==ESTADO_SW3A){
						current_state = BLUE;
					}else {
						current_state = YELLOW;
					}
					break;
				case GREEN:
					LedColor(green);
					if(cs==ESPERA){
						current_state = YELLOW;
					}else if(cs==ESTADO_SW2){
						current_state = BLUE;
					}else if(cs==ESTADO_SW3A){
						current_state = BLUE;
					}else {
						current_state = PURPLE;
					}
					break;
				case BLUE:
					LedColor(blue);
					if(cs==ESPERA){
						current_state = YELLOW;
					}else if(cs==ESTADO_SW2){
						current_state = RED;
					}else if(cs==ESTADO_SW3A){
						current_state = WHITE;
					}else {
						current_state = GREEN;
					}
					break;
				case WHITE:
					LedColor(white);
					if(cs==ESPERA){
						current_state = YELLOW;
					}else if(cs==ESTADO_SW2){
						current_state = GREEN;
					}else if(cs==ESTADO_SW3A){
						current_state = RED;
					}else {
						current_state = GREEN;
					}
					break;
				default:
					current_state = ESPERA;
					ledOff();
					break;
    		}
    		timer_state=false;
    	}
    }
    return 0 ;
}

