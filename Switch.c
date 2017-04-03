// filename ******** Switch.c ************** 
// Lab 5 Spring 2017
// Matt Owens & Rebecca Ho
// 2/21/17

#include <stdint.h>
#include <stdbool.h>
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/inc/tm4c123gh6pm.h"
#include "SysTick.h"
#include "Music.h"

#define PF1             (*((volatile uint32_t *)0x40025008))
#define PF2             (*((volatile uint32_t *)0x40025010))
#define PF3							(*((volatile uint32_t *)0x40025020))
#define PF4   					(*((volatile uint32_t *)0x40025040))
	
bool PlayPressed = false;
bool RewindPressed = false;
bool ModePressed = false;

// PF4-1 output
void PortF_Init() {
	SYSCTL_RCGCGPIO_R |= 0x20;            // activate port F clock
	while((SYSCTL_PRGPIO_R&0x20)==0){}; 	// allow time for clock to start

	GPIO_PORTF_DIR_R |= 0x1E;             // make PF2, PF1 out (built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x1E;          // disable alt funct on PF4-1
	GPIO_PORTF_PCTL_R &= ~0x1E;						// configure PF4-1 as GPIO
  GPIO_PORTF_DEN_R |= 0x1E;             // enable digital I/O on PF4-1
                                        // configure PF2 as GPIO
  //GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF00F)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;               // disable analog functionality on PF
	//GPIO_PORTF_PUR_R |= 0x10;         // 5) pullup for PF4
	
	//GPIO_PORTF_IS_R &= ~0x10;			// PF4 is edge-sensitive
	//GPIO_PORTF_IBE_R &= ~0x10;		// PF4 is not both edges
	//GPIO_PORTF_IEV_R |= 0x10;			// PF4 rising edge event
	//GPIO_PORTF_ICR_R = 0x10;			// clear flag5-4
	//GPIO_PORTF_IM_R |= 0x10;			// arm interrupts on PF4
	//GPIO_PORTF_PCTL_R &= ~0x000F0000; // configure PF4 as GPIO

	//GPIO_PORTF_IM_R |= 0x10;      // (f) arm interrupt on PF4 *** No IME bit as mentioned in Book ***
  //NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // priority 5
  //NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC

	PF1 = 0;	// turn off LED
	PF2 = 0;	
	PF3 = 0;
	PF4 = 0;
}
//pf4 for speaker, switches on pf0-3


void GPIOPortF_Handler(void){		// PF4, PLAY/PAUSE switch
  GPIO_PORTF_ICR_R = 0x10;      // acknowledge flag4
	SysTick_Wait10ms(10);
	if(GPIO_PORTF_DATA_R&0x10) {
		PlayPressed = true;
	}
}

void ResetSwitches() {
	PlayPressed = false;
	RewindPressed = false;
	ModePressed = false;
}

void CheckSwitches() {
	if(PlayPressed) {
		if(GetPlayState() == false) { // music not currently playing
			PlaySong();
		} else {
			Pause();
		}
		ResetSwitches();
	} else if(RewindPressed) {
			Rewind(GetPlayState());
			ResetSwitches();
	} else if(ModePressed) {
			ChangeTempo();
			ResetSwitches();
	}

}

