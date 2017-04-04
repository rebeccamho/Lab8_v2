// filename ******** Switch.c ************** 
// Lab 5 Spring 2017
// Matt Owens & Rebecca Ho
// 2/21/17

#include <stdint.h>
#include <stdbool.h>
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/inc/tm4c123gh6pm.h"
#include "SysTick.h"
#include "Music.h"

#define PF1             (*((volatile uint32_t *)0x40025008)) // yellow LED
#define PF2             (*((volatile uint32_t *)0x40025010)) // green LED
#define PF3							(*((volatile uint32_t *)0x40025020))
#define PF4   					(*((volatile uint32_t *)0x40025040))
	
// PF4-1 output
void PortF_Init() {
	SYSCTL_RCGCGPIO_R |= 0x20;            // activate port F clock
	while((SYSCTL_PRGPIO_R&0x20)==0){}; 	// allow time for clock to start

	GPIO_PORTF_DIR_R |= 0x1E;             // make PF2, PF1 out (built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x1E;          // disable alt funct on PF4-1
	GPIO_PORTF_PCTL_R &= ~0x1E;						// configure PF4-1 as GPIO
  GPIO_PORTF_DEN_R |= 0x1E;             // enable digital I/O on PF4-1
                                        // configure PF2 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFF0000F)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;               // disable analog functionality on PF


	PF1 = 0;	// turn off LED
	PF2 = 0;	
	PF3 = 0;
	PF4 = 0;
}

void LED_GreenOn() {
	PF2 |= 0x04;
}

void LED_GreenOff() {
	PF2 &= ~0x04;
}

void LED_YellowOn() {
	PF1 |= 0x02;
}

void LED_YellowOff() {
	PF1 &= ~0x02; // = 0?
}


