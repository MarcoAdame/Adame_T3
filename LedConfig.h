/*
 * LedConfig.h
 *
 *  Created on: 8 jun. 2021
 *      Author: Marco Adame
 */


#include <stdio.h>
#include "pin_mux.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"

#define LED_R 22u  	//PortB
#define LED_B 21u	//PortB
#define LED_G 26u	//PortE

typedef enum{
	red,
	green,
	blue,
	purple,
	white,
	yellow,
};

gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        1,
    };

void LedBegin(){
	  CLOCK_EnableClock(kCLOCK_PortB);
	  CLOCK_EnableClock(kCLOCK_PortE);

	  PORT_SetPinMux(PORTB, LED_R, kPORT_MuxAsGpio);
	  GPIO_PinInit(GPIOB, LED_R, &led_config);
	  PORT_SetPinMux(PORTE, LED_G, kPORT_MuxAsGpio);
	  GPIO_PinInit(GPIOE, LED_G, &led_config);
	  PORT_SetPinMux(PORTB, LED_B, kPORT_MuxAsGpio);
	  GPIO_PinInit(GPIOB, LED_B, &led_config);
}

void ledOff(){
	GPIO_PortSet(GPIOB, 1u << LED_R);
	GPIO_PortSet(GPIOB, 1u << LED_B);
	GPIO_PortSet(GPIOE, 1u << LED_G);
}

void LedColor(int color){
	switch(color){
	case red:
		ledOff();
		GPIO_PortClear(GPIOB, 1u << LED_R);
		printf("Led color:  Red \n");
		break;
	case green:
		ledOff();
		GPIO_PortClear(GPIOE, 1u << LED_G);
		printf("Led color:  Green \n");
		break;
	case blue:
		ledOff();
		GPIO_PortClear(GPIOB, 1u << LED_B);
		printf("Led color:  Blue \n");
		break;
	case white:
		ledOff();
		GPIO_PortClear(GPIOB, 1u << LED_R);
		GPIO_PortClear(GPIOE, 1u << LED_G);
		GPIO_PortClear(GPIOB, 1u << LED_B);
		printf("Led color:  White \n");
		break;
	case purple:
		ledOff();
		GPIO_PortClear(GPIOB, 1u << LED_R);
		GPIO_PortClear(GPIOB, 1u << LED_B);
		printf("Led color:  Purple \n");
		break;
	case yellow:
		ledOff();
		GPIO_PortClear(GPIOB, 1u << LED_R);
		GPIO_PortClear(GPIOE, 1u << LED_G);
		printf("Led color:  Yellow \n");
		break;
	default:
		ledOff();
		printf("No se encontro el color en la base de datos \n");
		break;
	}
}

