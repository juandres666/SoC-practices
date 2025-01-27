/*
 * mtr_code.c
 *
 *  Created on: 3 d�c. 2018
 *      Author: jvalverd
 */


/*
 * adc_scr.c
 *
 *  Created on: 13 nov. 2018
 *      Author: jvalverd
 */

#include "xparameters.h"
#include "xgpio.h"
#include "xspi.h"

//#include <xtmrctr.h>

#include "xtmrctr_l.h"
#include "xtmrctr.h"

//#include "xintc.h"
//#include <stdio.h>
//#include <stdlib.h>
#include <string.h>


int main()
{
	XSpi mySPI;
	//Xspi_mIntrGlobalDisable(&mySPI);
	XSpi_Initialize(&mySPI, XPAR_XPS_SPI_0_DEVICE_ID); /* Initialize the SPI and clear	the SPI bus */
	XSpi_SetOptions(&mySPI, XSP_MASTER_OPTION);
	XSpi_SetSlaveSelect(&mySPI, 1);
	XSpi_Start(&mySPI);


	/*Timer*/	/*Timer 0 -pwm-*/
	XTmrCtr TimerCounter;
	//XTmrCtr *InstanciaTimer=&TimerCounter;

	/* #define XPAR_XPS_TIMER_0_DEVICE_ID 0
	#define XPAR_XPS_TIMER_0_BASEADDR 0x83C00000
	#define XPAR_XPS_TIMER_0_HIGHADDR 0x83C0FFFF*/

	XTmrCtr_Initialize(&TimerCounter, XPAR_XPS_TIMER_0_DEVICE_ID);//Inicializa el timer en modo pwm
	XTmrCtr_mSetLoadReg(&TimerCounter,0,50000); //para 1khz
	XTmrCtr_mWriteReg(&TimerCounter,0,XTC_TCSR_OFFSET,0x00000204);

	XGpio led, sw;  // defined gpio variables
	XGpio_Initialize (&led, XPAR_GPIO_0_DEVICE_ID);
	XGpio_SetDataDirection (&led,1,0); // set display as output ports
	XGpio_Initialize (&sw,XPAR_GPIO_1_DEVICE_ID);
	XGpio_SetDataDirection (&sw,1,1); // set digit as input ports



	unsigned int adc[2] = {0x00, 0x00};
	unsigned int gain_a, gain_b;

	Xuint8 data = 0;

	while(1)
	{


//		PWM_PERIOD = (TLR0 + 2) x PLB_CLOCK_PERIOD
//		PWM_HIGH_TIME = (TLR1 + 2) x PLB_CLOCK_PERIOD


		data=XGpio_DiscreteRead(&sw, 1);
		XGpio_DiscreteWrite(&led, 1, data);

	}

}
