// filename ******** MoistureSensor.c ************** 
// Lab 8 Spring 2017
// Matt Owens & Rebecca Ho
// 3/29/17

#include <stdint.h>
#include <stdbool.h>
#include "../ValvanoWareTM4C123/ValvanoWareTM4C123/inc/tm4c123gh6pm.h"
#include "ST7735.h"


#define PE0       (*((volatile uint32_t *)0x40024004))

// Initializes ADC2 (PE1,soil) and ADC1 (PE2,light) sampling
// Initializes PE0 as output
// 125k max sampling
// SS2 triggering event: software trigger, busy-wait sampling
// SS2 1st sample source: Ain2 (PE1)
// SS2 2nd sample source: Ain1 (PE2)
// SS2 interrupts: enabled after 2nd sample but not promoted to controller
void ADC_Init12(void){ 
  volatile uint32_t delay;                         
//  SYSCTL_RCGC0_R |= 0x00010000; // 1) activate ADC0 (legacy code)
  SYSCTL_RCGCADC_R |= 0x00000001; // 1) activate ADC0
  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4; // 1) activate clock for Port E
  delay = SYSCTL_RCGCGPIO_R;      // 2) allow time for clock to stabilize
  delay = SYSCTL_RCGCGPIO_R;
  GPIO_PORTE_DIR_R &= ~0x06;      // 3) make PE1 PE2 input
	GPIO_PORTE_DIR_R |= 0x01;				// 		make PE0 output
  GPIO_PORTE_AFSEL_R |= 0x06;     // 4) enable alternate function on PE1 PE2
	GPIO_PORTE_AFSEL_R &= ~0x01;		//		disable alternate function onf PE0
  GPIO_PORTE_DEN_R &= ~0x06;      // 5) disable digital I/O on PE1 PE2
	GPIO_PORTE_DEN_R |= 0x01;				//		enable digital I/O on PE0
                                  // 5a) configure PE4 as ?? (skip this line because PCTL is for digital only)
  GPIO_PORTE_PCTL_R = GPIO_PORTE_PCTL_R&0xFFFFFFF0;
  GPIO_PORTE_AMSEL_R |= 0x06;     // 6) enable analog functionality on PE1 PE2
	GPIO_PORTE_AMSEL_R &= ~0x01;		//		disable analog functionality on PE0
  ADC0_PC_R &= ~0xF;              // 8) clear max sample rate field
  ADC0_PC_R |= 0x1;               //    configure for 125K samples/sec
  ADC0_SSPRI_R = 0x3210;          // 9) Sequencer 3 is lowest priority
  ADC0_ACTSS_R &= ~0x0004;        // 10) disable sample sequencer 2
  ADC0_EMUX_R &= ~0x0F00;         // 11) seq2 is software trigger
  ADC0_SSMUX2_R = 0x0012;         // 12) set channels for SS2
  ADC0_SSCTL2_R = 0x0060;         // 13) no TS0 D0 IE0 END0 TS1 D1, yes IE1 END1
  ADC0_IM_R &= ~0x0004;           // 14) disable SS2 interrupts
  ADC0_ACTSS_R |= 0x0004;         // 15) enable sample sequencer 2
}

//------------ADC_In12------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: two 12-bit result of ADC conversions
// Samples ADC8 and ADC9 
// 125k max sampling
// software trigger, busy-wait sampling
// data returned by reference
// data[0] is ADC8 (PE5) 0 to 4095
// data[1] is ADC9 (PE4) 0 to 4095
void ADC_In12(uint32_t data[2]){ 
  ADC0_PSSI_R = 0x0004;            // 1) initiate SS2
  while((ADC0_RIS_R&0x04)==0){};   // 2) wait for conversion done
  data[1] = ADC0_SSFIFO2_R&0xFFF;  // 3A) read first result (PE1)
  data[0] = ADC0_SSFIFO2_R&0xFFF;  // 3B) read second result (PE2)
  ADC0_ISC_R = 0x0004;             // 4) acknowledge completion
}

void CheckSensors(){
	PE0 |= 0x01; // turn on soil sensor
	uint32_t data[2];
	ADC_In12(data);
	uint32_t light = data[0];
	uint32_t soil = data[1];
	PE0 &= ~0x01; // turn off soil sensor
	
	ST7735_FillScreen(ST7735_BLACK); // added for testing
	ST7735_DrawString(0, 0, "Soil moisture:", ST7735_YELLOW);
	ST7735_SetCursor(0,1); // added for testing
	ST7735_OutUDec(soil); // added for testing
	ST7735_DrawString(0, 2, "Light:", ST7735_YELLOW);
	ST7735_SetCursor(0,3); // added for testing
	ST7735_OutUDec(light); // added for testing
	//Output moisture to server
	//If threshold crossed, play song
}
