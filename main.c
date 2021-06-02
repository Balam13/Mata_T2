#include <stdio.h>
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"
#include "pin_mux.h"
#define CORE_FREQ 21000000u
#define DELAY 200000u

gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        1,
    };

gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput,
        0,
	};

port_pin_config_t sw ={
		kPORT_PullUp,
};

#define PIN26        26u //led verde
#define PIN22        22u //led rojo
#define PIN21        21u //led azul
#define PIN06        6u  //switch2
#define PIN04        4u  //switch3

void limpiar(void);
void verde (void);
void azul (void);
void morado (void);
void rojo (void);
void amarillo (void);
void blanco(void);



int main(void) {

	int inicio = 1;

	 CLOCK_EnableClock(kCLOCK_PortA);
	 CLOCK_EnableClock(kCLOCK_PortB);
	 CLOCK_EnableClock(kCLOCK_PortC);
	 CLOCK_EnableClock(kCLOCK_PortE);

	 PORT_SetPinMux(PORTB, PIN22, kPORT_MuxAsGpio);
	 PORT_SetPinMux(PORTB, PIN21, kPORT_MuxAsGpio);
	 PORT_SetPinMux(PORTE, PIN26, kPORT_MuxAsGpio);
	 PORT_SetPinMux(PORTC, PIN06, kPORT_MuxAsGpio);
	 PORT_SetPinMux(PORTA, PIN04, kPORT_MuxAsGpio);

	 GPIO_PinInit(GPIOB, PIN22, &led_config);
	 GPIO_PinInit(GPIOB, PIN21, &led_config);
	 GPIO_PinInit(GPIOE, PIN26, &led_config);
	 GPIO_PinInit(GPIOC, PIN06, &sw_config);
	 GPIO_PinInit(GPIOA, PIN04, &sw_config);


	 while(1) {

		limpiar();

		switch(inicio){
		case 1:  //Verde
				verde();
				SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

				if(!GPIO_PinRead(GPIOC, PIN06) && !GPIO_PinRead(GPIOA, PIN04))
				{
					blanco();
					break;
				}
				//presionar switch 3
				if (!GPIO_PinRead(GPIOA, PIN04))
				{
					//GPIO_PortSet(GPIOE, 1u << PIN26);
					inicio = 2; //azul
					break;
				}
				//presionar switch 2
				if (!GPIO_PinRead(GPIOC, PIN06))
				{
					inicio = 5;   //amarillo();
					break;
				}

				break;


		case 2:  //Azul
				azul();
				SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

				if(!GPIO_PinRead(GPIOC, PIN06) && !GPIO_PinRead(GPIOA, PIN04))
				{
					blanco();
					break;
				}
				//presionar switch 3
				if (!GPIO_PinRead(GPIOA, PIN04))
				{ inicio = 3; //morado()
				break;
				}
				//presionar switch 2
				if (!GPIO_PinRead(GPIOC, PIN06)){
					//GPIO_PortSet(GPIOB, 1u << PIN21);
					inicio = 1; //verde();
					break;
				}

				break;


		case 3:  //morado
				morado();
				SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

				if(!GPIO_PinRead(GPIOC, PIN06) && !GPIO_PinRead(GPIOA, PIN04))
				{
					blanco();
					break;
				}
				if(!GPIO_PinRead(GPIOA, PIN04)) //presionar switch 3
				{
					//GPIO_PortSet(GPIOB, 1u << PIN21);
					inicio = 4;   //rojo();
					break;
				}

				if (!GPIO_PinRead(GPIOC, PIN06)) //presionar switch 2
				{
					//GPIO_PortSet(GPIOB, 1u << PIN22);
					inicio = 2; //azul();
					break;
				}

				break;

		case 4:   //rojo
				rojo();
				SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

				if(!GPIO_PinRead(GPIOC, PIN06) && !GPIO_PinRead(GPIOA, PIN04))
				{
						blanco();
						break;
			   	}
				if(!GPIO_PinRead(GPIOA, PIN04)) //presionar switch 3
					{
						inicio = 5;  //amarillo();
						break;
					}

				if (!GPIO_PinRead(GPIOC, PIN06)) //presionar switch 2
					{
						inicio = 3;  //morado();
						break;
					}

				break;

		case 5: //amarillo
				amarillo();
				SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

				if(!GPIO_PinRead(GPIOC, PIN06) && !GPIO_PinRead(GPIOA, PIN04))
				{
				blanco();
				break;
				}
				if (!GPIO_PinRead(GPIOA, PIN04)) //presionar switch 3
					{
						//GPIO_PortSet(GPIOB, 1u << PIN22);
						inicio = 1; //verde();
						break;
					}

				if (!GPIO_PinRead(GPIOC, PIN06)) //presionar switch 2
					{
						//GPIO_PortSet(GPIOE, 1u << PIN26);
						inicio = 4;  //rojo();
						break;
					}

				break;

		}



    }


    return 0 ;
}

void limpiar(void){
	GPIO_PortSet(GPIOB, 1u << PIN21);
	GPIO_PortSet(GPIOE, 1u << PIN26);
	GPIO_PortSet(GPIOB, 1u << PIN22);
}
//
void azul (void){
	GPIO_PortClear(GPIOB, 1u << PIN21);
}
//
void morado (void){
	GPIO_PortClear(GPIOB, 1u << PIN22);
	GPIO_PortClear(GPIOB, 1u << PIN21);
}
//
void rojo (void){
	GPIO_PortClear(GPIOB, 1u << PIN22);
}

//
void amarillo (void){
	GPIO_PortClear(GPIOB, 1u << PIN22);
	GPIO_PortClear(GPIOE, 1u << PIN26);
}
//
void verde (void){
	GPIO_PortClear(GPIOE, 1u << PIN26);
}
//

void blanco(void){
	GPIO_PortClear(GPIOB, 1u << PIN22);
	GPIO_PortClear(GPIOE, 1u << PIN26);
	GPIO_PortClear(GPIOB, 1u << PIN21);
	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
}
