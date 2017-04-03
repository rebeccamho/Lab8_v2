// filename ******** MoistureSensor.h ************** 
// Lab 8 Spring 2017
// Matt Owens & Rebecca Ho
// 3/29/17

// Initializes ADC8 and ADC9 sampling
// 125k max sampling
// SS2 triggering event: software trigger, busy-wait sampling
// SS2 1st sample source: Ain9 (PE4)
// SS2 2nd sample source: Ain8 (PE5)
// SS2 interrupts: enabled after 2nd sample but not promoted to controller
void ADC_Init12(void);

//------------ADC_In89------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: two 12-bit result of ADC conversions
// Samples ADC8 and ADC9 
// 125k max sampling
// software trigger, busy-wait sampling
// data returned by reference
// data[0] is ADC8 (PE5) 0 to 4095
// data[1] is ADC9 (PE4) 0 to 4095
void ADC_In12(uint32_t data[2]);

void InitMoistureSensor(void);

void CalibrateMoistureSensor(void);

void ReportMoistureStatus(void);