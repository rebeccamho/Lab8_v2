// filename ******** main.c ************** 
// Lab 5 Spring 2017
// Matt Owens & Rebecca Ho
// 2/21/17

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
  Program 7.5, example 7.6

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// oscilloscope or LED connected to PF3-1 for period measurement
// When using the color wheel, the blue LED on PF2 is on for four
// consecutive interrupts then off for four consecutive interrupts.
// Blue is off for: dark, red, yellow, green
// Blue is on for: light blue, blue, purple, white
// Therefore, the frequency of the pulse measured on PF2 is 1/8 of
// the frequency of the Timer0A interrupts.

#include "..\ValvanoWareTM4C123\ValvanoWareTM4C123\inc\tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include "PLL.h"
#include "Timer.h"
#include "DAC.h"
#include "Switch.h"
#include "SysTick.h"
#include "Music.h"
#include "Sensors.h"
#include "ST7735.h"


#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
#define LEDS      (*((volatile uint32_t *)0x40025038))


	
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode


// if desired interrupt frequency is f, Timer0A_Init parameter is busfrequency/f
#define F16HZ (50000000/16)
#define F20KHZ (50000000/20000)
#define F10KHZ (50000000/10000)
#define F1HZ 50000000
#define F100mHZ 50000000*10
//debug code
int main(void){ 
  PLL_Init(Bus50MHz);              // bus clock at 50 MHz
	Output_Init();
	PortF_Init();
	ADC_Init12();
  Timer0A_Init(F100mHZ);  // initialize timer0A (16 Hz)
	Timer1A_Init(F1HZ);  // initialize timer1A (16 Hz)
	SysTick_Init();
	DAC_Init(0x1000);  // initialize with command: Vout = Vref
	SetCheckFrequency(6); // 6 sensor checks being done per minute
  EnableInterrupts();
	
  while(1){
		CheckMoisture();
		CheckLight();
    WaitForInterrupt();
		//if(becomeDry)
			//play sunshine
		//else if(becomeMoist)
			//play other song (TBD)
  }
}
