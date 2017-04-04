// filename ******** Switch.h ************** 
// Lab 5 Spring 2017
// Matt Owens & Rebecca Ho
// 2/21/17

//------------PortF_Init------------
// Initialization of PortF, making PF1, and PF2 outputs
// and enabling PF4 to be used as a switch
// Input: none
// Output: none
void PortF_Init(void);

//------------LED_GreenOn------------
// Make PF2 high, turning on green LED.
// Input: none
// Output: none
void LED_GreenOn(void);

//------------LED_GreenOff------------
// Make PF2 low, turning off green LED.
// Input: none
// Output: none
void LED_GreenOff(void);

//------------LED_YellowOn------------
// Make PF1 high, turning on yellow LED.
// Input: none
// Output: none
void LED_YellowOn(void);

//------------LED_YellowOff------------
// Make PF1 low, turning off yellow LED.
// Input: none
// Output: none
void LED_YellowOff(void);
